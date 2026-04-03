#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 10
#define MAX_BOOKINGS 50

// Room categories
typedef enum {
    DELUXE,
    SUPER_DELUXE,
    KING_SIZE
} RoomCategory;

// Room structure
typedef struct {
    int roomNumber;
    RoomCategory category;
    int isBooked;
    int price;
} Room;

// Customer structure
typedef struct {
    char name[50];
    char nationalId[30];
    char phone[20];
} Customer;

// Booking structure
typedef struct {
    Customer customer;
    Room *room;
    int days;
    int totalCost;
} Booking;

// Global data
Room rooms[MAX_ROOMS];
Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;
int roomCount = 6;

// Initialize rooms
void initRooms() {
    rooms[0] = (Room){101, DELUXE, 0, 2000};
    rooms[1] = (Room){102, DELUXE, 0, 2000};
    rooms[2] = (Room){201, SUPER_DELUXE, 0, 4000};
    rooms[3] = (Room){202, SUPER_DELUXE, 0, 4000};
    rooms[4] = (Room){301, KING_SIZE, 0, 6000};
    rooms[5] = (Room){302, KING_SIZE, 0, 6000};
}

// Show available rooms
void showAvailableRooms() {
    printf("\n--- AVAILABLE ROOMS ---\n");
    int found = 0;
    for (int i = 0; i < roomCount; i++) {
        if (!rooms[i].isBooked) {
            printf("Room %d | Price: %d\n", rooms[i].roomNumber, rooms[i].price);
            found = 1;
        }
    }
    if (!found) printf("No rooms available.\n");
}

// Book room
void bookRoom() {
    Customer c;
    int roomNo, days;

    printf("Enter Name: ");
    scanf("%s", c.name);
    printf("Enter NID: ");
    scanf("%s", c.nationalId);
    printf("Enter Phone: ");
    scanf("%s", c.phone);

    showAvailableRooms();

    printf("Enter Room Number: ");
    scanf("%d", &roomNo);
    printf("Enter Days: ");
    scanf("%d", &days);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNo && !rooms[i].isBooked) {
            rooms[i].isBooked = 1;

            bookings[bookingCount].customer = c;
            bookings[bookingCount].room = &rooms[i];
            bookings[bookingCount].days = days;
            bookings[bookingCount].totalCost = rooms[i].price * days;

            printf("Booked successfully! Total Cost: %d\n",
                   bookings[bookingCount].totalCost);

            bookingCount++;
            return;
        }
    }
    printf("Room not available!\n");
}

// View bookings
void viewBookings() {
    printf("\n--- ALL BOOKINGS ---\n");
    if (bookingCount == 0) {
        printf("No bookings yet.\n");
        return;
    }

    for (int i = 0; i < bookingCount; i++) {
        printf("Room %d | %s | Days: %d | Cost: %d\n",
               bookings[i].room->roomNumber,
               bookings[i].customer.name,
               bookings[i].days,
               bookings[i].totalCost);
    }
}

// Cancel booking
void cancelBooking() {
    int roomNo;
    printf("Enter Room Number to cancel: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].room->roomNumber == roomNo) {
            bookings[i].room->isBooked = 0;

            // shift bookings
            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }

            bookingCount--;
            printf("Booking cancelled.\n");
            return;
        }
    }
    printf("Booking not found.\n");
}

// Main menu
int main() {
    initRooms();
    int choice;

    while (1) {
        printf("\n==== HOTEL MANAGEMENT ====\n");
        printf("1. View Available Rooms\n");
        printf("2. Book Room\n");
        printf("3. View Bookings\n");
        printf("4. Cancel Booking\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showAvailableRooms();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                viewBookings();
                break;
            case 4:
                cancelBooking();
                break;
            case 5:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}