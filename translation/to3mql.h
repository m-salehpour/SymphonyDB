#ifndef TO3MQL_H
#define TO3MQL_H


#include "indexchain.h"
#include <unordered_map>
#include "pathextract.h"
#include "../translation/checktype.h"
#include "../translation/tossmql.h"
#include "../translation/tosomql.h"
#include "../translation/to3mql.h"
//#include <bits/stdc++.h>
#include <set>

using namespace std;

//set<string> set_bound_var;

std::string sparql_to_t3_mql_translate(string sparql_query, std::vector<triple_pattern> get_triple_patterns_structs_local, std::vector<triple_pattern> get_optional_patterns_structs_local){

	
	map<std::string, std::tuple< std::string, std::string, std::string >>  filter_map_tmp;
	map<std::string, std::tuple< std::string, std::string, std::string >>::iterator filter_it;
	map<std::string, std::tuple< std::string, std::string, std::string >>::iterator tmp_filter_it;

	std::map<std::string, std::tuple< std::string, std::string >> predicate_map_tmp;
	std::map<std::string, std::tuple< std::string, std::string >>::iterator predicate_map_it;
	
	std::map<std::string, std::vector<std::string>> map_predicate_multivalue;

	set<string> set_optional_predicate;
	
	
	std::string sub, pre, obj;
	char homepage_indicator_char = 'N';
	
	tosse tosse_obj;

	map<tuple<string, string, string>, string>::iterator it_pre_linked_map;


	vector<string> get_filter_patterns_local = tosse_obj.get_sparql_query_filters(sparql_query); // filters
	//predicate_map_tmp = tosse_obj.get_predicate_map(sparql_query,get_triple_patterns_structs_local); // when object variables are repeated, no direct access is possible!

	std::map < int, std::pair<int, std::string> > map_modifiers_local = tosse_obj.get_sparql_query_modifiers(sparql_query);

	//vector<string> get_optional_patterns_local = tosse_obj.get_sparql_query_optional(sparql_query); // optional
		
		//cout<< "  \n OPT:  ";
		
		//cout<< "  \n ChecknDebug \n  ";

		//cout << "\n\n OPT SIZE: " << get_optional_patterns_structs_local.size() << "\n";
//-------------------------------------------------------
		//int map_key=-1;
	if ( !get_optional_patterns_structs_local.empty() )
	{
		for (size_t j=0; j < get_optional_patterns_structs_local.size();j++)
		{


			
			
			// comment the following lines to not shorten URIs!			
			//------------------------------------------------
			homepage_indicator_char = 'N';
			//sub = get_subject_without_uri(get_triple_patterns_structs_local[i].subject);
			string tmp_cmp_pre = get_predicate_without_uri(get_optional_patterns_structs_local[j].predicate);
			if ( tmp_cmp_pre == "\"page\"")
				homepage_indicator_char = 'Y';
			string tmp_cmp_obj = get_object_without_uri(get_optional_patterns_structs_local[j].object, homepage_indicator_char);
			//------------------------------------------------
			
			//cout << "\n\n Pre_OPT: " << tmp_cmp_pre << "\n";
			
			if (set_optional_predicate.find(tmp_cmp_pre)  == set_optional_predicate.end())
			{
				set_optional_predicate.insert(tmp_cmp_pre);
			}
			
			
			
		}
	}
		//cout<< "  \n OPT:  ";
			
			//for (string const& pre_opt : set_optional_predicate)
			//	cout << "   \n OPT-print  :" << pre_opt << endl;

		
		//cout << "\n BEF SIZE: " << get_triple_patterns_structs_local.size() << "\n";
		if ( !get_optional_patterns_structs_local.empty() )
			get_triple_patterns_structs_local.insert(
			get_triple_patterns_structs_local.end(),
			get_optional_patterns_structs_local.begin(),
			get_optional_patterns_structs_local.end());
		//cout << "\n AFT SIZE: " << get_triple_patterns_structs_local.size() << "\n";			

		//cout<< "  \n OPT:  ";

//-------------------------------------------------------
		for (size_t j=0; j < get_triple_patterns_structs_local.size();j++)
		{


			
			
			// comment the following lines to not shorten URIs!			
			//------------------------------------------------
			homepage_indicator_char = 'N';
			string tmp_cmp_sub = get_subject_without_uri(get_triple_patterns_structs_local[j].subject);
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
					sub = get_subject_without_uri(get_triple_patterns_structs_local[i].subject);
					pre = get_predicate_without_uri(get_triple_patterns_structs_local[i].predicate);
					if ( pre == "\"page\"")
						homepage_indicator_char = 'Y';
					obj = get_object_without_uri(get_triple_patterns_structs_local[i].object, homepage_indicator_char);
					//------------------------------------------------
				

				
				
				
					if (  i != j && tmp_cmp_pre == pre &&  obj.find('?') == string::npos && tmp_cmp_sub == sub)
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
		

	
	
	
	
	
	/*
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
	
	*/
	

//-------------------------------------------------------






	string mql_query="db.sub.aggregate([ ";


	//cout << "\n # edges:  " <<	get_triple_patterns_structs_local.size() << endl;		

	
	set<string> vertex_set;


		


	for (size_t i = 0; i < get_triple_patterns_structs_local.size(); i++)
	{

		if (vertex_set.find(get_triple_patterns_structs_local[i].object)  == vertex_set.end())
			vertex_set.insert(get_triple_patterns_structs_local[i].object);		

		if (vertex_set.find(get_triple_patterns_structs_local[i].subject)  == vertex_set.end())
			vertex_set.insert(get_triple_patterns_structs_local[i].subject);		
	}
	
	cout << "\n # nodes:  " <<	vertex_set.size() << endl;		


	unordered_map <string, int> vertex_map;
	unordered_map <int, string> reverse_map;

	
	int node_map=0;
	
	for (string const& vertex : vertex_set)
	{
		vertex_map[vertex]    = node_map;
		reverse_map[node_map] = vertex;
		node_map++;
	        //std::cout << "\n map: " + vertex + " --> " << (node_map - 1) << endl;
       	        std::cout << "\n map: " + vertex + " --> " << vertex_map[vertex]<< endl;
	}


	string string_index_starter_node = get_string_index_starter_node_chain(get_triple_patterns_structs_local); //it might be a set of starting indexes --later will be modified!
	set<string> set_end_vertex = get_set_index_end_node_chain(get_triple_patterns_structs_local);

	//for (string const& vertex : set_end_vertex)
	//	std::cout << "\n end node: " + vertex + " map--> " << vertex_map[vertex] << endl;


	int total_edges = get_triple_patterns_structs_local.size();
	vector < vector<int>> GRAPH_edge_list(100);
	
       
	for (size_t i = 0; i < get_triple_patterns_structs_local.size(); i++)
	{
	
		int u = vertex_map[get_triple_patterns_structs_local[i].subject];
		int v = vertex_map[get_triple_patterns_structs_local[i].object];
		GRAPH_edge_list[u].push_back(v);
	
	}
        
	


	vector<vector<vector<int>>> tmp_all_path_from_source;
	vector<vector<int>> all_path_from_source;

	
	for (string const& vertex : set_end_vertex)
		tmp_all_path_from_source.push_back(extract_path_from_tps(vertex_map[string_index_starter_node] ,vertex_map[vertex] ,vertex_set.size(),total_edges, GRAPH_edge_list ));


	for (int i = 0; i < tmp_all_path_from_source.size(); i++)
		for (int j = 0; j < tmp_all_path_from_source[i].size(); j++)
			all_path_from_source.push_back(tmp_all_path_from_source[i][j]);
		

	
	

	//cout << "\n SIZE:  " << all_path_from_source.size();

	std::sort(all_path_from_source.begin(), all_path_from_source.end(),
          [](const std::vector<int>& a, const std::vector<int>& b) {
	  return ( a.size() < b.size() || ( a.size() == b.size() && a < b )  );
	});


	// The following (two) for-loops need to be chanaged as comment after the test process!
	//******************************************
	for (int i = 0; i < all_path_from_source.size(); i++)
	{
		cout << "\n ------------------------------------------------------ " << "\n PATH:  ";
		for (int j = 0; j < all_path_from_source[i].size(); j++)
		{
			cout << " " << all_path_from_source[i][j];
		}
	}
	//******************************************

	
	//cout << "\n";
	
	map<pair<int, int>, string> predicate_map;

	std::vector< vector<triple_pattern> > vec_of_vec_tree_struct;
	vector<triple_pattern> vec_sub_order;
	for (int i = 0; i < all_path_from_source.size(); i++)
	{
		//cout << "\n ------------------------------------------------------ " << "\n PATH:  ";
		for (int j = 1; j < all_path_from_source[i].size(); j++)
		{
			
			string node_u = reverse_map[all_path_from_source[i][j-1]] , node_v = reverse_map[all_path_from_source[i][j]];
			

			for (size_t k = 0; k < get_triple_patterns_structs_local.size(); k++)
			{
				if (get_triple_patterns_structs_local[k].subject == node_u &&  get_triple_patterns_structs_local[k].object == node_v)
				{
			     			 
				vec_sub_order.push_back({
					get_triple_patterns_structs_local[k].subject,
					get_triple_patterns_structs_local[k].predicate,
					get_triple_patterns_structs_local[k].object
					});	
				
				predicate_map.insert(make_pair(make_pair(all_path_from_source[i][j-1],all_path_from_source[i][j]), get_triple_patterns_structs_local[k].predicate));
				/*	
				cout << get_triple_patterns_structs_local[k].subject
				     << " "  + get_triple_patterns_structs_local[k].predicate
				     << " "  + get_triple_patterns_structs_local[k].object << "\n";
				*/
			     	break;
				}
			}
		}
		cout << endl;	
		vec_of_vec_tree_struct.push_back(vec_sub_order);
		vec_sub_order.clear();
	}	
	


	map<pair<int, int>, string> linked_map;

	map<tuple<string, string, string>, string> pre_linked_map;
	
	int join_order_index = 0;
	string loop_join_name = "", inner_join_name="";
	
	set<string> multi_var_set;
	set<string> optional_multi_var_set;
	
	if (get_subject_without_uri(vec_of_vec_tree_struct[0][0].subject).find('?') == std::string::npos)
		mql_query += "{\"$match\":{ \"idPrimaryKey\" : " + get_subject_without_uri(vec_of_vec_tree_struct[0][0].subject) + "}},";
						
	string tmp_q_remover;
	int opt_cnt = 0;
	std::string opt_pre = "OPT";
	for (int i = 0; i < all_path_from_source.size(); i++)
	{
		//cout << "\n ------------------------------------------------------ " << "\n PATH:  ";
		for (int j = 1; j < all_path_from_source[i].size(); j++)
		{
			
			
			// comment the following lines to not shorten URIs!			
			//------------------------------------------------
			char homepage_indicator_char = 'N';
			string pre = get_predicate_without_uri(vec_of_vec_tree_struct[i][j-1].predicate);
			if ( pre == "\"page\"")
				homepage_indicator_char = 'Y';
			string obj = get_object_without_uri( vec_of_vec_tree_struct[i][j-1].object , homepage_indicator_char);
			//------------------------------------------------
			
			//cout << " \n pre: " << pre  <<"\n";
			
			if ( linked_map.find(make_pair( all_path_from_source[i][j-1] , all_path_from_source[i][j] ) )  == linked_map.end() )
			{			// not found
				
				if ( ( j + 1 ) == all_path_from_source[i].size())
				{		//match
				
					if (j > 1)
						loop_join_name = linked_map[make_pair(all_path_from_source[i][j-2],all_path_from_source[i][j-1])];
					else
						loop_join_name = "";
						
					
					
					
					
					opt_pre = "OPT" + to_string(++opt_cnt);
						
					linked_map.insert(make_pair(make_pair(all_path_from_source[i][j-1],all_path_from_source[i][j]), loop_join_name));


					//cout << " \n pre loope  : " << pre <<"   "<< " \n pre opt  : " << opt_pre <<"\n";

						if ( set_optional_predicate.find(pre) == set_optional_predicate.end() )
							pre_linked_map.emplace(make_tuple( reverse_map[all_path_from_source[i][j-1]]  , reverse_map[all_path_from_source[i][j]] , pre), loop_join_name);
						else
						{
							if (optional_multi_var_set.find(pre) == optional_multi_var_set.end())
							{
						
								if (loop_join_name != "")						
									pre_linked_map.emplace(make_tuple( reverse_map[all_path_from_source[i][j-1]]  , reverse_map[all_path_from_source[i][j]] , pre), loop_join_name.substr(0,loop_join_name.rfind('.'))+"."+ opt_pre);
								else
									pre_linked_map.emplace(make_tuple( reverse_map[all_path_from_source[i][j-1]]  , reverse_map[all_path_from_source[i][j]] , pre), opt_pre);
							}
							else
							{
							
								it_pre_linked_map = pre_linked_map.begin();
								while (it_pre_linked_map != pre_linked_map.end())
								{
									if ( get<2>(it_pre_linked_map->first) == pre )
										pre_linked_map.emplace(make_tuple( get<0>(it_pre_linked_map->first)  , obj , get<2>(it_pre_linked_map->first)), it_pre_linked_map->second);
									it_pre_linked_map++;
								     
								}
							
							}
							
							
							
							
						}
					

					auto it_map_find = map_predicate_multivalue.find(pre);
					
					
					string multi_var_loop_name = "";

					if (loop_join_name == "")
					{
						loop_join_name += pre;
						multi_var_loop_name = "";
					}
					else
					{
						boost::trim(pre);
						pre.erase(0,1);
						multi_var_loop_name = loop_join_name+".";
						loop_join_name = "\"" + loop_join_name + "." + pre;					
					}
					
					
					
					

					if (pre[0] != '\"')
						pre = "\"" + pre;
					tmp_q_remover = loop_join_name;
					if (tmp_q_remover != "")
						tmp_q_remover.erase(0,1);

					//cout << " \n 2nd pre loope  : " << pre <<"   "<< " \n 2ndpre opt  : " << opt_pre <<"\n";
					
					if ( set_optional_predicate.find(pre) != set_optional_predicate.end() && optional_multi_var_set.find(pre) == optional_multi_var_set.end())
					{
						
						if (obj.find('?') != string::npos)
							optional_multi_var_set.insert(pre);
						if (loop_join_name[0] == '\"')
							{loop_join_name[0] = '$'; loop_join_name = "\"" +loop_join_name ;}


						if (loop_join_name.rfind('.') != string::npos && loop_join_name != pre)
						{
							//mql_query += " {\"$addFields\": { "+ loop_join_name.substr(0,loop_join_name.rfind('.'))+"."+ opt_pre +"\" : { \"$cond\": { if: { \"$not\" : ["+loop_join_name+"]}, then:[ ] , else:\"$"+tmp_q_remover+" }}}} ,";

							mql_query += " {\"$addFields\": { \""+  opt_pre +"\" : { \"$cond\": { if: { \"$not\" : ["+loop_join_name+"]}, then:[ ] , else:\"$"+tmp_q_remover+" }}}} ,";
					
						}
						else
						{
							mql_query += " {\"$addFields\": { \""+ opt_pre +"\" : { \"$cond\": { if: { \"$not\" : ["+loop_join_name+"]}, then:[ ] , else:\"$"+tmp_q_remover+" }}}} ,";
						
						}
					}
					
					
					
					
					
					if (it_map_find == map_predicate_multivalue.end())
					{   //non-multivalue --NO array
					
					
					
					
						
						if (pre.find('?') == std::string::npos)					
						{			
							if (obj.find('?') != std::string::npos)
							{

								if (set_optional_predicate.find(pre) == set_optional_predicate.end())
								{
									if (pre == "\"member\"")
									{
									mql_query += "{\"$match\":{ ";
									if (loop_join_name.find('.') != string::npos)
										loop_join_name = loop_join_name.substr(0, loop_join_name.rfind('.'));
									mql_query += loop_join_name + "\" : {\"$ne\": [ ]}";
									mql_query += "}},";

									}
									else
									{									
									mql_query += "{\"$match\":{ ";
									mql_query += loop_join_name + " : {\"$exists\": true}";
									mql_query += "}},";
									}
								}								
								
								
								//	mql_query += loop_join_name.substr(0,loop_join_name.rfind('.'))+"."+ opt_pre  + "\" : {$exists: true}";
								//else
								//	mql_query += loop_join_name + " : {$exists: true}";

							}
							else
							{
							
							
							
									if (pre == "\"member\"")
									{
										mql_query += "{\"$match\":{ ";
										if (loop_join_name.find('.') != string::npos)
											loop_join_name = loop_join_name.substr(0, loop_join_name.rfind('.'));
										mql_query += loop_join_name + "\" : {\"$ne\": [ ]}";
										mql_query += "}},";

									}
									else
									{	
								mql_query += "{\"$match\":{ ";							
								if (set_optional_predicate.find(pre) != set_optional_predicate.end() && optional_multi_var_set.find(pre) == optional_multi_var_set.end())
								{
									//mql_query += loop_join_name.substr(0,loop_join_name.rfind('.'))+"."+ opt_pre + " :  " + obj ;
								
									if (loop_join_name.find('.') !=string::npos && loop_join_name != pre)
										//mql_query += " \"$or\": [ { " + loop_join_name.substr(0,loop_join_name.rfind('.'))+"."+ opt_pre + " :\"null\" },{ " +loop_join_name.substr(0,loop_join_name.rfind('.'))+"."+ opt_pre + " :  " + obj +"}]}";
										mql_query += " \"$or\": [ { \"" + opt_pre + " :\"null\" },{ \"" + opt_pre + " :  " + obj +"}]}";
									else
										mql_query += " \"$or\": [ { \"" + opt_pre + "\" :\"null\" },{ \"" +opt_pre + "\" :  " + obj +"}]}";
								}								
								else
									mql_query += loop_join_name + " :  " + obj ;
									
								mql_query += "}},";
							}
							}
						
						}
					} else 
					{   //multivalue --array
					
					
					//cout << "\n\nPRE--->" << it_map_find->first;
						if ( optional_multi_var_set.find(pre) == optional_multi_var_set.end() ) 
						{
						
						
						
						
							optional_multi_var_set.insert(pre);

							
							if (multi_var_set.find(it_map_find->first)  == multi_var_set.end())
							{
							    multi_var_set.insert(it_map_find->first);
							    mql_query += "{\"$match\":{ ";
					    
							    string tmp_pre = it_map_find->first;
							    if (multi_var_loop_name != "") {tmp_pre.erase(0,1);  multi_var_loop_name = "\"" + multi_var_loop_name;}
					    
					    
							    if (set_optional_predicate.find(it_map_find->first) != set_optional_predicate.end())
							    {
						
    								   if (loop_join_name.find('.') !=string::npos && loop_join_name != pre)
								   	mql_query += loop_join_name.substr(0,loop_join_name.rfind('.'))+"."+ opt_pre + " :{ $all:[";
								   else
									mql_query += opt_pre + " :{ $all:[";
							    }
							    else
							    	    mql_query += multi_var_loop_name + tmp_pre + " :{ \"$all\":[";
					   
					    
					    
		    					    vector<string> vIt = it_map_find->second;
	
							    for (size_t k=0; k< vIt.size()-1; k++)
		    						mql_query += vIt[k] + ", ";

					        	    mql_query += vIt.back();
        		
					       		    mql_query += "]}}}, ";
					       		}
				  		}
					   
					}
					
					
					
					
					
					
					
					
					

				
				}
				else		//lookup
				{

					if (j > 1)
					{
						loop_join_name = linked_map[make_pair(all_path_from_source[i][j-2],all_path_from_source[i][j-1])];
						//pre_linked_map.emplace(make_tuple( reverse_map[all_path_from_source[i][j-2]]  , reverse_map[all_path_from_source[i][j-1]] , pre), loop_join_name);
					}
					else	loop_join_name = "";
					

					
					join_order_index++;
					inner_join_name = "sojoin";
					inner_join_name += to_string(join_order_index);								
	
					if (loop_join_name == "")
						inner_join_name = inner_join_name += to_string(join_order_index);
					else
						inner_join_name = loop_join_name+"."+ inner_join_name += to_string(join_order_index);	
					
					string tmp_pre_opt = pre;

					boost::trim(pre);
					pre.erase(0,1);

					if (loop_join_name == "")
						loop_join_name += pre;
					else
						loop_join_name = loop_join_name + "." + pre;					


					tmp_q_remover = inner_join_name;
					if (tmp_q_remover != "" )
						tmp_q_remover.erase(0,1);
					
					
					
					if ( set_optional_predicate.find(tmp_pre_opt) == set_optional_predicate.end() )
						mql_query += "{$match:{\"" + loop_join_name +":{$exists:true}}}, {\"$lookup\":{from:\"sub\", localField:\"" + loop_join_name + ",foreignField:\"idPrimaryKey\", as: \""+  inner_join_name +"\" }} ,";// {\"$unwind\": \"$"+ inner_join_name +"\"} , ";
					else
					mql_query += "{\"$lookup\":{from:\"sub\", localField:\"" + loop_join_name + ",foreignField:\"idPrimaryKey\", as: \""+  inner_join_name +"\" }} ,";// {\"$unwind\": \"$"+ inner_join_name +"\"} , ";

					
					pre = "\"" + pre;
					linked_map.insert(make_pair(make_pair(all_path_from_source[i][j-1],all_path_from_source[i][j]), inner_join_name));
					pre_linked_map.emplace(make_tuple( reverse_map[all_path_from_source[i][j-1]]  , reverse_map[all_path_from_source[i][j]] , pre), inner_join_name);
				
				
				}
				
				


			} //else			// found
			//{

			//}
			
		}
	}


	//cout << "CHECK: " << endl;
	//cout << linked_map[make_pair(5,0)] << endl;


	boost::trim(mql_query);
	//pre.erase(0,1);
	mql_query.pop_back();
	




	
	std::string str_filtering_part_of_the_query = "";
		
		
		
	const std::string
        boundOperator      = "op_bound" ,
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


	int int_tmp_key = 0;
	//map<tuple<string, string, string>, string>::iterator it_pre_linked_map;

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
		
		
		filter_map_tmp.clear();
		filter_map_tmp = parse_filter_to_AST_map(get_filter_patterns_local[i]);
		
		
		
		
		/*
		filter_it = filter_map_tmp.begin();
		while (filter_it != filter_map_tmp.end())
		{
			cout << "  \n  FILTER:   " << filter_it->first << "   \n";
			filter_it++;
		}
		//filter_map_tmp.clear();
		*/
		
		
		
		
		filter_it = filter_map_tmp.begin();
		
		
		
		
		
		
		//cout << " \n SIZE:--->  " << filter_map_tmp.size();

		while (filter_it != filter_map_tmp.end())
		{

			std::string word = filter_it->first;
			std::string opera = std::get< 1 > ( filter_it->second ).replace(0,1,"");
			
			
			//cout << " \n word:--->  " << word << "   opera--->  " << opera << "\n";
			
				string op1=std::get< 0 >( filter_it->second),
				       op2=std::get< 2 >( filter_it->second);
				
			
			cout << "\n bef op1: " << op1 << "   op2: " << op2 << "\n";
			
			if ( op1.find('>') != std::string::npos )
				op1 = get_object_without_uri( op1 , 'N');

			if ( op2.find('>') != std::string::npos )
				op2 = get_object_without_uri( op2 , 'N');
			
			cout << "\n aft op1: " << op1 << "   op2: " << op2 << "\n";
			
				


				       
				       


			
			if (opera != notOperator )
			{

				opera = "$" + std::get< 1 > ( filter_it->second ).substr(
				std::get< 1 > ( filter_it->second ).find('_')+1,std::get< 1 > ( filter_it->second ).length());
	
//-----------------------------------------------------------------------------------------------------------

				it_pre_linked_map = pre_linked_map.begin();
	

				while (it_pre_linked_map != pre_linked_map.end())
				{
				
					if (std::get< 1 >( it_pre_linked_map-> first ) == std::get< 0 >( filter_it->second) )
					{


						op1 = std::get< 2 >( it_pre_linked_map->first );
						
						
						
		 				if (op1.find('%') == std::string::npos && op1.substr(0,4) != "key_" && !is_number(op1))
						{
							if ( op1.find('\"') != string::npos)
							{
								op1.replace(0,1,"");
								op1.pop_back();
							}
					
						}
						
					

					
					
						

 						if ( it_pre_linked_map->second != "")
 						{

 						//cout << "\n\n Bef OP1: " << op1 << "\n";
 						
 							if ( (it_pre_linked_map->second).find("OPT") == string::npos )//set_optional_predicate.find(("\""+op1+"\"")) == set_optional_predicate.end() )
	 							op1 = it_pre_linked_map->second +"."+ op1;
	 						else
		 						//op1 = it_pre_linked_map->second;
		 						op1 = (it_pre_linked_map->second).substr((it_pre_linked_map->second).rfind('.')+1,(it_pre_linked_map->second).length()) ;
 						//cout << "\n\n Aft OP1: " << op1 << "\n";		 						
 						}
 							

	 					op1 = "$" + op1;
 					
 					}


					if (std::get< 1 >( it_pre_linked_map-> first ) == std::get< 2 >( filter_it->second) )
					{
						op2 = std::get< 2 >( it_pre_linked_map->first );


						
		 				if (op2.find('%') == std::string::npos && op2.substr(0,4) != "key_" && !is_number(op2))
						{
							if ( op2.find('\"') != string::npos)
							{
								op2.replace(0,1,"");
								op2.pop_back();
							}
					
						}
						

 						if ( it_pre_linked_map->second != "")
 						{
						//cout << "\n\n Bef OP2" << op2 << "\n";
 							if ( (it_pre_linked_map->second).find("OPT") == string::npos ) //set_optional_predicate.find(("\""+op2+"\"")) == set_optional_predicate.end() )
	 							op2 = it_pre_linked_map->second +"."+ op2;
	 						else
		 						//op2 = it_pre_linked_map->second;
								op2 = (it_pre_linked_map->second).substr((it_pre_linked_map->second).rfind('.')+1,(it_pre_linked_map->second).length()) ;
						//cout << "\n\n Aff OP2" << op2 << "\n";		 						
						
 						}
 							

	 					op2 = "$" + op2;
						
						
						

 					}
 					

				

				       it_pre_linked_map++;
				}





//-----------------------------------------------------------------------------------------------------------







			
				//cout << "\n OP1: " << op1 << "   op2:  " << op2 << "\n";
				boost::replace_all(op1, "\"", "");
				boost::replace_all(op2, "\"", "");
				if (!is_number(op1) && op1.find('\"') ==string::npos)
					op1 = "\"" + op1 + "\"";
				if (!is_number(op2)&& op2.find('\"') ==string::npos)
					op2 = "\"" + op2 + "\"";

				if (opera != "$bound")		//not-Bound
					str_filtering_part_of_the_query +=
	 				",{ \"$addFields\": { \""+ word +"\" :{ \""+ opera+"\":[ " +
	 				 op1 +", " +  op2 +" ] }}}" ;
 				 
 				 else				//Bound
					str_filtering_part_of_the_query +=
	 				",{ \"$addFields\": { \""+ word +"\" :{ \"$ne\":[ " +
	 				 op1 +", [ ] ] }}}" ;

 				 //mql_query += " \"$or\": [ { \"" + opt_pre + "\" :\"null\" },{ \"" +opt_pre + "\" :  " + obj +"}]}";

				tmp_filter_it = filter_it;
				//std::advance(tmp_filter_it, 1);
				tmp_filter_it++;

				if (  tmp_filter_it != filter_map_tmp.end()  )
				{
				
					if (std::get< 1 > ( tmp_filter_it->second).substr(1,std::get< 1 > ( tmp_filter_it->second).length()) != notOperator &&
					    opera != sumOperator && opera != differenceOperator && opera != factorOperator && opera != divisionOperator)
					{
						
						if (opera == "$bound")
							str_filtering_part_of_the_query +=
	 							",{\"$match\": { \""+ word +"\" : true   }  }  " ;
	 					else
	 					{
						
						cout << "\n OP1:  " << op1 << "\n";
						cout << "\n OP2:  " << op2 << "\n";
						if ( op1.find('$') != string::npos &&  op1.find("OPT") == string::npos )
						{
							boost::trim(op1);
							op1 = op1.substr( op1.find('$')+1 , op1.rfind('\"') - op1.find('$') - 1 );
							//cout << "\n OP1:  " << op1 << "\n";
							str_filtering_part_of_the_query +=
 							",{\"$match\": { \"$or\" : [ {   \""+ word +"\" : true   }, { \""+ op1 +"\" : [ ]  } ] }}  " ;					
 							
 						}	
						else if ( op2.find('$') != string::npos &&  op2.find("OPT") == string::npos )
						{
							boost::trim(op2);
							op2 = op2.substr( op2.find('$')+1 , op2.rfind('\"') - op2.find('$') - 1 );
							str_filtering_part_of_the_query +=
 							",{\"$match\": { \"$or\" : [ {   \""+ word +"\" : true   }, { \""+ op2 +"\" : [ ]  } ] }}  " ;
 						}
 						else
							str_filtering_part_of_the_query +=
 							",{\"$match\": { \""+ word +"\" : true   }  }  " ;
 						}
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

					//tmp_filter_it--;
					//cout << "\n WORD:  " << ( tmp_filter_it->first) << "\n";
					//cout << "\n Bingo  OP1" << op1 << "  find: " << op1.find("OPT") << "\n";
					
					
					
					
					
					if (opera != sumOperator && opera != differenceOperator && opera != factorOperator && opera != divisionOperator)
					{
						string tmp_op1 = op1, tmp_op2 = op2;
						
						if (tmp_op1 != "")
							tmp_op1.erase(1,1);
						if (tmp_op2 != "")	
							tmp_op2.erase(1,1);
						
						if (opera == "$bound")
							str_filtering_part_of_the_query +=
	 							",{\"$match\": { \""+ word +"\" : true   }  }  " ;
	 					else
	 					{
						if ( op1.find('$') != string::npos &&  op1.find("OPT") != string::npos )
							str_filtering_part_of_the_query +=
 							",{\"$match\": { \"$or\" : [ {   \""+ word +"\" : true   }, { "+ tmp_op1 +" : [ ]  } ] }}  " ;					
						else if ( op2.find('$') != string::npos &&  op2.find("OPT") != string::npos )
							str_filtering_part_of_the_query +=
 							",{\"$match\": { \"$or\" : [ {   \""+ word +"\" : true   }, { "+ tmp_op2 +" : [ ]  } ] }}  " ;
 						else
							str_filtering_part_of_the_query +=
 							",{\"$match\": { \""+ word +"\" : true   }  }  " ;
						}					
					
					
						//str_filtering_part_of_the_query +=
 						//",{\"$match\": { \""+ word +"\" : true   }  }  " ;
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


	//cout << " \n\n FILTER :  " << str_filtering_part_of_the_query << "\n\n";

	//cout << " \n\n MULTI-VAR :  " << str_multi_valued_pre << "\n\n";
	
	
	
	
	

				
				
				

			std::string str_sort_part_of_the_query  = "{  \"$sort\": {";
			std::string str_skip_part_of_the_query  = "{  \"$skip\":  ";
			std::string str_limit_part_of_the_query = "{ \"$limit\":  ";
			string tmp_pre = "";
			
			//cout << "\n limit 1 : " << str_limit_part_of_the_query << "\n";

		std::map < int, std::pair<int, std::string> >::iterator map_modifiers_it = map_modifiers_local.begin();
		while (map_modifiers_it != map_modifiers_local.end())
		{
			
			
			//str_sort_part_of_the_query  = "{  \"$sort\": {";
			//str_skip_part_of_the_query  = "{  \"$skip\":  ";
			//str_limit_part_of_the_query = "{ \"$limit\":  ";
			//tmp_pre = "";


	            	switch ( std::get<0>(map_modifiers_it->second) )
			{            	
        		    	case (0):
        		    		//std::cout << "ASC: " << std::get<1>(map_modifiers_it->second) << "\n";
					if (str_sort_part_of_the_query.find('1') != string::npos)
						str_sort_part_of_the_query += ",";
					
        				it_pre_linked_map = pre_linked_map.begin();
					while (it_pre_linked_map != pre_linked_map.end())
					{
						if (std::get< 1 >( it_pre_linked_map-> first ) == std::get<1>(map_modifiers_it->second) )
						{
							tmp_pre = std::get< 2 >( it_pre_linked_map-> first );
							
							//cout << "  \n tmp_pre  :  " << tmp_pre << "\n";
							
							
							boost::replace_all(tmp_pre, "\"", "");			
							if (it_pre_linked_map-> second != "")
							{
								if (set_optional_predicate.find("\""+tmp_pre+"\"") != set_optional_predicate.end())	
									str_sort_part_of_the_query += "\""+it_pre_linked_map-> second + "\": 1";
								else
									str_sort_part_of_the_query += "\""+it_pre_linked_map-> second +"."+ tmp_pre + "\": 1";														
							}
							else
								str_sort_part_of_the_query += "\"" + tmp_pre + "\": 1";

						}
					it_pre_linked_map++;
					}

        		    		break;
        		    		
        		    	case (1):
        		    		//std::cout << "DESC: " << std::get<1>(map_modifiers_it->second) << "\n";

					if (str_sort_part_of_the_query.find('1') != string::npos)
						str_sort_part_of_the_query += ",";
					
        				it_pre_linked_map = pre_linked_map.begin();
					while (it_pre_linked_map != pre_linked_map.end())
					{
						if (std::get< 1 >( it_pre_linked_map-> first ) == std::get<1>(map_modifiers_it->second) )
						{
							tmp_pre = std::get< 2 >( it_pre_linked_map-> first );
							boost::replace_all(tmp_pre, "\"", "");
														if (it_pre_linked_map-> second != "")
							{
								if (set_optional_predicate.find(tmp_pre) != set_optional_predicate.end())	
									str_sort_part_of_the_query += "\""+it_pre_linked_map-> second + "\": -1";
								else
									str_sort_part_of_the_query += "\""+it_pre_linked_map-> second +"."+ tmp_pre + "\": 1";														
							}
							else
								str_sort_part_of_the_query += "\"" + tmp_pre + "\": -1";

							
										
							//if (it_pre_linked_map-> second != "")
							//	str_sort_part_of_the_query += "\""+ it_pre_linked_map-> second +"."+ tmp_pre + "\": -1";
							//else
							//str_sort_part_of_the_query +=  "\"" + tmp_pre + "\": -1";
							
						}
					
					it_pre_linked_map++;
					
					}

        		    		break;
        		    	case (2):
        		    		//std::cout << "OFFSET: " << std::get<1>(map_modifiers_it->second) << "\n";

        		    		str_skip_part_of_the_query += std::get<1>(map_modifiers_it->second) + "}";
        		    		
        		    		
        		    		break;
        		    	case (3):
        		    		//std::cout << "LIMIT: " << std::get<1>(map_modifiers_it->second) << "\n";
					
					//cout << "\n limit 2 : " << str_limit_part_of_the_query << "\n";
					str_limit_part_of_the_query += std::get<1>(map_modifiers_it->second) + "}";
					//cout << "\n limit 3 : " << str_limit_part_of_the_query << "\n";
        		    		
        		    		break;
        	    	}
            	
            	map_modifiers_it++;
            	}
            	
            	            	            		
	str_sort_part_of_the_query += "}}";
	
	mql_query += str_filtering_part_of_the_query;
	
	if (str_sort_part_of_the_query.find('1') != string::npos)
		mql_query += "," + str_sort_part_of_the_query;
	
	if (str_skip_part_of_the_query.find('}') != string::npos)
		mql_query += "," + str_skip_part_of_the_query;

	if (str_limit_part_of_the_query.find('}') != string::npos)
		mql_query += "," + str_limit_part_of_the_query;

	//cout << "\n limit 4 : " << str_limit_part_of_the_query << "\n";	
	
	mql_query +=  "]).pretty()";


	


return mql_query;
}


#endif





