#pragma once

#include <string>
#include <vector>
#include "../cipher.hpp"
#include "../monoalphabetic_substitution_ciphers/shift.hpp"

class vigenere : public cipher{
public:
    vigenere(const std::string& key);
private:
    std::vector<shift> shifts;
    std::string encrypt_implementation(const std::string& plaintext);
    std::string decrypt_implementation(const std::string& plaintext);
};
vigenere::vigenere(const std::string& key){//TODO go back to cipher.hpp and split format_key up. vigenere ciphers accept repeating chars
    for(const char& c : key){
        shifts.push_back(shift(c-97));
    }
}
std::string vigenere::encrypt_implementation(const std::string& plaintext){
    int count = 0;
    std::string str;
    for(const char& c : plaintext){
        std::string pt(1,c);
        str.append(shifts.at(count).cipher::encrypt(pt));
        count++;
        if(count == shifts.size()){count = 0;}
    }
    return str;
}
std::string vigenere::decrypt_implementation(const std::string& ciphertext){
    int count = 0;
    std::string str;
    for(const char& c : ciphertext){
        std::string ct(1,c);
        str.append(shifts.at(count).cipher::decrypt(ct));
        count++;
        if(count == shifts.size()){count = 0;}
    }
    return str;
}