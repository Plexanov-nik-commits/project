#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int inf;
    tree* right;
    tree* left;
    tree* parent;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) {
        tr = n;
    }
    else {
        tree* y = tr;
        while (y) {
            if (n->inf > y->inf) {
                if (y->right)
                    y = y->right;
                else {
                    n->parent = y;
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) {
                if (y->left)
                    y = y->left;
                else {
                    n->parent = y;
                    y->left = n;
                    break;
                }
            }
            else {
                delete n;
                break;
            }
        }
    }
}

// Функция для вывода узлов, имеющих только правого ребенка
void prr(tree* tr) {
    if (!tr) return;

    // Сначала проверяем левое поддерево
    prr(tr->left);

    // Проверяем текущий узел
    if (tr->left == NULL && tr->right != NULL) {
        cout << tr->inf << " ";
    }

    // Затем правое поддерево
    prr(tr->right);
}

int prrcount(tree* tr) {
    if (!tr) return 0;

    int count = 0;
    if (tr->left == NULL && tr->right != NULL) {
        count = 1;
    }

    return count + prrcount(tr->left) + prrcount(tr->right);
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
    int n, x;

    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите " << n << " целых чисел:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x;
        insert(tr, x);
    }

    cout << "\nУзлы, имеющие только правого ребенка: ";
    prr(tr);
    cout << endl;

    int count = prrcount(tr);
    cout << "Количество таких узлов: " << count << endl;
    printTree(tr);
    return 0;
}