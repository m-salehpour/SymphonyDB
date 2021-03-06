#ifndef TOSSE_H
#define TOSSE_H


#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include "qsf.h"
#include "prefixdecoupler.h"
#include "projectiondecoupler.h"
#include "stringsplit.h"
#include "cifs.h"
#include "tpdecoupler.h"
#include <locale>
#include "../translation/extractfromtps.h"
#include <map>
#include "modifiersdecouple.hpp"
using namespace std;
namespace qi    = boost::spirit::qi;

class tosse
{

public:

std::map<std::string, std::tuple< std::string, std::string >>  get_predicate_map(std::string sparql_query_original_form, std::vector<triple_pattern> get_triple_patterns_structs_local_l) //vector<string>
{
	std::map<std::string, std::tuple< std::string, std::string >> predicate_map;
	int int_tmp_key = 0;
	std::string sub, pre, obj;
	char homepage_indicator_char = 'N';
	//auto get_triple_patterns_structs_local_l = get_triple_patterns_structs(sparql_query_original_form);

			for (size_t i=0; i < get_triple_patterns_structs_local_l.size();i++)
			{


				// comment the following lines to not shorten URIs!			
				//------------------------------------------------
				homepage_indicator_char = 'N';
				sub = get_subject_without_uri(get_triple_patterns_structs_local_l[i].subject);
				pre = get_predicate_without_uri(get_triple_patterns_structs_local_l[i].predicate);
				if ( pre == "\"page\"")
					homepage_indicator_char = 'Y';
				obj = get_object_without_uri(get_triple_patterns_structs_local_l[i].object, homepage_indicator_char);
				//------------------------------------------------
				
				////cout << "\n obj: " << obj << "\n";
				if (pre.find('?') == std::string::npos)					
				{			
					////cout << "  sub:  " << sub 
					//     << "  pre:  " << pre 
					//     << "  obj:  " << obj << endl;

					if (obj.find('?') != std::string::npos)
						predicate_map.emplace( ( "key_" + std::to_string(++int_tmp_key) ) , std::make_tuple(pre, obj) );
					
					     
				}
			}// for loop triple_pattenrs

	
	

	return predicate_map;
}


std::vector<string> get_name_spaces(std::string sparql_query_original_form) //vector<string>
{


		
	bool is_select_form = sparql_query_form_check(sparql_query_original_form);
	vector<string> name_spaces_local;
		
	
			
	if (is_select_form)
	{	
		
		name_spaces_local = sparql_query_name_spaces(sparql_query_original_form);
		
		

		cout << "\n" <<"################################"<< "\n";
		cout << "\n" <<"      name_spaces               "<< "\n";
		cout << "\n" <<"################################"<< "\n";
		for(string const& word : name_spaces_local )
		{
			if ( word != "error")
				cout << word << "\n";
			else
				break;
		}

		
		
	}






	return name_spaces_local;


}

std::vector<string> get_projection_variables(std::string sparql_query_original_form)
{

	
	bool is_select_form = sparql_query_form_check(sparql_query_original_form);
	vector<string> projection_variables_local;
		
	
			
	if (is_select_form)
	{	
		
	



		projection_variables_local = sparql_query_projection(sparql_query_original_form);		

				        
		        
    		cout << "\n" <<"################################"<< "\n";
		cout << "\n" <<"      projection_variables               "<< "\n";
		cout << "\n" <<"################################"<< "\n";
		for(string const& word : projection_variables_local )
		        cout << word << "\n";

		        
	}
	
	return projection_variables_local;



}

std::vector<triple_pattern> get_triple_patterns_structs (std::string sparql_query_original_form)
{
		
	bool is_select_form = sparql_query_form_check(sparql_query_original_form);
	vector<triple_pattern> triple_patterns_structs_local;

		
	
			
	if (is_select_form)
	{	
		
		//cout << "\n X1 Flag size: " ;	
		triple_patterns_structs_local = sparql_query_tp(sparql_query_original_form);		
		//cout << "\n X2 Flag size: " ;	
		
		
		/*
    		cout << "\n" <<"################################"<< "\n";
		cout << "\n" <<"        triple patterns         "<< "\n";
		cout << "\n" <<"################################"<< "\n";   
		for (size_t i=0; i < triple_patterns_structs_local.size();i++)
			cout << triple_patterns_structs_local[i].subject
			     << "  " + triple_patterns_structs_local[i].predicate
			     << "  " + triple_patterns_structs_local[i].object
			     << "\n"<<"\n";
		*/
	
		
	
	}
  	
  	return 	triple_patterns_structs_local;


}




vector<string> get_sparql_query_filters(std::string sparql_query_original_form)
{

	bool is_select_form = sparql_query_form_check(sparql_query_original_form);
	vector<string> get_filetrs = sparql_query_filters(sparql_query_original_form);
	
		////cout << "\n INSIDE CHECK:  SIZE:    " << get_filetrs.size() << "\n";

	if (!is_select_form)
		cout << "Error!" << endl;

	
		
	return get_filetrs;
	

}


vector<string> get_sparql_query_optional(std::string sparql_query_original_form)
{

	bool is_select_form = sparql_query_form_check(sparql_query_original_form);
	
	////cout << "\n Bef INSIDE CHECK:  SIZE:    "/ << get_filetrs.size() << "\n";
	
	vector<string> get_optional = sparql_query_optional(sparql_query_original_form);
	
	////cout << "\n Aft INSIDE CHECK:  SIZE:    ";// << get_filetrs.size() << "\n";

	if (!is_select_form)
		cout << "Error!" << endl;

	//cout << "\n\nAfter Size  :"<< get_optional.size();
		
	return get_optional;
	

}




std::map < int, std::pair<int, std::string> > get_sparql_query_modifiers(std::string sparql_query_original_form)
{

	string str_mod = sparql_query_original_form.substr( sparql_query_original_form.rfind('}')+1, sparql_query_original_form.length());
	
	return get_modifiers(str_mod, qi::space);

}








};





#endif

