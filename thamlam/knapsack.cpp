#include <iostream>
#include <vector>
#include <algorithm> // For sort function
#include <utility>   // For pair

using namespace std;

// Hàm để so sánh hai món đồ dựa trên tỷ lệ giá trị trên khối lượng
bool compare(pair<double, pair<int, int>> a, pair<double, pair<int, int>> b) {
    return a.first > b.first;
}

// Thuật toán tham lam cho bài toán thuê xe-balo
pair<int, vector<pair<int, int>>> knapsack_greedy(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<pair<double, pair<int, int>>> value_density;

    for (int i = 0; i < n; ++i) {
        value_density.push_back(make_pair((double)values[i] / weights[i], make_pair(weights[i], values[i])));
    }

    // Sắp xếp danh sách các món đồ theo tỷ lệ giá trị trên khối lượng
    sort(value_density.begin(), value_density.end(), compare);

    int total_value = 0, total_weight = 0;
    vector<pair<int, int>> items_taken;

    for (auto& item : value_density) {
        int weight = item.second.first;
        int value = item.second.second;
        if (total_weight + weight <= capacity) {
            items_taken.push_back(make_pair(weight, value));
            total_weight += weight;
            total_value += value;
        }
    }

    return make_pair(total_value, items_taken);
}

int main() {
    int n, capacity;
    cout << "Nhap so luong mon do: ";
    cin >> n;

    vector<int> weights(n), values(n);

    cout << "Nhap khoi luong mon do: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << "Nhập gia tri: ";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    cout << "nhap dung luong toi da: ";
    cin >> capacity;

    auto result = knapsack_greedy(weights, values, capacity);
    int max_value = result.first;
    auto items = result.second;

    cout << "Ket qua:" << endl;
    cout << "Tong gia tri lon nhat: " << max_value << endl;
    cout << "cac mon do duoc chon: ";
    for (auto& item : items) {
        cout << "(" << item.first << ", " << item.second << ") ";
    }
    cout << endl;
        return 0;
}

    