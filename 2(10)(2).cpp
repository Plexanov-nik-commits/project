#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Employee {
    string surname;
    string position;
    string fullDate; 
    int experience;
    int salary;
};

// Функция для корректного замера длины UTF-8 строк (для выравнивания)
int utf8_length(const string& str) {
    int length = 0;  
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] & 0xc0) != 0x80) length++; 
    }
    return length; 
}

void printLeft(ostream& out, const string& str, int width) {
    int actualLen = utf8_length(str);
    int padding = width - actualLen;
    if (padding < 0) padding = 0;
    out << str << string(padding, ' ');
}

void gnomeSort(vector<Employee>& a) {
    int n = a.size();
    int i = 0;
    while (i < n) {
        // Условие swap (когда нужно поменять местами):
        // 1. Если текущая должность "меньше" (раньше по алфавиту) предыдущей.
        // 2. ИЛИ если должности одинаковые, но текущая зарплата БОЛЬШЕ предыдущей (для убывания).
        if (i == 0 || !(a[i].position < a[i - 1].position || 
                      (a[i].position == a[i - 1].position && a[i].salary < a[i - 1].salary))) {
            i++;
        } else {
            swap(a[i], a[i - 1]);
            i--;
        }
    }
}


int main() {
    ifstream inFile("/Users/nikita/Documents/BD.txt");
    ofstream outFile("output2.txt");

    if (!inFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл!" << endl;
        return 1;
    }

    vector<Employee> employees;
    Employee temp;
    
    while (inFile >> temp.surname >> temp.position >> temp.fullDate >> temp.experience >> temp.salary) {
        employees.push_back(temp);
    }

    // Применяем сортировку
    gnomeSort(employees);

    // Вывод в файл
    int w = 20;
    printLeft(outFile, "Фамилия", w);
    printLeft(outFile, "Должность", w);
    printLeft(outFile, "Дата рожд.", w);
    printLeft(outFile, "Стаж", w);
    outFile << "Зарплата" << endl;
    outFile << string(w * 4 + 10, '-') << endl;
    
    for (const auto& e : employees) {
        printLeft(outFile, e.surname, w);
        printLeft(outFile, e.position, w);
        printLeft(outFile, e.fullDate, w);
        printLeft(outFile, to_string(e.experience), w); 
        outFile << e.salary << endl;
    }

    inFile.close();
    outFile.close();
    cout << "Готово! Данные отсортированы по должности и зарплате." << endl;
    
    return 0;
}
