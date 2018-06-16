#include <bits/stdc++.h>

/*Дано число N < 106 и последовательность пар целых чисел из [-2^31, 2^31] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
 * Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
 * Добавление узла в декартово дерево выполняйте второй версией алгоритма,
 * рассказанного на лекции: При добавлении узла (x, y) выполняйте спуск по ключу
 * до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так,
 * чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x.
 * Получившиеся два дерева сделайте дочерними для нового узла (x, y).
 * Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi.
 * Равные ключи добавляйте в правое поддерево. Вычислить разницу глубин наивного дерева поиска
 * и декартового дерева. Разница может быть отрицательна.
 */

using namespace std;

class NodeBST {
    int x, deep;
    NodeBST* left;
    NodeBST* right;

public:
    // Конструктор по умолчанию
    NodeBST(int x = 0) {
        this->x= x;
        this->deep = 0;
        left = nullptr;
        right = nullptr;
    }

    // Правило трёх
    NodeBST(const NodeBST &other) : x(other.x), deep(other.deep),
                                    left(other.left), right(other.right) {
    }

    NodeBST& operator=(const NodeBST &other) {
        x = other.x;
        deep = other.deep;
        left = other.left;
        right = other.right;
        return *this;
    }

    ~NodeBST() {
        if (left != nullptr)
            delete left;
        left = nullptr;
        if (right != nullptr)
            delete right;
        right = nullptr;
    }

    // Возвращает deep
    int get_deep() {
        return deep;
    }

    friend void recnt(NodeBST* &);
    friend void add_in_BST_tree(NodeBST* &, int);

};

// Пересчитывает высоту дерева
void recnt(NodeBST* &root) {
    if (root == nullptr)
        return;

    // Высота дерева - максимум из высот детей и еще одна вершина
    root->deep = 0;
    if (root->left != nullptr)
        root->deep = max(root->deep, root->left->deep);
    if (root->right != nullptr)
        root-> deep = max(root->deep, root->right->deep);
    if ((root->left != nullptr) || (root->right != nullptr))
            root->deep++;
}

// Добавляет вершину в наивное дерево поиска
void add_in_BST_tree(NodeBST* &root, int a) {
    // Если дерево пусто, добавим вершину
    if (root == nullptr){
        root = new NodeBST(a);
        return;
    }

    if (root->x < a)
        add_in_BST_tree(root->right, a);
    else
        add_in_BST_tree(root->left, a);

    recnt(root);
}

class NodeTreap {
    int x, y, deep;
    NodeTreap* left;
    NodeTreap* right;

public:
    // Конструктор по умолчанию
    NodeTreap(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
        left = nullptr;
        right = nullptr;
        deep = 0;
    }

    // Правило трёх
    NodeTreap(const NodeTreap &other) {
        x = other.x;
        y = other.y;
        deep = other.deep;
        left = other.left;
        right = other.right;
    }

    NodeTreap& operator=(const NodeTreap &other) {
        x = other.x;
        y = other.y;
        deep = other.deep;
        left = other.left;
        right = other.right;
        return *this;
    }

    ~NodeTreap() {
        if (left != nullptr)
            delete left;
        left = nullptr;
        if(right != nullptr)
            delete right;
        right = nullptr;
    }

    // Возвращает deep
    int get_deep() {
        return deep;
    }

    friend void update(NodeTreap* &);
    friend pair<NodeTreap*, NodeTreap*> split(NodeTreap* &, int);
    friend NodeTreap* add_in_treap(NodeTreap* &, NodeTreap*);
};

// Пересчитывает высоту декартового дерева
void update(NodeTreap* &root) {
    if (root == nullptr)
        return;

    // Высота дерева - максимум из высот детей и еще одна вершина
    root->deep = 0;
    if (root->left != nullptr)
        root->deep = max(root->deep, root->left->deep);
    if (root->right != nullptr)
        root-> deep = max(root->deep, root->right->deep);
    if ((root->left != nullptr) || (root->right != nullptr))
        root->deep++;
}

// Разбивает декартово дерево на два декартовых дерева, причем
// все значения в левом меньше, чем все значения в правом
pair<NodeTreap*, NodeTreap*> split(NodeTreap* &root, int x) {
    NodeTreap* t1;
    NodeTreap* t2;

    if (root == nullptr)
        return {nullptr, nullptr};

    if (root->x == x) {
        t1 = root->left;
        t2 = root;
        t2->left = nullptr;
    }
    else if (x > root->x) {
            pair<NodeTreap*, NodeTreap*> tt = split(root->right, x);
            t1 = root;
            t1->right = tt.first;
            t2 = tt.second;
        }
        else {
            pair<NodeTreap*, NodeTreap*> tt = split(root->left, x);
            t2 = root;
            t2->left = tt.second;
            t1 = tt.first;
        }

    update(t1);
    update(t2);

    return {t1, t2};
};

// Добавляет вершину в декартово дерево
NodeTreap* add_in_treap(NodeTreap* &root, NodeTreap* a) {
    if (root == nullptr)
        return a;

    // По ключам - куча, поэтому важен y и первая вершина, в которой
    // ключ будет меньше
    if (a->y > root->y) {
        pair<NodeTreap*, NodeTreap*> tt = split(root, a->x);

        a->left = tt.first;
        a->right = tt.second;

        update(a);

        return a;
    }

    // Ищем место вставки, как в наивном дереве поиска
    if (root->x <= a->x) {
        root->right = add_in_treap(root->right, a);
        update(root);
    }
    else {
        root->left = add_in_treap(root->left, a);
        update(root);
    }

    return root;
}

int main() {
    int n;
    cin >> n;

    int a, b;
    cin >> a >> b;
    NodeBST* bst = new NodeBST(a);
    NodeTreap* treap = new NodeTreap(a, b);

    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        add_in_BST_tree(bst, a);
        treap = add_in_treap(treap, new NodeTreap(a, b));
    }

    cout << bst->get_deep() - treap->get_deep() << endl;

    delete bst;
    delete treap;

    return 0;
}