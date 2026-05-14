#include <iostream>
#include <climits>  // для INT_MAX и INT_MIN
using namespace std;

// Структура узла стека 
struct mystack {
    int inf;
    mystack* next;
};

// Добавление элемента в стек 
void push(mystack*& h, int x) {
    mystack* r = new mystack;
    r->inf = x;
    r->next = h;
    h = r;
}

// Удаление элемента из стека 
int pop(mystack*& h) {
    int i = h->inf;
    mystack* r = h;
    h = h->next;
    delete r;
    return i;
}

// Переворачивание стека 
void reverse(mystack*& h) {
    mystack* head1 = NULL;
    while (h != NULL) {
        push(head1, pop(h));
    }
    h = head1;
}

// Подсчет количества элементов в стеке
int getSize(mystack* h) {
    if (h == NULL) return 0;
    
    mystack* temp = NULL;
    int size = 0;
    
    // Перекладываем все элементы во временный стек
    while (h != NULL) {
        push(temp, pop(h));
        size++;
    }
    
    // Возвращаем элементы обратно
    while (temp != NULL) {
        push(h, pop(temp));
    }
    
    return size;
}

// Нахождение максимума и минимума в стеке
void findMinMax(mystack* h, int& minVal, int& maxVal) {
    if (h == NULL) return;
    
    mystack* temp = NULL;
    minVal = INT_MAX;
    maxVal = INT_MIN;
    
    // Перекладываем элементы и находим min/max
    while (h != NULL) {
        int val = pop(h);
        if (val > maxVal) maxVal = val;
        if (val < minVal) minVal = val;
        push(temp, val);
    }
    
    // Возвращаем элементы обратно
    while (temp != NULL) {
        push(h, pop(temp));
    }
}

// Нахождение позиций первого и последнего максимума
void findMaxPositions(mystack* h, int maxVal, int& firstPos, int& lastPos, int size) {
    if (h == NULL) return;
    
    mystack* temp = NULL;
    firstPos = -1;
    lastPos = -1;
    
    // Перекладываем во временный стек (порядок изменится)
    while (h != NULL) {
        push(temp, pop(h));
    }
    
    // Теперь проходим в правильном порядке (от первого к последнему)
    int pos = 0;
    mystack* temp2 = NULL;
    while (temp != NULL) {
        int val = pop(temp);
        if (val == maxVal) {
            if (firstPos == -1) firstPos = pos;
            lastPos = pos;
        }
        push(temp2, val);
        pos++;
    }
    
    // Восстанавливаем исходный стек
    while (temp2 != NULL) {
        push(h, pop(temp2));
    }
}

// Основная функция: вставка минимума после первого и последнего максимума (без массива)
void insertMinAfterFirstAndLastMax(mystack*& h) {
    if (h == NULL) return;
    
    // 1. Находим минимум, максимум и позиции в одном проходе
    mystack* temp = NULL;
    int minVal = INT_MAX, maxVal = INT_MIN;
    int size = 0;
    
    // Первый проход: находим min, max и размер
    while (h != NULL) {
        int val = pop(h);
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
        push(temp, val);
        size++;
    }
    
    // Восстанавливаем стек
    while (temp != NULL) {
        push(h, pop(temp));
    }
    
    // 2. Находим позиции первого и последнего максимума
    int firstMaxPos = -1, lastMaxPos = -1;
    int pos = 0;
    
    while (h != NULL) {
        int val = pop(h);
        if (val == maxVal) {
            if (firstMaxPos == -1) firstMaxPos = pos;
            lastMaxPos = pos;
        }
        push(temp, val);
        pos++;
    }
    
    // Восстанавливаем стек
    while (temp != NULL) {
        push(h, pop(temp));
    }
    
    // 3. Создаем результат, проходя стек с начала
    // Для этого переворачиваем стек
    reverse(h);
    
    mystack* result = NULL;
    pos = 0;
    
    // Теперь h в правильном порядке (сверху первый элемент)
    while (h != NULL) {
        int val = pop(h);
        push(result, val);
        
        if (pos == firstMaxPos+1) {
            push(result, minVal);
        }
        
        if (pos == lastMaxPos+1 && firstMaxPos+1 != lastMaxPos) {
            push(result, minVal);
        }
        
        pos++;
    }
    
    // Переворачиваем результат обратно
    reverse(result);
    
    // Очищаем старый стек
    while (h != NULL) {
        pop(h);
    }
    
    h = result;
}

// Печать стека (без разрушения)
void printStack(mystack* h) {
    if (h == NULL) {
        cout << "Стек пуст" << endl;
        return;
    }
    
    mystack* temp = NULL;
    
    // Перекладываем для печати в правильном порядке
    while (h != NULL) {
        cout << h->inf << " ";
        push(temp, pop(h));
    }
    
    // Восстанавливаем стек
    while (temp != NULL) {
        push(h, pop(temp));
    }
    cout << endl;
}

int main() {
    mystack* head = NULL;
    int n, value;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Стек пуст" << endl;
        return 0;
    }
    
    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        push(head, value);
    }
    
    
    
    insertMinAfterFirstAndLastMax(head);
    
    cout << "Стек после вставки: ";
    printStack(head);
    
    return 0;
}