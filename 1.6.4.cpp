#include <bits/stdc++.h>

/*
��� ������ ����������� ����� A[0..n), n �� ����������� 100 000 000.
��� �� ����� ������ ��������� ���� (��������������� ������������� ��������� �������)
� ���� ������� k, k<=n.
��������� ��� ������� ��������� ���� (�� 0 � �� n-k)
������� �������� ��������� � ����.
�������� ������ O(n log n), ������ O(k).
*/

using namespace std;

// ����������� �����
void sift_up(pair<int, int> *heap, int index) {
    while (index > 0){
        // ������ index
        int p = (index - 1) / 2;
        // ���� ���� ����� ���������� (������ ������ ����)
        if (heap[p].first >= heap[index].first)
            return;
        // ������ ���� ����������
        swap(heap[p], heap[index]);
        index = p;
    }
}

// ����������� ����
void sift_down(int heap_size, pair<int, int> *heap, int index = 0) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // ���� �������� ����, ���� ����� ����
    int largest = index;
    if  ((left < heap_size) && (heap[largest].first < heap[left].first))
        largest = left;
    if  ((right < heap_size) && (heap[largest].first < heap[right].first))
        largest = right;

    // ���� ���� ������� ���, �� ������������ �������� � ����
    if (largest != index) {
        swap(heap[largest], heap[index]);
        sift_down(heap_size, heap, largest);
    }
}

// ���������� � ����
void heap_add(pair<int, int> *heap, int &realsize, int index, int value) {
    heap[realsize] = {value, index};
    sift_up(heap, realsize);
    realsize++;
}

// �������� ��������� �� ����
void heap_delete(int heap_size, pair<int, int> *heap, int &realsize) {
    swap(heap[0], heap[realsize - 1]);
    heap[realsize - 1] = {0, 0};
    sift_down(heap_size, heap, 0);
    realsize--;
}

// ���������� ������� ����
int find_size_of_heap(int n) {
    int heap_size = 1;
    while (heap_size <= n) {
        heap_size = heap_size << 1;
    }
    return heap_size;
}

// ������������� ���� � ������
void initialization(pair<int, int> *heap, int k, int *a, int heap_size) {
    for (int i = 0; i < k; i++) {
        heap[i] = {a[i], i};
        sift_up(heap, i);
    }
    for (int i = k; i < heap_size; i++)
        heap[i] = {0, 0};
}

int main() {
    int n;
    cin >> n;

    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int k;
    cin >> k;

    int heap_size = find_size_of_heap(n);

    pair<int, int> *heap = new pair<int, int> [heap_size];
    int realsize = k;
    initialization(heap, k, a, heap_size);

    cout << heap[0].first;
    for (int i = k; i < n; i++) {
        heap_add(heap, realsize, i, a[i]);
        // ���� ���������� �������� �������, ������� �� �������� � ������� ���� ������� k
        while (heap[0].second <= (i - k))
            heap_delete(heap_size, heap, realsize);
        cout << " " << heap[0].first;
    }

    delete[] heap;
    delete[] a;

    return 0;
}
