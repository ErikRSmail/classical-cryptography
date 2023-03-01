#pragma once
/*
[describe cipher]
*/
#include <string>
#include "affine.hpp"

class shift : public affine{
public:
    std::string encrypt(const std::string& plaintext) override;
    std::string decrypt(const std::string& ciphertext) override;
    shift(int b) : affine(1,b){}
};