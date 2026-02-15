#include "Driver.hpp"

#include <sstream>
#include <stdexcept>
#include <utility>

Driver::Driver() : available(true) {}

Driver::Driver(std::string id, std::string name, std::string cabNumber, std::string password, bool available)
    : id(std::move(id)),
      name(std::move(name)),
      cabNumber(std::move(cabNumber)),
      password(std::move(password)),
      available(available) {}

const std::string& Driver::getId() const {
    return id;
}

const std::string& Driver::getName() const {
    return name;
}

const std::string& Driver::getCabNumber() const {
    return cabNumber;
}

bool Driver::isAvailable() const {
    return available;
}

void Driver::setAvailability(bool status) {
    available = status;
}

bool Driver::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}

std::string Driver::serialize() const {
    return id + "|" + name + "|" + cabNumber + "|" + password + "|" + (available ? "1" : "0");
}

Driver Driver::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string id;
    std::string name;
    std::string cabNumber;
    std::string password;
    std::string availability;

    std::getline(ss, id, '|');
    std::getline(ss, name, '|');
    std::getline(ss, cabNumber, '|');
    std::getline(ss, password, '|');
    std::getline(ss, availability, '|');

    if (id.empty()) {
        throw std::runtime_error("Invalid driver record");
    }

    const bool isAvailable = (availability == "1");
    return Driver(id, name, cabNumber, password, isAvailable);
}