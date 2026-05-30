#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Struct representation for a real-world scenario record
// Written by: Member 1
struct DeliveryOrder {
    int orderID;
    string customerName;
    string restaurantName;
    string foodItem;
    double totalPrice;
    int deliveryTimeMinutes; // The primary key for benchmarking
    string orderStatus;
};

// Function prototypes (existing)
void generateOrders(DeliveryOrder arr[], int size, int caseType);
void shellSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements);
void combSortByTime(DeliveryOrder arr[], int n, long long &comparisons, long long &movements);



// Written by: Member 4 - Performance Comparison Table
void displayComparisonTable(int sizes[], double shellTime[], double combTime[], 
                            long long shellComp[], long long combComp[], int numSizes) {
    cout << "\n";
    cout << "========================================================================================\n";
    cout << "                     PERFORMANCE COMPARISON: SHELL SORT vs COMB SORT\n";
    cout << "========================================================================================\n";
    cout << "Size\t| Shell Time(us)\t| Comb Time(us)\t| Shell Comp\t| Comb Comp\n";
    cout << "----------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numSizes; i++) {
        cout << sizes[i] << "\t| " << shellTime[i] << "\t\t| " << combTime[i] 
             << "\t\t| " << shellComp[i] << "\t\t| " << combComp[i] << "\n";
    }
    cout << "========================================================================================\n";
}

// Written by: Member 4 - Categorised Orders Display
void displayCategorisedOrders(DeliveryOrder arr[], int n) {
    cout << "\n========== CATEGORISED DELIVERY ORDERS ==========\n";
    
    cout << "\n[FASTEST 5 DELIVERIES]\n";
    for (int i = 0; i < min(5, n); i++) {
        cout << "  " << i+1 << ". Order ID: " << arr[i].orderID 
             << " | Time: " << arr[i].deliveryTimeMinutes << " mins"
             << " | Customer: " << arr[i].customerName << "\n";
    }
    
    cout << "\n[SLOWEST 5 DELIVERIES]\n";
    int startIdx = max(0, n-5);
    for (int i = startIdx; i < n; i++) {
        cout << "  " << i+1 << ". Order ID: " << arr[i].orderID 
             << " | Time: " << arr[i].deliveryTimeMinutes << " mins"
             << " | Customer: " << arr[i].customerName << "\n";
    }
    
    cout << "\n[ORDERS EXCEEDING 60 MINUTES]\n";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].deliveryTimeMinutes > 60) {
            cout << "  Order ID: " << arr[i].orderID 
                 << " | Time: " << arr[i].deliveryTimeMinutes << " mins"
                 << " | Customer: " << arr[i].customerName << "\n";
            count++;
        }
    }
    if (count == 0) cout << "  No orders exceed 60 minutes.\n";
    
    cout << "\n[TOTAL ORDERS PROCESSED]: " << n << " records\n";
    cout << "==================================================\n";
}



int main() {
    srand(time(0)); 
    
    // Create a static array large enough to hold the maximum required records
    const int MAX_SIZE = 1000; 
    DeliveryOrder orders[MAX_SIZE];
    
    // For storing benchmark results (Member 4 will use these)
    int benchmarkSizes[3] = {100, 300, 500};
    double shellTimes[3] = {0, 0, 0};
    double combTimes[3] = {0, 0, 0};
    long long shellComps[3] = {0, 0, 0};
    long long combComps[3] = {0, 0, 0};
    bool benchmarksRun = false;
    
    int dataSize = 100; // Default size
    int choice = 0;
    bool dataGenerated = false;

    while (choice != 6) {
        cout << "\n==============================================\n";
        cout << "      FOOD DELIVERY TRACKING SYSTEM\n";
        cout << "==============================================\n";
        cout << "1. Generate Original Dataset (Best/Worst/Average)\n";
        cout << "2. Run Shell Sort (Sort by Delivery Time)\n";
        cout << "3. Run Comb Sort (Sort by Delivery Time)\n";
        cout << "4. Run Both Sorts & Show Categorised Output\n";
        cout << "5. Show Performance Comparison Table\n";
        cout << "6. Exit System\n";
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
                benchmarksRun = false;

                cout << "\n--- Dataset Generated! Showing First 10 Records ---\n";
                for (int i = 0; i < 10; i++) {
                    cout << "Order ID: " << orders[i].orderID 
                         << " | Time: " << orders[i].deliveryTimeMinutes << " mins"
                         << " | Customer: " << orders[i].customerName << "\n";
                }
                break;
            }
            case 2: {
                if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    // Make a copy of orders to avoid affecting original
                    DeliveryOrder tempOrders[MAX_SIZE];
                    for (int i = 0; i < dataSize; i++) {
                        tempOrders[i] = orders[i];
                    }
                    
                    long long comparisons = 0;
                    long long movements = 0;

                    cout << "\nRunning Shell Sort on " << dataSize << " records...\n";

                    // Start timer
                    auto start = chrono::high_resolution_clock::now();

                    shellSortByTime(tempOrders, dataSize, comparisons, movements);

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
                    
                    // Member 4's categorised output
                    displayCategorisedOrders(tempOrders, dataSize);
                }
                break;
            }
            case 3: {
                if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    // Make a copy of orders to avoid affecting original
                    DeliveryOrder tempOrders[MAX_SIZE];
                    for (int i = 0; i < dataSize; i++) {
                        tempOrders[i] = orders[i];
                    }
                    
                    long long comparisons = 0;
                    long long movements = 0;

                    cout << "\nRunning Comb Sort on " << dataSize << " records...\n";

                    // Start timer
                    auto start = chrono::high_resolution_clock::now();

                    combSortByTime(tempOrders, dataSize, comparisons, movements);

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
                    
                    // Member 4's categorised output
                    displayCategorisedOrders(tempOrders, dataSize);
                }
                break;
            }
            case 4: {
                // Run both sorts and show categorised output for current dataset
                if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    cout << "\n========== RUNNING BENCHMARK ON CURRENT DATASET ==========\n";
                    
                    // Test Shell Sort
                    DeliveryOrder shellCopy[MAX_SIZE];
                    for (int i = 0; i < dataSize; i++) shellCopy[i] = orders[i];
                    
                    long long shellComp = 0, shellMov = 0;
                    auto start = chrono::high_resolution_clock::now();
                    shellSortByTime(shellCopy, dataSize, shellComp, shellMov);
                    auto end = chrono::high_resolution_clock::now();
                    double shellTime = chrono::duration<double, micro>(end - start).count();
                    
                    cout << "\n--- SHELL SORT RESULTS (Size: " << dataSize << ") ---\n";
                    cout << "Time: " << shellTime << " us | Comparisons: " << shellComp << "\n";
                    displayCategorisedOrders(shellCopy, dataSize);
                    
                    // Test Comb Sort
                    DeliveryOrder combCopy[MAX_SIZE];
                    for (int i = 0; i < dataSize; i++) combCopy[i] = orders[i];
                    
                    long long combComp = 0, combMov = 0;
                    start = chrono::high_resolution_clock::now();
                    combSortByTime(combCopy, dataSize, combComp, combMov);
                    end = chrono::high_resolution_clock::now();
                    double combTime = chrono::duration<double, micro>(end - start).count();
                    
                    cout << "\n--- COMB SORT RESULTS (Size: " << dataSize << ") ---\n";
                    cout << "Time: " << combTime << " us | Comparisons: " << combComp << "\n";
                    displayCategorisedOrders(combCopy, dataSize);
                    
                    // Store in benchmark arrays for current size
                    for (int i = 0; i < 3; i++) {
                        if (benchmarkSizes[i] == dataSize) {
                            shellTimes[i] = shellTime;
                            combTimes[i] = combTime;
                            shellComps[i] = shellComp;
                            combComps[i] = combComp;
                            break;
                        }
                    }
                    benchmarksRun = true;
                }
                break;
            }
            case 5: {
                // Member 4's Performance Comparison Table
                if (!benchmarksRun && dataGenerated) {
                    cout << "\n[!] No benchmark data for 100, 300, and 500. Please run Option 4 with each dataset size first.\n";
                    cout << "    Suggested workflow:\n";
                    cout << "    1. Generate 100 records (Option 1) ? Run Option 4\n";
                    cout << "    2. Generate 300 records (Option 1) ? Run Option 4\n";
                    cout << "    3. Generate 500 records (Option 1) ? Run Option 4\n";
                    cout << "    4. Then select Option 5 to see comparison table.\n";
                } else if (!dataGenerated) {
                    cout << "\n[!] Error: You must generate data first (Option 1)!\n";
                } else {
                    displayComparisonTable(benchmarkSizes, shellTimes, combTimes, 
                                           shellComps, combComps, 3);
                }
                break;
            }
            case 6:
                cout << "\nExiting system. Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice. Please enter 1-6.\n";
        }
    }
    return 0;
}

// Universal Data Generator - Written by: Member 1
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

// Shell Sort with Visualization - Written by: Member 2
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

// Comb Sort with Visualization - Written by: Member 3
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
