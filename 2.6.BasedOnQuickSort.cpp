#include <iostream>
#include <vector>
#include <stack>

/* Дан массив целых чисел в диапазоне [0..109]. Размер массива кратен 10
 * и ограничен сверху значением 2.5 * 107 элементов. Все значения массива
 * являются элементами псевдо-рандомной последовательности. Необходимо
 * отсортировать элементы массива за минимально время и вывести каждый
 * десятый элемент отсортированной последовательности.
 * Реализуйте сортировку, основанную на QuickSort.
 * Минимальный набор оптимизаций, который необходимо реализовать:
 * 1. Оптимизация ввода/вывода
 * 2. Оптимизация выбора опорного элемента
 * 3. Оптимизация Partition
 * 4. Оптимизация рекурсии
 * 5. Оптимизация концевой рекурсии
*/

using namespace std;

int Partition(vector<int> &arr, int beginning, int ending) {

    // Если в куске [beginning, ending) 0 или 1 элемент, их можно не сортировать
    if(ending - beginning <= 1)
        return beginning;

    // Выбор опорного элемента рандомом
    int pivot = (rand() % (ending - beginning)) + beginning;

    // Чтобы опорный элемент ни с кем не поменять, меняем его с последним и сортируем только [beginning, ending)
    swap(arr[pivot], arr[ending - 1]);
    int i = beginning, j = ending - 2;

    while( i <= j ) {

        // Ищем первый элемент больший опорного
        for( ; (arr[i] < arr[ending - 1]); ++i ) {}

        // Ищем первый элемент меньший опорного
        for( ; (j >= beginning) && (arr[j] >= arr[ending - 1]); --j ) {}

        // Меняем их местами
        if(i < j)
            swap(arr[i++], arr[j--]);
    }

    // Ставим опорный элемент на свое место
    swap(arr[i], arr[ending - 1]);

    return i;
}

void UnrecursionQuickSort(vector<int> &a, int left, int right){

    // Стек из полуинтервалов отрезков, которые необходимо посортировать
    stack<pair<int,int> > s;
    s.push({left, right});

    // Пока есть неотсортированные куски
    while (!s.empty()) {
        pair<int, int> cur = s.top();
        s.pop();
        int l = cur.first, r = cur.second;

        //Если в куске 0 или 1 элемент, его можно не сортить
        if (r - l <= 1)
            continue;

        int i = Partition(a, l, r);

        // Раньше кладем больший кусок
        if (i - l > r - i) {
            s.push({l, i});
            s.push({i + 1, r});
        }
        else {
            s.push({i + 1, r});
            s.push({l, i});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector <int> arr;
    int b, n = 0;
    while (cin >> b) {
        arr.push_back(b);
        n++;
    }

    UnrecursionQuickSort(arr, 0, n);

    for (int i = 9; i < n; i += 10)
        cout << arr[i] << " ";
    cout << "\n";

    return 0;
}