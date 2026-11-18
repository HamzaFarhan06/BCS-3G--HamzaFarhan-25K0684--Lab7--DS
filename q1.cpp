#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string name;
    int urgency;
    int time;
};

int comp = 0;

void print(Patient a[], int st, int en) {
    cout << "[";
    for (int i = st; i <= en; i++) {
        cout << a[i].name << " (Urgency: " << a[i].urgency << ", Arrival: " << a[i].time << ")";
        if (i < en) cout << ", ";
    }
    cout << "]";
}

void merge(Patient a[], int st, int mid, int en) {
    int n1 = mid - st + 1;
    int n2 = en - mid;

    Patient l[100], r[100];

    for (int i = 0; i < n1; i++)
        l[i] = a[st + i];

    for (int i = 0; i < n2; i++)
        r[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = st;

    while (i < n1 && j < n2) {
        comp++;

        if (l[i].urgency > r[j].urgency) {
            a[k] = l[i];
            i++;
        }
        else if (l[i].urgency < r[j].urgency) {
            a[k] = r[j];
            j++;
        }
        else {
            if (l[i].time <= r[j].time) {
                a[k] = l[i];
                i++;
            }
            else {
                a[k] = r[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) {
        a[k] = l[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = r[j];
        j++;
        k++;
    }

    cout << "Join Result: ";
    print(a, st, en);
    cout << "\n";
}

void mergeSort(Patient a[], int st, int en) {
    if (st < en) {
        int mid = st + (en - st) / 2;

        cout << "Cut: Left part ";
        print(a, st, mid);
        cout << " | Right part ";
        print(a, mid + 1, en);
        cout << "\n";

        mergeSort(a, st, mid);
        mergeSort(a, mid + 1, en);

        merge(a, st, mid, en);
    }
}

int main() {
    int n;
    cin >> n;

    if (n <= 0 || n > 100) return 0;

    Patient a[100];

    for (int i = 0; i < n; i++) {
        cin >> a[i].name >> a[i].urgency >> a[i].time;
    }

    cout << "\nInitial Patient List:\n";
    print(a, 0, n - 1);
    cout << "\n\nProcess of Cuts and Joins:\n";

    mergeSort(a, 0, n - 1);

    cout << "\nTotal comparisons made: " << comp << "\n";

    cout << "\nFinal Ordered Patient List:\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". Patient: " << a[i].name
             << " | Urgency: " << a[i].urgency
             << " | Arrival Time: " << a[i].time << "\n";
    }

    cout << "\nFirst patient to see the doctor: " << a[0].name << "\n";

    return 0;
}