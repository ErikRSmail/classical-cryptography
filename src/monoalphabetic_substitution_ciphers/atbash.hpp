#pragma once
/*
[describe cipher]
*/
#include <string>
#include "multiplicative.hpp"

class atbash : public multiplicative{
public:
    atbash() : multiplicative(25){}
};