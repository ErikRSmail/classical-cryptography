#pragma once
/*
[describe cipher]
ax+b mod 26
*/
#include <string>
#include <map>
#include <forward_list>
#include <algorithm>
#include "assert.h"
#include "cipher.hpp"
#include "text_based.hpp"

class substitution : public cipher, public text_based{
public:
    substitution(const std::map<char,char>& subs);
    std::string encrypt(const std::string& plaintext) override;
    std::string decrypt(const std::string& ciphertext) override;
private:
    std::map<char,char> substitutions;
    std::map<char,char> substitutions_inverse;

    bool is_valid(const std::map<char,char>& subs);
    char encrypt(const char& pt);
    char decrypt(const char& ct);
    std::map<char,char> inverse_map(const std::map<char,char>& subs);
};
/*Need to: 
- make sure all keys are lowercase.
- make sure all values are uppercase.
- make sure we have 26 key/value pairs.
- make sure we have no duplicate keys or values. */
bool substitution::is_valid(const std::map<char,char>& subs){
    if(subs.size() != 26){return false;}
    std::forward_list<char> keys_so_far;
    std::forward_list<char> vals_so_far;
    for(const auto& [key, value] : subs){
        if( !(key <=122 && key >= 97) //key is NOT ascii lowercase
        ||  !(value <=90 && value >= 65) //or value is NOT ascii uppercase
        ||   (std::find(keys_so_far.begin(), keys_so_far.end(), key) != keys_so_far.end())//or we have alduplicate key
        ||   (std::find(vals_so_far.begin(), vals_so_far.end(), value) != vals_so_far.end())//or we have alduplicate value
        ){
            return false;
        }
        keys_so_far.push_front(key);
        vals_so_far.push_front(value);
    }
    return true;//TODO have not tested this thoroughly
}
substitution::substitution(const std::map<char,char>& subs){
    assert(is_valid(subs));
    substitutions = subs;
    substitutions_inverse = inverse_map(subs);
}
std::string substitution::encrypt(const std::string& plaintext){
    assert(text_based::is_valid(plaintext));
    std::string pt = format_plaintext(plaintext);
    std::string str; 
    for(const char& c : pt){
        str.push_back(encrypt(c));
    }
    return str;
}
std::string substitution::decrypt(const std::string& ciphertext){
    std::string str; 
    for(const char& c : ciphertext){
        str.push_back(decrypt(c));
    }
    return str;
}
char substitution::encrypt(const char& pt){
    return substitutions.at(pt);
}
char substitution::decrypt(const char& ct){
    return substitutions_inverse.at(ct);
}
std::map<char,char> substitution::inverse_map(const std::map<char,char>& subs){
    std::map<char,char> m;
    for(const auto& [key, value] : subs){  
        m[value] = key;
    }
    return m;
}