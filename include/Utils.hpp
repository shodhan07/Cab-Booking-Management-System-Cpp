#pragma once

#include <string>

namespace Utils {
std::string trim(const std::string& value);
std::string generateId(const std::string& prefix, int number);
}