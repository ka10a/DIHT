#include <bits/stdc++.h>

/* На числовой прямой окрасили N отрезков. Известны координаты левого
 * и правого концов каждого отрезка (Li и Ri). Найти сумму длин
 * частей числовой прямой, окрашенных ровно в один слой.
 */

using namespace std;

struct Point {
    int x; // координата точки
    bool begin; // начало отрезка - 1, конец - 0

    Point(int x = 0, bool begin = 1) {
        this->x = x;
        this->begin = begin;
    }
};


//Компаратор для двух точек
bool cmp(Point a, Point b) {
    if (a.x < b.x) {
        return true;
    }
    
    if ((a.x == b.x) && (a.begin < b.begin)) {
        return true;
    }
    
    return false;
}


// Просеивание в куче вниз
void sift_down(vector<Point>& heap, int n, int ind) {

    // Дети левый и правый
    int left_child = 2 * ind + 1, right_child = 2 * ind + 2;

    //Ищем наименьшего из родителя и двух детей, если таковые есть
    int smallest = ind;
    if ((left_child < n) && (cmp(heap[left_child], heap[ind]))) {
        smallest = left_child;
    }
    if ((right_child < n) && (cmp(heap[right_child], heap[smallest]))) {
        smallest = right_child;
    }

    // Меняем наименьшего с текущим, если это не он сам
    if (smallest != ind) {
        swap(heap[ind], heap[smallest]);
        sift_down(heap, n, smallest);
    }
}


//Строит кучу
void HeapSort(vector<Point>& heap) {
    for (int j = ((int) heap.size() / 2) + 1; j >= 0; --j) {
        sift_down(heap, (int) heap.size(), j);
    }
}


// Вытаскивает текущий минимум из кучи
point get_min(vector<Point>& heap, int n) {
    swap(heap[0], heap[n - 1]);
    sift_down(heap, --n, 0);
    return heap[n];
}


// Считает ответ
int count_ans(vector<Point>& heap, int n) {
    int ans = 0;
    int cnt = 0; // количество открытых отрезков сейчас

    // Запоминает последнюю точку
    point last = point();

    while (n > 0) {
        // С каждой новой точкой cnt меняется

        // Текущая точка
        point curr = get_min(heap, n);

        // Если сейчас открыт 1 отрезок, то надо прибавить расстояние от последней точки до текущей
        if (cnt == 1) {
            ans += curr.x - last.x;
        }

        // Если текущая точка начало отрезка, то надо открыть еще один отрезок, иначе закрыть
        if (curr.begin == 1) {
            cnt++;
        }
        else {
            cnt--;
        }

        last = curr;
    }

    return ans;
}

int main()  {
    int n;
    cin >> n;

    vector<Point> heap(2 * n);
    for (int i = 0; i < 2 * n; i += 2) {
        int x, y;
        cin >> x >> y;
        heap[i] = Point(x, 1);
        heap[i + 1] = Point(y, 0);
    }

    HeapSort(heap);
    cout << count_ans(heap, 2 * n);

    return 0;
}
