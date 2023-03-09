#pragma once

#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include "assert.h"
#include "../cipher.hpp"

class playfair : public cipher{
public:
    playfair(const std::string& key_in);
private:
    std::string key;

    bool in_row(int a, int b);
    bool is_valid_playfair_ciphertext(const std::string & ciphertext);
    std::string encrypt_implementation(const std::string& plaintext);
    std::string decrypt_implementation(const std::string& ciphertext);
};
playfair::playfair(const std::string& key_in){
    assert(is_valid_key(key_in));//can have valid playfair keys longer than 26 iff the length sans duplicates is less than 26
    std::string formatted_key = format_key(key_in);
    for(int i = 97;i<=122;i++){//106 is small j in ascii
        if(!std::count(formatted_key.begin(),formatted_key.end(),char(i)) && i!=106){
            formatted_key.push_back(char(i));
        }
    }
    assert(formatted_key.size() == 25);
    key = formatted_key;
}
bool playfair::in_row(int a, int b){
    for(int i=0;i<25;i+=5){
        if((a>=i && a<i+5) && (b>=i && b<i+5)){
            return true;
        }
    }
    return false;
}
bool playfair::is_valid_playfair_ciphertext(const std::string & ciphertext){
    if(ciphertext.size()%2 !=0){return false;}
    for(int i=0;i<ciphertext.size();i+=2){
        if(ciphertext.at(i) == ciphertext.at(i+1)){
            return false;
        }
    }
    return true;
}
std::string playfair::encrypt_implementation(const std::string& plaintext){
    std::string first_pass = plaintext;
    std::replace(first_pass.begin(), first_pass.end(), 'j', 'i');
    std::string formatted_pt;
    for(int i=0; i< plaintext.size();i++){
        if(formatted_pt.back() != plaintext.at(i) || formatted_pt.size()%2==0){
            formatted_pt.push_back(plaintext.at(i));
        }        
        else if(formatted_pt.back() == plaintext.at(i) && formatted_pt.size()%2==1){//if we would put identical 
            formatted_pt.push_back('x');
            formatted_pt.push_back(plaintext.at(i));
        }
    }
    if(formatted_pt.size() % 2 != 0 && formatted_pt.back() != 'x'){
        formatted_pt.push_back('x');
    }
    else if(formatted_pt.size() % 2 != 0 && formatted_pt.back() == 'x'){
        formatted_pt.pop_back();
    }
    //Above is all formatting plaintext. now we do the actual encryption
    std::string ct;
    
    int loc1, loc2;
    for(int i=0;i<formatted_pt.size();i+=2){
        loc1 = key.find(formatted_pt.at(i));
        loc2 = key.find(formatted_pt.at(i+1));
        if(loc1 % 5 == loc2 % 5){//if both chars in our bigram are in the same column of our playfair key matrix
            ct.push_back(key.at((loc1 + 5)%25)-32);
            ct.push_back(key.at((loc2 + 5)%25)-32);
        }
        else if(in_row(loc1, loc2)){//case both chars are in same row
            if(loc1 % 5 !=4){ct.push_back(key.at(loc1 + 1)-32);}
            else{ct.push_back(key.at(loc1-4)-32);}
            if(loc2 % 5 !=4){ct.push_back(key.at(loc2 + 1)-32);}
            else{ct.push_back(key.at(loc2-4)-32);}
        }
        else{//case chars are in different rows and columns of our key
            ct.push_back(key.at(loc1 - loc1%5 + loc2%5)-32);
            ct.push_back(key.at(loc2 - loc2%5 + loc1%5)-32);
        }
    }
    return ct;
}
std::string playfair::decrypt_implementation(const std::string& ciphertext){
    assert(is_valid_playfair_ciphertext(ciphertext));
    std::string pt;
    std::string ct;
    for(const char& c : ciphertext){ct.push_back(c+32);}
    int loc1, loc2;
    for(int i=0;i<ct.size();i+=2){
        loc1 = key.find(ct.at(i));
        loc2 = key.find(ct.at(i+1));
        if(loc1 % 5 == loc2 % 5){//if both chars in our bigram are in the same column of our playfair key matrix
            pt.push_back(key.at((loc1 + 20)%25));
            pt.push_back(key.at((loc2 + 20)%25));
        }
        else if(in_row(loc1, loc2)){//case both chars are in same row
            if(loc1 % 5 !=0){pt.push_back(key.at(loc1 - 1));}
            else{pt.push_back(key.at(loc1+4));}
            if(loc2 % 5 !=0){pt.push_back(key.at(loc2 - 1));}
            else{pt.push_back(key.at(loc2+4));}
        }
        else{//case chars are in different rows and columns of our key
            pt.push_back(key.at(loc1 - loc1%5 + loc2%5));
            pt.push_back(key.at(loc2 - loc2%5 + loc1%5));
        }
    }
    return pt;
}