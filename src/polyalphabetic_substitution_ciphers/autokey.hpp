#pragma once

#include <string>
#include <vector>
#include "assert.h"
#include "../cipher.hpp"

class autokey : public cipher{
public:
    autokey(const std::string& key_input);
private:
    std::vector<int> key;
    std::string encrypt_implementation(const std::string& plaintext);
    std::string decrypt_implementation(const std::string& ciphertext);
};
autokey::autokey(const std::string& key_input){
    assert(is_valid_key(key_input));
    for(const char& c : key_input){
        if(c>=97 && c<=122){
            key.push_back(c-97);
            }
        else if(c>=65 && c<=90){
            key.push_back(c-65);
        }
    }
}
std::string autokey::encrypt_implementation(const std::string& plaintext){
    std::string ct;
    int pt;
    for(int i=0;i<key.size();i++){
        pt = int(plaintext.at(i) - 97);
        pt = (pt + key.at(i)) % 26;
        ct.push_back(pt + 65);
    }
    for(int i=key.size();i<plaintext.size();i++){
        pt = int(plaintext.at(i) - 97);
        pt = (pt + (plaintext.at(i-key.size()) - 97)) % 26;
        ct.push_back(pt + 65);
    }
    return ct;
}

std::string autokey::decrypt_implementation(const std::string& ciphertext){
    std::string pt;
    int ct;
    for(int i=0; i<key.size();i++){
        ct = ciphertext.at(i) - 65;
        ct = (ct - key.at(i)) % 26;
        pt.push_back(ct+97);
    }
    for(int i=key.size();i<ciphertext.size();i++){
        ct = ciphertext.at(i) - 65;
        ct = ct - (pt.at(i-key.size()) - 97);
        if(ct < 0){ct+=26;}
        ct = ct % 26;
        pt.push_back(ct+97);
    }

    return pt;
}