#pragma once

#include <string>
/*
Should really re-read virtual function docs to make sure this makes sense. I think i might have Java brainrot.
The idea is that every cipher must, at a bare minimum, have an encrypt and decrypt function that operates on strings of ascii chars.
*/
//does it make sense to force every cipher to have a input validation function?
class cipher{
public:
    virtual std::string encrypt(const std::string& plaintext) = 0;
    virtual std::string decrypt(const std::string& ciphertext) = 0;
};