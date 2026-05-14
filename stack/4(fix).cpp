#include <iostream>
#include <cctype>
using namespace std;

// Структура узла стека
struct mystack{
    char inf;
    mystack* next;
};

// Добавление элемента в стек
void push(mystack*& h, char x) {
    mystack* r = new mystack;
    r->inf = x;
    r->next = h;
    h = r;
}

// Удаление элемента из стека
char pop(mystack*& h) {
    char i = h->inf;
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

// Функция проверки, является ли буква согласной
bool isConsonant(char ch) {
    ch = tolower(ch);
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
        return false;
    }
    return (ch >= 'a' && ch <= 'z');
}

// Подсчет количества элементов в стеке
int getSize(mystack* h) {
    if (h == NULL) return 0;
    
    mystack* temp = NULL;
    int size = 0;
    
    while (h != NULL) {
        push(temp, pop(h));
        size++;
    }
    
    while (temp != NULL) {
        push(h, pop(temp));
    }
    
    return size;
}

// Основная функция: вставка '?' после последней согласной
void insertAfterLastConsonant(mystack*& h) {
    if (h == NULL) return;
    
    // 1. Сначала переворачиваем стек, чтобы работать с начала
    reverse(h);
    
    // 2. Создаем временный стек для хранения элементов
    mystack* temp = NULL;
    mystack* result = NULL;
    
    // 3. Первый проход: переносим во временный стек и находим последнюю согласную
    int pos = 0;
    int lastConsonantPos = -1;
    
    while (h != NULL) {
        char val = pop(h);
        push(temp, val);
        
        if (isConsonant(val)) {
            lastConsonantPos = pos;
        }
        pos++;
    }
    
    // Если согласных нет, восстанавливаем стек и выходим
    if (lastConsonantPos == -1) {
        cout << "Согласных букв нет. Стек не изменен." << endl;
        // Восстанавливаем исходный стек
        while (temp != NULL) {
            push(h, pop(temp));
        }
        reverse(h); // возвращаем исходный порядок
        return;
    }
    
    
    // 4. Второй проход: переносим обратно в h с вставками
    pos = 0;
    while (temp != NULL) {
        char val = pop(temp);
        push(h, val);
        pos++;
    }
    
    // 5. Теперь h содержит элементы в обратном порядке, переворачиваем
    reverse(h);
    
    // 6. Создаем результат с вставками
    pos = 0;
    while (h != NULL) {
        char val = pop(h);
        push(result, val);
        
        if (pos == lastConsonantPos-1) {
            push(result, '?');
            cout << "Вставляем '?' после позиции " << lastConsonantPos << endl;
        }
        pos++;
    }
    
    // 7. Переворачиваем результат
    reverse(result);
    
    // 8. Очищаем старый стек
    while (h != NULL) {
        pop(h);
    }
    
    h = result;
}

// Печать стека
void printStack(mystack* h) {
    if (h == NULL) {
        cout << "Стек пуст" << endl;
        return;
    }
    
    mystack* temp = NULL;
    bool first = true;
    
    while (h != NULL) {
        if (!first) {
            cout << ", ";
        }
        cout << h->inf;
        push(temp, pop(h));
        first = false;
    }
    
    while (temp != NULL) {
        push(h, pop(temp));
    }
    cout << endl;
}

int main() {
    mystack* head = NULL;
    int n;
    char ch;
    
    cout << "Введите количество букв: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Стек пуст" << endl;
        return 0;
    }
    
    cout << "Введите " << n << " букв латинского алфавита через пробел: ";
    
    for (int i = 0; i < n; i++) {
        cin >> ch;
        push(head, ch);
    }
    
    reverse(head);
    insertAfterLastConsonant(head);
    
    cout << "Стек после вставки: ";
    printStack(head);
    
    return 0;
}