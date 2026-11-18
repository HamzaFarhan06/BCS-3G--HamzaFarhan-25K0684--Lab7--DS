#include <iostream>
#include <string>
using namespace std;

struct Player {
    string name;
    int runs;
    int matches;
    int idx;
};

int comp = 0;
int ties = 0;

void print(Player a[], int st, int en) {
    cout << "[";
    for (int i = st; i <= en; i++) {
        cout << a[i].name << " (Runs: " << a[i].runs << ", Matches: " << a[i].matches << ")";
        if (i < en) cout << ", ";
    }
    cout << "]";
}

void merge(Player a[], int st, int mid, int en) {
    int n1 = mid - st + 1;
    int n2 = en - mid;

    Player l[100], r[100];

    for (int i = 0; i < n1; i++)
        l[i] = a[st + i];

    for (int i = 0; i < n2; i++)
        r[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = st;

    while (i < n1 && j < n2) {
        comp++;

        if (l[i].runs > r[j].runs) {
            a[k] = l[i];
            i++;
        }
        else if (l[i].runs < r[j].runs) {
            a[k] = r[j];
            j++;
        }
        else {
            ties++;

            if (l[i].matches < r[j].matches) {
                a[k] = l[i];
                i++;
            }
            else if (l[i].matches > r[j].matches) {
                a[k] = r[j];
                j++;
            }
            else {
                if (l[i].idx <= r[j].idx) {
                    a[k] = l[i];
                    i++;
                }
                else {
                    a[k] = r[j];
                    j++;
                }
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

void mergeSort(Player a[], int st, int en) {
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

    Player a[100];

    for (int i = 0; i < n; i++) {
        cin >> a[i].name >> a[i].runs >> a[i].matches;
        a[i].idx = i;
    }

    cout << "\nInitial Players List:\n";
    print(a, 0, n - 1);
    cout << "\n\nProcess of Cuts and Joins:\n";

    mergeSort(a, 0, n - 1);

    cout << "\nTotal comparisons made: " << comp << "\n";
    cout << "Times tie was decided using matches: " << ties << "\n";

    cout << "\nFinal Cricket Tournament Ranking:\n";
    for (int i = 0; i < n; i++) {
        cout << "Rank " << i + 1 << ": " << a[i].name
             << " | Runs: " << a[i].runs
             << " | Matches: " << a[i].matches << "\n";
    }

    return 0;
}