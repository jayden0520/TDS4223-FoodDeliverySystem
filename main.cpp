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
void combSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements);

int main() {
    srand(time(0)); 
    
    // Create a static array large enough to hold the maximum required records
    const int MAX_SIZE = 1000; 
    DeliveryOrder orders[MAX_SIZE];
    
    int dataSize = 100; // Default size
    int choice = 0;
    bool dataGenerated = false;

    while (choice != 4) {
        cout << "\n==============================================\n";
        cout << "      FOOD DELIVERY TRACKING SYSTEM\n";
        cout << "==============================================\n";
        cout << "1. Generate Original Dataset (Best/Worst/Average)\n";
        cout << "2. Run Shell Sort (Sort by Delivery Time)\n";
        cout << "3. Run Comb Sort (Sort by Delivery Time)\n";
        cout << "4. Exit System\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nEnter dataset size to generate (e.g., 100, 300, 500): ";
                cin >> dataSize;

                if (dataSize > MAX_SIZE || dataSize <= 0) {
                    cout << "[!] Invalid size. Setting to default 100.\n";
                    dataSize = 100;
                }

                int caseType;
                cout << "Select Case (1=Best, 2=Worst, 3=Average): ";
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

                    // Start timer
                    auto start = chrono::high_resolution_clock::now();

                    shellSortByTime(orders, dataSize, comparisons, movements);

                    // Stop timer
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, micro> duration = end - start;

                    cout << "\n==============================================\n";
                    cout << "          SHELL SORT EXECUTION STATS\n";
                    cout << "==============================================\n";
                    cout << "Dataset Size      : " << dataSize << " records\n";
                    cout << "Execution Time    : " << duration.count() << " us\n";
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
                if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    long long comparisons = 0;
                    long long movements = 0;

                    cout << "\nRunning Comb Sort on " << dataSize << " records...\n";

                    // Start timer
                    auto start = chrono::high_resolution_clock::now();

                    combSortByTime(orders, dataSize, comparisons, movements);

                    // Stop timer
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, micro> duration = end - start;

                    cout << "\n==============================================\n";
                    cout << "           COMB SORT EXECUTION STATS\n";
                    cout << "==============================================\n";
                    cout << "Dataset Size      : " << dataSize << " records\n";
                    cout << "Execution Time    : " << duration.count() << " us\n";
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
            case 4:
                cout << "\nExiting system. Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice. Please enter 1, 2, 3, or 4.\n";
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

// 100% Manual Algorithm Implementation - Shell Sort (Member 2)
void shellSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements) {
    comparisons = 0;
    movements = 0;
    
    for (int gap = n / 2; gap > 0; gap /= 2) {

        if (n <= 20) {
            cout << "\n[Visualizer] Current Gap Size: " << gap << "\n";
        }

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

// 100% Manual Algorithm Implementation - Comb Sort (Member 3)
// -------------------------------------------------------------
// Comb Sort improves Bubble Sort by comparing elements that are a
// "gap" distance apart. The gap starts at n and shrinks by the
// factor 1.3 each pass, until it reaches 1.
// -------------------------------------------------------------
void combSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements) {
    comparisons = 0;
    movements = 0;

    int gap = n;
    const double shrinkFactor = 1.3;
    bool sorted = false;

    while (!sorted) {

        // Shrink the gap for this pass
        gap = (int)(gap / shrinkFactor);
        if (gap <= 1) {
            gap = 1;
            sorted = true; // assume sorted; reset to false below if a swap occurs
        }

        if (n <= 20) {
            cout << "\n[Visualizer] Current Gap Size: " << gap << "\n";
        }

        // Compare elements that are 'gap' positions apart
        for (int i = 0; i + gap < n; i++) {
            comparisons++;
            if (arr[i].deliveryTimeMinutes > arr[i + gap].deliveryTimeMinutes) {
                // Swap arr[i] and arr[i + gap]  (3 element assignments)
                DeliveryOrder temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                movements += 3;
                sorted = false;
            }
        }
    }
    cout << "\n--- Comb Sort Completed! ---\n";
}
