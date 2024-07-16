#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++)
        cout << arr[i] << (i < size - 1 ? ", " : "");
    cout << "]";
}

//mergeSort algorithm
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    cout << "Gộp các mảng: ";
    printArray(L, n1);
    cout << " ";
    printArray(R, n2);
    cout << endl;
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        cout << "So sánh " << L[i] << " <= " << R[j] << endl;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            cout << "Đúng -> Đặt " << L[i] << " vào vị trí " << k << endl << endl;
            i++;
        } else {
            arr[k] = R[j];
            cout << "Sai -> Đặt " << R[j] << " vào vị trí " << k << endl << endl;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        cout << "Sao chép " << L[i] << " vào vị trí " << k << endl;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        cout << "Sao chép " << R[j] << " vào vị trí " << k << endl;
        j++;
        k++;
    }

    cout << "Sau khi gộp: ";
    printArray(arr + left, right - left + 1);
    cout << endl << "-------------------------------" << endl;
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
// end merge sort algorithm

//quickSort
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    cout << "Pivot (phần tử cuối mảng): " << pivot << endl;

    for (int j = low; j <= high - 1; j++) {
        bool isSwapping = arr[j] < pivot;
        cout << "So sánh " << arr[j] << " < " << pivot << ": " << (isSwapping ? "đúng" : "sai") << endl;
        if (isSwapping) {
            i++;
            swap(&arr[i], &arr[j]);
            cout << "Hoán đổi " << arr[i] << " và " << arr[j] << endl << "Ta được: ";
            printArray(arr, high + 1);
            cout << endl;
        }
    }
    cout << endl << "Left pointer trùng với right pointer -> ";
    swap(&arr[i + 1], &arr[high]);
    cout << "Hoán đổi " << arr[i + 1] << " và " << arr[high] << endl << "Ta được: ";
    printArray(arr, high + 1);
    cout << endl << endl;
    
    return (i + 1);
}

void quickSort(int arr[], int first, int last) {
    int index = partition(arr, first, last);

    if (first < index - 1)
	    quickSort(arr, first, index - 1);
    if (index < last)
	    quickSort(arr, index, last);
}
//end quickSort

//binarySearch
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        cout << "Chỉ số giữa: " << m << ", Phần tử giữa: " << arr[m] << endl;

        if (arr[m] == x) {
            cout << "Phần tử tìm thấy ở chỉ số " << m << endl;
            return m;
        }

        if (arr[m] < x) {
            cout << "Phần tử " << x << " lớn hơn " << arr[m] << endl;
            l = m + 1;
        } else {
            cout << "Phần tử " << x << " nhỏ hơn " << arr[m] << endl;
            r = m - 1;
        }
    }

    cout << "Phần tử không có trong mảng" << endl;
    return -1;
}

//
string multiply(string num1, string num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0)
        return "0";

    vector<int> result(n1 + n2, 0);

    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        int digit1 = num1[i] - '0';
        cout << endl;

        for (int j = n2 - 1; j >= 0; j--) {
            int digit2 = num2[j] - '0';
            cout << digit1 << " x " << digit2;

            int sum = digit1 * digit2 + result[i + j + 1] + carry;
            carry = sum / 10;
            result[i + j + 1] = sum % 10;

            cout << " = " << result[i + j + 1] << " (tổng = " << sum << ", dư = " << carry << ")" << endl;
        }

        result[i + n2] += carry;

        cout << "Kết quả sau khi cộng phần dư: ";
        bool leadingZero = true;
        for (int k = 0; k < result.size(); k++) {
            if (result[k] != 0) leadingZero = false;
            if (!leadingZero) cout << result[k];
        }
        cout << endl;
    }

    int i = 0;
    while (i < result.size() && result[i] == 0)
        i++;

    string s = "";
    while (i < result.size())
        s += std::to_string(result[i++]);

    return s.empty() ? "0" : s;
}

int main() {
    // 1.
    int qArr[] = {10, 7, 8, 9, 1, 5, 23, 45, 16, 37, 3, 99, 22};
    int qArrSize = sizeof(qArr) / sizeof(qArr[0]);

    cout << "Mảng ban đầu: ";
    printArray(qArr, qArrSize);
    cout << endl;
    cout << "-------------------------------" << endl << endl;

    quickSort(qArr, 0, qArrSize - 1);

    cout << "-------------------------------" << endl << endl;
    cout << "Mảng đã sắp xếp: ";
    printArray(qArr, qArrSize);
    cout << endl;
    
    // 2.
    int mArr[] = {10, 7, 8, 9, 1, 5, 23, 45, 16, 37, 3, 99, 22};
    int mArrSize = sizeof(mArr) / sizeof(mArr[0]);

    cout << "Mảng ban đầu: ";
    printArray(mArr, mArrSize);
    cout << endl << "-------------------------------" << endl;
    
    mergeSort(mArr, 0, mArrSize - 1);

    cout << "Mảng đã sắp xếp: ";
    printArray(mArr, mArrSize);
    cout << endl;
    
    
    // 3
    int bArr[] = {2, 3, 4, 10, 40};
    int nBiArr = sizeof(bArr) / sizeof(bArr[0]);
    int x = 5;
    cout << "Mảng: ";
    printArray(bArr, nBiArr);
    cout << endl;
    
    binarySearch(bArr, 0, nBiArr - 1, x);
    
    //
    string str1 = "123";
    string str2 = "456";

    if ((str1.at(0) == '-' || str2.at(0) == '-') && (str1.at(0) != '-' || str2.at(0) != '-'))
        cout << "-";

    if (str1.at(0) == '-')
        str1 = str1.substr(1);

    if (str2.at(0) == '-')
        str2 = str2.substr(1);

    cout << "Nhân " << str1 << " và " << str2 << endl;
    cout << "Kết quả: " << multiply(str1, str2) << endl;

    return 0;
}
