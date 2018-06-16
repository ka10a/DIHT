#include <bits/stdc++.h>

/*Дано число N < 106 и последовательность целых чисел из [-2^31..2^31] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root,
 * если root→Key ≤ K, то узел K добавляется в правое поддерево root;
 * иначе в левое поддерево root. Выведите элементы в порядке pre-order (сверху вниз).
 */

using namespace std;

class Node {
    int x;
    Node* left;
    Node* right;

public:
    // Конструктор по-умолчанию
    Node(int x = 0, Node* left = nullptr, Node* right = nullptr) {
        this->x= x;
        this->left = left;
        this->right = right;
    }

    // Правило трёх
    Node(const Node &other) {
        x = other.x;
        left = other.left;
        right = other.right;
    }

    Node& operator=(const Node &other) {
        x = other.x;
        left = other.left;
        right = other.right;
        return *this;
    }

    ~Node() {
        if (left != nullptr)
            delete left;
        left = nullptr;
        if (right != nullptr)
            delete right;
        right = nullptr;
    }

    friend void AddInTree(Node *&, int);
    friend void PrintPreOrder(Node*);
};

// Строит наивное дерево поиска
void AddInTree(Node *&root, int a) {
    // Если дерево пусто, вставляем вершину
    if (root == nullptr){
        root = new Node(a);
        return;
    }

    // Ищем место вставки
    if (root->x < a)
        AddInTree(root->right, a);
    else
        AddInTree(root->left, a);
}

// Вывоит веришны в порядке pre-order
void PrintPreOrder(Node* root) {
    if (root == nullptr)
        return;

    cout << root->x << '\n';
    PrintPreOrder(root->left);
    PrintPreOrder(root->right);
}

int main() {
    int n;
    cin >> n;

    int a;
    cin >> a;
    Node* root = new Node(a);

    for (int i = 1; i < n; i++) {
        cin >> a;
        AddInTree(root, a);
    }

    PrintPreOrder(root);

    delete root;

    return 0;
}