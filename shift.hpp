#pragma once
/*
[describe cipher]
*/
#include <string>
#include "affine.hpp"

class shift : public affine{
public:
    shift(int b) : affine(1,b){}
};