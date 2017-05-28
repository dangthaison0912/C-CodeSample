int main () => initialise rotors, reflector and call enigma() to encrypt the message.

void createRotors() => create a number of rotors based on the input of user.

void enigma() => each character of the message will go through all the rotors once, be
reflected by the reflector, enter the rotors the second time before return the final result.
Each time a character is encrypted, the rotors will also be shifted, making it very difficult
to decrypt.
