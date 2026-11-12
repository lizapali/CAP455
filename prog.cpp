#include <iostream>
using namespace std;

const int MAX_SLOTS = 5;
const double RATE_PER_HOUR = 20.0;

struct Slot {
    int slotId;
    int isOccupied;        
    char vehicleNumber[20];   
    int entryHour;           
    int entryMinute;         
};

Slot station[MAX_SLOTS];

void initializeStation() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        station[i].slotId = i + 1;
        station[i].isOccupied = 0; 
        station[i].vehicleNumber[0] = '\0';
        station[i].entryHour = 0;
        station[i].entryMinute = 0;
    }
}

void displaySlots() {
    cout << "\n--- EV Charging Station Status ---\n";
    cout << "Slot\tStatus\t\tVehicle No\tEntry Time\n";
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < MAX_SLOTS; i++) {
        cout << station[i].slotId << "\t";
        
        if (station[i].isOccupied == 1) {
            cout << "Occupied\t" << station[i].vehicleNumber << "\t\t";
            cout << station[i].entryHour << ":" << station[i].entryMinute << "\n";
        } else {
            cout << "Available\t---\t\t--:--\n";
        }
    }
}

void checkIn() {
    int freeIndex = -1;

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (station[i].isOccupied == 0) {
            freeIndex = i;
            break;
        }
    }

    if (freeIndex == -1) {
        cout << "\nError: Station is full! No slots available.\n";
        return;
    }

    cout << "\nEnter Vehicle Number: ";
    cin >> station[freeIndex].vehicleNumber;

    cout << "Enter Entry Hour (0-23): ";
    cin >> station[freeIndex].entryHour;

    cout << "Enter Entry Minute (0-59): ";
    cin >> station[freeIndex].entryMinute;

    station[freeIndex].isOccupied = 1;

    cout << "Success: Slot #" << station[freeIndex].slotId << " allocated!\n";
}

void checkOut() {
    int id;
    cout << "\nEnter Slot ID to vacate (1 to " << MAX_SLOTS << "): ";
    cin >> id;

    int index = id - 1;

    if (index < 0 || index >= MAX_SLOTS) {
        cout << "Error: Invalid Slot ID!\n";
        return;
    }
    if (station[index].isOccupied == 0) {
        cout << "Error: Slot is already empty!\n";
        return;
    }

    int exitHour, exitMinute;
    cout << "Enter Exit Hour (0-23): ";
    cin >> exitHour;
    cout << "Enter Exit Minute (0-59): ";
    cin >> exitMinute;

    int entryTotalMin = (station[index].entryHour * 60) + station[index].entryMinute;
    int exitTotalMin = (exitHour * 60) + exitMinute;

    if (exitTotalMin < entryTotalMin) {
        exitTotalMin += 24 * 60;
    }

    int totalMinutes = exitTotalMin - entryTotalMin;
    double totalHours = totalMinutes / 60.0;
    double billAmount = totalHours * RATE_PER_HOUR;

    cout << "\n--- BILL RECEIPT ---\n";
    cout << "Vehicle Number : " << station[index].vehicleNumber << "\n";
    cout << "Slot Number    : " << station[index].slotId << "\n";
    cout << "Total Time     : " << totalMinutes << " minutes (" << totalHours << " hours)\n";
    cout << "Rate per Hour  : " << RATE_PER_HOUR << "\n";
    cout << "Total Bill     : " << billAmount << "\n";
    cout << "--------------------\n";

    station[index].isOccupied = 0;
    station[index].vehicleNumber[0] = '\0';
    station[index].entryHour = 0;
    station[index].entryMinute = 0;

    cout << "Slot #" << id << " is now vacant.\n";
}

int main() {
    initializeStation();
    int choice;

    do {
        cout << "\n=== EV STATION MENU ===\n";
        cout << "1. Display Slots\n";
        cout << "2. Check-In Vehicle\n";
        cout << "3. Check-Out & Bill\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displaySlots();
                break;
            case 2:
                checkIn();
                break;
            case 3:
                checkOut();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}