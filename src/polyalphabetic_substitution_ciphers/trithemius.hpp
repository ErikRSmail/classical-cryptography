#pragma once

#include "vigenere.hpp"

class trithemius : public vigenere{
public:
    trithemius() : vigenere("abcdefghijklmnopqrstuvwxyz"){}
};