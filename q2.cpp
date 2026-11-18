#include <iostream>
using namespace std;

int swaps = 0;
int skipped = 0;

void print(int a[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << a[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

int partition(int a[], int low, int high, int n) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            swaps++;
        }
    }

    i++;
    int temp = a[i];
    a[i] = a[high];
    a[high] = temp;
    swaps++;

    int pos = i;

    cout << "\nPlaced reference parcel (weight " << pivot << ") at position " << pos + 1 << " (index " << pos << ").\n";
    cout << "Array state: ";
    print(a, n);
    cout << "\n";

    return pos;
}

void quickSelect(int a[], int low, int high, int target, int n) {
    if (low > high) return;

    if (low == high) {
        cout << "\nSingle parcel remaining at index " << low << " (weight " << a[low] << "), already in final position.\n";
        return;
    }

    int pos = partition(a, low, high, n);

    if (pos == target) {
        cout << "\nTarget K-th position reached at index " << pos << "!\n";

        if (low <= pos - 1) {
            cout << "Skipped left group [indices " << low << ".." << pos - 1 << "] (answer already located).\n";
            skipped++;
        }

        if (pos + 1 <= high) {
            cout << "Skipped right group [indices " << pos + 1 << ".." << high << "] (answer already located).\n";
            skipped++;
        }
        return;
    }

    if (target < pos) {
        if (pos + 1 <= high) {
            cout << "Skipped right group [indices " << pos + 1 << ".." << high << "] (cannot contain the " << target + 1 << "-th lightest parcel).\n";
            skipped++;
        }

        if (low <= pos - 1) {
            quickSelect(a, low, pos - 1, target, n);
        }
    }
    else {
        if (low <= pos - 1) {
            cout << "Skipped left group [indices " << low << ".." << pos - 1 << "] (cannot contain the " << target + 1 << "-th lightest parcel).\n";
            skipped++;
        }

        if (pos + 1 <= high) {
            quickSelect(a, pos + 1, high, target, n);
        }
    }
}

int main() {
    int n, k;
    cin >> n;

    if (n <= 0 || n > 100) return 0;

    int a[100];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cin >> k;

    if (k < 1 || k > n) return 0;

    cout << "\nInitial parcels array: ";
    print(a, n);
    cout << "\n\nPartitioning and Selection Process:";

    int target = k - 1;
    quickSelect(a, 0, n - 1, target, n);

    cout << "\nTotal number of swaps: " << swaps << "\n";
    cout << "The " << k << "-th lightest parcel weight: " << a[target] << "\n";
    cout << "Total groups skipped: " << skipped << "\n";

    return 0;
}