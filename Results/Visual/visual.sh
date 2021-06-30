#!/bin/bash

echo "\"Visualization\" Started..." 

for d in ../* ; do (

        echo "$d"
	
	

	
	sort  -t ',' -k1n,1 -k2n,2 --output="$d"  "$d"
	

	
	



)
done

