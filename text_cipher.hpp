#pragma once

#include <string>
#include "cipher.hpp"
/*
A convention in cryptography, at least when working with historical ciphers, is that plaintext should be written in lowercase.
Many historical ciphers were designed to operate on aphabetic characters only.
Punctuation and spacing are not preserved under encryption.
Convention is to output the ciphertext in blocks of five uppercase chars seperated by a space.

So we only accept alphabetic characters, spaces, and punctuation in plaintext.
We discard spaces and punctuation.
*/
class text_cipher : public cipher{
    bool is_valid(const std::string& plaintext);
    std::string format_input(const std::string& plaintext);
    void format_output(std::string& ciphertext);
};

bool text_cipher::is_valid(const std::string& plaintext){

}

std::string text_cipher::format_input(const std::string& plaintext){

}

void text_cipher::format_output(std::string& ciphertext){

}