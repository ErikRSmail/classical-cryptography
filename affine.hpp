#pragma once
/*
[describe cipher]
ax+b mod 26
*/
#include <string>
#include "text_cipher.hpp"

class affine : public text_cipher{
public:
    std::string encrypt(const std::string& plaintext) override;
    std::string decrypt(const std::string& ciphertext) override;
protected:
    affine(int a, int b) : a(a), b(b) {}
private:
    int a, b;
};