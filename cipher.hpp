#pragma once

#include <string>
//does it make sense to force every cipher to have a input validation function?
//should I add a stream cipher / block cipher class?

//just trying to enforce a consistent interface with this. all ciphers take in and spit out strings, and do not mutate their inputs.
class cipher{
public:
    virtual std::string encrypt(const std::string& plaintext) = 0;
    virtual std::string decrypt(const std::string& ciphertext) = 0;
};