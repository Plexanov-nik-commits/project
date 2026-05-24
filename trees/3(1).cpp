#include <iostream>
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

// Поиск узла по значению
tree* find(tree* tr, int x) {
    if (!tr || x == tr->inf)
        return tr;
    if (x < tr->inf)
        return find(tr->left, x);
    else
        return find(tr->right, x);
}

// Поиск минимального элемента в поддереве
tree* Min(tree* tr) {
    if (!tr->left) return tr;
    else return Min(tr->left);
}

// Поиск следующего элемента (для удаления)
tree* Next(tree* tr, int x) {
    tree* n = find(tr, x);
    if (n->right)
        return Min(n->right);
    tree* y = n->parent;
    while (y && n == y->right) {
        n = y;
        y = y->parent;
    }
    return y;
}

// Удаление узла 
void Delete(tree*& tr, tree* v) {
    if (!v) return;

    tree* p = v->parent;

    // Случай 1: нет детей (лист)
    if (!v->left && !v->right) {
        if (!p) {
            tr = NULL;
        }
        else {
            if (p->left == v) p->left = NULL;
            if (p->right == v) p->right = NULL;
        }
        delete v;
    }
    // Случай 2: только один ребенок
    else if (!v->left || !v->right) {
        tree* child = (v->left) ? v->left : v->right;

        if (!p) {
            tr = child;
            child->parent = NULL;
        }
        else {
            if (p->left == v) p->left = child;
            else p->right = child;
            child->parent = p;
        }
        delete v;
    }
    // Случай 3: два ребенка
    else {
        tree* succ = Next(tr, v->inf);
        v->inf = succ->inf;

        // Удаляем succ (у него нет левого ребенка)
        if (succ->parent->left == succ) {
            succ->parent->left = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;
        }
        else {
            succ->parent->right = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;
        }
        delete succ;
    }
}

// Удаление всех четных элементов
void deleteEvenNodes(tree*& tr) {
    if (!tr) return;

    // Сначала рекурсивно обходим левое и правое поддеревья
    deleteEvenNodes(tr->left);
    deleteEvenNodes(tr->right);

    // Проверяем текущий узел (после обработки детей, чтобы не потерять ссылки)
    if (tr->inf % 2 == 0) {
        Delete(tr, tr);
    }
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

    deleteEvenNodes(tr);

    cout << "\nВизуальное представление:" << endl;
    printTree(tr);

    return 0;
}