#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip>

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

// --- FUNCTION PROTOTYPES ---
void generateOrders(DeliveryOrder arr[], int size, int caseType);
void shellSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements);
void combSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements);
void displayTable(const DeliveryOrder arr[], int size);
void writeToFile(const string &filename, const DeliveryOrder arr[], int size);

int main() {
    srand(time(0)); // Seed random generator
    
    const int MAX_SIZE = 1000; 
    DeliveryOrder orders[MAX_SIZE];
    
    int dataSize = 100; // Default size
    int choice = 0;
    bool dataGenerated = false;

    while (choice != 5) {
        cout << "\n==============================================\n";
        cout << "      FOOD DELIVERY TRACKING SYSTEM\n";
        cout << "==============================================\n";
        cout << "1. Generate Original Dataset (Best/Worst/Average)\n";
        cout << "2. Run Shell Sort (Sort by Delivery Time)\n";
        cout << "3. Run Comb Sort (Sort by Delivery Time)\n";
        cout << "4. Display Current Dataset Table\n";
        cout << "5. Exit System\n";
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
                
                // Write the raw un-sorted data to file
                writeToFile("original_dataset.txt", orders, dataSize);
                
                cout << "\n--- Dataset Generated & Saved to 'original_dataset.txt'! ---\n";
                displayTable(orders, dataSize > 10 ? 10 : dataSize); // Show preview of first 10
                break;
            }
            case 2:
                if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    long long comparisons = 0;
                    long long movements = 0;

                    cout << "\nRunning Shell Sort on " << dataSize << " records...\n";

                    auto start = chrono::high_resolution_clock::now();
                    shellSortByTime(orders, dataSize, comparisons, movements);
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
                    
                    writeToFile("shell_sorted_dataset.txt", orders, dataSize);
                    cout << "[*] Sorted result saved to 'shell_sorted_dataset.txt'\n";
                    
                    cout << "\nShowing Top 5 Fastest Deliveries:\n";
                    displayTable(orders, dataSize > 5 ? 5 : dataSize);
                }
                break;

            case 3:
                if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    long long comparisons = 0;
                    long long movements = 0;

                    cout << "\nRunning Comb Sort on " << dataSize << " records...\n";

                    auto start = chrono::high_resolution_clock::now();
                    combSortByTime(orders, dataSize, comparisons, movements);
                    auto end = chrono::high_resolution_clock::now();
                    
                    chrono::duration<double, milli> duration = end - start;

                    cout << "\n==============================================\n";
                    cout << "          COMB SORT EXECUTION STATS\n";
                    cout << "==============================================\n";
                    cout << "Dataset Size      : " << dataSize << " records\n";
                    cout << "Execution Time    : " << duration.count() << " ms\n";
                    cout << "Total Comparisons : " << comparisons << "\n";
                    cout << "Total Movements   : " << movements << "\n";
                    cout << "==============================================\n";
                    
                    writeToFile("comb_sorted_dataset.txt", orders, dataSize);
                    cout << "[*] Sorted result saved to 'comb_sorted_dataset.txt'\n";
                    
                    cout << "\nShowing Top 5 Fastest Deliveries:\n";
                    displayTable(orders, dataSize > 5 ? 5 : dataSize);
                }
                break;

            case 4:
                if (!dataGenerated) {
                    cout << "\n[!] Error: No data available to display!\n";
                } else {
                    cout << "\n--- Displaying Full Current Dataset (" << dataSize << " records) ---\n";
                    displayTable(orders, dataSize);
                }
                break;

            case 5:
                cout << "\nExiting system. Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice. Please enter 1 to 5.\n";
        }
    }
    return 0;
}

// MEMBER 1: Universal Data Generator
void generateOrders(DeliveryOrder arr[], int size, int caseType) {
    for (int i = 0; i < size; i++) {
        arr[i].orderID = 1000 + i;
        arr[i].customerName = "Cust_" + to_string(i + 1);
        arr[i].restaurantName = "Rest_" + to_string((i % 5) + 1);
        arr[i].foodItem = "Meal_" + to_string((i % 10) + 1);
        arr[i].totalPrice = (rand() % 500) / 10.0 + 10.0; 
        arr[i].orderStatus = "Pending";

        if (caseType == 1) {
            arr[i].deliveryTimeMinutes = 10 + i; // Best Case (Pre-sorted)
        } 
        else if (caseType == 2) {
            arr[i].deliveryTimeMinutes = (size + 15) - i; // Worst Case (Reverse sorted)
        } 
        else if (caseType == 3) {
            arr[i].deliveryTimeMinutes = (rand() % 111) + 10; // Average Case (Random)
        }
    }
}

// MEMBER 1: Manual Shell Sort Implementation
void shellSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements) {
    comparisons = 0;
    movements = 0;
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Step-by-step trace demonstration for small arrays (Rubric Visualization Requirement)
        if (n <= 10) {
            cout << "[Visualizer] Current pass gap tracking distance: " << gap << " elements\n";
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
    cout << "--- Shell Sort Completed! ---\n";
}

// MEMBER 3: Manual Comb Sort Implementation (Integrated from your teammate's file)
void combSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements) {
    comparisons = 0;
    movements = 0;
    
    int gap = n;
    double shrink = 1.3;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (int)(gap / shrink);
        if (gap < 1) {
            gap = 1;
        }

        if (n <= 10) {
            cout << "[Visualizer] Current pass gap tracking distance: " << gap << " elements\n";
        }

        swapped = false;

        for (int i = 0; i < n - gap; i++) {
            comparisons++; // Comparing arr[i] and arr[i+gap]
            if (arr[i].deliveryTimeMinutes > arr[i + gap].deliveryTimeMinutes) {
                // Manual swap block without using external swap functions
                DeliveryOrder temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                
                movements += 3; // A physical swap counts as 3 variable movements
                swapped = true;
            }
        }
    }
    cout << "--- Comb Sort Completed! ---\n";
}

// TEAMMATE FUNCTION: Display structural console table
void displayTable(const DeliveryOrder arr[], int size) {
    cout << setfill('-') << setw(85) << "-" << endl;
    cout << setfill(' ');
    cout << "| " << setw(8) << left << "OrderID" 
         << "| " << setw(10) << left << "Customer" 
         << "| " << setw(12) << left << "Restaurant" 
         << "| " << setw(10) << left << "Food Item" 
         << "| " << setw(12) << left << "Total Price" 
         << "| " << setw(14) << left << "Delivery Time" 
         << "|\n";
    cout << setfill('-') << setw(85) << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < size; i++) {
        cout << "| " << setw(8) << left << arr[i].orderID 
             << "| " << setw(10) << left << arr[i].customerName 
             << "| " << setw(12) << left << arr[i].restaurantName 
             << "| " << setw(10) << left << arr[i].foodItem 
             << "| $" << setw(10) << fixed << setprecision(2) << left << arr[i].totalPrice 
             << "| " << setw(10) << left << arr[i].deliveryTimeMinutes << " mins " 
             << "|\n";
    }
    cout << setfill('-') << setw(85) << "-" << endl;
    cout << setfill(' ');
}

// TEAMMATE FUNCTION: Write datasets to flat disk text files
void writeToFile(const string &filename, const DeliveryOrder arr[], int size) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "[!] Error opening file for writing: " << filename << endl;
        return;
    }

    outFile << "OrderID,CustomerName,RestaurantName,FoodItem,TotalPrice,DeliveryTimeMinutes,OrderStatus\n";
    for (int i = 0; i < size; i++) {
        outFile << arr[i].orderID << ","
                << arr[i].customerName << ","
                << arr[i].restaurantName << ","
                << arr[i].foodItem << ","
                << fixed << setprecision(2) << arr[i].totalPrice << ","
                << arr[i].deliveryTimeMinutes << ","
                << arr[i].orderStatus << "\n";
    }
    outFile.close();
}