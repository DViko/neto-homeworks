# Database Homework 05 - Contact Management

This project demonstrates a C++ application for managing contact information with PostgreSQL database using libpqxx library.

## Features

- Database connection management
- Contact entity with support for multiple phone numbers and stable phone IDs
- Repository pattern for database operations
- Full CRUD operations: Create, Read, Update, Delete
- Search functionality across contact fields
- Command-line interface (CLI) for user interaction
- CMake build system with FetchContent for dependencies

## Database Schema

### Tables:
- `contacts`: Stores contact information
  - `id`: SERIAL PRIMARY KEY
  - `first_name`: TEXT NOT NULL
  - `last_name`: TEXT NOT NULL
  - `email`: TEXT UNIQUE NOT NULL

- `phones`: Stores phone numbers for contacts
  - `id`: SERIAL PRIMARY KEY
  - `contact_id`: INTEGER (Foreign Key to contacts)
  - `phone_number`: TEXT NOT NULL

## Class Methods

`ContactRepository` provides the following methods:

1. **`create_tables()`** - Creates the database schema
2. **`add_contact(const entities::Contact& contact)`** - Adds a new contact with initial phones
3. **`add_phone(int contact_id, const std::string& phone)`** - Adds a phone number to an existing contact
4. **`update_contact(const entities::Contact& contact)`** - Updates contact information; leaving phones empty preserves existing numbers
5. **`remove_phone(int phone_id)`** - Removes a specific phone number
6. **`remove_contact(int contact_id)`** - Deletes a contact and associated phones
7. **`find_contacts(const std::string& search_term)`** - Finds contacts by name, last name, email, or phone number
8. **`get_all_contacts()`** - Retrieves all contacts with their phone numbers

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
2. **Add contact** - Register a new contact with optional phone numbers
3. **Add phone to contact** - Add a phone number to an existing contact
4. **Update contact** - Modify contact information (name, email, phones)
5. **Remove phone** - Delete a phone number
6. **Remove contact** - Delete a contact and their phone numbers
7. **Find contacts** - Search by first name, last name, email, or phone number
8. **List all contacts** - Display all contacts with their information
9. **Exit** - Close the application

## Usage Example

```
=== Contact Management CLI ===
1. Create tables
2. Add contact
...
Choose an option (1-9): 1
Tables created successfully.

Choose an option (1-9): 2
Enter first name: John
Enter last name: Doe
Enter email: john@example.com
Enter phone numbers (comma-separated, or empty): 123-456, 789-012
Contact added successfully.

Choose an option (1-9): 8
All contacts:
ID: 1, Name: John Doe, Email: john@example.com, Phones: 123-456, 789-012
```

## Dependencies

- CMake 3.20 or higher
- PostgreSQL 12+
- libpqxx 7.10.1 (automatically fetched via FetchContent)
- C++20 compiler (GCC 11+, Clang 12+, etc.)