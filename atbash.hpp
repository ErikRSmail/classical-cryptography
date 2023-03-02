#pragma once
/*
[describe cipher]
*/
#include <string>
#include "affine.hpp"

class atbash : public affine{
public:
    atbash() : affine(25,0){}
};