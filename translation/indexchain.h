#ifndef INDEXCHAIN_H
#define INDEXCHAIN_H



#include <set>


string get_string_index_starter_node_chain(std::vector<triple_pattern> get_triple_patterns_structs_local_index){

//*****************************************************

	set<string> subject_set,object_set;
	string str_index_starter_node;	

		


	for (size_t i = 0; i < get_triple_patterns_structs_local_index.size(); i++)
	{
	
		if ( object_set.find(get_triple_patterns_structs_local_index[i].object) == object_set.end() ) object_set.insert(get_triple_patterns_structs_local_index[i].object);
	}
	
	
	
	

	for (size_t i = 0; i < get_triple_patterns_structs_local_index.size(); i++)
	{
	
		if ( object_set.find(get_triple_patterns_structs_local_index[i].subject) == object_set.end() )
		{
				str_index_starter_node = get_triple_patterns_structs_local_index[i].subject;
				break;
				
		}
	}





return str_index_starter_node;

}

int get_index_starter_node_chain(std::vector<triple_pattern> get_triple_patterns_structs_local_index){

//*****************************************************

	set<string> subject_set,object_set;
	int index_starter_node;	

		


	for (size_t i = 0; i < get_triple_patterns_structs_local_index.size(); i++)
	{
	
		if ( object_set.find(get_triple_patterns_structs_local_index[i].object) == object_set.end() ) object_set.insert(get_triple_patterns_structs_local_index[i].object);
	}
	
	
	
	

	for (size_t i = 0; i < get_triple_patterns_structs_local_index.size(); i++)
	{
	
		if ( object_set.find(get_triple_patterns_structs_local_index[i].subject) == object_set.end() )
		{
				index_starter_node = i;
				break;
				
		}
	}



//cout << "\nstart:   " << index_starter_node  << "\n";

	
	





/*
	bool starter_node_found = false;
			int index_starter_node;	
						
			for (size_t j=0; j < get_triple_patterns_structs_local_index.size(); j++)
			{
				
				std::string tmp_sub = get_triple_patterns_structs_local_index[j].subject;

				for (size_t i = 0; i < get_triple_patterns_structs_local_index.size(); i++)
				{
					if ( get_triple_patterns_structs_local_index[i].object == tmp_sub )	break;
									
					if ( (i+1) == get_triple_patterns_structs_local_index.size() )
					{
						starter_node_found = true;
						index_starter_node = j;										
					}
				}
			 if (starter_node_found) break;
			}

*/
return index_starter_node;

}

int get_single_index_end_node_chain(std::vector<triple_pattern> get_triple_patterns_structs_local_index){

			int index_end_node;	
			bool end_node_found = false;
						
			for (size_t j=0; j < get_triple_patterns_structs_local_index.size(); j++)
			{
				
				std::string tmp_obj = get_triple_patterns_structs_local_index[j].object;

				for (size_t i = 0; i < get_triple_patterns_structs_local_index.size(); i++)
				{
					if ( get_triple_patterns_structs_local_index[i].subject == tmp_obj )	break;
									
					if ( (i+1) == get_triple_patterns_structs_local_index.size() )
					{
						end_node_found = true;
						index_end_node = j;										
					}
				}
			 if (end_node_found) break;
			}

			//cout << "\nstart:   " << index_starter_node << "\tend:  " << index_end_node << "\n";


return index_end_node;

}



set<string> get_set_index_end_node_chain(std::vector<triple_pattern> get_triple_patterns_structs_local_index){

			set<string> object_set;			
			std::string tmp_obj;
		
			for (size_t j=0; j < get_triple_patterns_structs_local_index.size(); j++)
			{
				
				tmp_obj = get_triple_patterns_structs_local_index[j].object;

				for (size_t i = 0; i < get_triple_patterns_structs_local_index.size(); i++)
				{
					if ( get_triple_patterns_structs_local_index[i].subject == tmp_obj )	break;
									
					if ( (i+1) == get_triple_patterns_structs_local_index.size() )
						if ( object_set.find(tmp_obj) == object_set.end() )
							object_set.insert(tmp_obj);						
					
				}

			}

			//cout << "\nstart:   " << index_starter_node << "\tend:  " << index_end_node << "\n";


return object_set;

}





#endif
