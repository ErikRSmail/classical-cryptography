#pragma once
/*
[describe cipher]
*/
#include <string>
#include "affine.hpp"

class atbash : public affine{
public:
    std::string encrypt(const std::string& plaintext) override;
    std::string decrypt(const std::string& ciphertext) override;

    
};