#include <bits/stdc++.h>

/*
Дана последовательность N прямоугольников различной ширины и высоты (wi, hi).
Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо).
Требуется найти M - площадь максимального прямоугольника (параллельного осям координат),
который можно вырезать из этой фигуры.
Время работы - O(n).
*/

using namespace std;

int find_ans(pair<int, int> *buffer, int h, int ind, int &curr, int *prefix) {
    //Ищет ответ, когда встретился прямоугольник ниже по высоте
    int ans = -1;
    while ((curr > 1) && (h < buffer[curr - 1].first)) {
        //Считаем площадь текущего прямоугольника и сравниваем с ответом
        int tmp = buffer[curr - 1].first * (prefix[ind - 1] - prefix[buffer[curr - 2].second]);
        ans = max(ans, tmp);
        curr--;
    }
    return ans;
}


int add(pair<int, int> *buffer, int h, int ind, int &curr, int *prefix) {
    //Добавление в буфер
    int ans = find_ans(buffer, h, ind, curr, prefix);
    //Буфер состоит из пар высоты и индекса в массиве префикс-сумм(в т.ч. начальных данных)
    buffer[curr] = {h, ind};
    curr++;
    return ans;
};

int main() {
    int n;
    cin >> n;

    int *data = new int[n + 1];
    int *prefix = new int[n + 1];
    data[0] = 0;
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        int w, h;
        cin >> w >> h;
        data[i] = h;
        //Префикс-сумма длин прямоугольников
        prefix[i] = prefix[i - 1] + w;
    }

    pair <int, int> *buffer = new pair <int, int>[n + 1];
    int curr = 1, ans = 0;
    buffer[0] = {0, 0};
    for (int i = 1; i <= n; i++) {
        ans = max(ans, add(buffer, data[i], i , curr, prefix));
    }

    //Обновляем ответ, если буфер не пустой
    ans = max(find_ans(buffer, 0, n + 1, curr, prefix), ans);

    cout << ans << endl;

    delete[] buffer;
    delete[] prefix;
    delete[] data;

    return 0;
}
