#include <string>
#include <iostream>

std::string manual_trim(const std::string& str) {
    if (str.empty()) {
        return "";
    }
    size_t first = 0;
    while (first < str.length() && (str[first] == ' ' || str[first] == '\t')) {
        first++;
    }
    if (first == str.length()) {
        return "";
    }
    size_t last = str.length() - 1;
    while (last > first && (str[last] == ' ' || str[last] == '\t')) {
        last--;
    }
    return str.substr(first, last - first + 1);
}

std::string find_value_manually(const std::string& values_line,
                                const std::string& key_to_find,
                                bool& found)
{
    size_t current_pos = 0;
    found = false;

    while (current_pos < values_line.length()) {
        size_t comma_pos = values_line.find(',', current_pos);
        if (comma_pos == std::string::npos) {
            comma_pos = values_line.length();
        }

        std::string pair_str = values_line.substr(current_pos, comma_pos - current_pos);

        size_t sep_pos = std::string::npos;
        size_t dash_pos = pair_str.find('-');
        size_t equals_pos = pair_str.find('=');

        if (dash_pos != std::string::npos && equals_pos != std::string::npos) {
            sep_pos = (dash_pos < equals_pos) ? dash_pos : equals_pos;
        } else if (dash_pos != std::string::npos) {
            sep_pos = dash_pos;
        } else {
            sep_pos = equals_pos;
        }

        if (sep_pos != std::string::npos) {
            std::string current_key_raw = pair_str.substr(0, sep_pos);
            std::string current_value_raw = pair_str.substr(sep_pos + 1);

            std::string current_key = manual_trim(current_key_raw);
            std::string current_value = manual_trim(current_value_raw);

            if (!current_key.empty() && current_key == key_to_find) {
                found = true;
                return current_value;
            }
        }

        current_pos = comma_pos + 1;
        while (current_pos < values_line.length() && values_line[current_pos] == ' ') {
             current_pos++;
        }
    }

    return "";
}

int main() {
    std::string values_line;
    std::getline(std::cin, values_line);

    std::string template_str;
    std::getline(std::cin, template_str);

    std::string result = "";
    size_t current_pos = 0;

    while (current_pos < template_str.length()) {
        size_t open_bracket_pos = template_str.find('[', current_pos);
        if (open_bracket_pos == std::string::npos) {
            result += template_str.substr(current_pos);
            break;
        } else {
            result += template_str.substr(current_pos, open_bracket_pos - current_pos);
            size_t close_bracket_pos = template_str.find(']', open_bracket_pos + 1);
            if (close_bracket_pos == std::string::npos) {
                result += '[';
                current_pos = open_bracket_pos + 1;
            } else {
                std::string placeholder_name = template_str.substr(open_bracket_pos + 1, close_bracket_pos - open_bracket_pos - 1);
                bool key_was_found = false;
                std::string value_to_insert = find_value_manually(values_line, placeholder_name, key_was_found);
                if (key_was_found) {
                    result += value_to_insert;
                } else {
                    result += template_str.substr(open_bracket_pos, close_bracket_pos - open_bracket_pos + 1);
                }
                current_pos = close_bracket_pos + 1;
            }
        }
    }

    std::cout << result << std::endl;
    return 0;
}
