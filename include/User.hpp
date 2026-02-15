#pragma once

#include <string>

class User {
public:
    User();
    User(std::string id, std::string name, std::string phone, std::string password);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getPhone() const;
    bool verifyPassword(const std::string& password) const;

    std::string serialize() const;
    static User deserialize(const std::string& line);

private:
    std::string id;
    std::string name;
    std::string phone;
    std::string password;
};