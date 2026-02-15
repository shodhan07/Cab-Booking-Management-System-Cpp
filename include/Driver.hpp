#pragma once

#include <string>

class Driver {
public:
    Driver();
    Driver(std::string id, std::string name, std::string cabNumber, std::string password, bool available = true);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getCabNumber() const;
    bool isAvailable() const;
    void setAvailability(bool status);
    bool verifyPassword(const std::string& password) const;

    std::string serialize() const;
    static Driver deserialize(const std::string& line);

private:
    std::string id;
    std::string name;
    std::string cabNumber;
    std::string password;
    bool available;
};