#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <assert.h>
/*
All ciphers encrypt() functions take in strings of printable ascii chars absent numbers.
All ciphers decrypt() functions return strings of uppercase ascii chars with spaces inserted every 5 chars.
All ciphers disregard inputs other than alphabetic characters.
No cipher mutates its input.
*/
class cipher{
public:
    virtual std::string encrypt(const std::string& plaintext) final;
    virtual std::string decrypt(const std::string& ciphertext) final;
protected:
    bool is_valid_key(const std::string& key);
    std::string format_key(const std::string& key);
    virtual std::string encrypt_implementation(const std::string& plaintext)=0;
    virtual std::string decrypt_implementation(const std::string& ciphertext)=0;
private:
    bool is_lowercase(const char& c);
    bool is_uppercase(const char& c);
    bool is_punctuation(const char& c);
    bool is_valid_plaintext(const char& c);//checks for valid key OR plaintext input
    bool is_valid_plaintext(const std::string& plaintext);//checks for valid key OR plaintext input
    bool is_valid_ciphertext(const std::string& ciphertext);
    std::string format_plaintext(const std::string& plaintext);//returns input but with all alphabetic chars in lowercase and no spaces/punctuation
    std::string format_ciphertext(const std::string& ciphertext);//returns input but with spaces inserted every 5 chars.
};
bool cipher::is_lowercase(const char& c){
    if(c>=97 && c<=122){return true;}
    else{return false;}
}
bool cipher::is_uppercase(const char& c){
    if(c>=65 && c<=90){return true;}
    else{return false;}
}
bool cipher::is_punctuation(const char& c){//bad name because this also checks if c is a space, 32 in ascii.
        if((c>=32 && c<=47) || (c>=58 && c<=64) || (c>=91 && c<=96) || (c>=123 && c<=126)){
            return true;
        }
        else{
            return false;
        }
}
bool cipher::is_valid_plaintext(const char& c){//yes, this could be much more efficient if we just checked ascii 32-126 sans the numbers.
    if(is_lowercase(c) || is_uppercase(c) || is_punctuation(c)){return true;}
    else{return false;}
}
bool cipher::is_valid_plaintext(const std::string& plaintext){
    for(const char& c : plaintext){
        if(!is_valid_plaintext(c)){return false;}
    }
    return true;
}
bool cipher::is_valid_ciphertext(const std::string& ciphertext){
    for(const char& c : ciphertext){
        if(!is_uppercase(c)){return false;}
    }
    return true;
}
bool cipher::is_valid_key(const std::string& key){
    return is_valid_plaintext(key);//same functionality soooo
    //need to add verification that our key is not empty after formatting
}
std::string cipher::format_plaintext(const std::string& plaintext){
    std::string str;
    for(const char& c : plaintext){
        if(c>=65 && c<=90){//if char is uppercase ascii
            str.push_back(c+32);//adding 32 maps uppercase ascii to lowercase
        }
        else if(c>=97 && c<=122){//if char is lowercase ascii
            str.push_back(c);
        }
    }
    return str;
}
std::string cipher::format_ciphertext(const std::string& ciphertext){
    return ciphertext;//TODO implement
}
std::string cipher::format_key(const std::string& key){
    std::string first_pass = format_plaintext(key);//little smelly. This removes spaces and punctuation and downshifts all alphabetic chars
    std::string second_pass;
    for(char c : first_pass){
        if(!std::count(second_pass.begin(), second_pass.end(), c)){//should produce our final key with duplicate letters removed
            second_pass.push_back(c);
        }
    }
    return second_pass;
}
std::string cipher::encrypt(const std::string& plaintext){
    assert(is_valid_plaintext(plaintext));
    return format_ciphertext(encrypt_implementation(format_plaintext(plaintext)));
}
std::string cipher::decrypt(const std::string& ciphertext){
    assert(is_valid_ciphertext(ciphertext));
    return format_plaintext(decrypt_implementation(ciphertext));
}
/*
So I want every encryption/decryption function to validate and format input, then do its own
specific encryption algorithm. Is this a good way to do that? ie: forcing every base class to
implement a private encrypt_implementation function. Is that a reasonable way to name these?
*/