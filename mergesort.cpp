#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

vector<int> merge(const vector<int>& left, const vector<int>& right) {
    vector<int> result;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i++]);
        } else {
            result.push_back(right[j++]);
        }
    }
    while (i < left.size()) result.push_back(left[i++]);
    while (j < right.size()) result.push_back(right[j++]);
    return result;
}

// merge sort function
vector<int> mergeSort(const vector<int>& arr) {
    if (arr.size() <= 1) return arr;
    size_t mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());
    return merge(mergeSort(left), mergeSort(right));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <array_size>" << endl;
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        cerr << "Array size must be a positive integer." << endl;
        return 1;
    }

    srand(time(0));
    vector<int> arr(n);
    for (int &num : arr) {
        num = rand() % 10000; 
    }

    auto start = chrono::high_resolution_clock::now();
    vector<int> sortedArr = mergeSort(arr);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Sorting " << n << " elements took: " << elapsed.count() << " seconds." << endl;
    return 0;
}
