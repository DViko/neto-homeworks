# Database Homework 05

This project demonstrates a simple C++ application using PostgreSQL with libpqxx library and a CLI interface for user management.

## Features

- Database connection management
- User entity and repository pattern with CRUD operations
- Command-line interface (CLI) for user interaction
- CMake build system with FetchContent for dependencies

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

Ensure PostgreSQL is running and configure the connection in main.cpp.

```bash
./exec
```

The application will connect to the database and present a CLI menu with the following options:
1. Create users table
2. Add user
3. Update user
4. Remove user
5. List all users
6. Get user by ID
7. Exit

## Dependencies

- CMake 3.20+
- PostgreSQL
- libpqxx 7.10.1 (fetched automatically)