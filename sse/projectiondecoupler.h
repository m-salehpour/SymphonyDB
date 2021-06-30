#ifndef PROJECTION_DECOUPLER_H    
#define PROJECTION_DECOUPLER_H    
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "cifs.h"           
#include "stringsplit.h"

using namespace std;
vector<string> sparql_query_projection(std::string sparql_query){

	

	
	string projection_query;
	int delimiter_length = 0;
	vector<string> elems;
	char qm_keyword = '?';
	
	
	int keyword_exist_first_qm = sparql_query.find('?');
	
	std::string where_keyword = "WHERE" ;
	int keyword_exist_where = ci_find_substr( sparql_query , where_keyword, std::locale() );
	
	assert(keyword_exist_where != -1 && keyword_exist_first_qm != std::string::npos && "Whoops, select and { ould not be found --- > projectdecoupler.h file");
	
	
	projection_query = sparql_query.substr( keyword_exist_first_qm + delimiter_length, (keyword_exist_where - (keyword_exist_first_qm + delimiter_length) ));
	
	
	
	auto elems_tmp = split_to_words(projection_query , '?');
	
	//elems_tmp.erase(elems_tmp.begin()); //a trim added to split instead! for the space before first '?'
	
	for(string const& word : elems_tmp )
	        elems.push_back("?"+word);
	
	return elems;



}
#endif
