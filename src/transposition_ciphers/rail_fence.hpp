#pragma once

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include "assert.h"
#include "../cipher.hpp"

class rail_fence : public cipher{
public:
    rail_fence(int key);
private:
    int period;
    int n;
    std::string encrypt_implementation(const std::string& plaintext);
    std::string decrypt_implementation(const std::string& ciphertext);
};
rail_fence::rail_fence(int key){
    period=2*(key-1);
    n=key;
}

std::string rail_fence::encrypt_implementation(const std::string& plaintext){
    std::string pt = plaintext;
    while(pt.size() % period != 0){
        pt.push_back('x');
    }
    std::vector<std::string> strings(n);
    int oscillator = 0;
    bool decreasing = false;
    for(const char& c : pt){
        strings.at(oscillator).push_back(c-32);
        if(decreasing == true){oscillator--;}
        if(decreasing == false){oscillator++;}
        if(oscillator == n-1){decreasing = true;}
        if(oscillator == 0){decreasing = false;}
    }
    std::string ct;
    for(std::string str : strings){
        ct.append(str);
    }
    return ct;
}
std::string rail_fence::decrypt_implementation(const std::string& ciphertext){
    assert(ciphertext.size() % period == 0);
    std::vector<std::string> strings(n);
    int k = ciphertext.size() / (period);
    std::string ct = ciphertext;
    
    for(int i = 0; i<strings.size();i++){
        if(i == 0 || i == strings.size() - 1){//case we are doing first or last subdivision of ciphertext
            strings.at(i) = ct.substr(0,k);
            ct.erase(0,k);
        }
        else{
            strings.at(i) = ct.substr(0,2*k);
            ct.erase(0,2*k);
        }
    }
    std::string pt;
    int oscillator = 0;
    bool increasing = true;
    while(pt.size() != ciphertext.size()){
        if(!strings.at(oscillator).empty()){
            pt.push_back(strings.at(oscillator).at(0));
            strings.at(oscillator).erase(0,1);
        }
        if(increasing){oscillator++;}
        else{oscillator--;}
        if(oscillator == 0){increasing = true;}
        else if(oscillator == strings.size() - 1){increasing = false;}
    }
    return pt;
}