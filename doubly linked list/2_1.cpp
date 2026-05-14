#include <iostream>
using namespace std;

struct list {
    int inf;
    list *next;
    list *prev;
};

void push(list *&h, list *&t, int x) {
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    
    if (!h && !t) {
        r->prev = NULL;
        h = r;
    } else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void print(list *h, list *t) {
    list *p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

void del_list(list *&h, list *&t) {
    while (h) {
        list *p = h;
        h = h->next;
        if (h) h->prev = NULL;
        delete p;
    }
    t = NULL;
}

int main() {
    list *head = NULL;
    list *tail = NULL;
    list *evenHead = NULL;
    list *evenTail = NULL;
    list *oddHead = NULL;
    list *oddTail = NULL;
    
    int n, value;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        push(head, tail, value);
    }
    
    cout << "Исходный список: ";
    print(head, tail);
    
    // Разделяем на четные и нечетные
    list *current = head;
    while (current) {
        if (current->inf % 2 == 0) {
            push(evenHead, evenTail, current->inf);
        } else {
            push(oddHead, oddTail, current->inf);
        }
        current = current->next;
    }
    
    // Очищаем исходный список
    del_list(head, tail);
    
    // Соединяем: сначала четные, потом нечетные
    if (evenHead) {
        head = evenHead;
        if (oddHead) {
            evenTail->next = oddHead;
            oddHead->prev = evenTail;
            tail = oddTail;
        } else {
            tail = evenTail;
        }
    } else {
        head = oddHead;
        tail = oddTail;
    }
    
    cout << "Результат (четные в начале): ";
    print(head, tail);
    
    // Очищаем память
    del_list(head, tail);
    
    return 0;
}