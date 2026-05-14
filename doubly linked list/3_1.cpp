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

void print(list *h) {
    while (h) {
        cout << h->inf << " ";
        h = h->next;
    }
    cout << endl;
}

void del_node(list *&h, list *&t, list *r) {
    if (r == h && r == t) h = t = NULL;
    else if (r == h) {
        h = h->next;
        h->prev = NULL;
    } else if (r == t) {
        t = t->prev;
        t->next = NULL;
    } else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

// Функция вычисления среднего арифметического элементов от start до конца
double avgFrom(list *start) {
    if (!start) return 0;
    int sum = 0, count = 0;
    while (start) {
        sum += start->inf;
        count++;
        start = start->next;
    }
    return (double)sum / count;
}

// Основная функция обработки списка
void process(list *&h, list *&t) {
    bool changed;
    do {
        changed = false;
        list *current = h;
        
        while (current && current->next) { // последний элемент не проверяем
            double avgNext = avgFrom(current->next);
            
            if (current->inf > avgNext) {
                list *toDelete = current;
                current = current->next; // запоминаем следующий ДО удаления
                del_node(h, t, toDelete);
                changed = true;
                // continue, чтобы current не увеличивался дважды
                continue;
            }
            current = current->next;
        }
    } while (changed);
}

int main() {
    list *head = NULL, *tail = NULL;
    int n, x;
    
    cout << "n = ";
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(head, tail, x);
    }
    
    cout << "Было: ";
    print(head);
    
    process(head, tail);
    
    cout << "Стало: ";
    print(head);
    
    return 0;
}