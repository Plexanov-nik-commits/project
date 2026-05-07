#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
using namespace std;
void bucketSortDescending(vector<double>& arr) {
    // находим min и max
    double minVal = arr[0];
    double maxVal = arr[0];
    for (double val : arr) {
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
    }
    if (minVal == maxVal) return;
    int n = arr.size();
    vector<vector<double>> buckets(n);
    // раскидываем по блокам
    for (double val : arr) {
        double normalized = (val - minVal) / (maxVal - minVal);
        int bucketIndex = static_cast<int>(normalized * (n - 1));
        buckets[bucketIndex].push_back(val);
    }
    // сортировка внутри блоков
    int index = 0;
    // идем с ПОСЛЕДНЕГО блока к ПЕРВОМУ для обеспечения убывания между блоками
    for (int i = n - 1; i >= 0; --i) {
        if (!buckets[i].empty()) {
            // сортируем внутри блока по убыванию
            sort(buckets[i].begin(), buckets[i].end(), greater<double>());
            for (double val : buckets[i]) {
                arr[index++] = val;
            }
        }
    }
}
vector<vector<double>> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<double>> matrix;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<double> row;
        stringstream ss(line);
        double value;
        while (ss >> value) {
            row.push_back(value);
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }
    file.close();
    return matrix;
}
void writeMatrixToFile(const string& filename, const vector<vector<double>>& matrix) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка создания файла: " << filename << endl;
        return;
    }
    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); j++) {
            file << row[j];
            if (j < row.size() - 1) {
                file << " ";
            }
        }
        file << endl;
    }
    file.close();
    cout << "Результат записан в файл: " << filename << endl;
}
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}
int main() {
    string inputFile = "/Users/nikita/Documents/proga/bd.txt";
    string outputFile = "output.txt";
    vector<vector<double>> matrix = readMatrixFromFile(inputFile);
    // проверка на квадратность
    size_t n = matrix.size();
    for (const auto& row : matrix) {
        if (row.size() != n) {
            cerr << "матрица не квадратная "<< endl;
            return 1;
        }
    }
    cout << "исходная матрица (" << n << "x" << n << "):" << endl;
    printMatrix(matrix);
    cout << endl;
    // сортируем каждую строку по убыванию
    for (auto& row : matrix) {
        bucketSortDescending(row);
    }
    cout << "отсортированная матрица :" << endl;
    printMatrix(matrix);
    writeMatrixToFile(outputFile, matrix);
    return 0;
}