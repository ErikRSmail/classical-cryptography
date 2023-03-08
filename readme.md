# What is this?

This is a collection of classical cryptography ciphers. These are insecure ciphers, often crack-able by hand, that are no longer used. It is useable in personal/educational projects, but is built to be easily read and understood.

## How do I use it?
No complicated builds, just put src in a local directory, #include the cipher you want to use, and start messing around. 
#### The Interface
All ciphers are objects with their key as the parameter to their constructor. To construct a vigenere cipher with key "alphabet" just state `Vigenere v("alphabet");`. To construct a shift cipher with key 7 just state `shift s(7);`. To encrypt or decrypt you have to call the encrypt or decrpyt function of the cipher parent object, ie `v.cipher::encrypt("plaintext");` or `s.cipher::decrypt(ciphertext);`.

Note that `encrypt` will reject strings composed of anything other than alphabetic characters, punctuation, and spaces and `decrypt` will reject strings composed of anything other than capitalized ascii chars.
#### Example
 If you want to use an affine cipher, which just encrypts a message one plaintext character `X` at a time to its ciphertext equivalent `Y` by the equation `Y=(aX+b) mod 26` the key is the two numbers `a, b`. So that's the key we feed the constructor of the affine cipher class.
```
#include <string>
#include src/monoalphabetic_substitution_ciphers/affine.hpp

int main(){
	affine A(3,2);
	std::string plaintext = "Good plaintext!";
	std::string ciphertext = A.cipher::encrypt(plaintext);
}
```
## What ciphers do you plan to implement?
Almost all non-mechanical, non-modern ciphers.
###  Specifically
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
- - Vigenere (key-autokey)
- - text-autokey (by vigenere)
- - Trithemius
- Polygraphic Ciphers
- - Playfair
- - Two Square
- - Four Square
- - Hill
- Transposition
- - Simple Columnar
- - Keyed Columnar
- - Rail Fence
- Other
- - ADFGX

This list is not finalized, but I don't forsee expanding it by anything more than a couple ciphers that I can't recall at the moment.
## Misc
### Why would you model cryptographic *Functions* with *Objects* instead of *Function* composition?
An idea I have (which might be a bad one) is to use OOP ideas to help illustrate some of the connections between different ciphers. eg: ceasar inherits from shift inherits from affine because a ceasar cipher IS a specialized unkeyed shift cipher, and a shift cipher IS a specialized affine cipher with a smaller key.

I hope to document and structure this well enough that someone with knowledge of c++ but minimal cryptography knowledge could pick through the structure and get the gist of classical cryptography.

Most of these ciphers are just maps with caveats so it makes sense to me to just tack a bunch of helper methods onto map(s) and encapsulate that behind just a constructor, encrypt function, and decrypt function. 

### Why didn't you use X Y Z?
I'm going to avoid C style code/ manual memory management, C++23 features, functional programming, external dependencies, etc because I want to prioritize accessibility. 