#pragma once

#include <map>
#include "substitution.hpp"

class random_substitution : public substitution{
public:
    random_substitution() : substitution(random_map()){}
private:
    std::map<char,char> random_map();
};
std::map<char,char> random_substitution::random_map(){
    std::map<char,char> m;
    for(int i = 97; i<=122; i++){//loop from 'a' to 'z' 
        m[i] = i-32;//TODO fill with random int from 65-90, which is ascii 'A' to 'Z'
    }
    return m;
}