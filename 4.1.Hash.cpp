#include <bits/stdc++.h>

using namespace std;

/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы
 * с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена
 * методом Горнера. Начальный размер таблицы должен быть равным 8-ми. Перехеширование
 * выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы
 * достигает 3/4. Структура данных должна поддерживать операции добавления строки в множество,
 * удаления строки из множества и проверки принадлежности данной строки множеству.
 * 1_1. Для разрешения коллизий используйте квадратичное пробирование.
 * i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 * 1_2. Для разрешения коллизий используйте двойное хеширование.
 */

class HashTable {
    vector <string> s_table;
    vector <long long>  h_table;
    long long t_size, real_size;
    const long long P = 10003, MOD = 1e9 + 7;
    const double LOAD_FACTOR = 0.75;

    int find(long long g, const string& s, function<bool(long long, const string&)> check) {
        for (int i = 1; !check(g, s); ++i) {
            g = (g + i) % t_size;
        }
        return g;
    }

    long long calc_hash(const string& s) {
        long long h = 0;
        for (auto c : s) {
            h = (h * P + int(c)) % MOD;
        }
        return h;
    }

    bool insert_into_table(const string& s) {
        long long hash = calc_hash(s);

        int index = find(hash % t_size, s, [hash, this](long long index, const string& s) {
            return h_table[index] == -1 || (h_table[index] == hash && s == s_table[index]);
        });

        if (h_table[index] == -1) {
            h_table[index] = hash;
            s_table[index] = s;
            real_size++;
            return true;
        }
        return false;
    }

    void grow_table() {
        vector<string> contained_strings;
        for (int i = 0; i < t_size; i++) {
            if (h_table[i] >= 0) {
                contained_strings.push_back(s_table[i]);
            }
        }

        if ((int) contained_strings.size() > t_size * LOAD_FACTOR / 2) {
            t_size *= 2;
        }

        s_table.clear();
        s_table.resize(t_size);
        h_table.clear();
        h_table.resize(t_size, -1);
        real_size = 0;

        for (auto s : contained_strings) {
            insert_into_table(s);
        }
    }

public:
    HashTable() {
        s_table.resize(8);
        h_table.resize(8, -1);
        t_size = 8;
        real_size = 0;
    }

    bool add_str(const string &s) {
        if ((int)(t_size * LOAD_FACTOR) <= real_size)
            grow_table();

        return insert_into_table(s);
    }

    bool remove_str(const string& s){
        long long hash = calc_hash(s);

        int index = find(hash % t_size, s, [hash, this](long long index, const string& s) {
            return h_table[index] == -1 || (h_table[index] == hash && s == s_table[index]);
        });

        if (h_table[index] != -1) {
            h_table[index] = -2;
            s_table[index] = "";
            return true;
        }
        return false;
    }

    bool exist_str(const string& s) {
        long long hash = calc_hash(s);

        int index = find(hash % t_size, s, [hash, this](long long index, const string& s) {
            return h_table[index] == -1 || (h_table[index] == hash && s == s_table[index]);
        });

        if (h_table[index] == -1)
            return false;
        return true;
    }
};

int main() {
    HashTable hash_table = HashTable();

    char c;
    string s;
    while (cin >> c >> s) {
        bool flag;
        if (c == '?') {
            flag = (hash_table.exist_str(s));
        }
        if (c == '+') {
            flag = hash_table.add_str(s);
        }
        if (c == '-') {
            flag = hash_table.remove_str(s);
        }

        if (flag) {
            cout << "OK" << endl;
        }
        else {
            cout << "FAIL" << endl;
        }
    }

    return 0;
}
