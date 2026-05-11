#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

bool isConsonant(char ch) {
    ch = tolower(ch);
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') return false;
    return (ch >= 'a' && ch <= 'z');
}

int main() {
    int n;
    char ch;
    
    cout << "Введите количество букв: ";
    cin >> n;
    
    cout << "Введите " << n << " букв латинского алфавита через пробел: ";
    
    // Создаем стек и заполняем его
    stack<char> originalStack;
    for (int i = 0; i < n; i++) {
        cin >> ch;
        originalStack.push(ch);
    }
    
    // Переворачиваем стек в другой стек для правильного порядка обработки
    stack<char> tempStack;
    while (!originalStack.empty()) {
        tempStack.push(originalStack.top());
        originalStack.pop();
    }
    
    // Находим позицию последней согласной (считая с начала)
    stack<char> copyStack = tempStack;
    int pos = -1;
    int currentPos = 0;
    
    while (!copyStack.empty()) {
        if (isConsonant(copyStack.top())) {
            pos = currentPos;
        }
        copyStack.pop();
        currentPos++;
    }
    
    // Создаем новый стек с вставкой '?' после последней согласной
    stack<char> resultStack;
    currentPos = 0;
    
    while (!tempStack.empty()) {
        char val = tempStack.top();
        resultStack.push(val);
        tempStack.pop();
        
        // Если это позиция последней согласной, вставляем '?'
        if (currentPos == pos) {
            resultStack.push('?');
        }
        currentPos++;
    }
    
    // Переворачиваем результат для правильного вывода
    stack<char> finalStack;
    while (!resultStack.empty()) {
        finalStack.push(resultStack.top());
        resultStack.pop();
    }
    
    // Выводим элементы через запятую
    bool first = true;
    while (!finalStack.empty()) {
        if (!first) {
            cout << ", ";
        }
        cout << finalStack.top();
        finalStack.pop();
        first = false;
    }
    cout << endl;
    
    return 0;
}