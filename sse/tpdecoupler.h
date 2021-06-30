#ifndef TPDECOUPLER_H
#define TPDECOUPLER_H


#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>



using namespace std;

struct triple_pattern {
	
	string subject;
	string predicate;
	string object;

	triple_pattern(const string s, const string p, const string o):	subject(s),predicate(p),object(o){}

};



std::string triple_pattern_global;
vector<triple_pattern> tps;
	
void decouple_triple();
std::string get_first();



vector<string> sparql_query_filters(std::string sparql_query){

	string tp_query;
	vector<string> filters;

	int keyword_exist_start_bracket = sparql_query.find('{');
	
	int keyword_exist_finish_bracket = sparql_query.rfind('}');

	assert(keyword_exist_finish_bracket != std::string::npos && keyword_exist_start_bracket != std::string::npos && "Whoops, brackets do not exists in the PARQL query --- > tpdecoupler.h file");
	
	tp_query = sparql_query.substr( keyword_exist_start_bracket + 1, (keyword_exist_finish_bracket - (keyword_exist_start_bracket + 1) ));
	
	
	
	
	auto tp_tmp = split_to_words(tp_query);

	cout << "\n" <<"################################"<< "\n";
	cout << "\n" <<"              Filters           "<< "\n";
	cout << "\n" <<"################################"<< "\n";   

	////cout << "\n TODECOUPLE INSIDE CHECK:  SIZE:    " << tp_tmp[1].size() << "\n";

	//for (int j=0; j<tp_tmp[1].size(); j++)
	//{
	
		for (int j=0; j<tp_tmp[1].size(); j++)
		{
		filters.push_back(tp_tmp[1][j]);
		cout << tp_tmp[1][j] <<"\n";
		}
	
	
	//}
		
	return filters;
	

}

vector<string> sparql_query_optional(std::string sparql_query){

	string tp_query;
	vector<string> optional;

	int keyword_exist_start_bracket = sparql_query.find('{');
	
	int keyword_exist_finish_bracket = sparql_query.rfind('}');

	assert(keyword_exist_finish_bracket != std::string::npos && keyword_exist_start_bracket != std::string::npos && "Whoops, brackets do not exists in the PARQL query --- > tpdecoupler.h file");
	
	tp_query = sparql_query.substr( keyword_exist_start_bracket + 1, (keyword_exist_finish_bracket - (keyword_exist_start_bracket + 1) ));
	
	
	
	
	auto tp_tmp = split_to_words(tp_query);

	//cout << "\n" <<"################################"<< "\n";
	//cout << "\n" <<"              Optioal           "<< "\n";
	//cout << "\n" <<"################################"<< "\n";   

	////cout << "\n TODECOUPLE INSIDE CHECK:  SIZE:    " << tp_tmp[2].size() << "\n";

	//for (int j=0; j<tp_tmp[1].size(); j++)
	//{
	
		for (int j=0; j<tp_tmp[2].size(); j++)
		{
		optional.push_back(tp_tmp[2][j]);
		//cout << tp_tmp[2][j] <<"\n";
		}
	
	
	//}
	
	////cout << "\n TODECOUPLE INSIDE CHECK:  SIZE:    " << tp_tmp[2].size() << "\n";
		
	return optional;
	

}



vector<triple_pattern> sparql_query_tp(std::string sparql_query){
	
	tps.clear();
	string tp_query;


	int keyword_exist_start_bracket = sparql_query.find('{');
	int keyword_exist_finish_bracket = sparql_query.rfind('}');

	assert(keyword_exist_finish_bracket != std::string::npos && keyword_exist_start_bracket != std::string::npos && "Whoops, brackets do not exists in the PARQL query --- > tpdecoupler.h file");
	
	tp_query = sparql_query.substr( keyword_exist_start_bracket + 1, (keyword_exist_finish_bracket - (keyword_exist_start_bracket + 1) ));
	
	////cout << "\n TP-->:    " << tp_query << "\n";
	
	//cout << "\n X3 Flag size: " ;	
	auto tp_tmp = split_to_words(tp_query);
	//cout << "\n X4 Flag size: " ;	
	
	//auto filter_expressions = get_filters_after_split_to_words();
	
	//for(string const& word : tp_tmp[1]  )
	//	//cout <<word <<"\n\n";
		
	
	
	
	for (int j=0; j<tp_tmp[0].size(); j++)
	{
		
		//cout << "\n TP:   " + tp_tmp[0][j] <<"\n\n";
	
		triple_pattern_global = tp_tmp[0][j];
		boost::trim(triple_pattern_global);
		decouple_triple();
		
		////cout << " Global:   " + triple_pattern_global <<"\n\n";
		//cin.ignore();		
		
		////cout << "---------------------------------\n";
		//auto decouple_tp_tmp = decouple_triple();
		//for(string const& dword : decouple_tp_tmp )
		//	//cout << dword << "\n";
		////cout << "---------------------------------\n";
		
		////cout << word + "no" <<"\n\n";
		//break;
		
	//cout << "\n X4 Flag size: " ;		
	}
	
	//cout << "\n X4 Flag size: " ;	

	
	return tps;

}



void decouple_triple(){

	

	
	
	////cout << "\ntriple: " << triple_pattern_global <<"\n";
	////cout << "\nsubject: " << get_first() <<"\n";

	//bool filter_flag = false;
	

	string subject = get_first();
	string predicate = get_first(); 
	string object = get_first(); 
	
	tps.push_back({subject, predicate, object});
	
	
}

	






std::string get_first(){

	int pos_space, pos_less_than, pos_greater_than, pos_single_quotation, pos_double_quotation, pos_qm, next_pos;
	string strtmp = triple_pattern_global.substr(1,triple_pattern_global.length());
	int dummy_big_value = 10000;
	string return_value =  "error";
	
	////cout << "\n the triple pattern  " << triple_pattern_global << "\n";
	
	switch (triple_pattern_global.front())
	{
		

		case '<':
			pos_greater_than = strtmp.find('>');
			//assert(pos_greater_than != std::string::npos && "tripledecoupler syntax error < without > ");
			
						
			return_value = triple_pattern_global.substr(0,pos_greater_than+2);

			////cout << "\n first part:  " << return_value << "\n";
						
			triple_pattern_global = triple_pattern_global.substr(pos_greater_than+2,triple_pattern_global.length());
			boost::trim(triple_pattern_global);
			
			////cout << "\n the rest part:  " << triple_pattern_global << "\n";
			
			//return triple_pattern_global.substr(0,pos_greater_than+2	);
			
			break;
	

		case '\'':
			pos_single_quotation = strtmp.find('\'');
			assert(pos_single_quotation != std::string::npos && "tripledecoupler syntax error \' without \' ");
			////cout << "\n first part:  " << triple_pattern_global.substr(0,pos_single_quotation+2) << "\n";
			
			return_value = triple_pattern_global.substr(0,pos_single_quotation+2);
						
			triple_pattern_global = triple_pattern_global.substr(pos_single_quotation+2,triple_pattern_global.length());
			boost::trim(triple_pattern_global);
			
			////cout << "\n the rest part:  " << triple_pattern_global << "\n";
			
			//return triple_pattern_global.substr(0,pos_single_quotation+2);
			
			break;
	

		case '\"':
			pos_double_quotation = strtmp.find('\"');
			assert(pos_double_quotation != std::string::npos && "tripledecoupler syntax error \" without \" ");
			////cout << "\n first part:  " << triple_pattern_global.substr(0,pos_double_quotation+2) << "\n";
			return_value = triple_pattern_global.substr(0,pos_double_quotation+2);
						
			triple_pattern_global = triple_pattern_global.substr(pos_double_quotation+2,triple_pattern_global.length());
			boost::trim(triple_pattern_global);
			
			////cout << "\n the rest part:  " << triple_pattern_global << "\n";
			
			//return triple_pattern_global.substr(0,pos_double_quotation+2);
			
			break;
			
		default:
		
			pos_space = strtmp.find(' ');
			if (pos_space == std::string::npos) pos_space = dummy_big_value;
			
			pos_less_than = strtmp.find('<');
			if (pos_less_than == std::string::npos) pos_less_than = dummy_big_value;
			
			pos_qm = strtmp.find('?');
			if (pos_qm == std::string::npos) pos_qm = dummy_big_value;
			
			pos_single_quotation = strtmp.find('\'');
			if (pos_single_quotation == std::string::npos) pos_single_quotation = dummy_big_value;

			pos_double_quotation = strtmp.find('\"');
			if (pos_double_quotation == std::string::npos) pos_double_quotation = dummy_big_value;

			next_pos = std::min({pos_space, pos_less_than, pos_qm,pos_single_quotation,pos_double_quotation});
			
			if ( next_pos == dummy_big_value ) next_pos = triple_pattern_global.length() - 1; //for variable objects
			
			return_value = triple_pattern_global.substr(0,next_pos+1);
					
			////cout << "\n first part:  " << return_value << "\n";
			
			
						
			triple_pattern_global = triple_pattern_global.substr(next_pos+1,triple_pattern_global.length());
			boost::trim(triple_pattern_global);
			
			////cout << "\n the rest part:  " << triple_pattern_global << "\n";
			
			//return triple_pattern_global.substr(0,next_pos+1);
			
		
			
			break;
	
	
	
	
	}

	return return_value ;

}



#endif



