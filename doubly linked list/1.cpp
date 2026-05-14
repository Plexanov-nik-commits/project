#include <iostream>
using namespace std;

// Структура узла двусвязного списка
struct Node {
    int inf;
    Node* next;
    Node* prev;
};

// Функция добавления элемента в конец списка
void push(Node*& h, Node*& t, int x) {//h- начало списка, t-конец списка, x-конкретный элемент ссылка на указатель, чтобы можно было изменить сами указатели
    Node* r = new Node;//создаем новый узел
    r->inf = x;//добавляем в информацционное поле элемент
    r->next = NULL;
    
    if (!h && !t) { // список пуст
        r->prev = NULL;
        h = r;
    } else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

// Функция печати списка
void printList(Node* h) {
    Node* p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

// Функция поиска минимального значения
int findMin(Node* h) {
    int minVal = h->inf;
    Node* p = h;
    while (p) {
        if (p->inf < minVal)
            minVal = p->inf;
        p = p->next;
    }
    return minVal;
}

// Функция поиска последнего нечетного элемента
int findLastOdd(Node* h) {
    int lastOdd = -1;
    Node* p = h;
    while (p) {
        if (p->inf % 2 != 0)
            lastOdd = p->inf;
        p = p->next;
    }
    return lastOdd;
}

// Функция вставки элемента после заданного узла
void insertAfter(Node*& t, Node* pos, int x) {
    Node* r = new Node;
    r->inf = x;
    
    if (pos == t) { // вставка после хвоста
        r->next = NULL;
        r->prev = pos;
        pos->next = r;
        t = r;
    } else {
        r->next = pos->next;
        r->prev = pos;
        pos->next->prev = r;
        pos->next = r;
    }
}

// Функция удаления списка для освобождения памяти
void deleteList(Node*& h, Node*& t) {
    while (h) {
        Node* p = h;
        h = h->next;
        if (h) h->prev = NULL;
        delete p;
    }
    t = NULL;
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    int n, value;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        push(head, tail, value);
    }
    
    if (!head) {
        cout << "Список пуст" << endl;
        return 0;
    }
    
    // Находим минимальное число
    int minVal = findMin(head);
    
    // Находим последний нечетный элемент
    int lastOdd = findLastOdd(head);
    
    if (lastOdd == -1) {
        cout << "Нет нечетных элементов. Список: ";
        printList(head);
        deleteList(head, tail);
        return 0;
    }
    
    // Вставляем lastOdd после каждого минимального элемента
    Node* p = head;
    while (p) {
        if (p->inf == minVal) {
            insertAfter(tail, p, lastOdd);
            p = p->next; // пропускаем вставленный элемент
        }
        p = p->next;
    }
    
    cout << "Результат: ";
    printList(head);
    
    // Освобождаем память
    deleteList(head, tail);
    
    return 0;
}