# Database Homework 05 - Client Management

This project demonstrates a C++ application for managing client information with PostgreSQL database using libpqxx library.

## Features

- Database connection management
- Client entity with support for multiple phone numbers
- Repository pattern for database operations
- Full CRUD operations: Create, Read, Update, Delete
- Search functionality across client fields
- Command-line interface (CLI) for user interaction
- CMake build system with FetchContent for dependencies

## Database Schema

### Tables:
- `clients`: Stores client information
  - `id`: SERIAL PRIMARY KEY
  - `first_name`: TEXT NOT NULL
  - `last_name`: TEXT NOT NULL
  - `email`: TEXT UNIQUE NOT NULL

- `phones`: Stores phone numbers for clients
  - `id`: SERIAL PRIMARY KEY
  - `client_id`: INTEGER (Foreign Key to clients)
  - `phone_number`: TEXT NOT NULL

## Class Methods

`ClientRepository` provides the following methods:

1. **`create_tables()`** - Creates the database schema
2. **`add_client(const entities::Client& client)`** - Adds a new client with initial phones
3. **`add_phone(int client_id, const std::string& phone)`** - Adds a phone number to an existing client
4. **`update_client(const entities::Client& client)`** - Updates client information and phone numbers
5. **`remove_phone(int phone_id)`** - Removes a specific phone number
6. **`remove_client(int client_id)`** - Deletes a client and associated phones
7. **`find_clients(const std::string& search_term)`** - Finds clients by name, last name, email, or phone number
8. **`get_all_clients()`** - Retrieves all clients with their phone numbers

## Building

```bash
cd /path/to/database_05
mkdir build
cd build
cmake ..
make
```

## Running

Ensure PostgreSQL is running and configured. Update the connection settings in `main.cpp` if needed.

```bash
./exec
```

## CLI Menu Options

1. **Create tables** - Initialize database schema
2. **Add client** - Register a new client with optional phone numbers
3. **Add phone to client** - Add a phone number to an existing client
4. **Update client** - Modify client information (name, email, phones)
5. **Remove phone** - Delete a phone number
6. **Remove client** - Delete a client and their phone numbers
7. **Find clients** - Search by first name, last name, email, or phone number
8. **List all clients** - Display all clients with their information
9. **Exit** - Close the application

## Usage Example

```
=== Client Management CLI ===
1. Create tables
2. Add client
...
Choose an option (1-9): 1
Tables created successfully.

Choose an option (1-9): 2
Enter first name: John
Enter last name: Doe
Enter email: john@example.com
Enter phone numbers (comma-separated, or empty): 123-456, 789-012
Client added successfully.

Choose an option (1-9): 8
All clients:
ID: 1, Name: John Doe, Email: john@example.com, Phones: 123-456, 789-012
```

## Dependencies

- CMake 3.20 or higher
- PostgreSQL 12+
- libpqxx 7.10.1 (automatically fetched via FetchContent)
- C++20 compiler (GCC 11+, Clang 12+, etc.)