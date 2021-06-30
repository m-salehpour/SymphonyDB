#ifndef STRING_SPLIT_H
#define STRING_SPLIT_H

#include <vector>
#include <string>

using namespace std;
vector<vector<string>>  split_to_words(const string query);

vector<string>  split_to_words(string query, char delim);

#endif
