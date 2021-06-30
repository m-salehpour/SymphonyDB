#!/bin/bash




#############################################################
#                      running DMSs                         #
#                                                           #
#                                                           #
#                                                           #
#############################################################




	#RDF-3X does not need to be started first

	#MongoDB
	sudo service mongod start
	
	#Virtuoso
	cd ./virf/bin
        ./virtuoso-t -fd -c ../var/lib/virtuoso/db/virtuoso.ini &

        sleep 5
        echo "Waiting to launch Virtuoso (isql) on 1111..."

        while ! nc -z localhost 1111; do
            sleep 1
        done
        echo "Virtuoso (isql) launch on 1111..."
	cd ../../

	#Blazegraph
	cd ./Blazegraph
        (java -server -Xmx4g -jar blazegraph.jar &) & bpid=$!

        sleep 5
        echo "Waiting to launch Blazegraph on 9999..."
        counter=1;
        while ! nc -z localhost 9999; do
            sleep 1
        done
        echo "Blazegraph launch on 9999..."
        cd ..

#############################################################
#                     running queries                       #
#                                                           #
#                                                           #
#                                                           #
#############################################################
	cd ./queries
	
	echo "">../mongotmptime.txt
	echo "">../rdftmptime.txt
	echo "">../blazegraphtmptime.txt
	echo "">../virtuosotmptime.txt
	while read -r kg_name sparql_query
	do
	
		q_type=`../multidb.out <(echo $sparql_query) -t`
		#echo $kg_name
		echo "$sparql_query" > ./tmpQ
		echo 3 > /proc/sys/vm/drop_caches ; swapoff -a ; printf '\n%s\n' 'Ram-cache and Swap Cleared'

		
		
		case $q_type in

		ss)
			#echo "rdf $linenum">>../tmptime.txt
			(cd ../rdf3x-0.3.7/bin/ && ts=$(date +%s%N) && ./rdf3xquery ../$kg_name ../../queries/tmpQ   && tt=$((($(date +%s%N) - $ts)/1000000)) && echo “RDF-3X Time taken For $kg_name: $tt milliseconds” >>../../rdftmptime.txt ) 
			mql=`../multidb.out <(echo $sparql_query) ./`
			sed -i '1s/^/use '$kg_name'\n/' ./MQL.js
			#echo "mongo $linenum">>../tmptime.txt
			(ts=$(date +%s%N) && mongo < ./MQL.js && tt=$((($(date +%s%N) - $ts)/1000000)) && echo “MongoDB Time taken For $kg_name : $tt milliseconds” >>../mongotmptime.txt  )


		
		#echo "**********"
		#echo "rdf:  $(cat $tmprtt) "
		#echo "mongo:  $(cat $tmpmtt) "
		#echo $mql
		;;

		so)
			#echo "Subject-to-obj"

			(ts=$(date +%s%N) ; curl -X POST http://127.0.0.1:9999/blazegraph/namespace/$kg_name/sparql --data-urlencode 'query='"$sparql_query"''  -H 'Accept:application/rdf+xml'; tt=$((($(date +%s%N) - $ts)/1000000)) ; echo “Blazegraph Time taken For $kg_name: $tt milliseconds”>>../blazegraphtmptime.txt) 


		;;

		t3)
			
			(cd ../virf/bin ; ts=$(date +%s%N) ; ./isql 1111 dba dba exec="sparql $sparql_query ;" ; tt=$((($(date +%s%N) - $ts)/1000000)) ; echo “Virtuoso Time taken For $kg_name: $tt milliseconds”>>../../virtuosotmptime.txt) 
		;;
		*)
			echo "error"
		esac

	
	    #$kg_name
		






	done < "queries.txt"













	
#####u#######################################################
#                      terminating DMSs                     #
#                                                           #
#                                                           #
#                                                           #
#############################################################
kill -9 $bpid
	

cd ../virf/bin ; ./isql 1111 dba dba exec="checkpoint;" ; ./isql 1111 dba dba exec="shutdown;" ; cd ../../




