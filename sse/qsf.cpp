#include "qsf.h"  
#include<bits/stdc++.h>

bool sparql_query_form_check(std::string sparql_query){

	
	transform(sparql_query.begin(), sparql_query.end(), sparql_query.begin(), ::toupper); 
	if (sparql_query.find("SELECT") != std::string::npos)
		return 1 ;	
	else
        	return 0;
}
