#pragma once

#include <string>
#include <bits/stdc++.h>
/*
A convention in cryptography, at least when working with historical ciphers, is that plaintext should be written in lowercase.
Many historical ciphers were designed to operate on aphabetic characters only.
Punctuation and spacing are not preserved under encryption.
Convention is to output the ciphertext in blocks of five uppercase chars seperated by a space.

So we only accept alphabetic characters, spaces, and punctuation in plaintext.
We discard spaces and punctuation.
*/
class text_based{
protected:
    bool is_alphabetic(const char& c);
    bool is_valid(const std::string& plaintext);
    std::string format_plaintext(const std::string& plaintext);
    std::string format_ciphertext(const std::string& ciphertext);
};
bool text_based::is_alphabetic(const char& c){
        if((c>=65 && c<=90) || (c>=97 && c<=122)){ //65-90 and 97-122 are upper and lowercase a-z in ascii
            return true;
        }
        else{
            return false;
        }
    }

bool text_based::is_valid(const std::string& plaintext){
    for(const char& c : plaintext){
        if(!is_alphabetic(c) && c != 32 ){//32 is space in ascii 
            return false;
        }
    }
    return true;
}

std::string text_based::format_plaintext(const std::string& plaintext){
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
/*
std::string text_based::format_ciphertext(const std::string& ciphertext){
    std::string str;
    for(const char& c: ciphertext){
        str.push_back(c-32);//this maps lowercase ascii to uppercase ascii
    }
    return str;
}//TODO should probably assert we are in allcaps, and insert spaces every 5 chars
*/