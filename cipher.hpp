#pragma once

#include <string>
//does it make sense to force every cipher to have a input validation function?
//should I add a stream cipher / block cipher class?
class cipher{
public:
    virtual std::string encrypt(const std::string& plaintext) = 0;
    virtual std::string decrypt(const std::string& ciphertext) = 0;
};