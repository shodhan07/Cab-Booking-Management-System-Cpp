#include "User.hpp"

#include <sstream>
#include <stdexcept>
#include <utility>

User::User() = default;

User::User(std::string id, std::string name, std::string phone, std::string password)
    : id(std::move(id)), name(std::move(name)), phone(std::move(phone)), password(std::move(password)) {}

const std::string& User::getId() const {
    return id;
}

const std::string& User::getName() const {
    return name;
}

const std::string& User::getPhone() const {
    return phone;
}

bool User::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}

std::string User::serialize() const {
    return id + "|" + name + "|" + phone + "|" + password;
}

User User::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string id;
    std::string name;
    std::string phone;
    std::string password;

    std::getline(ss, id, '|');
    std::getline(ss, name, '|');
    std::getline(ss, phone, '|');
    std::getline(ss, password, '|');

    if (id.empty()) {
        throw std::runtime_error("Invalid user record");
    }

    return User(id, name, phone, password);
}