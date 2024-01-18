#pragma once


#include <iostream>
#include <vector>
#include <algorithm>

class Encryption {
private:
    static  std::string key;

public:
    std::string encrypt(const std::string& text);

    std::string decrypt(const std::string& encrypted_text);
};
