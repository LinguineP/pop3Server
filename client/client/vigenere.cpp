#include "vigenere.h"


std::string Encryption::key = "alanturing";

std::string Encryption::encrypt(const std::string& text) {
    std::string encrypted_text = "";
    int key_length = key.length();

    for (int i = 0; i < text.length(); i++) {
        int value = (int)text[i] + (int)key[i % key_length] - 130;
        encrypted_text += (char)value;
    }

    return encrypted_text;
}

std::string Encryption::decrypt(const std::string& encrypted_text) {
    std::string decrypted_text = "";
    int key_length = key.length();

    for (int i = 0; i < encrypted_text.length(); i++) {
        int value = (int)encrypted_text[i] - (int)key[i % key_length] + 130;
        decrypted_text += (char)value;
    }

    return decrypted_text;
}
