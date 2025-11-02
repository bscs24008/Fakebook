#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
using namespace std;

template <typename T>
class Heap {
private:
    vector<T> data;
    function<bool(T, T)> cmp; 

    int parent_ind(int index) { return (index - 1) / 2; }
    int childL_ind(int index) { return 2 * index + 1; }
    int childR_ind(int index) { return 2 * index + 2; }

    void heapify_up(int index) {
        if (index == 0) return;
        int parent = parent_ind(index);

        if (!cmp(data[index], data[parent])) {
            swap(data[index], data[parent]);
            heapify_up(parent);
        }
    }

    void heapify_down(int index) {
        int left = childL_ind(index);
        int right = childR_ind(index);
        int best = index;

        if (left < data.size() && !cmp(data[left], data[best]))
            best = left;
        if (right < data.size() && !cmp(data[right], data[best]))
            best = right;

        if (best != index) {
            swap(data[index], data[best]);
            heapify_down(best);
        }
    }

    bool isHeapRecursive(int index) {
        int left = childL_ind(index);
        int right = childR_ind(index);

        if (left >= data.size())
            return true; 

        if (left < data.size() && cmp(data[index], data[left]))
            return false;
        if (right < data.size() && cmp(data[index], data[right]))
            return false;

        return isHeapRecursive(left) && (right >= data.size() || isHeapRecursive(right));
    }

public:
    Heap(function<bool(T, T)> comp = [](T a, T b) { return a < b; }) {
        cmp = comp;
    }

    void insert(T value) {
        data.push_back(value);
        heapify_up(data.size() - 1);
    }

    T extract() {
        if (data.empty())
            throw runtime_error("Empty Heap");

        T root = data[0];
        data[0] = data.back();
        data.pop_back();

        if (!data.empty())
            heapify_down(0);

        return root;
    }

    T peek() {
        if (data.empty())
            throw runtime_error("Empty Heap");
        return data[0];
    }

    void buildHeap(const vector<T>& arr) {
        data = arr;
        for (int i = (data.size() / 2) - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }

    bool isHeap() {
        if (data.empty())
            return true;
        return isHeapRecursive(0);
    }

    void printHeap() {
        for (int i = 0; i < data.size(); i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    vector<T> heapSort() {
        vector<T> sorted;
        Heap<T> tempHeap = *this;

        while (!tempHeap.data.empty()) {
            sorted.push_back(tempHeap.extract());
        }

        reverse(sorted.begin(), sorted.end());
        return sorted;
    }

    static void heapSort(vector<T>& vec) {
        Heap<T> heap;
        heap.buildHeap(vec);

        for (int i = (int)vec.size() - 1; i >= 0; i--) {
            vec[i] = heap.extract();
        }
    }

    bool is_empty() {
        if (data.size() == 0)
            return true;
        return false;
    }
};
