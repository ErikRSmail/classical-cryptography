#pragma once //TODO implement

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "assert.h"
#include "monoalphabetic_substitution.hpp"

class simple_keyword_substitution : public monoalphabetic_substitution{
public:
    simple_keyword_substitution(const std::string& key) : monoalphabetic_substitution(generate_map(key)){}
private:
    std::map<char,char> generate_map(const std::string& key);
};

std::map<char,char> simple_keyword_substitution::generate_map(const std::string& key){
    assert(cipher::is_valid_key(key));
    std::string str = format_key(key);//converts any string to all lowercase w/ duplicates removed
    std::map<char,char> m;
    std::vector<char> v;
    for(int i = 0; i<str.size();i++){v.push_back(str.at(i)-32);}
    std::sort(v.begin(),v.end(),std::greater<char>());
    for(int i=0; i<=25;i++){//loop over 'a'-'z'
        if(i < str.size()){//if we haven't yet pushed all key chars to map
            m[i+97] = char(str.at(i) - 32);//then push uppercase ascii version of key char
        }
        else if(std::count(str.begin(),str.end(),char(i+97-v.size()))){//if we already pushed value from string
            v.pop_back();
            m[i+97] = i+65-v.size();
        }
        else{
            m[i+97] = i+65-v.size();
        }
    }//yeah this is disgusting hackery. TODO rewrite
    
    return m;
}