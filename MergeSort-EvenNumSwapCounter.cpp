#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Answer {
public:
    static const int MAX = 150;
    int array[MAX];
    int numbersRead = 0;
    int totalEvenSwapped = 0;

    void ReadInputFile() {
        ifstream inputFile("input.txt");
        if (inputFile.is_open()) {
            int current_number;
            while (inputFile >> current_number && numbersRead < MAX) {
                array[numbersRead] = current_number;
                numbersRead++;
            }
            inputFile.close();
            cout << "Read " << numbersRead << " numbers from the file input.txt" << endl;
        } else {
            cout << "Error in opening the file input.txt!" << endl;
        }
    }

    int merge(int array[], int leftArray[], int leftSize, int rightArray[], int rightSize) {
        int i = 0, j = 0, k = 0;
        int occurrences = 0;
        while (i < leftSize && j < rightSize) {
            if (leftArray[i] <= rightArray[j]) {
                array[k] = leftArray[i];
                i++;
            } else {
                if (rightArray[j] % 2 == 0) {
                    occurrences += leftSize - i; 
                }
                array[k] = rightArray[j];
                j++;
            }
            k++;
        }
        while (i < leftSize) {
            array[k] = leftArray[i];
            i++;
            k++;
        }
        while (j < rightSize) {
            array[k] = rightArray[j];
            j++;
            k++;
        }
        return occurrences;
    }

    void mergeSort(int array[], int start, int end) {
        if (start < end) {
            int middle = start + (end - start) / 2;
            mergeSort(array, start, middle);
            mergeSort(array, middle + 1, end);
            int leftSize = middle - start + 1;
            int rightSize = end - middle;
            vector<int> leftArray(leftSize), rightArray(rightSize);
            for (int i = 0; i < leftSize; i++) {
                leftArray[i] = array[start + i];
            }
            for (int j = 0; j < rightSize; j++) {
                rightArray[j] = array[middle + 1 + j];
            }
            int occurrences = merge(array + start, &leftArray[0], leftSize, &rightArray[0], rightSize);
            totalEvenSwapped += occurrences;
        }
    }
};

int main() {
    Answer answer;
    answer.ReadInputFile();
    answer.mergeSort(answer.array, 0, answer.numbersRead - 1);

    cout << "Sorted array: { ";
    for (int i = 0; i < answer.numbersRead; i++) {
        cout << answer.array[i];
        if (i != answer.numbersRead - 1) {
            cout << ", ";
        }
    }
    cout << " }" << endl << endl;

    cout << "Total number of occurrences where two even numbers are swapped: " << answer.totalEvenSwapped << endl;

    return 0;
}
