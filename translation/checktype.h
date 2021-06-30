#ifndef CHECKTYPE_H
#define CHECKTYPE_H


#include <set>


/*
// to sort triple patterns
	bool SortBySubject(const triple_pattern & p1, const triple_pattern & p2)
	{
	    return p1.subject < p2.subject || (boost::iequals( p1.subject,p2.subject) && p1.predicate < p2.predicate) || (boost::iequals( p1.subject,p2.subject) && boost::iequals( p1.predicate,p2.predicate) && p1.object < p2.object) ;
	}
*/




enum QueryTypes {SS, SO, T3, OPT};
	
QueryTypes get_sparql_query_type(std::vector<triple_pattern> all_trple_patterns){

	QueryTypes detected_query_type;
	
	//sort(all_trple_patterns.begin(), all_trple_patterns.end(), SortBySubject);

		//We assume that each query has more than one TP
		
/*
 **********************************************************************************************************
 */
		
		
		bool ss_type = true;
		for (size_t i=1; i < all_trple_patterns.size();i++)
		{
			//cout << "\nSubject " << i-1 << " : " << all_trple_patterns[i-1].subject << "    Subject " << i << " : " << all_trple_patterns[i-1].subject << "\n";
			if (all_trple_patterns[i-1].subject != all_trple_patterns[i].subject)
				ss_type = false;			     
		}// for loop





/*
 **********************************************************************************************************
 */


		bool t3_type = false;
		std::string tmp_obj;
		std::string tmp_sub;

		set<string> subject_set,object_set;
		
		bool so_type = false;
		int so_match_counter = 0;		
		if (!ss_type)
		{

			for (size_t j=0; j < all_trple_patterns.size()-1;j++)
			{
				tmp_obj = all_trple_patterns[j].object;
				tmp_sub = all_trple_patterns[j].subject;
				
										
				//if (tmp_obj.find('?') != std::string::npos || tmp_sub.find('?') != std::string::npos)
				//{	
					for (size_t i = (j + 1); i < all_trple_patterns.size(); i++)
					{
						//cout << "\nSubject " << i-1 << " : " << all_trple_patterns[i-1].subject << "    Subject " << i << " : " << all_trple_patterns[i-1].subject << "\n";
						if (all_trple_patterns[i].subject == tmp_obj || all_trple_patterns[i].object == tmp_sub )
						{

							so_match_counter++;
							//so_type = true;			     
							//break;
						}
						
						if ( ( all_trple_patterns[i].subject == tmp_sub ) &&
   					           ( subject_set.find(tmp_sub) == subject_set.end() )
						   )
							   	subject_set.insert(tmp_sub);
						
						
						
					}// for loop
				//}
			}
			
		//cout << "\nSize: " << all_trple_patterns.size() << "   counter:   " << so_match_counter << "\n";			
		if (  subject_set.size() == 0  &&  (so_match_counter+1) == all_trple_patterns.size() ) so_type = true;			  
			
			
			
		}






/*

 **********************************************************************************************************







		set<string> subject_set,object_set;
					
		if (!ss_type && !so_type)
		{

			for (size_t j = 0; j < all_trple_patterns.size();j++)
			{
				tmp_obj = all_trple_patterns[j].object;
				tmp_sub = all_trple_patterns[j].subject;
				
					for (size_t i = 0; i < all_trple_patterns.size(); i++)
					{
						if ( i != j)
						{
							if ( ( all_trple_patterns[i].subject == tmp_sub ) &&
							     ( subject_set.find(tmp_sub) == subject_set.end() )
							   )
							   	subject_set.insert(tmp_sub);
							   	
							if ( ( all_trple_patterns[i].subject == tmp_obj ) &&
							     ( object_set.find(tmp_obj) == object_set.end() )
							   )
							   	object_set.insert(tmp_obj);
						}
						
					}// for loop
			}
			
		
		}

		//cout << "\nSize of SS: " << subject_set.size() << "   Size of So:   " << object_set.size() << "\n";			
		if ( ( subject_set.size() > 0 ) && ( object_set.size() > 0 ) ) t3_type = true;			  



		if (!ss_type)	t3_type = true;




 **********************************************************************************************************
 */

		if (!ss_type && !so_type) t3_type = true;







	
		if (ss_type) detected_query_type = SS; //^enum QueryTypes^	
		if (so_type) detected_query_type = SO; //^enum QueryTypes^
		if (t3_type) detected_query_type = T3; //^enum QueryTypes^



		//cout << "TYPE:  " << detected_query_type << "\n";

		//detected_query_type = T3;	//It can be changed
	
	

return detected_query_type;

}


#endif
