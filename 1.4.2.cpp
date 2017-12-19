#include <bits/stdc++.h>

using namespace std;


/*
Реализовать дек с динамическим зацикленным буфером.
Обрабатывать команды push * и pop *.
*/

// Динамический массив с расширением. При расширении инвалидируются указатели на элементы.

class Deque {
    size_t _size; // разсер буфеоа
    // буфер массива, указатель на начало и на ячейку памяти,
    // которая идет после конца данных в буфере
    int *_buffer, *_begin, *_end;
    int realsize;

    // Создание нового буфера с новым размером и копированием данных из старого буфера
    void copy_(size_t newSize) {
        int *oldbuffer = _buffer;
        size_t oldsize = _size;
        _buffer = new int[newSize];
        // Если данные идут подряд
        if (_end > _begin){
            copy(_begin, _end, _buffer);
        }
        // Если была закольцовка дека
        else{
            copy(_begin, oldbuffer + oldsize, _buffer);
            copy(oldbuffer, _end, _buffer + ((oldbuffer + oldsize) - _begin));
        }

        _begin = _buffer;
        _end = _buffer + realsize;
        _size = newSize;
        delete[] oldbuffer;
    }

    // Проверка на то, закончился ли буфер
    void prove() {
        // Если буфер закончился
        if (realsize + 1 >= _size)
            copy_(_size * 2);
    }

    int* inc(int *it) {
        it++;
        if (it == _buffer + _size)
            it = _buffer;
        return it;
    }

    int* decr(int *it) {
        if (it == _buffer)
            it = _buffer + _size;
        it--;
        return it;
    }

public:
    bool empty() {
        return (realsize == 0);
    }

    void pushfront(int a) {
        prove();

        _begin = decr(_begin);
        *_begin = a;
        realsize++;
    }

    int popfront() {
        if (empty())
            return -1;

        int a = *_begin;
        _begin = inc(_begin);
        realsize--;

        return a;
    }

    void pushback(int a) {
        prove();

        *_end = a;
        _end = inc(_end);
        realsize++;
    }

    int popback() {
        if (empty())
            return -1;

        int a;
        int *it = decr(_end);

        a = *it;
        _end = it;
        realsize--;

        return a;
    }

    // Конструктор по-умолчанию
    explicit Deque(size_t _size = 1) {
        _buffer = new int[_size];
        this->_size = _size;
        realsize = 0;
        _begin = _buffer;
        _end = _buffer;
    }

    // Правило трёх
    Deque(const Deque& a) {
        _buffer = new int[a._size];
        _begin = _buffer + (a._begin - a._buffer);
        _end = _buffer + (a._end - a._buffer);
        realsize = a.realsize;
        _size = a._size;
        copy(a._buffer, a._buffer +a._size, _buffer);
    }

    Deque& operator=(const Deque& a) {
        delete[] _buffer;
        _buffer = new int[a._size];
        _begin = _buffer + (a._begin - a._buffer);
        _end = _buffer + (a._end - a._buffer);
        realsize = a.realsize;
        _size = a._size;
        copy(a._buffer, a._buffer + a._size, _buffer);
        return *this;
    }

    ~Deque() {
        delete[] _buffer;
    }
};


int main(){
    int n;
    cin >> n;
    Deque t;

    for (int i = 0; i < n; i++){
        int a, c;
        scanf("%d%d", &a, &c);

        if (a == 1)
            t.pushfront(c);
        else{
            if (a == 3)
                t.pushback(c);
            else {
                int b;
                if (a == 2)
                    b = t.popfront();
                else
                    b = t.popback();

                if (b != c){
                    cout << "NO";
                    return 0;
                }
            }
        }

    }

    cout << "YES";

    return 0;
}
