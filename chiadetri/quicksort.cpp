#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int> &items, int leftIndex, int rightIndex) {
    int temp = items[leftIndex];
    items[leftIndex] = items[rightIndex];
    items[rightIndex] = temp;
}

int partition(vector<int> &items, int left, int right) {
    int pivot = items[(right + left) / 2];
    int i = left;
    int j = right;

    cout << "Pivot: " << pivot << endl;
    cout << "Current array: ";
    for (int k = left; k <= right; k++) {
        cout << items[k] << " ";
    }
    cout << endl;

    while (i <= j) {
        while (items[i] < pivot) {
            i++;
        }
        while (items[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(items, i, j);
            cout << "Swapped " << items[i] << " and " << items[j] << ": ";
            for (int k = left; k <= right; k++) {
                cout << items[k] << " ";
            }
            cout << endl;
            i++;
            j--;
        }
    }

    return i;
}

void quickSort(vector<int> &items, int left, int right) {
    if (left < right) {
        int index = partition(items, left, right);

        vector<int> leftArray(items.begin() + left, items.begin() + index);
        vector<int> rightArray(items.begin() + index, items.begin() + right + 1);

        cout << "Section 1: [";
        for (int num : leftArray) {
            cout << num << " ";
        }
        cout << "]" << endl;

        cout << "Section 2: [";
        for (int num : rightArray) {
            cout << num << " ";
        }
        cout << "]" << endl << endl;

        if (left < index - 1) {
            quickSort(items, left, index - 1);
        }
        if (index < right) {
            quickSort(items, index, right);
        }
    }
}

int main() {
    vector<int> items = {42, 23, 74, 11, 65, 58, 94, 36, 99, 87};
    // vector<int> items = {5, 3, 7, 6, 2, 9};

    cout << "Initial array:" << endl;
    for (int num : items) {
        cout << num << " ";
    }
    cout << endl << endl;

    cout << "Sorting process:" << endl << endl;
    quickSort(items, 0, items.size() - 1);

    cout << endl << "Sorted array:" << endl;
    for (int num : items) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

