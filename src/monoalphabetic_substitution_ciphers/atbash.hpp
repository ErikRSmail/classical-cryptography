#pragma once
/*
[describe cipher]
*/
#include <string>
#include "multiplicative.hpp"

class atbash : public affine{
public:
    atbash() : affine(25,25){}
};