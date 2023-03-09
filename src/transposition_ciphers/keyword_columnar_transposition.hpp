#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include "../cipher.hpp"

class keyword_columnar_transposition : public cipher{
public:
    keyword_columnar_transposition(const std::string& key);
private:
    std::vector<int> order;

    std::string encrypt_implementation(const std::string& plaintext);
    std::string decrypt_implementation(const std::string& ciphertext);
};
keyword_columnar_transposition::keyword_columnar_transposition(const std::string& key){
    assert(is_valid_key(key));
    std::string formatted_key = format_key(key);
    std::string sorted_key = formatted_key;
    std::sort(sorted_key.begin(), sorted_key.end());
    int loc;
    for(int i=0;i<formatted_key.size();i++){
        loc = sorted_key.find(formatted_key.at(i));
        order.push_back(loc);
    }
}
std::string keyword_columnar_transposition::encrypt_implementation(const std::string& plaintext){
    std::vector<std::string> columns;
    std::string pt = plaintext;
    for(int i=0;i<order.size();i++){
        std::string str;
        columns.push_back(str);
    }
    while(pt.size() % order.size() != 0){//pad
        pt.push_back('x');
    }
    int cycler=0;
    for(const char& c : pt){//fill columns
        columns.at(cycler).push_back(c);
        cycler++;
        if(cycler == order.size()){cycler=0;}
    }
    std::string ct;
    int j=0;
    for(int i=0;i<order.size();i++){
        while(i != order.at(j)){
            j++;
        }
        ct.append(columns.at(j));
        j=0;
    }
    for(int i=0;i<ct.size();i++){
        ct.at(i) -=32;
    }
    return ct;
}
std::string keyword_columnar_transposition::decrypt_implementation(const std::string& ciphertext){
    assert(ciphertext.size() % order.size() == 0);
    std::vector<std::string> columns;
    for(int i=0;i<order.size();i++){
        std::string str;
        columns.push_back(str);
    }
    int k=0;
    for(int i : order){
        columns.at(k) = ciphertext.substr(i*(ciphertext.size() / order.size()),ciphertext.size() / order.size());
        k++;
    }
    std::string pt;
    for(int i=0;i<(ciphertext.size() / order.size());i++){//for length of column strings
        for(int j=0;j<order.size();j++){//for number of columns
            pt.push_back(columns.at(j).at(i)+32);
        }
    }
    return pt;
}