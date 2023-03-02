#pragma once
/*
[describe cipher]
ax+b mod 26
*/
#include <string>
#include <map>
#include "assert.h"
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
    assert(inverse.count(a_in) != 0);
    assert((b_in >= 0) && (b_in <= 25));
    a = a_in;
    b = b_in;
    a_inverse = inverse.at(a);
}
char affine::encrypt(const char& pt){
    int ct = pt-97;//maps a-z to 0-25
    ct = (ct*a + b) % 26;//apply encryption
    ct += 65; //remap to uppercase ascii range
    return char(ct);
}

char affine::decrypt(const char& ct){//y=ax+b mod 26=> x = (y-b)*a^-1 mod 26
    int pt = ct-65;//maps a-z to 0-25
    if(pt < b){pt = pt + 26 -b;}//subtraction by b mod 26
    else{pt -=b;}//subtraction by b mod 26
    pt = (pt*a_inverse)%26;
    pt += 97; //remap to lowercase ascii range
    return char(pt);
}

std::string affine::encrypt(const std::string& plaintext){
    assert(is_valid(plaintext));
    std::string pt = format_plaintext(plaintext);
    std::string str; 
    for(const char& c : pt){
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