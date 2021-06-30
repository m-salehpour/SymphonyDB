#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "stringsplit.h"
#include <boost/algorithm/string.hpp>
#include "cifs.h"


using namespace std;


vector<string>  split_to_words(string query, char delim){
	
	
	stringstream ss(query);
	vector<string> elems;
	string item;
	while (getline(ss, item, delim))
	{
		boost::trim(item);
		if (item.length() > 1) //the space after the last triple pattern will be deleted
			elems.push_back(item);
	}
	return elems;

}



vector <vector<string>>  split_to_words(string query){
	
	
	
	vector<string> elems;
	vector<string> filter_elems;
	vector<string> optional_elems;
	vector < vector<string>> output_elements;
	boost::trim(query);
	int point_pos, delimiter_pos, less_count=0, great_count=0, flag=0, open_para=0, close_para=0, tmp_open_para=0, open_optional=0;;
	bool filter_flag=false;
	string str_tmp_check="";
	bool optional_flag=false;
        string opt_keyword = "optional";
        string tmp_filter= "filter";

	////cout << "\nQuery: " << query << endl;
		
	point_pos = query.find('.');
	int opt_f1 = ci_find_substr( query,  opt_keyword, std::locale());
	if (point_pos == std::string::npos && opt_f1 == -1)
	{
	    elems.push_back(query);
	    ////cout << "\n inside  :" << query << "  f1:  " << opt_f1 <<"\n";
	    
	}
	else
	{
	    while ( point_pos != std::string::npos && query.size()!=1)
	    {
	    
                flag = query.size();
                for(std::string::size_type i = 0; i < query.size(); ++i)
                {
    
		    int opt_f1 = ci_find_substr( query,  opt_keyword, std::locale());
                    if ( i == opt_f1 && !optional_flag)
                    	optional_flag = true;
                    
                    
                    
                    if (query[i] == '{' && optional_flag) open_optional = i;
                    if (query[i] == '}' && optional_flag)
                    {
	                    optional_flag = false;
	                    optional_elems.push_back( query.substr( (open_optional+1) , (i - (open_optional+1)) ) );
	                    
                 	    //cout << "\n\nAlready inserted: " << query.substr( (open_optional+1) , (i - (open_optional+1)) ) << "\n";
                 	    //cout << "\n Flag size: " << flag << "    Query size: " << query.size() << "\n";
                 	    //cout << "\n Start optional: " << (open_optional+1) << "    end optional " << (i - (open_optional+1)) << "\n" ;
                 	    //cout << "\n i: " << i << "    query.length " << query.length()<< "\n" ;
	                    
	                    if ((i+1) == query.length()) break;
	                    
				    //cout << " \n\n OPT BLOCK?  :  " << query.substr( (open_optional+1) , (i - (open_optional+1)) ) << "\n";
     				    query = query.substr(i+1,query.length());
				    boost::trim(query);
				    //cout << " \n\n after OPT query?  :  " << query;
			   
			    break;
                    }
                      
                    
                    if (query[i] == '<' && !filter_flag) less_count++;  // not needed to assign a zero to it at each llop
                    if (query[i] == '>' && !filter_flag) great_count++; // not needed to assign a zero to it at each llop
			
		    if (query[i] == '(' )
		    {
		    	if (!filter_flag){  tmp_open_para=i; filter_flag=true;}
		    	open_para++;
		    }
		    if (query[i] == ')' ) close_para++;

		    if ( filter_flag && open_para == close_para  )
		    {
			//cout << "\nstring: " << query.substr(tmp_open_para,(i+1)-tmp_open_para) << endl;
			filter_flag=false;
			filter_elems.push_back(query.substr(tmp_open_para,(i+1)-tmp_open_para));
			if (!optional_flag)
			{
				query = query.substr(i+1,query.length());
				boost::trim(query);
			//cout << "\n2nd string: " << query << endl;
                        	break;
                        }
                        else
                        {
				//cout << " \n\n before   :" << query << "\n";
                        	
	                        string tmp_fr = query.substr(0,ci_find_substr( query,  tmp_filter, std::locale()));
      	                        string tmp_sec = query.substr(i+1,query.length());
      	                        query = tmp_fr + tmp_sec ;
      	                        boost::trim(query);
       				//cout << " \n\n AFTEr   :" << query << "\n";
                        
                        }
		
		   }			
                    
                        
                        
                        
                        if ( (query[i] == '.')  && (less_count == great_count) && (i > 1) && !optional_flag && !filter_flag)   
                        {
                            delimiter_pos = i;
                            elems.push_back(query.substr(0,i));
                            query = query.substr(i+1,query.length());
                            boost::trim(query);
			    //cout << "\nQQQ: " << query << endl;
                            break;
                        }
                }
                
                //cout << "\n Flag size: " << flag << "    Query size: " << query.size() ;
	        if (flag == query.size())
	        {
	        	//cout << " \n\n BREAK  :\t" << query << "\n" ;
	        	            //cout << "\n Flag size: " << flag << "    Query size: " << query.size() ;
	        	break;
	        	            
	        }    

	        

	        
        	if (query.size() > 1)
	        {	point_pos = query.find('.');
        		boost::trim(query);
        	}
        	else
        	       	break;
	        
	        


    
    
        }
        
             ////cout << "\n Flag size: " << flag << "    Query size: " << query.size() ;
    }
    
    

            
	if (flag != query.size() && query.size() > 1)
	{


		int opt_f1 = ci_find_substr( query,  opt_keyword, std::locale());
	        
	        
	        
		if (query.find('(') == std::string::npos && opt_f1 == -1)
		{	   
		    elems.push_back(query);
		}
		else if (opt_f1 != -1)
		{
			optional_elems.push_back(query.substr( query.find('{')+1, (query.find('}') - (query.find('{')+1) ) ));
		}
		else if (query.find('(') != string::npos)
		{
		    filter_elems.push_back(query.substr(query.find('('),query.length()));
		}

		
	}
	

	//for(string const& word : filter_elems )
	//	//cout << "\nFilter:  " << word <<"\n\n";
	
	//for(string const& word : elems )
	//	//cout << "\nTP:  " << word <<"\n\n";
	
	//for(string const& word : optional_elems )
	//	//cout << "\nOPTIONAL:  " << word <<"\n\n";
	
	
	
	//(here be dragons!) The following vectors are statically called/indexed in next stages!
	
	//if (!elems.empty())
		    output_elements.push_back(elems);

	//if (!filter_elems.empty())
	  output_elements.push_back(filter_elems);

	//if(!optional_elems.empty())
	 output_elements.push_back(optional_elems);


	return output_elements;

}


