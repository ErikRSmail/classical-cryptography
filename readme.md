# What is this?

This is a collection of classical cryptography ciphers. These are insecure ciphers, generally crack-able by hand, that are no longer used. This library is  meant to be understandable by a wide audience (of people who know C++), or used in personal/educational projects. 

I just started this, so it is just a skeleton for now. 

## How do I use it?
For now, just copy all of the files into a local directory, #include the cipher you want to use, and start messing around. 
#### Example
 If you want to use an affine cipher, which just encrypts a message one plaintext character `X` at a time to its ciphertext equivalent `Y` by the equation `Y=(aX+b) mod 26` the key is the tuple `(a, b)`. So that's the key we feed the constructor of the affine cipher class.
```
#include <string>
#include src/monoalphabetic_substitution_ciphers/affine.hpp

int main(){
	affine A(3,2);
	std::string plaintext = "Good plaintext!";
	std::string ciphertext = A.cipher::encrypt(plaintext);
}
```
Note that encrypt will reject messages composed of anything other than alphabetic characters, punctuation, and spaces. Also, the functions are not true inverses since `cipher.encrypt()` does not preserve capitalization, punctuation, or spaces.
## What ciphers do you plan to implement?
Every classical cipher that operates on text.
###  Real answer
- Monoalphabetic Substitution Ciphers
- - Random 
- - Simple Keyed
- - Keyword Columnar
- - Affine
- - - Shift
- - - - Caesar
- - - - Rot13
- - - Multiplicative
- - - - Atbash
- Polyalphabetic Ciphers
- - Vigenere
- - Alberti
- - Trithemius
- - M4 Enigma
- - - M3 Enigma
- Polygraphic Ciphers
- - Playfair
- - Two Square
- - Four Square
- - Hill
- Transposition
- - Simple Columnar
- - Keyed Columnar
- - Scytale
- - - Rail Fence
- Codes
- - Navajo Code
- Other
- - ADFGX

This list is not at all finalized; I am definitely forgetting tons.
I'm unsure of the various disk ciphers and machine ciphers. They might get tossed in. 
## Misc thoughts
### Why on earth would you model cryptographic *Functions* with *Objects* instead of *Function* composition?
An idea I have (I have no clue if it's a good one) is to use OOP ideas to help illustrate some of the connections between different ciphers. eg: ceasar inherits from shift inherits from affine because a ceasar cipher IS a specialized unkeyed shift cipher, and a shift cipher IS a specialized affine cipher with a smaller key.

Also I think it's accessible by a wider audience. I don't know if that is reasonable or not but I'm just gonna roll with it. I think this might still work out to be more organized and reduce duplicate effort.

### What about cryptanalysis?
I don't know if I want to tack cryptanalysis tools onto this. I probably won't, but that might change once most ciphers are implemented.
### What is going to change?
I'm not competent enough to know.
### You're a hack buddy (please give feedback)
Please explain. I have only ever really worked on personal projects in isolation so I have no frame of reference for what is good/bad design/style out of what I mimic or copy from learning resources. I welcome any feedback.
### Why didn't you use X Y Z?
I'm going to avoid most C style code, manual memory management, C++23 features, functional programming, external dependencies, etc because I want to prioritize accessibility. 