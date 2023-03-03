#pragma once

#include <map>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include "substitution.hpp"

class random_substitution : public substitution{
public:
    random_substitution() : substitution(random_map()){}
    random_substitution(const std::string& seed) : substitution(random_map(seed)){}
private:
    std::map<char,char> random_map();
    std::map<char,char> random_map(const std::string& seed);
};
std::map<char,char> random_substitution::random_map(){//generate random mapping from 'a'-'z' -> 'A'-'Z'
    std::map<char,char> m;
    std::mt19937 rng(std::random_device{}());
    std::vector<char> v;
    for(int i = 65;i<=90;i++){v.push_back(char(i));}//fill a vec with 'A' through 'Z' in order
    std::shuffle(std::begin(v), std::end(v), rng);
    for(int i = 97; i<=122; i++){//loop from 'a' to 'z' 
        m[i] = v[i-97];
    }
    return m;
}

std::map<char,char> random_substitution::random_map(const std::string& seed){//generate random mapping from 'a'-'z' -> 'A'-'Z'
    std::map<char,char> m;

    std::seed_seq seq (seed.begin(),seed.end());
    std::mt19937 rng(seq);
    
    std::vector<char> v;
    for(int i = 65;i<=90;i++){v.push_back(char(i));}//fill a vec with 'A' through 'Z' in order
    std::shuffle(std::begin(v), std::end(v), rng);
    for(int i = 97; i<=122; i++){//loop from 'a' to 'z' 
        m[i] = v[i-97];
    }
    return m;
}