#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> 

using namespace std;

struct Employee {
    string surname;
    string position;
    string fullDate; 
    int dateKey; 
    int experience;
    int salary;
};

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


void countingSortByFullDate(vector<Employee>& arr) {
    int minKey = arr[0].dateKey;
    int maxKey = arr[0].dateKey;
    for (const auto& e : arr) {
        minKey = min(minKey, e.dateKey);
        maxKey = max(maxKey, e.dateKey);
    }
    int range = maxKey - minKey + 1;
    vector<int> count(range, 0);
    for (const auto& e : arr) {
        count[e.dateKey - minKey]++;
    }
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    vector<Employee> output(arr.size());
    // проходим с конца для сохранения порядка
    for (int i = arr.size() - 1; i >= 0; i--) {
        int index = arr[i].dateKey - minKey;
        count[index]--;
        output[count[index]] = arr[i];
    }
    // Копируем обратно в исходный массив
    arr = move(output);
}
int main() {
    ifstream inFile("/Users/nikita/Documents/BD.txt");
    ofstream outFile("output.txt");
    vector<Employee> employees;
    Employee temp;
    while (inFile >> temp.surname >> temp.position >> temp.fullDate >> temp.experience >> temp.salary) {
        try {
            // Конвертируем DD.MM.YYYY в число YYYYMMDD
            int d = stoi(temp.fullDate.substr(0, 2));
            int m = stoi(temp.fullDate.substr(3, 2));
            int y = stoi(temp.fullDate.substr(6, 4));
            temp.dateKey = y * 10000 + m * 100 + d;
            
            employees.push_back(temp);
        } catch (...) { continue; }
    }

    countingSortByFullDate(employees);
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
    cout << "Сортировка по дням, месяцам и годам завершена!" << endl;
    return 0;
}
