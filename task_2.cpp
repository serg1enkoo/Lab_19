#include <iostream>
#include <string>

int main() {
    std::string password;
    std::getline(std::cin, password);

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < password.length(); ++i) {
        char c = password[i];
        if (c >= 'A' && c <= 'Z') {
            has_upper = true;
        } else if (c >= 'a' && c <= 'z') {
            has_lower = true;
        } else if (c >= '0' && c <= '9') {
            has_digit = true;
        } else if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ' || c == '\t')) {
            has_special = true;
        }
    }

    bool is_valid = true;

    if (password.length() != 8) {
        std::cout << "The password must be 8 characters long" << std::endl;
        is_valid = false;
    }
    if (!has_upper) {
        std::cout << "The password must have at least one upper case letter" << std::endl;
        is_valid = false;
    }
    if (!has_lower) {
        std::cout << "The password must have at least one lower case letter" << std::endl;
        is_valid = false;
    }
    if (!has_digit) {
        std::cout << "The password must have at least one digit" << std::endl;
        is_valid = false;
    }
    if (!has_special) {
        std::cout << "The password must have at least one special character" << std::endl;
        is_valid = false;
    }

    if (is_valid) {
        std::cout << "The password is valid" << std::endl;
    }

    return 0;
}
