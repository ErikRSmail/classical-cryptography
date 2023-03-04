#pragma once
/*
[describe cipher]
*/
#include <string>
#include "shift.hpp"

class rot13 : public shift{
public:
    rot13() : shift(13){}
};