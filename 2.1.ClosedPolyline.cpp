#include <bits/stdc++.h>

/* Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся замкнутую ломаную,
 * проходящую через все эти точки.
 * Предполагается, что никакие три точки не лежат на одной прямой.
 * Стройте ломаную от точки, имеющей наименьшую координату x. Если таких точек несколько,
 * то используйте точку с наименьшей координатой y. Точки на ломаной расположите в порядке
 * убывания углов лучей от начальной точки до всех остальных точек.
 * Для сортировки точек реализуйте алгоритм сортировки вставками.
 */

using  namespace std;

struct point{
    int x, y;

    point(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }
};

void InsertionSort(vector <point> &points, point start_point){
    for (int i = 2; i < (int) points.size(); i++){
        point tmp = points[i];
        // Поиск места вставки для текущей точки
        int left = 0, right = i;
        while (left + 1 < right){
            int m = (right + left) >> 1;
            point curr = points[m];
            // Координаты векторов из стартовой точки в точку для вставки и текущую точку
            int d_curr_y = curr.y - start_point.y, d_curr_x = curr.x - start_point.x;
            int d_tmp_y = tmp.y - start_point.y, d_tmp_x = tmp.x - start_point.x;

            if (d_tmp_x * d_curr_y - d_tmp_y * d_curr_x > 0)
                left = m;
            else
                right = m;
        }

        // Вставка точки для вставки
        for (int j = i - 1; j >= right; j--){
            points[j + 1] = points[j];
        }
        points[right] = tmp;
    }
}

int main() {
    int n;
    cin >> n;

    vector <point> points(n);

    int x, y;
    cin >> x >> y;
    point start_point = point(x, y);

    // Вводим координаты точек и ищем стартовую
    for (int i = 1; i < n; i++){
        cin >> x >> y;
        // Если текущая точка для первых i + 1 точки является стартовой
        if ((x < start_point.x) || ((x == start_point.x) && (y < start_point.y))){
            points[i] = start_point;
            start_point.x = x;
            start_point.y = y;
        }
        else {
            points[i] = point(x, y);
        }
    }
    points[0] = start_point;

    InsertionSort(points, start_point);

    for (int i = 0; i < n; i++){
        cout << points[i].x << " " << points[i].y << endl;
    }

    return 0;
}
