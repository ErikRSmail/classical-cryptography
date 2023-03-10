# What is this?

This is a collection of classical cryptography ciphers. These are insecure ciphers, often crack-able by hand, that are no longer used. It is useable in personal/educational projects, but is built to be easily read and understood rather than be efficient.

## Who is this for?
Anyone with some c++ experience who is interested in pre-electronic/mechanical cryptology who would like to learn by casually picking through implementation.

## How do I use it?
No complicated builds, just put src in a local directory, #include the cipher you want to use, and get started. 
#### The Interface
All ciphers are objects with their key as the parameter to their constructor. To construct a vigenere cipher with key "alphabet" just state `Vigenere v("alphabet");`. To construct a shift cipher with key 7 just state `shift s(7);`. To encrypt or decrypt you have to call the encrypt or decrpyt function of the cipher parent object, ie `v.cipher::encrypt("plaintext");` or `s.cipher::decrypt(ciphertext);`.

Note that `encrypt` will reject strings composed of anything other than alphabetic characters, punctuation, and spaces and `decrypt` will reject strings composed of anything other than capitalized ascii chars.
#### Example
 If you want to use an affine cipher, which just encrypts a message one plaintext character `X` at a time to its ciphertext equivalent `Y` by the equation `Y=(aX+b) mod 26` the key is the two ints `a, b`. So that's the key we pass to the constructor of the affine cipher class.
```
#include <string>
#include src/monoalphabetic_substitution_ciphers/affine.hpp

int main(){
	affine A(3,2);
	std::string plaintext = "Good plaintext!";
	std::string ciphertext = A.cipher::encrypt(plaintext);
}
```
## What ciphers are implemented?
Most historically significant non-mechanical, non-modern ciphers.
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
- - Text-autokey (by Vigenere)
- - Trithemius
- Polygraphic Ciphers
- - Playfair
- Transposition
- - Keyword Columnar
- - Simple Columnar
- - Rail Fence
- Other
- - ADFGX
## Misc
### Why would you model cryptographic *Functions* with *Objects* instead of *Function* composition?
An idea I have (which might be a bad one (update: I think this was a mediocre idea)) is to use OOP ideas to help illustrate some of the connections between different ciphers. eg: ceasar inherits from shift inherits from affine because a ceasar cipher IS a specialized unkeyed shift cipher, and a shift cipher IS a specialized affine cipher with a smaller key.

I hope to structure this well enough that someone with knowledge of c++ but minimal cryptography knowledge could pick through the structure and get the gist of some bits of classical cryptography.

Most of these ciphers are just maps with caveats so it makes sense to me to just tack a bunch of helper methods onto map(s) and encapsulate that behind just a constructor, encrypt function, and decrypt function. 

### Why didn't you use X Y Z?
I avoided C style code/ manual memory management, C++23 features, functional programming, external dependencies, etc because I want to prioritize accessibility. 