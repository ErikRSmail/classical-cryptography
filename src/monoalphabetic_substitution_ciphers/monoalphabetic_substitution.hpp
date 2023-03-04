#pragma once
/*
[describe cipher]
*/
#include <string>
#include <map>
#include <forward_list>
#include <algorithm>
#include "assert.h"
#include "../cipher.hpp"

class monoalphabetic_substitution : public cipher{
public:
    monoalphabetic_substitution(const std::map<char,char>& subs);
protected:
    virtual std::string encrypt_implementation(const std::string& plaintext) final;
    virtual std::string decrypt_implementation(const std::string& plaintext) final;
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
bool monoalphabetic_substitution::is_valid(const std::map<char,char>& subs){
    if(subs.size() != 26){return false;}
    std::forward_list<char> keys_so_far;
    std::forward_list<char> vals_so_far;
    for(const auto& [key, value] : subs){
        if( !(key <=122 && key >= 97) //key is NOT ascii lowercase//ugly. should add is_lowercase to text_based
        ||  !(value <=90 && value >= 65) //or value is NOT ascii uppercase//ugly. should add is_uppercase to text_based
        ||   (std::find(keys_so_far.begin(), keys_so_far.end(), key) != keys_so_far.end())//or we have a duplicate key
        ||   (std::find(vals_so_far.begin(), vals_so_far.end(), value) != vals_so_far.end())//or we have a duplicate value
        ){
            return false;
        }
        keys_so_far.push_front(key);
        vals_so_far.push_front(value);
    }
    return true;
}
monoalphabetic_substitution::monoalphabetic_substitution(const std::map<char,char>& subs){
    assert(is_valid(subs));
    substitutions = subs;
    substitutions_inverse = inverse_map(subs);
}
std::string monoalphabetic_substitution::encrypt_implementation(const std::string& plaintext){
    std::string str; 
    for(const char& c : plaintext){
        str.push_back(encrypt(c));
    }
    return str;
}
std::string monoalphabetic_substitution::decrypt_implementation(const std::string& ciphertext){
    std::string str; 
    for(const char& c : ciphertext){
        str.push_back(decrypt(c));
    }
    return str;
}
char monoalphabetic_substitution::encrypt(const char& pt){
    return substitutions.at(pt);
}
char monoalphabetic_substitution::decrypt(const char& ct){
    return substitutions_inverse.at(ct);
}
std::map<char,char> monoalphabetic_substitution::inverse_map(const std::map<char,char>& subs){
    std::map<char,char> m;
    for(const auto& [key, value] : subs){  
        m[value] = key;
    }
    return m;
}