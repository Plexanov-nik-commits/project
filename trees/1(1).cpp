#include <iostream>
#include <vector>
using namespace std;

// Структура узла дерева 
struct tree {
    int inf;
    tree* right;
    tree* left;
    tree* parent;
};

// Создание нового узла
tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

// Вставка элемента в дерево бинарного поиска 
void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) {
        tr = n; // первый элемент — корень
    }
    else {
        tree* y = tr;
        while (y) {
            if (n->inf > y->inf) { // правая ветка
                if (y->right)
                    y = y->right;
                else {
                    n->parent = y;
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { // левая ветка
                if (y->left)
                    y = y->left;
                else {
                    n->parent = y;
                    y->left = n;
                    break;
                }
            }
            else {
                // элемент уже существует — не вставляем
                delete n;
                break;
            }
        }
    }
}

// Поиск узла по значению 
tree* find(tree* tr, int x) {
    if (!tr || x == tr->inf)
        return tr;
    if (x < tr->inf)
        return find(tr->left, x);
    else
        return find(tr->right, x);
}

// Сумма всех предков узла
int sumOfAncestors(tree* node) {
    int sum = 0;
    tree* current = node->parent; // начинаем с родителя
    while (current) {
        sum += current->inf;
        current = current->parent;
    }
    return sum;
}
// Функция для вывода бинарного дерева только числами (горизонтально)
void printTree(tree* tr, int level = 0) {
    if (tr == NULL) {
        return;
    }

    // Выводим правое поддерево (с отступами)
    if (tr->right != NULL) {
        printTree(tr->right, level + 1);
    }

    // Выводим текущий узел с отступами
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << tr->inf << endl;

    // Выводим левое поддерево
    if (tr->left != NULL) {
        printTree(tr->left, level + 1);
    }
}

int main() {
    tree* tr = NULL;
    int n, x, X;

    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите " << n << " целых чисел:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x;
        insert(tr, x);
    }

    cout << "\nВведите узел X: ";
    cin >> X;

    tree* found = find(tr, X);

    if (found) {
        int sum = sumOfAncestors(found);
        cout << "\nУзел " << X << " найден в дереве." << endl;
        cout << "Сумма всех его предков: " << sum << endl;
    }
    else {
        cout << "\nУзел " << X << " не существует в дереве." << endl;
    }
    printTree(tr);
    return 0;
}