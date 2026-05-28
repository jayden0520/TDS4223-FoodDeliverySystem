#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Struct representation for a real-world scenario record
struct DeliveryOrder {
    int orderID;
    string customerName;
    string restaurantName;
    string foodItem;
    double totalPrice;
    int deliveryTimeMinutes; // The primary key for benchmarking
    string orderStatus;
};

void generateOrders(DeliveryOrder arr[], int size, int caseType);
void shellSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements);

int main() {
    srand(time(0)); // Seed random generator
    
    // Default size is 100, but can be changed to 300 or 500 for benchmarking
    int dataSize = 100; 
    DeliveryOrder orders[dataSize];
    
    int choice = 0;
    bool dataGenerated = false;

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
                    long long comparisons = 0;
                    long long movements = 0;

                    cout << "\nRunning Shell Sort on " << dataSize << " records...\n";

                    // Start timer using basic utility library clock
                    auto start = chrono::high_resolution_clock::now();

                    // Running your MANUALLY implemented algorithm
                    shellSortByTime(orders, dataSize, comparisons, movements);

                    // Stop timer
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> duration = end - start;

                    cout << "\n==============================================\n";
                    cout << "          SHELL SORT EXECUTION STATS\n";
                    cout << "==============================================\n";
                    cout << "Dataset Size      : " << dataSize << " records\n";
                    cout << "Execution Time    : " << duration.count() << " ms\n";
                    cout << "Total Comparisons : " << comparisons << "\n";
                    cout << "Total Movements   : " << movements << "\n";
                    cout << "==============================================\n";
                    
                    cout << "\nShowing Top 5 Fastest Deliveries:\n";
                    for (int i = 0; i < 5; i++) {
                        cout << "Order ID: " << orders[i].orderID 
                             << " | Time: " << orders[i].deliveryTimeMinutes << " mins"
                             << " | Price: $" << orders[i].totalPrice << "\n";
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

// Universal Data Generator
void generateOrders(DeliveryOrder arr[], int size, int caseType) {
    for (int i = 0; i < size; i++) {
        arr[i].orderID = 1000 + i;
        arr[i].customerName = "Cust_" + to_string(i + 1);
        arr[i].restaurantName = "Rest_" + to_string((i % 5) + 1);
        arr[i].foodItem = "Meal_" + to_string((i % 10) + 1);
        arr[i].totalPrice = (rand() % 500) / 10.0 + 10.0; 
        arr[i].orderStatus = "Pending";

        if (caseType == 1) {
            arr[i].deliveryTimeMinutes = 10 + i; // Best Case (Sorted)
        } 
        else if (caseType == 2) {
            arr[i].deliveryTimeMinutes = (size + 15) - i; // Worst Case (Reverse Sorted)
        } 
        else if (caseType == 3) {
            arr[i].deliveryTimeMinutes = (rand() % 111) + 10; // Average Case (Random)
        }
    }
}

// 100% Manual Algorithm Implementation
void shellSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements) {
    comparisons = 0;
    movements = 0;
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            DeliveryOrder temp = arr[i];
            movements++; 
            int j;

            for (j = i; j >= gap; j -= gap) {
                comparisons++; 
                if (arr[j - gap].deliveryTimeMinutes > temp.deliveryTimeMinutes) {
                    arr[j] = arr[j - gap];
                    movements++; 
                } else {
                    break;
                }
            }
            arr[j] = temp;
            movements++; 
        }
    }
    cout << "\n--- Shell Sort Completed! ---\n";
}