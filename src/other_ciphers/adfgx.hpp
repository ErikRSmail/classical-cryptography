#pragma once

#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include "../cipher.hpp"
#include "../transposition_ciphers/keyword_columnar_transposition.hpp"

class adfgx : public cipher{
public:
    adfgx(const std::string& poly_key_in, const std::string& transposition_key_in);
private:
    std::string poly_key;
    std::string transposition_key;
    std::array<char,5> ADFGX = {'A','D','F','G','X'};

    bool is_valid_poly_key(const std::string& poly_key_in);
    std::string encrypt_implementation(const std::string& plaintext);
    std::string decrypt_implementation(const std::string& ciphertext);
};
bool adfgx::is_valid_poly_key(const std::string& poly_key_in){
    if(poly_key_in.size()!=25){return false;}
    std::string str = poly_key_in;
    std::sort(str.begin(), str.end());
    for(int i=0;i<str.size()-1;i++){
        if(str.at(i)==str.at(i+1)){return false;}
    }
    for(char c : str){
        if(!(c>=97 && c<=122) && c!=106){return false;}
    }
    return true;
}
adfgx::adfgx(const std::string& poly_key_in, const std::string& transposition_key_in){
    assert(is_valid_poly_key(poly_key_in));
    poly_key = poly_key_in;
    transposition_key=transposition_key_in;
}
std::string adfgx::encrypt_implementation(const std::string& plaintext){
    std::string ct;
    int key_pos;
    std::string pt = plaintext;
    for(int i=0;i<pt.size();i++){
        if(pt.at(i) == 'j'){pt.at(i) = 'i';}
    }
    for(const char& c : pt){
        key_pos = poly_key.find(c);
        ct.push_back(ADFGX.at(key_pos / 5));//row
        ct.push_back(ADFGX.at(key_pos % 5));//column
    }
    keyword_columnar_transposition transpose(transposition_key);
    ct = transpose.cipher::encrypt(ct);
    return ct;
}
std::string adfgx::decrypt_implementation(const std::string& ciphertext){
    keyword_columnar_transposition transpose(transposition_key);
    std::string ct = transpose.cipher::decrypt(ciphertext);
    for(int i=0;i<ct.size();i++){//shift to uppercase
        ct.at(i) -=32;
    }
    if(ct.size() % 2 != 0){
        ct.pop_back();
    }
    std::string pt;
    int row_pos=0;
    int col_pos=0;
    for(int i=0;i<ct.size();i+=2){
        while(ADFGX[row_pos] != ct.at(i)){row_pos++;}
        while(ADFGX[col_pos] != ct.at(i+1)){col_pos++;}
        pt.push_back(poly_key.at(5*row_pos + col_pos));
        row_pos=0;
        col_pos=0;
    }
    return pt;
}