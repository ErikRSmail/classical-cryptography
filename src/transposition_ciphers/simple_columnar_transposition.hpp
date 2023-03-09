#pragma once

#include <string>
#include "keyword_columnar_transposition.hpp"

class simple_columnar_transposition : public keyword_columnar_transposition{
public:
    simple_columnar_transposition(int key) : keyword_columnar_transposition(gen_key(key)){}
private:
    std::string gen_key(int key);
};

std::string simple_columnar_transposition::gen_key(int key){
    std::string str;
    for(int i=0;i<key;i++){
        str.push_back(i+97);
    }
    return str;
}

