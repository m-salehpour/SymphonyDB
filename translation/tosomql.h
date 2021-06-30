#ifndef TOSOMQL_H
#define TOSOMQL_H



#include "../sse/tosse.h"
#include "extractfromtps.h"
#include "indexchain.h"
using namespace std;

std::string sparql_to_so_mql_translate(string sparql_query, std::vector<triple_pattern> get_triple_patterns_structs_local){

	/*
	std::string example_query = " SELECT ?v0 ?v2 ?v3 WHERE { 	?v0 <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://db.uwaterloo.ca/~galuc/wsdbm/ProductCategory9> . 	?v0 <http://schema.org/description> ?v2 . 	?v0 <http://schema.org/keywords> ?v3 . 	?v0 <http://schema.org/language> <http://db.uwaterloo.ca/~galuc/wsdbm/Language0> . }";
	*/

	string mql_query;
	string mql_projection_part = ",{ $project:{";
	
	tosse tosse_obj;
	auto get_namespace = tosse_obj.get_name_spaces(sparql_query);
	auto get_projection_variables_local = tosse_obj.get_projection_variables(sparql_query);
	//auto get_triple_patterns_structs_local = tosse_obj.get_triple_patterns_structs(sparql_query);
	
	
	
	
	
	
	
	
	string sub, pre, obj;
	char homepage_indicator_char = 'N';



/*****************************************************

	bool starter_node_found = false , end_node_found = false;
	
	
			mql_query = "db.sub.aggregate([";



				
				
			int index_starter_node;	
						
			for (size_t j=0; j < get_triple_patterns_structs_local.size(); j++)
			{
				
				std::string tmp_sub = get_triple_patterns_structs_local[j].subject;

				for (size_t i = 0; i < get_triple_patterns_structs_local.size(); i++)
				{
					if ( get_triple_patterns_structs_local[i].object == tmp_sub )	break;
									
					if ( (i+1) == get_triple_patterns_structs_local.size() )
					{
						starter_node_found = true;
						index_starter_node = j;										
					}
				}
			 if (starter_node_found) break;
			}


			int index_end_node;	
						
			for (size_t j=0; j < get_triple_patterns_structs_local.size(); j++)
			{
				
				std::string tmp_obj = get_triple_patterns_structs_local[j].object;

				for (size_t i = 0; i < get_triple_patterns_structs_local.size(); i++)
				{
					if ( get_triple_patterns_structs_local[i].subject == tmp_obj )	break;
									
					if ( (i+1) == get_triple_patterns_structs_local.size() )
					{
						end_node_found = true;
						index_end_node = j;										
					}
				}
			 if (end_node_found) break;
			}

			//cout << "\nstart:   " << index_starter_node << "\tend:  " << index_end_node << "\n";

*/

/*
  *--------------------------------------------------------------------------------------------------------------------------------------------------*
   *--------------------------------------------------------------------------------------------------------------------------------------------------*
    *--------------------------------------------------------------------------------------------------------------------------------------------------*
     *--------------------------------------------------------------------------------------------------------------------------------------------------*
     *--------------------------------------------------------------------------------------------------------------------------------------------------*
    *--------------------------------------------------------------------------------------------------------------------------------------------------*
   *--------------------------------------------------------------------------------------------------------------------------------------------------*
  *--------------------------------------------------------------------------------------------------------------------------------------------------*
*/			

			int index_starter_node = get_index_starter_node_chain(get_triple_patterns_structs_local);
			int index_end_node = get_single_index_end_node_chain(get_triple_patterns_structs_local);


			string mql_query_version2 = "db.sub.aggregate([";

			// comment the following lines to not shorten URIs!			
			//------------------------------------------------
			homepage_indicator_char = 'N';
			pre = get_predicate_without_uri(get_triple_patterns_structs_local[index_starter_node].predicate);
			if ( pre == "\"page\"")
				homepage_indicator_char = 'Y';
			obj = get_object_without_uri(get_triple_patterns_structs_local[index_starter_node].object, homepage_indicator_char);
			//------------------------------------------------




			if (get_subject_without_uri(get_triple_patterns_structs_local[index_starter_node].subject).find('?') == std::string::npos)
			{
				mql_query += " {$match: {\"idPrimaryKey\" : " + get_subject_without_uri(get_triple_patterns_structs_local[index_starter_node].subject) + ", " +
					       pre + " : {$exists:true}  }},";
					       
				mql_query_version2 += " {$match: {\"idPrimaryKey\" : " + get_subject_without_uri(get_triple_patterns_structs_local[index_starter_node].subject) + ", " +
					       pre + " : {$exists:true}  }},";	       
					
			}
		

			
			
			int join_order_index = 0;

			join_order_index++;
			string inner_join_name = "sojoin1";
			//string inner_join_name += to_string(join_order_index);			
			string loop_join_name = "";

			mql_query += "{$lookup:{from:\"sub\", localField:" + pre + ",foreignField:\"idPrimaryKey\", as: \""+ inner_join_name +"\" }} , {\"$unwind\" : \"$"+ inner_join_name +"\"}  ";

			mql_query_version2 += "{$lookup:{from:\"sub\", localField:" + pre + ",foreignField:\"idPrimaryKey\", as: \""+ inner_join_name +"\" }} ";


			

				

			
			for (size_t j=0; j < get_triple_patterns_structs_local.size(); j++)
			{
				for (size_t i = 0; i < get_triple_patterns_structs_local.size(); i++)
				{




					if ( get_triple_patterns_structs_local[i].subject == obj &&
					     get_triple_patterns_structs_local[i].subject != get_subject_without_uri(get_triple_patterns_structs_local[index_starter_node].subject) &&
					     get_triple_patterns_structs_local[i].object != get_triple_patterns_structs_local[index_end_node].object
					   )
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
	
						inner_join_name = "sojoin";
						for (size_t k = 0 ; k < join_order_index ; k++)
							loop_join_name += (inner_join_name = "sojoin" + to_string(k+1)) + ".";

						inner_join_name = "sojoin";
						join_order_index++;
						inner_join_name += to_string(join_order_index);			
						boost::trim(pre);
						pre.erase(0,1);
						//pre.pop_back();
						string unwind = loop_join_name;
						loop_join_name += pre ;
											
						mql_query += ", {$lookup:{from:\"sub\", localField:\"" + loop_join_name + ",foreignField:\"idPrimaryKey\", as: \""+
						              inner_join_name +"\" }}  , {\"$unwind\" : \"$"+ unwind+inner_join_name +"\"}  ";
						
						mql_query_version2 += ", {$lookup:{from:\"sub\", localField:\"" + loop_join_name + ",foreignField:\"idPrimaryKey\", as: \""+
						              inner_join_name +"\" }} ";


						loop_join_name = "";

					
					}
					
					
					
					
									
				
				
				
				
				}

			}
			
			
						/*
						* Last node
						*/

						// comment the following lines to not shorten URIs!			
						//------------------------------------------------
						homepage_indicator_char = 'N';
						//sub = get_subject_without_uri(get_triple_patterns_structs_local[i].subject);
						pre = get_predicate_without_uri(get_triple_patterns_structs_local[index_end_node].predicate);
						if ( pre == "\"page\"")
							homepage_indicator_char = 'Y';
						obj = get_object_without_uri(get_triple_patterns_structs_local[index_end_node].object, homepage_indicator_char);
						//------------------------------------------------			
						
						inner_join_name = "sojoin";
						for (size_t k = 0 ; k < join_order_index ; k++)
							loop_join_name += (inner_join_name = "sojoin" + to_string(k+1)) + ".";
						
						
						boost::trim(pre);
						pre.erase(0,1);					
						loop_join_name += pre ;
						
						if ( obj.find('?') != string::npos )
						{
					 		mql_query += " , {$match: {\""+ loop_join_name +" : {$exists:true } }}";

					 		mql_query_version2 += " , {$match: {\""+ loop_join_name +" : {$exists:true } }}";
					 	}
					 	else
					 	{
					 		mql_query += " ,  {$match: {\""+ loop_join_name +" : "+ obj +" }}";

					 		mql_query_version2 += " ,  {$match: {\""+ loop_join_name +" : "+ obj +" }}";					 						 							 	
						}				
								
			
			
			
			
			
			
			mql_query += "])";				
			mql_query_version2 += "])";
			
			
			cout << "\n MQL without unwind:\n" << mql_query_version2 << endl;
			
/*
				// comment the following lines to not shorten URIs!			
				//------------------------------------------------
				homepage_indicator_char = 'N';
				sub = get_subject_without_uri(get_triple_patterns_structs_local[index_starter_node].subject);
				pre = get_predicate_without_uri(get_triple_patterns_structs_local[index_starter_node].predicate);
				if ( pre == "\"page\"")
					homepage_indicator_char = 'Y';
				obj = get_object_without_uri(get_triple_patterns_structs_local[index_starter_node].object, homepage_indicator_char);
				//------------------------------------------------			
			
			
			
			
			
			
			
			
			
			

			for (size_t i=0; i < get_triple_patterns_structs_local.size();i++)
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
				if (pre.find('?') == std::string::npos)					
				{			
					
					
					

					if (obj.find('?') != std::string::npos)
					{



						if (flag_2nd_order_join == false)
						{					
							mql_query += " {$match: {" + pre + " :  {$exists:true}   }},";
							
							mql_query += "{$lookup:{from:\"sub\", localField:" + pre + ",foreignField:\"_id\", as: \"sojoin1\" }}";

							flag_2nd_order_join = true;
						} else
						{
							boost::trim(pre);
							pre.erase(0,1);
							pre.pop_back();
							mql_query += ",{$lookup:{from:\"sub\", localField: \"sojoin1."+pre + "\" ,foreignField:\"_id\", as: \"sojoin2\" }}";							
						
						}
						
						
					}
					else
						mql_query += "{$match: {" + pre + " :  " + obj + "} ,";
				
	
					for(string const& word : get_projection_variables_local )
					{
						if (obj == word && pre.find('?') == std::string::npos)
							mql_projection_part += pre + " : 1 , ";

								
									
						if ((i+1) == (get_triple_patterns_structs_local.size()-1) )
							if (lst_obj == word && lst_pre.find('?') == std::string::npos)
								mql_projection_part += lst_pre + " : 1 , ";
										
						
					}// for loop projection		
				
				}
			}// for loop triple_pattenrs
			

			
			if (lst_pre.find('?') == std::string::npos  && flag_2nd_order_join == false)					
			{			
				
				if (lst_obj.find('?') != std::string::npos)
					mql_query += lst_pre + " : {$exists: true}";
				else
					mql_query += ", {$match: {" + lst_pre + " :  " + lst_obj + " } ";

			}else mql_query.pop_back();		
					
			
				if (mql_projection_part != ",{")
					mql_projection_part += " \"_id\" : 1 }}";
				else
					mql_projection_part = "";
					
	mql_projection_part = ""; // For SO join!!
	mql_query += "}" + mql_projection_part + "])";				
				
	*/	
	
	
	return mql_query;
	
}

#endif
