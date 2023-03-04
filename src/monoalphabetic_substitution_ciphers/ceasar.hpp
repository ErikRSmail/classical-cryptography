#pragma once
/*
[describe cipher]
*/
#include <string>
#include "shift.hpp"

class ceasar : public shift{
public:
    ceasar() : shift(3){}
};