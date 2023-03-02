#pragma once

#include <string>
//does it make sense to force every cipher to have a input validation function?
class cipher{
public:
    virtual std::string encrypt(const std::string& plaintext) = 0;
    virtual std::string decrypt(const std::string& ciphertext) = 0;
};