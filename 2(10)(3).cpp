#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip> 

using namespace std;

void gnomeSort(vector<double>& arr, bool descending) {
    int n = arr.size();
    int index = 0;
    while (index < n) {
        if (index == 0) {
            index++;
        }
        bool ordered;
        if (descending) {
            ordered = (arr[index] <= arr[index - 1]); // Для убывания
        } else {
            ordered = (arr[index] >= arr[index - 1]); // Для возрастания
        }
        if (ordered) {
            index++;
        } else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}
vector<vector<double>> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<double>> matrix;
    string line;
    if (!file.is_open()) return matrix;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<double> row;
        stringstream ss(line);
        double value;
        while (ss >> value) row.push_back(value);
        if (!row.empty()) matrix.push_back(row);
    }
    file.close();
    return matrix;
}
void writeMatrixToFile(const string& filename, const vector<vector<double>>& matrix) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось создать файл для записи!" << endl;
        return;
    }
    for (const auto& row : matrix) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i] << (i == row.size() - 1 ? "" : " ");
        }
        file << endl;
    }
    file.close();
    cout << "Результат успешно сохранен в файл: " << filename << endl;
}
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) cout << val << "\t";
        cout << endl;
    }
}
int main() {
    string inputFile = "/Users/nikita/Documents/proga/bd.txt";   
    string outputFile = "result.txt"; 
    vector<vector<double>> matrix = readMatrixFromFile(inputFile);
    cout << "Исходная матрица:" << endl;
    printMatrix(matrix);
    for (int i = 0; i < matrix.size(); i++) {
        int rowNum = i + 1; 
        if (rowNum % 2 != 0) {
            gnomeSort(matrix[i], true);
        } else {
            gnomeSort(matrix[i], false); 
        }
    }
    cout << "\nМатрица после сортировки:" << endl;
    printMatrix(matrix);
    writeMatrixToFile(outputFile, matrix);
    return 0;
}
