#pragma once

#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include "assert.h"
#include "monoalphabetic_substitution.hpp"

class keyword_columnar_substitution : public monoalphabetic_substitution{
public:
    keyword_columnar_substitution(const std::string& key) : monoalphabetic_substitution(generate_map(key)){}
private:
    std::map<char,char> generate_map(const std::string& key);
};
std::map<char,char> keyword_columnar_substitution::generate_map(const std::string& key){
    assert(is_valid_key(key));
    std::string k = format_key(key);
    std::vector<std::vector<char>> columns;
    std::map<char,char> m;
    for(int i=0;i<k.size();i++){
        std::vector<char> column;
        column.push_back(k.at(i));
        columns.push_back(column);
    }
    int cycler = 0;
    for(int i=97;i<=122;i++){
        if(!std::count(k.begin(),k.end(),char(i))){//if we have not already pushed char(i) to columns
            columns.at(cycler).push_back(i);
            cycler = (cycler + 1) % k.size();
        }
    }
    int count = 0;
    for(auto& v : columns){
        for(char& c : v){
            m[count + 97] = c-32;
            count++;
        }
    }
    return m;
}