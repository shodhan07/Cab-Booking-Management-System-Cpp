#include "Ride.hpp"

#include <sstream>
#include <stdexcept>
#include <utility>

namespace {
std::string statusToString(RideStatus status) {
    switch (status) {
    case RideStatus::Requested:
        return "Requested";
    case RideStatus::Assigned:
        return "Assigned";
    case RideStatus::InProgress:
        return "InProgress";
    case RideStatus::Completed:
        return "Completed";
    case RideStatus::Cancelled:
        return "Cancelled";
    }
    return "Requested";
}

RideStatus stringToStatus(const std::string& status) {
    if (status == "Requested") {
        return RideStatus::Requested;
    }
    if (status == "Assigned") {
        return RideStatus::Assigned;
    }
    if (status == "InProgress") {
        return RideStatus::InProgress;
    }
    if (status == "Completed") {
        return RideStatus::Completed;
    }
    if (status == "Cancelled") {
        return RideStatus::Cancelled;
    }
    return RideStatus::Requested;
}
} 

Ride::Ride() : fare(0.0), status(RideStatus::Requested) {}

Ride::Ride(std::string id, std::string userId, std::string pickup, std::string dropoff, double fare)
    : id(std::move(id)),
      userId(std::move(userId)),
      pickup(std::move(pickup)),
      dropoff(std::move(dropoff)),
      fare(fare),
      status(RideStatus::Requested) {}

const std::string& Ride::getId() const {
    return id;
}

const std::string& Ride::getUserId() const {
    return userId;
}

const std::string& Ride::getDriverId() const {
    return driverId;
}

const std::string& Ride::getPickup() const {
    return pickup;
}

const std::string& Ride::getDropoff() const {
    return dropoff;
}

double Ride::getFare() const {
    return fare;
}

RideStatus Ride::getStatus() const {
    return status;
}

void Ride::assignDriver(const std::string& assignedDriverId) {
    driverId = assignedDriverId;
    status = RideStatus::Assigned;
}

void Ride::updateStatus(RideStatus newStatus) {
    status = newStatus;
}

std::string Ride::serialize() const {
    return id + "|" + userId + "|" + driverId + "|" + pickup + "|" + dropoff + "|" + statusToString(status) + "|" + std::to_string(fare);
}

Ride Ride::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string id;
    std::string userId;
    std::string driverId;
    std::string pickup;
    std::string dropoff;
    std::string statusText;
    std::string fareText;

    std::getline(ss, id, '|');
    std::getline(ss, userId, '|');
    std::getline(ss, driverId, '|');
    std::getline(ss, pickup, '|');
    std::getline(ss, dropoff, '|');
    std::getline(ss, statusText, '|');
    std::getline(ss, fareText, '|');

    if (id.empty()) {
        throw std::runtime_error("Invalid ride record");
    }

    double parsedFare = 0.0;
    if (!fareText.empty()) {
        parsedFare = std::stod(fareText);
    }

    Ride ride(id, userId, pickup, dropoff, parsedFare);
    ride.driverId = driverId;
    ride.status = stringToStatus(statusText);
    return ride;
}
