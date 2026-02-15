# Cab Booking Management System

A simple C++ console project that demonstrates:

- User and driver registration/login
- Ride request and assignment
- Ride completion and driver availability updates
- File-based persistence for users, drivers, and rides

## Project Structure

- `include/` contains class headers
- `src/` contains implementation files
- `data/` stores plain-text persistence files

## Build

From inside `CabBookingSystem`:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o cab_system
```

## Run

```bash
./cab_system
```

On Windows PowerShell:

```powershell
.\cab_system.exe
```