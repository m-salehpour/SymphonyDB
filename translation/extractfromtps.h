#ifndef EXTRACTFROMTPS_H
#define EXTRACTFROMTPS_H


#include <string>
#include <iostream>

using namespace std;

//******************************************************
//
//******************************************************
std::string get_subject_without_uri(string triple ){



	unsigned first, last;
	string subject;
	static const size_t npos = -1;
	
		first = 0;
		last = triple.find(">");
		subject = triple.substr (0,last);
		triple = triple.substr (last+1,triple.length());
		while ( subject.find("/") != string::npos )
		{
		
			first = subject.find("/");

			//cout << "*****First: " << first << "  Length:  " << subject.length() << " Subject:  " << subject << endl;
			
			subject = subject.substr (first+1, subject.length());

			//cout << "After ####### Length:  " << subject.length() << " Subject:  " << subject << endl;
			
			
			
			
		}

/*
		subject.erase(std::remove(subject.begin(), subject.end(), '/'), subject.end());				
		subject.erase(std::remove(subject.begin(), subject.end(), '\"'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '\''), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '\\'), subject.end());				
		subject.erase(std::remove(subject.begin(), subject.end(), ';'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '.'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '$'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '*'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '<'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '>'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), ':'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '|'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '?'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '_'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '%'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '-'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '!'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '~'), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), '#'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '^'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '&'), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), '('), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), ')'), subject.end());
		subject.erase(std::remove(subject.begin(), subject.end(), '+'), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), '='), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), '['), subject.end());				
		subject.erase(std::remove(subject.begin(), subject.end(), ']'), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), '{'), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), '}'), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), ','), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), '\t'), subject.end());		
		subject.erase(std::remove(subject.begin(), subject.end(), ' '), subject.end());													
*/		
		
						
		if ( subject.find(':') != string::npos)
			subject = subject.substr (subject.find(':')+1, subject.length());
		
		subject = "\"" + subject + "\"";

return subject;
}




//******************************************************
//
//******************************************************
std::string get_predicate_without_uri(string triple ){



	unsigned first, last;
	string predicate;
		static const size_t npos = -1;

		first = 0;
		last = triple.find(">");
		predicate = triple.substr (0,last);
		//triple = triple.substr (last+1,triple.length());
		while (predicate.find("/") != string::npos)
		{
			first = predicate.find("/");
			predicate = predicate.substr (first+1, predicate.length());
			//cout << subject << endl;
		}


		if ( predicate.find("#") != string::npos )
			predicate = predicate.substr ((predicate.find("#"))+1, predicate.length());

		if ( predicate.find(':') != string::npos )
			predicate = predicate.substr ((predicate.find(':'))+1, predicate.length());


		predicate = "\"" + predicate + "\"";
		//cout << predicate << endl;

	
return predicate;
}






//******************************************************
//
//******************************************************



bool is_number(string str){

	for(size_t i=0; i < str.length() ; i++)
	{
		if (!isdigit( str[ i ] ))
			return false;
	}

return true;
}//is_number










//******************************************************
//
//******************************************************
std::string get_object_without_uri(string triple, char homepage_indicator){


	unsigned first, last;
	string object;
	char flag = 't';


	first = 0;
	if (triple.find('?') != string::npos )
	{
		object = triple;
		
	}
	else
	{
		if (homepage_indicator == 'Y')
		{
			first = triple.find("<");
			last = triple.find(">");
			object = triple.substr (first+1, last-3);
			//object = "\"" + object + "\"";
			homepage_indicator = 'N';


		}else 
		{
		
		if ( (triple.find(">") != string::npos )  && (triple.find("^") == string::npos) )
		{


			object = triple.substr (0,triple.find(">"));
			if (object.substr(object.length()-2,object.length()).find("/") <= object.length())
				object = triple.substr (0,triple.find(">")-1);


			//while (first < object.length())
			//{
			//	first = object.find("/");
			//	object = object.substr (first+1, object.length());
			//	//cout << subject << endl;
			//}
			
			if (object.find("/") != string::npos)
				object = object.substr (object.rfind("/")+1, object.length());
			
				if ( object.find("#") <= object.length())
				{
					first = object.find("#");
					object = object.substr (first+1, object.length());
				}

				//object = "\"" + object + "\"";
				
				triple = "";
		//cout << "\n Obj:  " << object <<   "\n";		
		}
		//--------------------------------------------------------------------
		 if (triple.find(">") != string::npos  && (triple.find("^") != string::npos ) )
		{
			//flag = 'f';
			
			first = triple.find("\"");			
			last  = triple.substr (first+1,triple.length()).find("\"");
			


			if (is_number(triple.substr (first+1,last-1)) || ( triple.substr (first+1,last).find(".") <= triple.substr (first+1,last).length() &&
			triple.substr (first+1,last).find(":") > triple.substr (first+1,last).length() )) 
			{
				object = triple.substr (first+1,last);
				//cout << "number-->" << object << "\n";
				flag = 'f';

			}else if ( triple.substr (first+1,last).find("-") <= triple.substr (first+1,last).length() )  
			{
				object = triple.substr (first+1,last);

		

					if (object.find("T") <= object.length())
						object = object.substr (0,object.find("T"));// + "\"";

					//object = "{\"$date\":\"" + object + "T00:00:00.000Z\"}";  //ISODate("2013-10-01T00:00:00.000Z"),
					//object = "ISODate(\"" + object + "T00:00:00.000Z\")";  //ISODate("2013-10-01T00:00:00.000Z"),
					//object = "\"" + object + "T00:00:00.000Z\"";  //ISODate("2013-10-01T00:00:00.000Z"),
					//object = "\"" + object + "\"";
			
				
			
			}else
			{
				
				object = triple.substr (first,last+2);			
						
			
			}

		
			

			
			


		triple = "";

		}
		///-------------------------------------------------
		
		 if (triple.find(">") == string::npos && triple.find("^") == string::npos && triple != "")
		{
			
			flag = 'f';
			
			first = triple.find("\"");			
			last  = triple.substr (first+1,triple.length()).find("\"");
			


			if (is_number(triple.substr (first+1,last)) || ( triple.substr (first+1,last).find(".") <= triple.substr (first+1,last).length() &&
			triple.substr (first+1,last).find(":") > triple.substr (first+1,last).length() )) 
			{
				object = triple.substr (first+1,last);
				//cout << "number-->" << object << "\n";
				//flag = 'f';

			}else if ( triple.find("-") != string::npos )  
			{
				object = triple.substr (first+1,last);



					if (object.find("T") <= object.length())
						object = object.substr (0,object.find("T"));// + "\"";

					object = "{\"$date\":\"" + object + "T00:00:00.000Z\"}";  //ISODate("2013-10-01T00:00:00.000Z"),
					//object = "ISODate(\"" + object + "T00:00:00.000Z\")";  //ISODate("2013-10-01T00:00:00.000Z"),
					//object = "\"" + object + "T00:00:00.000Z\"";  //ISODate("2013-10-01T00:00:00.000Z"),
					//object = "\"" + object + "\"";
			
				
			
			}else
			{
				
				/*first = triple.find("\"");
			//triple.substr (first+1,triple.length());
			//last = triple.find("\"");
			if (first < triple.length())
			{
				
				object = triple;//.substr (first,last);
				//return object;
			}
				
				object = triple.substr (first,last+2);			
				*/
				//cout << "number2-->" << object << "\n";
				object = triple;
				//flag = 'f';
			
			}

		
			
			
			
			triple = "";	

		}
		
		
		}
	/*
	
	if (flag != 'f')
	{
		object.erase(std::remove(object.begin(), object.end(), '\n'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\a'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\b'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\t'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\v'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\f'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\r'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\x1B'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\0'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\00'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\000'), object.end());
		
		object.erase(std::remove(object.begin(), object.end(), '\"'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '('), object.end());
		object.erase(std::remove(object.begin(), object.end(), ')'), object.end());
		//object.erase(std::remove(object.begin(), object.end(), '?'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\''), object.end());
		object.erase(std::remove(object.begin(), object.end(), '\\'), object.end());
		
		//boost::replace_all(name, "\"", "\\\"");			
		
		object.erase(std::remove(object.begin(), object.end(), '*'), object.end());				
		object.erase(std::remove(object.begin(), object.end(), '#'), object.end());						
		object.erase(std::remove(object.begin(), object.end(), ';'), object.end());
		object.erase(std::remove(object.begin(), object.end(), '%'), object.end());
		
		object = "\"" + object + "\"";
	
	}
	*/
	
	//cout << "\n triple: " << triple << "\n";
	//cout << "\n Obj:  " << object <<   "\n";		
	
	if ( object.find(':') != string::npos || triple.find(':') != string::npos)
		object = "\"" + object.substr (object.find(':')+1, object.length()) + "\"" ;
	

	if (flag != 'f')
		object = "\"" + object + "\"";
	
	

	} // else of '?'
	
	//cout << "\n Obj:  " << object <<   "\n";		
	return object;

}





















#endif
