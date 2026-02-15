#pragma once

#include <string>

enum class RideStatus {
    Requested,
    Assigned,
    InProgress,
    Completed,
    Cancelled
};

class Ride {
public:
    Ride();
    Ride(std::string id, std::string userId, std::string pickup, std::string dropoff, double fare = 0.0);

    const std::string& getId() const;
    const std::string& getUserId() const;
    const std::string& getDriverId() const;
    const std::string& getPickup() const;
    const std::string& getDropoff() const;
    double getFare() const;
    RideStatus getStatus() const;

    void assignDriver(const std::string& driverId);
    void updateStatus(RideStatus newStatus);

    std::string serialize() const;
    static Ride deserialize(const std::string& line);

private:
    std::string id;
    std::string userId;
    std::string driverId;
    std::string pickup;
    std::string dropoff;
    double fare;
    RideStatus status;
};
