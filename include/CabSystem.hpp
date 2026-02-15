#pragma once

#include <string>
#include <vector>

#include "Driver.hpp"
#include "Ride.hpp"
#include "User.hpp"

class CabSystem {
public:
    CabSystem(std::string usersFile, std::string driversFile, std::string ridesFile);

    bool registerUser(const std::string& id, const std::string& name, const std::string& phone, const std::string& password);
    bool registerDriver(const std::string& id, const std::string& name, const std::string& cabNumber, const std::string& password);

    bool loginUser(const std::string& id, const std::string& password) const;
    bool loginDriver(const std::string& id, const std::string& password) const;

    bool requestRide(const std::string& rideId, const std::string& userId, const std::string& pickup, const std::string& dropoff, double distanceKm);
    bool completeRide(const std::string& rideId, double& fare);

    const std::vector<Ride>& getRides() const;

private:
    std::vector<User> users;
    std::vector<Driver> drivers;
    std::vector<Ride> rides;

    std::string usersFile;
    std::string driversFile;
    std::string ridesFile;

    void loadData();
    void saveUsers() const;
    void saveDrivers() const;
    void saveRides() const;
    static double calculateFare(double distanceKm);

    static bool fileExists(const std::string& path);
};
