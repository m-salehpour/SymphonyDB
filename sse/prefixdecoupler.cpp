#include <iostream>
#include "prefixdecoupler.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "cifs.h"           


using namespace std;
vector<string> sparql_query_name_spaces(std::string sparql_query){

	
	string str_error_msg = "error";
	string namespace_token;
	vector<string> elems;

	string prefix_query;
	int delimiter_length = 6;

	std::string select_keyword = "SELeCt" ;
	int keyword_exist_select = ci_find_substr( sparql_query , select_keyword, std::locale() );
	
	std::string prefix_keyword = "PREFIX" ;
	int keyword_exist_prefix = ci_find_substr( sparql_query , prefix_keyword, std::locale() );
	
	
	//assert(keyword_exist_prefix != -1 && keyword_exist_select != -1 && "Whoops, select and { ould not be found --- > prefixdecoupler.h file");
	
	if (keyword_exist_prefix == -1 || keyword_exist_select == -1)
	{
		elems.push_back(str_error_msg); //return nothing!
		return elems;

	}
	
		

	prefix_query = sparql_query.substr(keyword_exist_prefix+delimiter_length, ((keyword_exist_select-6) - keyword_exist_prefix ));
	

	

	
	
	
	
	while ((keyword_exist_prefix = ci_find_substr( prefix_query , prefix_keyword , std::locale() )) !=-1)
	{
		namespace_token = prefix_query.substr(0, keyword_exist_prefix);
		elems.push_back(namespace_token);
		prefix_query = prefix_query.substr(keyword_exist_prefix+delimiter_length,prefix_query.length());
		
			
	}
	elems.push_back(prefix_query);
	
	
	return elems;



}
