#pragma once
/*
[describe cipher]
ax+b mod 26
*/
#include <string>
#include "text_cipher.hpp"

class affine : public text_cipher{
public:
    std::string encrypt(const std::string& plaintext) override;
    std::string decrypt(const std::string& ciphertext) override;
    affine(int a, int b) : a(a), b(b) {}//TODO need to redo this to check we have valid keys. 
private:
    int a, b;

    char encrypt(const char& plaintext);
    char decrypt(const char& plaintext);
};

std::string affine::encrypt(const std::string& plaintext){
    if(!is_valid(plaintext)){}//TODO figure out error handling later
    std::string pt = format_plaintext(plaintext);
    std::string ct;
    for(const char& c : plaintext){
        ct.push_back(encrypt(c));
    }
    return format_ciphertext(ct);
}
//TODO just a shift cipher. must finish implementation
char affine::encrypt(const char& plaintext){//we have a (sort of..) guarantee pt is in [97..122]
    if(plaintext + b > 122){//if we "overflow the alphabet"
        return plaintext - 26 + b;//then loop back around
    }
    else{
        return plaintext + b;
    }
}
std::string affine::decrypt(const std::string& ciphertext){//TODO implement
    return "placeholder";
}
char affine::decrypt(const char& plaintext){//TODO implement
    return '0';
}