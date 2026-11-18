#include <iostream>
using namespace std;

void print(int a[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << a[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

int findMax(int a[], int n) {
    int mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > mx) mx = a[i];
    }
    return mx;
}

int countDigits(int num) {
    if (num <= 0) return 1;

    int cnt = 0;
    while (num > 0) {
        cnt++;
        num /= 10;
    }
    return cnt;
}

void radixSort(int a[], int n) {
    int mx = findMax(a, n);
    int rounds = countDigits(mx);

    cout << "\nLargest code found: " << mx << "\n";
    cout << "Total rounds needed: " << rounds << "\n";

    int exp = 1;

    for (int r = 1; r <= rounds; r++) {
        int box[10][200];
        int cnt[10] = {0};

        for (int i = 0; i < n; i++) {
            int digit = (a[i] / exp) % 10;
            box[digit][cnt[digit]] = a[i];
            cnt[digit]++;
        }

        cout << "\nRound " << r << " (Processing digit place: " << exp << "):\n";
        cout << "Content of 10 boxes:\n";

        for (int i = 0; i < 10; i++) {
            cout << "Box " << i << ": [";
            for (int j = 0; j < cnt[i]; j++) {
                cout << box[i][j];
                if (j < cnt[i] - 1) cout << ", ";
            }
            cout << "]\n";
        }

        int k = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < cnt[i]; j++) {
                a[k++] = box[i][j];
            }
        }

        cout << "Code list after Round " << r << ": ";
        print(a, n);
        cout << "\n";

        exp *= 10;
    }
}

void duplicates(int a[], int n) {
    bool found = false;
    cout << "\nDuplicate Tracking Codes:\n";

    int i = 0;
    while (i < n) {
        int cnt = 1;

        while (i + 1 < n && a[i] == a[i + 1]) {
            cnt++;
            i++;
        }

        if (cnt > 1) {
            found = true;
            cout << "Tracking Code " << a[i] << " appears " << cnt << " times.\n";
        }
        i++;
    }

    if (!found) {
        cout << "No duplicate tracking codes found.\n";
    }
}

int main() {
    int n;
    cin >> n;

    if (n <= 0 || n > 200) return 0;

    int a[200];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << "\nInitial tracking codes: ";
    print(a, n);
    cout << "\n";

    radixSort(a, n);

    cout << "\nFinal sorted tracking codes:\n";
    print(a, n);
    cout << "\n";

    duplicates(a, n);

    return 0;
}