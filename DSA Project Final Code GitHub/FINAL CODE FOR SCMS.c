#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

unsigned int lastCustomerId = 0;

// Forward declarations
struct Customer;
struct Booking;

struct Customer* createCustomer(char name[], char email[], char phoneNumber[], char address[], int age);
struct Booking* createBooking(int customerId, int sport, int timeSlot);
void addCustomer(struct Customer** head, struct Customer* newCustomer);
void addBooking(struct Booking** head, struct Booking* newBooking);
int listAvailableSports(struct Booking* bookingList, int *selectedSport, int *selectedTimeSlot);
void registerCustomer(struct Customer **customerHead, unsigned int *lastCustomerId);
void bookSlot(struct Customer* customerHead, struct Booking** bookingHead, unsigned int *lastCustomerId);
bool isValidEmail(const char *email);
bool isValidPhoneNumber(const char *phoneNumber);
bool isValidAddress(const char *address);
void displayBookedSlots(struct Booking* bookingHead, struct Customer* customerHead);
void freeCustomers(struct Customer* head);
void freeBookings(struct Booking* head);
void listCustomerInfo(struct Customer* head);
void searchCustomer(struct Customer* customerHead, struct Booking* bookingHead);
void deleteCustomer(struct Customer** customerHead, struct Booking** bookingHead, const char* deleteName);
void cancelBooking(struct Booking** bookingHead, struct Customer* customerHead, const char* cancelName);
const char* sportName(int sport);
struct Customer* findCustomerByName(struct Customer* head, const char* name);
struct Customer* findCustomerById(struct Customer* head, int id);
bool hasBookingInSport(struct Booking* bookingHead, int customerId, int sport);

struct Customer {
    int customerId;
    char name[50];
    char email[50];
    char phoneNumber[15];
    char address[100];
    int age;
    struct Customer* next;
};

struct Booking {
    int bookingId;
    int customerId;
    int sport;
    int timeSlot;
    struct Booking* next;
};

int listAvailableSports(struct Booking* bookingList, int *selectedSport, int *selectedTimeSlot) {
    printf("Available Time Slots for Different Sports (2 hours each, 8 AM to 8 PM):\n");

    const int openingHour = 8;
    const int closingHour = 20;
    const int slotDuration = 2;
    const int slotsPerSport = 6;
    const int maxCustomersPerSlot = 3;

    // Initialize the array to keep track of the number of customers booked for each slot
    int bookedSlotsCount[6][6] = {0}; // [sport][timeSlot]

    // Update booked slots count based on the existing bookings
    struct Booking* current = bookingList;
    while (current != NULL) {
        if (current->sport >= 1 && current->sport <= 6 && 
            current->timeSlot >= 1 && current->timeSlot <= 6) {
            bookedSlotsCount[current->sport - 1][current->timeSlot - 1]++;
        }
        current = current->next;
    }

    for (int i = 1; i <= 6; i++) {
        printf("%d. %s: ", i, sportName(i));

        for (int j = 0; j < slotsPerSport; j++) {
            int startTime = openingHour + j * slotDuration;
            int endTime = startTime + slotDuration;

            if (endTime <= closingHour) {
                int availableSlots = maxCustomersPerSlot - bookedSlotsCount[i - 1][j];

                if (availableSlots > 0) {
                    printf("\n %d) %02d:00 - %02d:00 (%d slots available)", j + 1, startTime, endTime, availableSlots);
                } else {
                    printf("\n %d) %02d:00 - %02d:00 (Fully booked)", j + 1, startTime, endTime);
                }

                if (j < slotsPerSport - 1) {
                    printf("; ");
                }
            } else {
                printf("Not available (Closing time reached)");
            }
        }
        printf(".\n");
    }

    int chosenSport;
    do {
        printf("Enter the sport number to choose a time slot (1-6): ");
        scanf("%d", &chosenSport);
        if (chosenSport < 1 || chosenSport > 6) {
            printf("Invalid sport number. Please enter a number between 1 and 6.\n");
        }
    } while (chosenSport < 1 || chosenSport > 6);

    int chosenSlot;
    do {
        printf("Enter the desired time slot for %s (1-6): ", sportName(chosenSport));
        scanf("%d", &chosenSlot);
        if (chosenSlot < 1 || chosenSlot > slotsPerSport) {
            printf("Invalid time slot. Please enter a number between 1 and 6.\n");
        }
    } while (chosenSlot < 1 || chosenSlot > slotsPerSport);

    // Check if the slot is available
    if (bookedSlotsCount[chosenSport - 1][chosenSlot - 1] >= maxCustomersPerSlot) {
        printf("Sorry, this time slot is fully booked. Please choose another slot.\n");
        return 0;
    }

    *selectedSport = chosenSport;
    *selectedTimeSlot = chosenSlot;
    
    int startTime = openingHour + (chosenSlot - 1) * slotDuration;
    int endTime = startTime + slotDuration;
    printf("You have chosen time slot %d (%02d:00 - %02d:00) for %s.\n", 
           chosenSlot, startTime, endTime, sportName(chosenSport));
    
    return 1;
}

const char* sportName(int sport) {
    switch (sport) {
        case 1: return "Tennis";
        case 2: return "Basketball";
        case 3: return "Swimming";
        case 4: return "Football";
        case 5: return "Badminton";
        case 6: return "Table Tennis";
        default: return "Unknown";
    }
}

struct Customer* createCustomer(char name[], char email[], char phoneNumber[], char address[], int age) {
    struct Customer* newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
    if (newCustomer != NULL) {
        strcpy(newCustomer->name, name);
        strcpy(newCustomer->email, email);
        strcpy(newCustomer->phoneNumber, phoneNumber);
        strcpy(newCustomer->address, address);
        newCustomer->age = age;
        newCustomer->next = NULL;
    }
    return newCustomer;
}

struct Booking* createBooking(int customerId, int sport, int timeSlot) {
    static int lastBookingId = 0;
    struct Booking* newBooking = (struct Booking*)malloc(sizeof(struct Booking));
    if (newBooking != NULL) {
        newBooking->bookingId = ++lastBookingId;
        newBooking->customerId = customerId;
        newBooking->sport = sport;
        newBooking->timeSlot = timeSlot;
        newBooking->next = NULL;
    }
    return newBooking;
}

void addCustomer(struct Customer** head, struct Customer* newCustomer) {
    if (*head == NULL) {
        *head = newCustomer;
    } else {
        struct Customer* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCustomer;
    }
}

void addBooking(struct Booking** head, struct Booking* newBooking) {
    if (*head == NULL) {
        *head = newBooking;
    } else {
        struct Booking* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newBooking;
    }
}

// Helper function for case-insensitive string comparison
int stringCompareIgnoreCase(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        char c1 = tolower(*str1);
        char c2 = tolower(*str2);
        if (c1 != c2) {
            return c1 - c2;
        }
        str1++;
        str2++;
    }
    return tolower(*str1) - tolower(*str2);
}

struct Customer* findCustomerByName(struct Customer* head, const char* name) {
    struct Customer* current = head;
    while (current != NULL) {
        if (stringCompareIgnoreCase(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct Customer* findCustomerById(struct Customer* head, int id) {
    struct Customer* current = head;
    while (current != NULL) {
        if (current->customerId == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool hasBookingInSport(struct Booking* bookingHead, int customerId, int sport) {
    struct Booking* current = bookingHead;
    while (current != NULL) {
        if (current->customerId == customerId && current->sport == sport) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool isValidEmail(const char *email) {
    return strchr(email, '@') != NULL && strchr(email, '.') != NULL;
}

bool isValidPhoneNumber(const char *phoneNumber) {
    int digitCount = 0;
    while (*phoneNumber) {
        if (isdigit(*phoneNumber)) {
            digitCount++;
        }
        phoneNumber++;
    }
    return digitCount == 10;
}

bool isValidAddress(const char *address) {
    bool hasLetter = false;
    bool hasDigit = false;
    while (*address) {
        if (isalpha(*address)) {
            hasLetter = true;
        } else if (isdigit(*address)) {
            hasDigit = true;
        }
        address++;
    }
    return hasLetter && hasDigit;
}

void registerCustomer(struct Customer **customerHead, unsigned int *lastCustomerId) {
    char name[50];
    char email[50];
    char phoneNumber[15];
    char address[100];
    int age;

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", name);

    // Check if customer already exists
    if (findCustomerByName(*customerHead, name) != NULL) {
        printf("Customer with name '%s' already exists! Use 'Book Slot' option to book slots for existing customers.\n", name);
        return;
    }

    // Email validation loop
    do {
        printf("Enter Customer Email: ");
        scanf(" %[^\n]", email);
        if (!isValidEmail(email)) {
            printf("Invalid email format. Please enter a valid email.\n");
        }
    } while (!isValidEmail(email));

    // Phone number validation loop
    do {
        printf("Enter Customer Phone Number (10 digits): ");
        scanf(" %[^\n]", phoneNumber);
        if (!isValidPhoneNumber(phoneNumber)) {
            printf("Invalid phone number format. Please enter a 10-digit phone number.\n");
        }
    } while (!isValidPhoneNumber(phoneNumber));

    // Address validation loop
    do {
        printf("Enter Customer Address (should contain both letters and numbers): ");
        scanf(" %[^\n]", address);
        if (!isValidAddress(address)) {
            printf("Invalid address format. Please enter an address containing both letters and numbers.\n");
        }
    } while (!isValidAddress(address));

    printf("Enter Customer Age: ");
    scanf("%d", &age);

    struct Customer *newCustomer = createCustomer(name, email, phoneNumber, address, age);
    if (newCustomer != NULL) {
        newCustomer->customerId = ++(*lastCustomerId);
        addCustomer(customerHead, newCustomer);
        printf("Customer '%s' registered successfully!\n", name);
        printf("Customer ID: %u\n", newCustomer->customerId);
        printf("Now you can book slots for this customer using the 'Book Slot' option.\n");
    } else {
        printf("Memory allocation error.\n");
    }
}

void bookSlot(struct Customer* customerHead, struct Booking** bookingHead, unsigned int *lastCustomerId) {
    char name[50];
    int selectedSport, selectedTimeSlot;

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", name);

    struct Customer* customer = findCustomerByName(customerHead, name);
    if (customer == NULL) {
        printf("Customer '%s' not found! Please register the customer first using 'Add Customer' option.\n", name);
        return;
    }

    printf("Customer found: %s (ID: %d)\n", customer->name, customer->customerId);

    // Check available slots and let user select
    if (listAvailableSports(*bookingHead, &selectedSport, &selectedTimeSlot)) {
        // Check if customer already has a booking in this sport
        if (hasBookingInSport(*bookingHead, customer->customerId, selectedSport)) {
            printf("Error: Customer '%s' already has a booking in %s. Each customer can book only one slot per sport.\n", 
                   customer->name, sportName(selectedSport));
            return;
        }

        struct Booking* newBooking = createBooking(customer->customerId, selectedSport, selectedTimeSlot);
        if (newBooking != NULL) {
            addBooking(bookingHead, newBooking);
            
            int startTime = 8 + (selectedTimeSlot - 1) * 2;
            int endTime = startTime + 2;
            printf("Slot booked successfully for customer '%s'!\n", customer->name);
            printf("Booking ID: %d\n", newBooking->bookingId);
            printf("Sport: %s\n", sportName(selectedSport));
            printf("Time Slot: %02d:00 - %02d:00\n", startTime, endTime);
        } else {
            printf("Memory allocation error.\n");
        }
    } else {
        printf("Booking failed. Please try again with an available slot.\n");
    }
}

void displayBookedSlots(struct Booking* bookingHead, struct Customer* customerHead) {
    if (bookingHead == NULL) {
        printf("No slots have been booked.\n");
        return;
    }

    printf("Booked Slots:\n");

    int slotsCount[6][6] = {0}; // [sport][timeSlot]

    struct Booking* current = bookingHead;
    while (current != NULL) {
        if (current->sport >= 1 && current->sport <= 6 && 
            current->timeSlot >= 1 && current->timeSlot <= 6) {
            slotsCount[current->sport - 1][current->timeSlot - 1]++;
        }
        current = current->next;
    }

    for (int i = 0; i < 6; i++) {
        bool sportHasBookings = false;
        for (int j = 0; j < 6; j++) {
            if (slotsCount[i][j] > 0) {
                sportHasBookings = true;
                break;
            }
        }
        
        if (sportHasBookings) {
            printf("%s:\n", sportName(i + 1));
            for (int j = 0; j < 6; j++) {
                if (slotsCount[i][j] > 0) {
                    int startTime = 8 + j * 2;
                    int endTime = startTime + 2;
                    printf("  Time Slot %02d:00 - %02d:00: %d booking(s)\n", 
                           startTime, endTime, slotsCount[i][j]);
                }
            }
        }
    }
}

void freeCustomers(struct Customer* head) {
    struct Customer* current = head;
    while (current != NULL) {
        struct Customer* next = current->next;
        free(current);
        current = next;
    }
}

void freeBookings(struct Booking* head) {
    struct Booking* current = head;
    while (current != NULL) {
        struct Booking* next = current->next;
        free(current);
        current = next;
    }
}

void listCustomerInfo(struct Customer* head) {
    if (head == NULL) {
        printf("No customers are registered.\n");
        return;
    }

    printf("Registered Customers:\n");
    struct Customer* current = head;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Email: %s, Phone: %s\n", 
               current->customerId, current->name, current->age, current->email, current->phoneNumber);
        current = current->next;
    }
    printf("\n");
}

void searchCustomer(struct Customer* customerHead, struct Booking* bookingHead) {
    if (customerHead == NULL) {
        printf("No customers are registered.\n");
        return;
    }

    int searchId;
    char searchName[50];
    int searchBy;

    printf("Search by:\n");
    printf("1. Customer Name\n");
    printf("2. Customer ID\n");
    printf("Enter your choice: ");
    scanf("%d", &searchBy);

    struct Customer* customer = NULL;

    if (searchBy == 1) {
        printf("Enter Customer Name to Search: ");
        scanf(" %[^\n]", searchName);
        customer = findCustomerByName(customerHead, searchName);
        if (customer == NULL) {
            printf("Customer with name '%s' not found.\n", searchName);
            return;
        }
    } else if (searchBy == 2) {
        printf("Enter Customer ID to Search: ");
        scanf("%d", &searchId);
        customer = findCustomerById(customerHead, searchId);
        if (customer == NULL) {
            printf("Customer with ID %d not found.\n", searchId);
            return;
        }
    } else {
        printf("Invalid choice for search. Please try again.\n");
        return;
    }

    printf("Customer Found:\n");
    printf("ID: %u\n", customer->customerId);
    printf("Name: %s\n", customer->name);
    printf("Age: %d\n", customer->age);
    printf("Email: %s\n", customer->email);
    printf("Phone: %s\n", customer->phoneNumber);
    printf("Address: %s\n", customer->address);
    
    // Show customer's bookings
    printf("Bookings:\n");
    struct Booking* booking = bookingHead;
    bool hasBookings = false;
    while (booking != NULL) {
        if (booking->customerId == customer->customerId) {
            int startTime = 8 + (booking->timeSlot - 1) * 2;
            int endTime = startTime + 2;
            printf("  - %s: %02d:00 - %02d:00 (Booking ID: %d)\n", 
                   sportName(booking->sport), startTime, endTime, booking->bookingId);
            hasBookings = true;
        }
        booking = booking->next;
    }
    if (!hasBookings) {
        printf("  No bookings found.\n");
    }
}

void deleteCustomer(struct Customer** customerHead, struct Booking** bookingHead, const char* deleteName) {
    if (*customerHead == NULL) {
        printf("No customers are registered.\n");
        return;
    }

    struct Customer* customer = findCustomerByName(*customerHead, deleteName);
    if (customer == NULL) {
        printf("Customer with name '%s' not found.\n", deleteName);
        return;
    }

    int customerId = customer->customerId;

    // Delete all bookings for this customer
    struct Booking* bookingCurrent = *bookingHead;
    struct Booking* bookingPrev = NULL;
    int deletedBookings = 0;

    while (bookingCurrent != NULL) {
        if (bookingCurrent->customerId == customerId) {
            if (bookingPrev == NULL) {
                *bookingHead = bookingCurrent->next;
            } else {
                bookingPrev->next = bookingCurrent->next;
            }
            struct Booking* toDelete = bookingCurrent;
            bookingCurrent = bookingCurrent->next;
            free(toDelete);
            deletedBookings++;
        } else {
            bookingPrev = bookingCurrent;
            bookingCurrent = bookingCurrent->next;
        }
    }

    // Delete the customer
    struct Customer* current = *customerHead;
    struct Customer* prev = NULL;

    while (current != NULL) {
        if (stringCompareIgnoreCase(current->name, deleteName) == 0) {
            if (prev == NULL) {
                *customerHead = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Customer '%s' and all their %d booking(s) have been permanently deleted.\n", 
                   deleteName, deletedBookings);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void cancelBooking(struct Booking** bookingHead, struct Customer* customerHead, const char* cancelName) {
    if (*bookingHead == NULL) {
        printf("No bookings found.\n");
        return;
    }

    struct Customer* customer = findCustomerByName(customerHead, cancelName);
    if (customer == NULL) {
        printf("Customer with name '%s' not found.\n", cancelName);
        return;
    }

    // Find and display customer's bookings
    struct Booking* booking = *bookingHead;
    int bookingCount = 0;
    printf("Bookings for customer '%s':\n", cancelName);
    
    while (booking != NULL) {
        if (booking->customerId == customer->customerId) {
            int startTime = 8 + (booking->timeSlot - 1) * 2;
            int endTime = startTime + 2;
            printf("%d. %s: %02d:00 - %02d:00 (Booking ID: %d)\n", 
                   ++bookingCount, sportName(booking->sport), startTime, endTime, booking->bookingId);
        }
        booking = booking->next;
    }

    if (bookingCount == 0) {
        printf("No bookings found for customer '%s'.\n", cancelName);
        return;
    }

    int bookingIdToCancel;
    printf("Enter Booking ID to cancel: ");
    scanf("%d", &bookingIdToCancel);

    // Cancel the specific booking
    struct Booking* current = *bookingHead;
    struct Booking* prev = NULL;

    while (current != NULL) {
        if (current->bookingId == bookingIdToCancel && current->customerId == customer->customerId) {
            int startTime = 8 + (current->timeSlot - 1) * 2;
            int endTime = startTime + 2;
            
            printf("Booking canceled: %s (%02d:00 - %02d:00) for customer '%s'.\n", 
                   sportName(current->sport), startTime, endTime, cancelName);
            printf("Customer details remain in the system.\n");

            if (prev == NULL) {
                *bookingHead = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Booking ID %d not found for customer '%s'.\n", bookingIdToCancel, cancelName);
}

int main() {
    struct Customer* customerList = NULL;
    struct Booking* bookingList = NULL;
    int choice;

    while (1) {
        printf("\nSports Center Management System\n");
        printf("1. Add Customer (Register new customer)\n");
        printf("2. List Customers\n");
        printf("3. Search Customer\n");
        printf("4. Delete Customer (Permanent deletion)\n");
        printf("5. Book Slot (For existing customers)\n");
        printf("6. Cancel Booking (Cancel specific booking only)\n");
        printf("7. Display Booked Slots\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerCustomer(&customerList, &lastCustomerId);
                break;
            case 2:
                listCustomerInfo(customerList);
                break;
            case 3:
                searchCustomer(customerList, bookingList);
                break;
            case 4:
                {
                    char deleteName[50];
                    printf("Enter Customer Name to Delete: ");
                    scanf(" %[^\n]", deleteName);
                    deleteCustomer(&customerList, &bookingList, deleteName);
                    break;
                }
            case 5:
                bookSlot(customerList, &bookingList, &lastCustomerId);
                break;
            case 6:
                {
                    char cancelName[50];
                    printf("Enter Customer Name to Cancel Booking: ");
                    scanf(" %[^\n]", cancelName);
                    cancelBooking(&bookingList, customerList, cancelName);
                    break;
                }
            case 7:
                displayBookedSlots(bookingList, customerList);
                break;
            case 8:
                freeCustomers(customerList);
                freeBookings(bookingList);
                printf("Thank you for using Sports Center Management System!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}