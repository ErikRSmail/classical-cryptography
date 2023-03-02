#pragma once
/*
[describe cipher]
ax+b mod 26
*/
#include <string>
#include <map>
#include "cipher.hpp"
#include "text_based.hpp"

class affine : public cipher, public text_based{
public:
    std::string encrypt(const std::string& plaintext) override;
    std::string decrypt(const std::string& ciphertext) override;
    affine(int a_in, int b_in);
private:
    int a, b, a_inverse;
    char encrypt(const char& pt);
    char decrypt(const char& ct);
    std::map<int, int> inverse{{1,1},{3,9},{5,21},{7,15},{9,3},{11,19},{15,7},{17,23},{19,11},{21,5},{23,17},{25,25}}; //multiplicative inverses mod 26
};
affine::affine(int a_in, int b_in){
        a = a_in;
        b = b_in;
        a_inverse = inverse[a];
    }//TODO need to redo this to check we have valid keys. also, 
char affine::encrypt(const char& pt){
    int ct = pt-97;//maps a-z to 0-25
    ct = (ct*a + b) % 26;//apply encryption
    ct += 97; //remap to ascii range
    return char(ct);
}

char affine::decrypt(const char& ct){//y=ax+b mod 26=> x = (y-b)*a^-1 mod 26
    int pt = ct-97;//maps a-z to 0-25
    if(pt < b){pt = pt + 26 -b;}
    else{pt -=b;}
    pt = (pt*a_inverse)%26;
    pt += 97; //remap to ascii range
    return char(pt);
}

std::string affine::encrypt(const std::string& plaintext){
    std::string str; 
    for(const char& c : plaintext){
        str.push_back(encrypt(c));
    }
    return str;
}

std::string affine::decrypt(const std::string& ciphertext){//TODO implement
    std::string str; 
    for(const char& c : ciphertext){
        str.push_back(decrypt(c));
    }
    return str;
}