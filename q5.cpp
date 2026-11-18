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
    int pivot = a[low];
    int i = low + 1;

    for (int j = low + 1; j <= high; j++) {
        if (a[j] > pivot) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            swaps++;
            i++;
        }
    }

    int temp = a[low];
    a[low] = a[i - 1];
    a[i - 1] = temp;
    swaps++;

    int pos = i - 1;

    cout << "\nReference student (" << pivot << ") placed at position " << pos + 1 << " (index " << pos << ").\n";
    cout << "Array state: ";
    print(a, n);
    cout << "\n";

    return pos;
}

void quickSelect(int a[], int low, int high, int k, int n) {
    if (low > high) return;

    if (low == high) return;

    int pos = partition(a, low, high, n);

    if (pos == k - 1) {
        cout << "\nTop K boundary reached at index " << pos << "!\n";

        if (pos + 1 <= high) {
            cout << "Skipped right group [" << pos + 1 << ".." << high << "]\n";
            skipped++;
        }
        return;
    }

    if (pos > k - 1) {
        if (pos + 1 <= high) {
            cout << "Skipped right group [" << pos + 1 << ".." << high << "]\n";
            skipped++;
        }

        quickSelect(a, low, pos - 1, k, n);
    }
    else {
        quickSelect(a, pos + 1, high, k, n);
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

    cout << "\nInitial marks: ";
    print(a, n);
    cout << "\n";

    quickSelect(a, 0, n - 1, k, n);

    cout << "\nTotal swaps: " << swaps << "\n";

    cout << "Top " << k << " marks: ";
    cout << "[";

    for (int i = 0; i < k; i++) {
        cout << a[i];
        if (i < k - 1) cout << ", ";
    }

    cout << "]\n";

    cout << "Total groups skipped: " << skipped << "\n";

    return 0;
}