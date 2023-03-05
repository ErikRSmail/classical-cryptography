#pragma once
/*
[describe cipher]
ax+b mod 26
*/
#include <map>
#include <algorithm>
#include <vector>
#include "assert.h"
#include "monoalphabetic_substitution.hpp"

class affine : public monoalphabetic_substitution{
public:
    affine(int a, int b) : monoalphabetic_substitution(affine_map(a,b)){}
private:
    //std::map<int, int> inverses{{1,1},{3,9},{5,21},{7,15},{9,3},{11,19},{15,7},{17,23},{19,11},{21,5},{23,17},{25,25}}; //multiplicative inverses mod 26
    //std::vector<int> has_inverse{1,3,5,7,9,11,15,17,19,23,25};
    std::map<char,char> affine_map(int a, int b);
    char affine_map(int a, int b, char pt);
};
char affine::affine_map(int a, int b, char pt){
    int ct = pt-97;//maps a-z to 0-25
    ct = (ct*a + b) % 26;//apply encryption
    ct += 65; //remap to uppercase ascii range
    return char(ct);
}

std::map<char,char> affine::affine_map(int a, int b){
    assert((b >= 0) && (b <= 25));
    std::map<char,char> m;
    for(int i=97;i<=122;i++){//loop from 'a' to 'z'
        m[i] = affine_map(a,b,i);
    }
    return m;
}