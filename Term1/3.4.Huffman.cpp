#include <bits/stdc++.h>
#include "Huffman.h"

using namespace std;
/*
 * Напишите две функции для создания архива из одного файла
 * и извлечения файла из архива.
 * Метод архивирует данные из потока original:
 * void Encode(IInputStream& original, IOutputStream& compressed);
 * Метод восстанавливает оригинальные данные:
 * void Decode(IInputStream& compressed, IOutputStream& original);
 *
 * где:
 * typedef char byte;
 * interface IInputStream {
 * // Возвращает false, если поток закончился
 * virtual bool Read(byte& value) = 0;
 * };
 * interface IOutputStream {
 * virtual void Write(byte value) = 0;
 * };
*/

class Node{
    int repeats;
    char c;
    Node* left;
    Node* right;

public:
    // Конструктор по умолчанию
    Node(int _repeats = 0, char _c = '\0', Node* _left = nullptr,
         Node* _right = nullptr) {
        repeats = _repeats;
        c = _c;
        left = _left;
        right = _right;
    }

    // Правило трех
    Node(const Node& other) {
        repeats = other.repeats;
        c = other.c;
        left = other.left;
        right = other.right;
    }

    Node& operator=(const Node& other) {
        repeats = other.repeats;
        c = other.c;
        left = other.left;
        right = other.right;
        return *this;
    }

    ~Node() {
        if (left != nullptr) {
            delete left;
        }
        left = nullptr;

        if (right != nullptr) {
            delete right;
        }
        right = nullptr;
    }

    friend bool cmp(Node* &, Node* &);
    friend void make_tree(vector<Node*> &);
    friend void make_table(vector<pair<char, string>> &, Node* &, string);
    friend void dfs(Node* &, string &);
    friend void recover_tree(Node* &, string &, int &, int &, bool &, bool &);
    friend void write_letters_in_tree(Node* &, vector<char> &, int &);
    friend string decode_string(string &);
};

bool cmp(Node* &a, Node* &b) {
    return a->repeats > b->repeats;
}

// Строит дерево Хаффмана
void make_tree(vector<Node*> &data) {
    while ((int) data.size() != 1) {
        Node *tree = new Node();
        tree->left = data.back();
        data.pop_back();
        tree->right = data.back();
        data.pop_back();
        tree->repeats = tree->left->repeats + tree->right->repeats;
        data.push_back(tree);
        sort(data.begin(), data.end(), cmp);
    }
}

// Строит таблицу Хаффмана по дереву Хаффмана для получения для символов их кодов явно
void make_table(vector<pair<char, string>> &table, Node* &tree, string s = "") {
    if ((tree->left == nullptr) && (tree->right == nullptr)) {
        table.push_back({tree->c, s});
        return;
    }
    if (tree->left != nullptr){
        make_table(table, tree->left, s + '0');
    }
    if (tree->right != nullptr){
        make_table(table, tree->right, s + '1');
    }
}

// Обход вершин в порядке pre-order для зашифровки дерева Хаффмана в архив
void dfs(Node* &tree, string &compressed) {
    if ((tree->left == nullptr) && (tree->right == nullptr)) {
        compressed += '0';
        return;
    }

    compressed += '1';
    if (tree->left != nullptr)
        dfs(tree->left, compressed);
    compressed += '1';
    if (tree->right != nullptr)
        dfs(tree->right, compressed);
}

// Кодирует данные
string encode_string(string &s) {
    int* cnt = new int[256];
    cnt += 128;
    for (int i = -128; i < 128; i++)
        cnt[i] = 0;

    // Считает частоты символов
    for (int i = 0; i < s.length(); i++) {
        cnt[(int) s[i]]++;
    }

    // Заполняет массив для построения дерева Хаффмана
    vector<Node*> data;
    for (int i = -128; i < 128; i++) {
        if (cnt[i] > 0) {
            data.push_back(new Node(cnt[i], char(i)));
        }
    }

    sort(data.begin(), data.end(), cmp);
    make_tree(data);

    vector<pair<char, string>> table;
    make_table(table, data[0]);

    // Кодирует дерево Хаффмана
    string compressed = "";
    dfs(data[0], compressed);
    compressed += '0';
    for (auto p : table) {
        compressed += p.first;
    }

    // Кодирует строку с помощью таблицы Хаффмана
    for (int i = 0; i < (int) s.length(); i++) {
        for (int j = 0; j < table.size(); j++) {
            if (s[i] == table[j].first) {
                compressed += table[j].second;
                break;
            }
        }
    }

    delete data[0];
    delete[] (cnt - 128);
    return compressed;
}

// Восстанавливает структуру дерева Хаффмана по закодированной строке
void recover_tree(Node* &tree, string &compressed, int &i, int &n,
                  bool &flag, bool &outfl) {
    if ((flag) && (compressed[i] == '0')) {
        outfl = true;
        return;
    }

    if (outfl) {
        return;
    }

    if (compressed[i] == '0') {
        flag = true;
        n++;
        i++;
        return;
    }

    if (compressed[i] == '1') {
        flag = false;
        if (tree->left == nullptr) {
            tree->left = new Node();
            i++;
            recover_tree(tree->left, compressed, i, n, flag, outfl);
        }
    }

    if (compressed[i] == '1') {
        flag = false;
        if (tree->right == nullptr) {
            tree->right = new Node();
            i++;
            recover_tree(tree->right, compressed, i, n, flag, outfl);
        }
    }
}

// Записывает символы в дерево Хаффмана
void write_letters_in_tree(Node* &tree, vector<char> &letters, int &i) {
    if ((tree->left == nullptr) && (tree->right == nullptr)) {
        tree->c = letters[i];
        i++;
        return;
    }

    if (tree->left != nullptr)
        write_letters_in_tree(tree->left, letters, i);
    if (tree->right != nullptr)
        write_letters_in_tree(tree->right, letters, i);
}

// Декодирует закодированную данные
string decode_string(string &compressed) {
    // Восстанавливает структуру дерева Хаффмана
    Node* tree = new Node();
    int i = 0, n = 0;
    bool flag = true, outfl = false;
    recover_tree(tree, compressed, i, n, flag, outfl);
    i++;

    // Восстанавливает символы в дереве Хаффмана
    vector<char> letters;
    for ( ; n > 0; n--, i++) {
        letters.push_back(char(compressed[i]));
    }
    int j = 0;
    write_letters_in_tree(tree, letters, j);

    // Декодирует данные
    string original = "";
    while(i < compressed.length()) {
        Node* cur = tree;
        while ((cur->left != nullptr) && (cur->right != nullptr)) {
            if (compressed[i] == '0')
                cur = cur->left;
            else
                cur = cur->right;
            i++;
        }
        original += cur->c;
    }

    delete tree;
    return original;
}

// Архивирует данные из потока input
void Encode(IInputStream& input, IOutputStream& output){
    string s;
    byte value;

    while (input.Read(value)) {
        s.push_back(value);
    }

    s = encode_string(s);

    int i = 0;
    while (s[i] != '0' || s[i + 1] != '0')
        ++i;
    ++i;

    int cnt_zeros = 0;
    for (int q = 0; q <= i; q += 8) {
        int k = 0;
        for (int t = 0; t < 8; ++t) {
            if (q + t <= i) {
                if (s[q + t] == '1')
                    k |= (1 << t);
                if (s[q + t] == '0')
                    ++cnt_zeros;
            }
        }
        output.Write((char)k);
    }
    cnt_zeros--;
    i++;
    for (int q = 0; q < cnt_zeros; ++q, ++i) {
        output.Write(s[i]);
    }

    int lastCnt = s.size() - i;
    output.Write((char)((lastCnt >> 24) & 255));
    output.Write((char)((lastCnt >> 16) & 255));
    output.Write((char)((lastCnt >> 8) & 255));
    output.Write((char)(lastCnt & (255)));
    for (; i < s.size(); i += 8) {
        int k = 0;
        for (int t = 0; t < 8; ++t) {
            if (i + t < s.size()) {
                if (s[i + t] == '1')
                    k |= (1 << t);
                if (s[i + t] == '0')
                    ++cnt_zeros;
            }
        }
        output.Write((char)k);
    }
}

// Метод восстанавливает оригинальные данные
void Decode(IInputStream& input, IOutputStream& output){
    cerr << "!!!!" << endl;
    string s;
    byte value;
    int cnt_zeros = 0;
    while (s.size() < 2 || (s.back() != '0' || s[s.size() - 2] != '0')) {
        input.Read(value);
        int tmp = (unsigned char)(char)value;
        int t = 0;
        while (s.size() < 2 || (s.back() != '0' || s[s.size() - 2] != '0')) {
            if (t == 8) break;
            if ((tmp & 1) == 0) cnt_zeros++;
            s.push_back((char)((tmp & 1) + (int) '0'));
            tmp /= 2;
            t++;
        }
    }

    --cnt_zeros;
    for (int i = 0; i < cnt_zeros; ++i) {
        input.Read(value);
        s.push_back(value);
    }

    int number = 0;
    input.Read(value);
    number += ((unsigned char)(char)value << 24);
    input.Read(value);
    number += ((unsigned char)(char)value << 16);
    input.Read(value);
    number += ((unsigned char)(char)value << 8);
    input.Read(value);
    number += ((unsigned char)(char)value << 0);

    for (int i = 0; i < number; i += 8) {
        input.Read(value);
        int tmp = (unsigned char)(char)value;
        for (int t = 0; t < 8; ++t) {
            if (i + t < number) {
                s.push_back((tmp & 1) + '0');
                tmp /= 2;
            }
        }
    }

    s = decode_string(s);

    for (char symbol : s){
        output.Write(byte(symbol));
    }
}