#pragma once
/*
[describe cipher]
*/
#include <string>
#include "affine.hpp"

class multiplicative : public affine{
public:
    multiplicative(int a) : affine(a,0){}
};