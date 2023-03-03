I intend for this to eventually be a library to demo historical or outdated cryptography algorithms. 
It is intended to be read and understood rather than used for any practical cryptographic purpose.
The intended audience is c++ beginners (who are not brand new to programming or c++).
Efficiency will take a backseat to readability when they are in conflict. 

I want to brush up on my c++ OOP skills so there will be plenty of Boilerplate Driven Development. Please give feedback if you think I've done anything completely insane.

An idea I have (I have no clue if it's a good one) is to use OOP ideas to help illustrate some of the connections between different ciphers. eg: ceasar inherits from shift inherits from affine because a ceasar cipher IS a specialized unkeyed shift cipher, and a shift cipher IS a specialized affine cipher with a smaller key. 

Really gotta start to add descriptions of the algorithms at this point.......


## HOW TO USE
For now, if you want to use any of these you should use the fastest and most reliable c++ build system: copying the files into a directory of your own, #include-ing them, then messing around.

All of the ciphers only have two public facing functions, encrypt and decrypt, that take strings as input and return strings as outputs. The constructors for all of the ciphers take keys (where applicable) as inputs. If you want to use a new key, you need to instantiate a new cipher.

###### ex:
if you want to use an affine cipher, which just encrypts a message one plaintext character (x) at a time to its ciphertext equivalent (y) by the equation y=(ax+b) mod 26 the key is the tuple (a,b). So that's the key we feed the constructor of the affine cipher class.

###### actual ex:

`#include <string>
#include <iostream>
#include affine

int main(){
    affine A(3,2);

    std::string plaintext = "Wow what a good plaintext";
    std::string ciphertext = A.encrypt(plaintext);//tada, that's it
}`

Note that encrypt will reject messages composed of anything other than alphabetic characters and spaces. Also, the functions are not true inverses since cipher.encrypt does not preserve capitalization or spaces. 