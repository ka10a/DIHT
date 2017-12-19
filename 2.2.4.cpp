#include <vector>
#include <iostream>


using namespace std;

struct point{
    int x;
    bool begin;

    point(int x = 0, bool begin = 1){
        this->x = x;
        this->begin = begin;
    }
};

bool cmp(point a, point b){
    if (a.x < b.x)
        return true;
    if ((a.x == b.x) && (a.begin < b.begin))
        return true;
    return false;
}

void sift_down(vector<point> &heap, int n, int ind){
    int left_child = 2 * ind + 1, right_child = 2 * ind + 2;
    int smallest = ind;
    if ((left_child < n) && (cmp(heap[left_child], heap[ind])))
        smallest = left_child;
    if ((right_child < n) && (cmp(heap[right_child], heap[smallest])))
        smallest = right_child;
    if (smallest != ind) {
        swap(heap[ind], heap[smallest]);
        sift_down(heap, n, smallest);
    }
}

void HeapSort(vector<point> &heap){
    for (int j = ((int) heap.size() / 2) + 1; j >= 0; j--)
        sift_down(heap, (int) heap.size(), j);
}

point get_min(vector<point> &heap, int &n){
    swap(heap[0], heap[n - 1]);
    sift_down(heap, --n,0);
    return heap[n];
}

int write(vector<point> &heap, int n){
    int ans = 0;
    int cnt = 0;
    point last = point();
    while (n > 0){

        point curr = get_min(heap, n);
        //cerr << curr.x << endl;

        if (cnt == 1){
            ans += curr.x - last.x;
        }

        if (curr.begin == 1)
            cnt++;
        else
            cnt--;

        last = curr;
    }

    return ans;
}

int main(){
    int n;
    cin >> n;

    vector<point> heap(2 * n);
    for (int i = 0; i < 2 * n; i += 2){
        int x, y;
        cin >> x >> y;
        heap[i] = point(x, 1);
        heap[i + 1] = point(y, 0);
    }

    HeapSort(heap);
    cout << write(heap, 2 * n);

    return 0;
}
