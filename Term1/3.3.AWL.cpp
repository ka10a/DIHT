#include <bits/stdc++.h>

/*Дано число N и N строк. Каждая строка содержащит команду добавления
 * или удаления натуральных чисел, а также запрос на получение
 * k-ой порядковой статистики. Команда добавления числа A задается
 * положительным числом A, команда удаления числа A задается отрицательным числом “-A”.
 * Запрос на получение k-ой порядковой статистики задается числом k.
 * Требуемая скорость выполнения запроса - O(log n).
 */

using namespace std;

class NodeAWL{
    int x, cnt, h;
    NodeAWL* left;
    NodeAWL* right;

public:
    // Конструктор по умолчанию
    NodeAWL(int x){
        this->x = x;
        cnt = 0;
        h = 0;
        left = right = nullptr;
    }

    // Правило трёх
    NodeAWL(const NodeAWL &other){
        x = other.x;
        cnt = other.cnt;
        h = other.h;
        left = other.left;
        right = other.right;
    }

    NodeAWL& operator=(const NodeAWL &other) {
        x = other.x;
        cnt = other.cnt;
        h = other.h;
        left = other.left;
        right = other.right;
        return *this;
    }

    ~NodeAWL(){
        if (left != nullptr)
            delete left;
        left = nullptr;

        if (right != nullptr)
            delete right;
        right = nullptr;
    }

    friend void update(NodeAWL* &);
    friend void left_rotate(NodeAWL* &);
    friend void huge_left_rotate(NodeAWL* &);
    friend void right_rotate(NodeAWL* &);
    friend void huge_right_rotate(NodeAWL* &);
    friend void check(NodeAWL* &);
    friend void add_in_awl(NodeAWL* &, int);
    friend void remake(NodeAWL* &);
    friend NodeAWL* remove_from_awl(NodeAWL* &, int);
    friend int find_k_stat(NodeAWL*, int);
};

// Обновляет значения cnt (количества вершин в дереве) и h (высоту дерева)
void update(NodeAWL* &root){
    if (root == nullptr)
        return;

    // Количество вершин в дереве - это сумма количества вершин
    // в левом поддереве и правом поддереве и еще сама вершина
    root->cnt = 0;
    if (root->left != nullptr)
        root->cnt += root->left->cnt;
    if (root->right != nullptr)
        root->cnt += root-> right->cnt;
    root->cnt++;

    // Высота дерева - это максимум из высот детей и еще одна вершина
    root->h = 0;
    if (root->left != nullptr)
        root->h = max(root->h, root->left->h + 1);
    if (root->right != nullptr)
        root->h = max(root->h, root->right->h + 1);
}

// Малое левое вращение
void left_rotate(NodeAWL* &root){
    NodeAWL* a = root;
    NodeAWL* b = root->right;

    NodeAWL* C = nullptr;
    if (b != nullptr)
        C = b->left;

    a->right = C;
    update(a);

    b->left = a;
    update(b);

    root = b;
}

// Большое левое вращение
void huge_left_rotate(NodeAWL* &root){
    NodeAWL* a = root;
    NodeAWL* b = a->right;

    NodeAWL* c = nullptr;
    if (b != nullptr)
        c = b->left;

    NodeAWL* L = nullptr;
    NodeAWL* R = nullptr;
    if (c != nullptr) {
        L = c->left;
        R = c->right;
    }

    a->right = L;
    update(a);

    b->left = R;
    update(b);

    c->left = a;
    c->right = b;
    update(c);

    root = c;
}

// Малое правое вращение
void right_rotate(NodeAWL* &root){
    NodeAWL* a = root;
    NodeAWL* b = a->left;
    NodeAWL* C = nullptr;

    if (b != nullptr)
        C = b->right;

    a->left = C;
    update(a);

    b->right = a;
    update(b);

    root = b;
}

// Большое правое вращение
void huge_right_rotate(NodeAWL* &root){
    NodeAWL* a = root;
    NodeAWL* b = a->left;

    NodeAWL* c = nullptr;
    if(b != nullptr)
        c = b->right;

    NodeAWL* L = nullptr;
    NodeAWL* R = nullptr;
    if (c != nullptr){
        L = c->left;
        R = c->right;
    }

    b->right = L;
    update(b);

    a->left = R;
    update(a);

    c->left = b;
    c->right = a;
    update(c);

    root = c;
}

// Проверяет дерево на правильность и перестраивает, если надо
void check(NodeAWL* &root){
    if (root == nullptr)
        return;

    // Высоты левого и правого поддерева соответственно
    int h_left = 0, h_right = 0;
    if (root->left != nullptr)
        h_left = root->left->h;
    if (root->right != nullptr)
        h_right = root->right->h;

    if (h_right == h_left + 2){
        int h_c = 0, h_r = 0;

        if (root->right != nullptr){
            if (root->right->left != nullptr)
                h_c = root->right->left->h;
            if (root->right->right != nullptr)
                h_r = root->right->right->h;
        }

        if (h_c <= h_r)
            left_rotate(root);
        else
            huge_left_rotate(root);
    }

    if (h_right + 2 == h_left){
        int h_c = 0, h_l = 0;

        if (root->left != nullptr){
            if (root->left->left != nullptr)
                h_l = root->left->left->h;
            if (root->left->right != nullptr)
                h_c = root->left->right->h;
        }

        if (h_c <= h_l)
            right_rotate(root);
        else
            huge_right_rotate(root);
    }
}

// Добавляет верщину в дерево
void add_in_awl(NodeAWL* &root, int a){
    // Если дерево пусто, создадим веришну
    if (root == nullptr){
        root = new NodeAWL(a);
        update(root);
        check(root);
        return;
    }

    // Как в наивном дереве поиска ищем место вставки
    if (a >= root->x)
        add_in_awl(root->right, a);
    else
        add_in_awl(root->left, a);

    update(root);
    check(root);
}

// Перестраивает дерево после удаления веришны с двумя детьми
void remake(NodeAWL* &root){
    // Если левого сына нет, то мы нашли вершину, которую хотим удалить
    if (root->left == nullptr)
        root = root->right;
    else
        remake(root->left);
    update(root);
    check(root);
}

// Удаляет вершину из дерева
NodeAWL* remove_from_awl(NodeAWL* &root, int a){
    if (root == nullptr)
        return nullptr;

    // Если нашли верщину, которую надо удалить
    if (a == root->x){
        NodeAWL* ans = nullptr; // здесь в итоге будет валидное дерево с удаленной вершиной

        //  Если есть оба ребенка
        if ((root->left != nullptr) && (root->right != nullptr)){
            ans = root;

            // Ищем вершину, следующую по значению за удаляемой
            NodeAWL* M = root->right;
            while (M->left != nullptr)
                M = M->left;

            ans->x = M->x;
            remake(ans->right);

            M->right = M->left = nullptr;
            delete M;
            M = nullptr;
        }
        else{
            // Если нет одного из сыновей
            if (root->left != nullptr)
                ans = root->left;
            else if (root->right != nullptr)
                ans = root->right;

            root->left = root->right = nullptr;

            delete root;
            root = nullptr;
        }

        root = ans;
    }
    else{
        // Ищем удаляемую вершину, как в наивном дереве поиска
        if (a >= root->x)
            root->right = remove_from_awl(root->right, a);
        else
            root->left = remove_from_awl(root->left, a);
    }

    update(root);
    check(root);

    return root;
}

// Ищет k-ю порядковую статистику
int find_k_stat(NodeAWL* root, int k){
    if (root == nullptr)
        return -1;

    // Т.к. слева все вершины меньше текущей, а справа больше или равны,
    // то номер веришны в статистике можно узнать, зная количество вершин до нее.

    //Если слева не пусто
    if (root->left != nullptr){
        // Если текущая вершина - искомая порядковая статистика
        if (root->left->cnt + 1 == k){
            return root->x;
        }
        else {
            // Если в левом поддереве вершин больше, чем k, то там лежит ответ
            // на запрос порядковой статистики. Иначе ищем в правом поддереве,
            // учитывая, что в левом поддереве уже root->left->cnt вершин и еще
            // одна текущая.
            if (root->left->cnt >= k)
                return find_k_stat(root->left, k);
            else
                return find_k_stat(root->right, k - root->left->cnt - 1);
        }
    }
    else {
        if (k == 1)
            return root->x;
        else
            return find_k_stat(root->right, k - 1);
    }
}

int main(){
    int n;
    cin >> n;

    NodeAWL* root = nullptr;

    for (int i = 0; i < n; i++){
        int a, k;
        cin >> a >> k;

        if (a > 0)
            add_in_awl(root, a);
        else
            root = remove_from_awl(root, abs(a));

        cout << find_k_stat(root, k + 1) << endl;
    }

    delete root;

    return 0;
}