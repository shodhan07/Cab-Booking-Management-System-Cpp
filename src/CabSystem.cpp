#include "CabSystem.hpp"

#include <fstream>
#include <utility>

CabSystem::CabSystem(std::string usersFile, std::string driversFile, std::string ridesFile)
    : usersFile(std::move(usersFile)),
      driversFile(std::move(driversFile)),
      ridesFile(std::move(ridesFile)) {
    loadData();
}

bool CabSystem::registerUser(const std::string& id, const std::string& name, const std::string& phone, const std::string& password) {
    for (const auto& user : users) {
        if (user.getId() == id) {
            return false;
        }
    }

    users.emplace_back(id, name, phone, password);
    saveUsers();
    return true;
}

bool CabSystem::registerDriver(const std::string& id, const std::string& name, const std::string& cabNumber, const std::string& password) {
    for (const auto& driver : drivers) {
        if (driver.getId() == id) {
            return false;
        }
    }

    drivers.emplace_back(id, name, cabNumber, password, true);
    saveDrivers();
    return true;
}

bool CabSystem::loginUser(const std::string& id, const std::string& password) const {
    for (const auto& user : users) {
        if (user.getId() == id && user.verifyPassword(password)) {
            return true;
        }
    }
    return false;
}

bool CabSystem::loginDriver(const std::string& id, const std::string& password) const {
    for (const auto& driver : drivers) {
        if (driver.getId() == id && driver.verifyPassword(password)) {
            return true;
        }
    }
    return false;
}

bool CabSystem::requestRide(const std::string& rideId, const std::string& userId, const std::string& pickup, const std::string& dropoff, double distanceKm) {
    if (distanceKm < 0.0) {
        return false;
    }

    for (const auto& user : users) {
        if (user.getId() == userId) {
            rides.emplace_back(rideId, userId, pickup, dropoff, calculateFare(distanceKm));

            for (auto& driver : drivers) {
                if (driver.isAvailable()) {
                    rides.back().assignDriver(driver.getId());
                    driver.setAvailability(false);
                    saveDrivers();
                    break;
                }
            }

            saveRides();
            return true;
        }
    }

    return false;
}

bool CabSystem::completeRide(const std::string& rideId, double& fare) {
    for (auto& ride : rides) {
        if (ride.getId() == rideId) {
            ride.updateStatus(RideStatus::Completed);
            fare = ride.getFare();
            for (auto& driver : drivers) {
                if (driver.getId() == ride.getDriverId()) {
                    driver.setAvailability(true);
                    break;
                }
            }
            saveRides();
            saveDrivers();
            return true;
        }
    }
    return false;
}

const std::vector<Ride>& CabSystem::getRides() const {
    return rides;
}

void CabSystem::loadData() {
    if (fileExists(usersFile)) {
        std::ifstream in(usersFile);
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty()) {
                users.push_back(User::deserialize(line));
            }
        }
    }

    if (fileExists(driversFile)) {
        std::ifstream in(driversFile);
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty()) {
                drivers.push_back(Driver::deserialize(line));
            }
        }
    }

    if (fileExists(ridesFile)) {
        std::ifstream in(ridesFile);
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty()) {
                rides.push_back(Ride::deserialize(line));
            }
        }
    }
}

void CabSystem::saveUsers() const {
    std::ofstream out(usersFile, std::ios::trunc);
    for (const auto& user : users) {
        out << user.serialize() << "\n";
    }
}

void CabSystem::saveDrivers() const {
    std::ofstream out(driversFile, std::ios::trunc);
    for (const auto& driver : drivers) {
        out << driver.serialize() << "\n";
    }
}

void CabSystem::saveRides() const {
    std::ofstream out(ridesFile, std::ios::trunc);
    for (const auto& ride : rides) {
        out << ride.serialize() << "\n";
    }
}

bool CabSystem::fileExists(const std::string& path) {
    std::ifstream in(path);
    return in.good();
}

double CabSystem::calculateFare(double distanceKm) {
    constexpr double baseFare = 50.0;
    constexpr double ratePerKm = 12.0;
    return baseFare + (distanceKm * ratePerKm);
}
