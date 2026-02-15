#include <iostream>

#include "CabSystem.hpp"

int main() {
    CabSystem system("data/users.txt", "data/drivers.txt", "data/rides.txt");

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Cab Booking Management System ===\n";
        std::cout << "1. Register User\n";
        std::cout << "2. Register Driver\n";
        std::cout << "3. User Login\n";
        std::cout << "4. Driver Login\n";
        std::cout << "5. Request Ride\n";
        std::cout << "6. Complete Ride\n";
        std::cout << "7. View Ride Count\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string id;
            std::string name;
            std::string phone;
            std::string password;
            std::cout << "User ID: "; std::cin >> id;
            std::cout << "Name: "; std::cin >> name;
            std::cout << "Phone: "; std::cin >> phone;
            std::cout << "Password: "; std::cin >> password;

            std::cout << (system.registerUser(id, name, phone, password) ? "User registered.\n" : "User ID already exists.\n");
        } else if (choice == 2) {
            std::string id;
            std::string name;
            std::string cabNumber;
            std::string password;
            std::cout << "Driver ID: "; std::cin >> id;
            std::cout << "Name: "; std::cin >> name;
            std::cout << "Cab Number: "; std::cin >> cabNumber;
            std::cout << "Password: "; std::cin >> password;

            std::cout << (system.registerDriver(id, name, cabNumber, password) ? "Driver registered.\n" : "Driver ID already exists.\n");
        } else if (choice == 3) {
            std::string id;
            std::string password;
            std::cout << "User ID: "; std::cin >> id;
            std::cout << "Password: "; std::cin >> password;
            std::cout << (system.loginUser(id, password) ? "User login successful.\n" : "Invalid user credentials.\n");
        } else if (choice == 4) {
            std::string id;
            std::string password;
            std::cout << "Driver ID: "; std::cin >> id;
            std::cout << "Password: "; std::cin >> password;
            std::cout << (system.loginDriver(id, password) ? "Driver login successful.\n" : "Invalid driver credentials.\n");
        } else if (choice == 5) {
            std::string rideId;
            std::string userId;
            std::string pickup;
            std::string dropoff;
            double distanceKm = 0.0;
            std::cout << "Ride ID: "; std::cin >> rideId;
            std::cout << "User ID: "; std::cin >> userId;
            std::cout << "Pickup: "; std::cin >> pickup;
            std::cout << "Dropoff: "; std::cin >> dropoff;
            std::cout << "Distance (km): "; std::cin >> distanceKm;
            std::cout << (system.requestRide(rideId, userId, pickup, dropoff, distanceKm) ? "Ride requested successfully.\n" : "Ride request failed.\n");
        } else if (choice == 6) {
            std::string rideId;
            double fare = 0.0;
            std::cout << "Ride ID: "; std::cin >> rideId;
            if (system.completeRide(rideId, fare)) {
                std::cout << "Ride completed. Fare: " << fare << "\n";
            } else {
                std::cout << "Ride not found.\n";
            }
        } else if (choice == 7) {
            std::cout << "Total rides in system: " << system.getRides().size() << "\n";
        } else if (choice == 0) {
            std::cout << "Exiting...\n";
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
