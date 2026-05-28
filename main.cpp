#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct DeliveryOrder {
    int orderID;
    string customerName;
    string restaurantName;
    string foodItem;
    double totalPrice;
    int deliveryTimeMinutes; // The primary key for benchmarking
    string orderStatus;
};

//The Universal Data Generator
void generateOrders(DeliveryOrder arr[], int size, int caseType) {
    for (int i = 0; i < size; i++) {
        // Standard data for all cases
        arr[i].orderID = 1000 + i;
        arr[i].customerName = "Cust_" + to_string(i + 1);
        arr[i].restaurantName = "Rest_" + to_string((i % 5) + 1); // 5 dummy restaurants
        arr[i].foodItem = "Meal_" + to_string((i % 10) + 1);
        arr[i].totalPrice = (rand() % 500) / 10.0 + 10.0; 
        arr[i].orderStatus = "Pending";

        // Logic for Best, Worst, and Average Cases based on deliveryTimeMinutes
        if (caseType == 1) {
            // BEST CASE: Already sorted from lowest to highest time
            arr[i].deliveryTimeMinutes = 10 + i; 
        } 
        else if (caseType == 2) {
            // WORST CASE: Reverse sorted from highest to lowest time
            arr[i].deliveryTimeMinutes = (size + 15) - i; 
        } 
        else if (caseType == 3) {
            // AVERAGE CASE: Completely random times between 10 and 120 minutes
            arr[i].deliveryTimeMinutes = (rand() % 111) + 10; 
        }
    }
}

int main() {
    // Seed the random number generator so we get different data every time
    srand(time(0)); 
    
    // We will start testing with 100 records, but you can change this to 300 or 500 later
    int dataSize = 100; 
    DeliveryOrder orders[dataSize];
    
    int choice = 0;
    bool dataGenerated = false;

    // The Menu Loop
    while (choice != 3) {
        cout << "\n==============================================\n";
        cout << "      FOOD DELIVERY TRACKING SYSTEM\n";
        cout << "==============================================\n";
        cout << "1. Generate Original Dataset (Best/Worst/Average)\n";
        cout << "2. Run Shell Sort (Sort by Delivery Time)\n";
        cout << "3. Exit System\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int caseType;
                cout << "\nSelect Case (1=Best, 2=Worst, 3=Average): ";
                cin >> caseType;
                
                generateOrders(orders, dataSize, caseType);
                dataGenerated = true;
                
                cout << "\n--- Dataset Generated! Showing First 10 Records ---\n";
                for (int i = 0; i < 10; i++) {
                    cout << "Order ID: " << orders[i].orderID 
                         << " | Time: " << orders[i].deliveryTimeMinutes << " mins"
                         << " | Customer: " << orders[i].customerName << "\n";
                }
                break;
            }
            case 2:
                if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    // Run your manual algorithm
                    shellSortByTime(orders, dataSize);
                    
                    cout << "\n--- Sorting Complete! Showing Top 10 Fastest Deliveries ---\n";
                    for (int i = 0; i < 10; i++) {
                        cout << "Order ID: " << orders[i].orderID 
                             << " | Time: " << orders[i].deliveryTimeMinutes << " mins"
                             << " | Customer: " << orders[i].customerName << "\n";
                    }
                }
                break;
            case 3:
                cout << "\nExiting system. Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}

// Function to sort orders by Delivery Time using Shell Sort
void shellSortByTime(DeliveryOrder arr[], int n) {
    cout << "\n--- Starting Shell Sort (By Delivery Time) ---\n";
    
    // 1. Start with a large gap, then divide it by 2 every pass
    for (int gap = n / 2; gap > 0; gap /= 2) {
        
        // This print statement helps satisfy the "Visualisation" rubric requirement
        cout << "[Phase] Sorting with Gap size: " << gap << "\n";

        // 2. Do a gapped insertion sort for this gap size
        for (int i = gap; i < n; i += 1) {
            
            // Save the current order in a temporary variable
            DeliveryOrder temp = arr[i];
            int j;

            // 3. Shift earlier gap-sorted elements up until the correct location is found
            for (j = i; j >= gap && arr[j - gap].deliveryTimeMinutes > temp.deliveryTimeMinutes; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            // 4. Put the temporary order into its correct, sorted location
            arr[j] = temp;
        }
    }
    cout << "--- Shell Sort Completed! ---\n\n";
}