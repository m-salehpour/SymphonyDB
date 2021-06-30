#ifndef TOSSMQL_H
#define TOSSMQL_H



#include "../sse/tosse.h"
#include "extractfromtps.h"
#include "filterdecouple.h"
#include <regex>
#include <sstream>


using namespace std;



template<typename T>
bool is_number(T x){
    std::string s;
    std::regex e ("^-?\\d*\\.?\\d+");
    std::stringstream ss; 
    ss << x;
    ss >> s;
    if (std::regex_match (s,e)) return true;
    else return false;}

std::string sparql_to_ss_mql_translate(string sparql_query, std::vector<triple_pattern> get_triple_patterns_structs_local){

	/*
	std::string example_query = " SELECT ?v0 ?v2 ?v3 WHERE { 	?v0 <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://db.uwaterloo.ca/~galuc/wsdbm/ProductCategory9> . 	?v0 <http://schema.org/description> ?v2 . 	?v0 <http://schema.org/keywords> ?v3 . 	?v0 <http://schema.org/language> <http://db.uwaterloo.ca/~galuc/wsdbm/Language0> . }";
	*/

	string mql_query  = sparql_query;
	string mql_projection_part = ",{ \"$project\": { ";
	
	std::map<std::string, std::tuple< std::string, std::string, std::string >> filter_map_tmp;
	std::map<std::string, std::tuple< std::string, std::string, std::string >>::iterator filter_it;
	std::map<std::string, std::tuple< std::string, std::string, std::string >>::iterator tmp_filter_it;

	std::map<std::string, std::tuple< std::string, std::string >> predicate_map_tmp;
	std::map<std::string, std::tuple< std::string, std::string >>::iterator predicate_map_it;
	
	std::map<std::string, std::vector<std::string>> map_predicate_multivalue;

	
	
	std::string sub, pre, obj;
	char homepage_indicator_char = 'N';
	
	tosse tosse_obj;
	auto get_namespace = tosse_obj.get_name_spaces(sparql_query);
	auto get_projection_variables_local = tosse_obj.get_projection_variables(sparql_query);
	//auto get_triple_patterns_structs_local = tosse_obj.get_triple_patterns_structs(sparql_query);
	vector<string> get_filter_patterns_local = tosse_obj.get_sparql_query_filters(sparql_query); // filters
	predicate_map_tmp = tosse_obj.get_predicate_map(sparql_query,get_triple_patterns_structs_local); // when object variables are repeated, no direct access is possible!
	std::map < int, std::pair<int, std::string> > map_modifiers_local = tosse_obj.get_sparql_query_modifiers(sparql_query);
	

	//cout << "\n CHECK:  SIZE:    " << get_filter_patterns_local.size();
	
	std::string str_filtering_part_of_the_query = "";
		
		
		
	const std::string
        notOperator        = "op_not" ,
        andOperator        = "op_and",
        orOperator         = "op_or",
        xorOperator        = "op_xor" ,
        equalOperator      = "op_eq",
        unequalOperator    = "op_ne",
        sumOperator        = "$add" ,
        differenceOperator = "$subtract" ,
        factorOperator     = "$multiply" ,
        divisionOperator   = "$divide" ,
        gteOperator        = "op_gte",
        gtOperator         = "op_gt" ,
        lteOperator        = "op_lte",
        ltOperator         = "op_lt" ;

			
		for (size_t j=0; j < get_triple_patterns_structs_local.size();j++)
		{


			
			
			// comment the following lines to not shorten URIs!			
			//------------------------------------------------
			homepage_indicator_char = 'N';
			//sub = get_subject_without_uri(get_triple_patterns_structs_local[i].subject);
			string tmp_cmp_pre = get_predicate_without_uri(get_triple_patterns_structs_local[j].predicate);
			if ( pre == "\"page\"")
				homepage_indicator_char = 'Y';
			string tmp_cmp_obj = get_object_without_uri(get_triple_patterns_structs_local[j].object, homepage_indicator_char);
			//------------------------------------------------
			
			bool flag_dup = false;
			std::map<std::string, std::vector<std::string>>::iterator tmp_pre_it = map_predicate_multivalue.find(tmp_cmp_pre);

			if (tmp_pre_it == map_predicate_multivalue.end())
			{
				for (size_t i=0; i < get_triple_patterns_structs_local.size();i++)
				{


					// comment the following lines to not shorten URIs!			
					//------------------------------------------------
					homepage_indicator_char = 'N';
					//sub = get_subject_without_uri(get_triple_patterns_structs_local[i].subject);
					pre = get_predicate_without_uri(get_triple_patterns_structs_local[i].predicate);
					if ( pre == "\"page\"")
						homepage_indicator_char = 'Y';
					obj = get_object_without_uri(get_triple_patterns_structs_local[i].object, homepage_indicator_char);
					//------------------------------------------------
				

				
				
				
					if (  i != j && tmp_cmp_pre == pre &&  obj.find('?') == string::npos)
					{
						if (!flag_dup)
						{						
							map_predicate_multivalue[pre].push_back(tmp_cmp_obj);
							flag_dup = true;
						}
						map_predicate_multivalue[pre].push_back(obj);
						//cout << "\n\n BINGO!" << pre << "   " << obj << endl;
					}
				}
			}
			
			
			
		}
		
	std::string str_multi_valued_pre= "";
	
	
	
	
	
	
	std::map<std::string, std::vector<std::string>>::iterator it_map = map_predicate_multivalue.begin();

	while (it_map != map_predicate_multivalue.end())
	{
	    str_multi_valued_pre += ","+ it_map->first + " :{ $all:[";
	    vector<string> vIt = it_map->second;
	
	    for (size_t i=0; i< vIt.size()-1; i++)
	    	str_multi_valued_pre += "\""+vIt[i] + "\", ";

	    	str_multi_valued_pre += "\""+vIt.back()+"\"";
        
       	    str_multi_valued_pre += "]} ";
	    it_map++;
	}

	
	//cout << "\n CHECK:  SIZE:    " << get_filter_patterns_local.size();
	int int_tmp_key = 0;

	for (size_t i = 0; i < get_filter_patterns_local.size(); i++)
	{

		/* 
		filter_it = filter_map_tmp.begin();
		while (filter_it != filter_map_tmp.end())
		{
			filter_map_tmp.erase (filter_it);
			filter_it++;
		}
		filter_map_tmp.clear();
		*/
		
		
		
		filter_map_tmp = parse_filter_to_AST_map(get_filter_patterns_local[i]);
		filter_it = filter_map_tmp.begin();
		tmp_filter_it = filter_map_tmp.begin();

		while (filter_it != filter_map_tmp.end())
		{

			std::string word = filter_it->first;
			std::string opera = std::get< 1 > ( filter_it->second ).replace(0,1,"");
			
			
				string op1=std::get< 0 >( filter_it->second),
				       op2=std::get< 2 >( filter_it->second);


			
			if (opera != notOperator)
			{

				opera = "$" + std::get< 1 > ( filter_it->second ).substr(
				std::get< 1 > ( filter_it->second ).find('_')+1,std::get< 1 > ( filter_it->second ).length());
	
				
				predicate_map_it = predicate_map_tmp.begin();
				while (predicate_map_it != predicate_map_tmp.end())
				{
		

 
 					
 					
 					if (std::get< 1 >( predicate_map_it->second ) == std::get< 0 >( filter_it->second) )
 						op1 =  std::get< 0 >( predicate_map_it->second );
 						
 					if (std::get< 1 >( predicate_map_it->second ) == std::get< 2 >( filter_it->second) )
 						op2 = std::get< 0 >( predicate_map_it->second );


					predicate_map_it++;
			
			
				}//while iterator
		

				if (op1.find('%') == std::string::npos && op1.substr(0,4) != "key_" && !is_number(op1))
				{
					op1.replace(0,1,"");
					op1.pop_back();
					op1 = "$" + op1;
				}
					
				if (op2.find('%') == std::string::npos && op2.substr(0,4) != "key_" && !is_number(op2))
				{
					op2.replace(0,1,"");
					op2.pop_back();
					op2 = "$" + op2;
				}
				
				
				str_filtering_part_of_the_query +=
 				",{ \"$addFields\": { \""+ word +"\" :{ \""+ opera+"\":[ \"" +
 				 op1 +"\", \"" +  op2 +"\" ] }}}" ;

				tmp_filter_it = filter_it;
				tmp_filter_it++;

				if (  tmp_filter_it != filter_map_tmp.end())
				{
				
					if (std::get< 1 > ( tmp_filter_it->second).substr(1,std::get< 1 > ( tmp_filter_it->second).length()) != notOperator &&
					    opera != sumOperator && opera != differenceOperator && opera != factorOperator && opera != divisionOperator)
					{
						str_filtering_part_of_the_query +=
 						",{\"$match\": { \""+ word +"\" : true   }  }  " ;
 					}
 					else if (std::get< 1 > ( tmp_filter_it->second).substr(1,std::get< 1 > ( tmp_filter_it->second).length()) == notOperator)
 				 	{			
						
						str_filtering_part_of_the_query +=
 						",{\"$match\": { \""+ word +"\" : false   }  }, {\"$addFields\": {  \""+tmp_filter_it->first+"\" : \"$"+ word +"\"   }  }  " ;
 						
						filter_it++;
 					}
 				
 				
 				}
				
				if (  tmp_filter_it == filter_map_tmp.end())
				{
					if (opera != sumOperator && opera != differenceOperator && opera != factorOperator && opera != divisionOperator)
					{
						str_filtering_part_of_the_query +=
 						",{\"$match\": { \""+ word +"\" : true   }  }  " ;
 					}
				
				}
 				 
 				 
 				 

				//cout << "\n" << str_filtering_part_of_the_query;
			
			
			}
			
 			/*
			std::cout << word << " :: \n" <<	
			"  0: " << std::get< 0 >( filter_it->second ) <<
			"  1: " << std::get< 1 >( filter_it->second ) <<
			"  2: " << std::get< 2 >( filter_it->second ) << std::endl;
			*/
			
 
			filter_it++;
			
			
		}//while iterator

	}//for_filter


	
 

 

	
	
	
	
	

	
	
	
			mql_query = "db.sub.aggregate([{ \"$match\":{";

			if (get_subject_without_uri(get_triple_patterns_structs_local[0].subject).find('?') == std::string::npos)
				mql_query += " \"_id\" : " + get_subject_without_uri(get_triple_patterns_structs_local[0].subject) + ",";

	
			// comment the following lines to not shorten URIs!			
			//------------------------------------------------
			homepage_indicator_char = 'N';
			string lst_pre = get_predicate_without_uri(get_triple_patterns_structs_local.back().predicate);
			if ( pre == "\"page\"")
				homepage_indicator_char = 'Y';
			string lst_obj = get_object_without_uri(get_triple_patterns_structs_local.back().object, homepage_indicator_char);
			//------------------------------------------------			
									
						

			for (size_t i=0; i < get_triple_patterns_structs_local.size()-1;i++)
			{


				// comment the following lines to not shorten URIs!			
				//------------------------------------------------
				homepage_indicator_char = 'N';
				sub = get_subject_without_uri(get_triple_patterns_structs_local[i].subject);
				pre = get_predicate_without_uri(get_triple_patterns_structs_local[i].predicate);
				if ( pre == "\"page\"")
					homepage_indicator_char = 'Y';
				obj = get_object_without_uri(get_triple_patterns_structs_local[i].object, homepage_indicator_char);
				//------------------------------------------------
				
				//cout << "\n obj: " << obj << "\n";
		
				
				
				auto it_map_find = map_predicate_multivalue.find(pre);

				if (it_map_find == map_predicate_multivalue.end())
				{
					//if (pre.find('?') == std::string::npos)					
					//{			
						if (obj.find('?') != std::string::npos)
							mql_query += pre + " : {$exists: true},";
						else
							mql_query += pre + " :  " + obj + " ,";
				
	
						for(string const& word : get_projection_variables_local )
						{
							if (obj == word && pre.find('?') == std::string::npos)
								mql_projection_part += pre + " : 1 , ";

								
									
							if ((i+1) == (get_triple_patterns_structs_local.size()-1) )
								if (lst_obj == word && lst_pre.find('?') == std::string::npos)
									mql_projection_part += lst_pre + " : 1 , ";
										
						
						}// for loop projection		
				
					//}
				}
			}// for loop triple_pattenrs
			

			auto it_map_find = map_predicate_multivalue.find(lst_pre);
			if (it_map_find == map_predicate_multivalue.end())
			{

				if (lst_pre.find('?') == std::string::npos)					
				{			
				
					if (lst_obj.find('?') != std::string::npos)
						mql_query += lst_pre + " : {$exists: true}";
					else
						mql_query += lst_pre + " :  " + lst_obj + " ";

				}else mql_query.pop_back();		
					
			}
				if (mql_projection_part != ",{")
					mql_projection_part += " \"_id\" : 1 }}";
				else
					mql_projection_part += "}}";
					
					
					
					
//-------------------------------------------------------------------------------------------------
					
			std::string str_sort_part_of_the_query  = "{  $sort: {";
			std::string str_skip_part_of_the_query  = "{  $skip:  ";
			std::string str_limit_part_of_the_query = "{ $limit:  ";
			string tmp_pre;			

		std::map < int, std::pair<int, std::string> >::iterator map_modifiers_it = map_modifiers_local.begin();
		while (map_modifiers_it != map_modifiers_local.end())
		{


	            	switch ( std::get<0>(map_modifiers_it->second) )
			{            	
        		    	case (0):
        		    		std::cout << "ASC: " << std::get<1>(map_modifiers_it->second) << "\n";
					if (str_sort_part_of_the_query.find('1') != string::npos)
						str_sort_part_of_the_query += ",";
					
        				predicate_map_it = predicate_map_tmp.begin();
					while (predicate_map_it != predicate_map_tmp.end())
					{
						if (std::get< 1 >( predicate_map_it-> second ) == std::get<1>(map_modifiers_it->second) )
						{
							tmp_pre = std::get< 0 >( predicate_map_it-> second );
							boost::replace_all(tmp_pre, "\"", "");			
							str_sort_part_of_the_query += "\"" + tmp_pre + "\": 1";
						}
					predicate_map_it++;
					}

        		    		break;
        		    		
        		    	case (1):
        		    		std::cout << "DESC: " << std::get<1>(map_modifiers_it->second) << "\n";

					if (str_sort_part_of_the_query.find('1') != string::npos)
						str_sort_part_of_the_query += ",";
					
        				predicate_map_it = predicate_map_tmp.begin();
					while (predicate_map_it != predicate_map_tmp.end())
					{
						if (std::get< 1 >( predicate_map_it-> second ) == std::get<1>(map_modifiers_it->second) )
						{
							tmp_pre = std::get< 0 >( predicate_map_it-> second );
							boost::replace_all(tmp_pre, "\"", "");			
							str_sort_part_of_the_query += "\"" + tmp_pre + "\": -1";
						}
					predicate_map_it++;
					}

        		    		break;
        		    	case (2):
        		    		std::cout << "OFFSET: " << std::get<1>(map_modifiers_it->second) << "\n";

        		    		str_skip_part_of_the_query += std::get<1>(map_modifiers_it->second) + "}";
        		    		
        		    		
        		    		break;
        		    	case (3):
        		    		std::cout << "LIMIT: " << std::get<1>(map_modifiers_it->second) << "\n";

        		    		str_limit_part_of_the_query += std::get<1>(map_modifiers_it->second) + "}";
        		    		
        		    		break;
        	    	}
            	
            	map_modifiers_it++;
            	}
            		
	str_sort_part_of_the_query += "}";
	
	mql_query += str_multi_valued_pre + "}"+ str_filtering_part_of_the_query+ mql_projection_part;				
	
	if (str_sort_part_of_the_query.find('1') != string::npos)
		mql_query += "," + str_sort_part_of_the_query;
	
	if (str_skip_part_of_the_query.find('}') != string::npos)
		mql_query += "," + str_skip_part_of_the_query;

	if (str_limit_part_of_the_query.find('}') != string::npos)
		mql_query += "," + str_limit_part_of_the_query;
	
					
				
					
					
					
					
					
//-----------------------------------------------------------------------------------------------------------------------------				
					
					
					
					
	mql_query += "])";				
				
	
	
	
	return mql_query;
	
}

#endif
