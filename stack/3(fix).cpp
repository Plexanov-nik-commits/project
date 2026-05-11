#include <iostream>
#include <stack>
#include <climits>
using namespace std;

void printStack(stack<int> s) {
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

void insertMinAfterFirstAndLastMax(stack<int>& s) {
    if (s.empty()) return;

    // 1. Найдем максимум и минимум
    stack<int> temp = s;
    int maxVal = INT_MIN, minVal = INT_MAX;
    while (!temp.empty()) {
        int val = temp.top();
        if (val > maxVal) maxVal = val;
        if (val < minVal) minVal = val;
        temp.pop();
    }

    // 2. Переложим стек в другой для обработки порядка
    stack<int> reversed;
    while (!s.empty()) {
        reversed.push(s.top());
        s.pop();
    }

    // 3. Найдем позиции первого и последнего максимума
    stack<int> copyForPos = reversed;
    int firstMaxPos = -1, lastMaxPos = -1;
    int pos = 0;
    while (!copyForPos.empty()) {
        if (copyForPos.top() == maxVal) {
            if (firstMaxPos == -1) firstMaxPos = pos;
            lastMaxPos = pos;
        }
        copyForPos.pop();
        pos++;
    }

    // 4. Собираем новый стек с вставками
    stack<int> result;
    pos = 0;
    while (!reversed.empty()) {
        int val = reversed.top();
        result.push(val);
        reversed.pop();

        if (pos == firstMaxPos) {
            result.push(minVal);
        }
        if (pos == lastMaxPos && firstMaxPos != lastMaxPos) {
            result.push(minVal);
        }
        pos++;
    }

    // 5. Переворачиваем результат обратно
    while (!result.empty()) {
        s.push(result.top());
        result.pop();
    }
}

int main() {
    stack<int> s;
    int n, value;

    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        s.push(value);
    }

    insertMinAfterFirstAndLastMax(s);

    cout << "Стек после вставки: ";
    printStack(s);

    return 0;
}