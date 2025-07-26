# Sports Center Management System 🏟️

A comprehensive **Sports Center Management System** built in C that allows efficient management of customer registrations and sports facility bookings. This project demonstrates the implementation of **Data Structures and Algorithms** concepts including linked lists, dynamic memory management, and efficient search algorithms.

## 🎯 Project Overview

The Sports Center Management System is designed to streamline the operations of a sports facility by providing:

- **Customer Registration Management**: Register new customers with complete personal details
- **Slot Booking System**: Book time slots for various sports activities
- **Real-time Availability Tracking**: Monitor available slots across different sports
- **Flexible Booking Management**: Allow multiple bookings per customer while preventing conflicts
- **Comprehensive Search Functionality**: Find customers and their booking details
- **Selective Cancellation**: Cancel specific bookings while preserving customer data

## 🏅 Features

### Core Functionality
- ✅ **Add Customer**: Register new customers with validation for email, phone, and address
- ✅ **List Customers**: Display all registered customers with their details
- ✅ **Search Customer**: Find customers by name or ID and view their booking history
- ✅ **Delete Customer**: Permanently remove customer and all associated bookings
- ✅ **Book Slot**: Reserve time slots for registered customers across different sports
- ✅ **Cancel Booking**: Cancel specific bookings while keeping customer details intact
- ✅ **Display Booked Slots**: View all current bookings organized by sport and time

### Sports Available
1. 🎾 **Tennis**
2. 🏀 **Basketball** 
3. 🏊 **Swimming**
4. ⚽ **Football**
5. 🏸 **Badminton**
6. 🏓 **Table Tennis**

### Time Management
- **Operating Hours**: 8:00 AM to 8:00 PM
- **Slot Duration**: 2 hours per slot
- **Slots Per Sport**: 6 time slots available daily
- **Capacity**: Maximum 3 customers per time slot
- **Booking Rules**: One booking per customer per sport (multiple sports allowed)

## 🛠️ Tech Stack

- **Programming Language**: C
- **Compiler**: GCC (GNU Compiler Collection)
- **Data Structures**: 
  - Singly Linked Lists
  - Dynamic Memory Allocation
- **Key Concepts**:
  - Pointer Manipulation
  - Structure-based Programming
  - Memory Management (malloc/free)
  - String Processing
  - Input Validation

## 📁 Project Structure

```
Sports-Center-Management-System/
│
├── src/
│   └── main.c                 # Main source code file
├── README.md                  # Project documentation
└── .gitignore                # Git ignore file
```

## 🚀 How to Run

### Prerequisites
- GCC compiler installed on your system
- Terminal/Command Prompt access

### For Windows:
```bash
# Navigate to project directory
cd Sports-Center-Management-System

# Compile the program
gcc main.c -o scms.exe

# Run the executable
scms.exe
```

### For Linux/Mac:
```bash
# Navigate to project directory
cd Sports-Center-Management-System

# Compile the program
gcc main.c -o scms

# Run the executable
./scms
```

### Alternative Compilation:
```bash
# With specific flags for better debugging
gcc -Wall -Wextra -std=c99 main.c -o scms
```

## 💻 Usage Guide

### 1. Adding a New Customer
```
Choose Option 1: Add Customer
- Enter customer details (name, email, phone, address, age)
- System validates input format
- Customer receives unique ID
- Customer is now registered and ready for bookings
```

### 2. Booking a Slot
```
Choose Option 5: Book Slot
- Enter registered customer name
- View available time slots across all sports
- Select sport and preferred time slot
- System prevents double booking in same sport
- Booking confirmation with unique booking ID
```

### 3. Managing Bookings
```
Cancel Booking (Option 6):
- Cancels specific booking only
- Customer details remain in system

Delete Customer (Option 4):
- Permanently removes customer
- Deletes all associated bookings
```

## 🔧 System Validation

### Input Validation Rules:
- **Email**: Must contain '@' and '.' symbols
- **Phone**: Exactly 10 digits required
- **Address**: Must contain both letters and numbers
- **Name**: Case-insensitive search and matching

### Business Logic:
- Maximum 3 customers per time slot
- No duplicate bookings for same customer in same sport
- Customers can book multiple sports
- Real-time availability updates

## 📊 Data Structures Used

### Customer Structure
```c
struct Customer {
    int customerId;           // Unique identifier
    char name[50];           // Customer name
    char email[50];          // Email address
    char phoneNumber[15];    // Phone number
    char address[100];       // Address
    int age;                 // Age
    struct Customer* next;   // Pointer to next customer
};
```

### Booking Structure
```c
struct Booking {
    int bookingId;           // Unique booking identifier
    int customerId;          // Reference to customer
    int sport;               // Sport type (1-6)
    int timeSlot;           // Time slot (1-6)
    struct Booking* next;   // Pointer to next booking
};
```

## 🎨 Menu Interface

```
Sports Center Management System
1. Add Customer (Register new customer)
2. List Customers
3. Search Customer
4. Delete Customer (Permanent deletion)
5. Book Slot (For existing customers)
6. Cancel Booking (Cancel specific booking only)
7. Display Booked Slots
8. Exit
```

## 🔍 Search Functionality

- **Search by Name**: Case-insensitive customer name search
- **Search by ID**: Direct customer ID lookup
- **Comprehensive Results**: Shows customer details + all bookings
- **Booking History**: Complete booking information with time slots

## 📈 Future Enhancements

- [ ] File-based data persistence
- [ ] Advanced reporting features
- [ ] Payment integration
- [ ] Email notifications
- [ ] Web-based interface
- [ ] Database integration (MySQL/PostgreSQL)
- [ ] Multi-location support
- [ ] Staff management module

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---
