#include <iostream>
#include <iomanip>
#include <cmath>

// print the matrix, use a window size of 3 and right align
void printMatrix(double** A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            std::cout << std::setw(10) << A[i][j]; //window 사이즈는 자유롭게 변경 가능하다는 교수님의 말씀에 따라 10으로 설정하였습니다.
        }
        std::cout << std::endl;
    }
}

// Swap two rows of a matrix
void swapRows(double** A, int row, int zerocount) {
    double* temp = A[zerocount]; //zerocount의 값은 행의 인덱스 숫자가 되도록 설정함.
    A[zerocount] = A[row];
    A[row] = temp;
}

void performGaussianElimination(double** A, int n) {
    for (int row = 0; row < n; row++) {
        int zerocount = 0; //각 행마다 앞에서부터 연속적으로 존재하는 0의 개수에 따른 row change를 위한 변수를 설정
        int col = 0;
        while (A[row][col] == 0) {
            zerocount++; //앞의 열에서부터 0이 연속적으로 발생할 때마다 zerocount의 값에 1을 더함
            col++;
            if (col == n) {
                break; //만약, 한 행에 대해 인덱스 n의 열까지 갔다면, while 문을 빠져나가도록 설정
            }
        }
        if (zerocount != 0 && zerocount != row) {
            swapRows(A, row, zerocount); //행의 (앞의 열에서부터) 연속적으로 발생하는 0의 개수를 담은 zerocount라는 변수가 0이 아니고, row값과도 다르다면, 행의 위치를 바꾸도록 함.
        }
    }

    for (int col = 0; col < n; col++) {
        for (int i = col + 1; i < n; i++) {
            if (A[i][col] != 0) {
                double temp = A[i][col] / A[col][col]; //temp라는 변수를 새로 설정함
                for (int j = col; j < n + 1; j++) {
                    A[i][j] -= temp * A[col][j]; //앞서 정의한 temp 변수를 사용해 변환하였음
                }
            }
        }
    }

    std::cout << "Gaussian Elimination result: the reduced row echelon form (RREF) matrix is:" << std::endl;
    printMatrix(A, n);
}

void backSubstitution(double** A, int n, double* solution) {
    for (int row = n - 1; row >= 0; row--) { //가장 아래의 행부터 진행함
        solution[row] = A[row][n] / A[row][row];
        for (int i = row - 1; i >= 0; i--) {
            A[i][n] -= A[i][row] * solution[row]; //그 다음에 진행할 행의 가장 오른쪽 값을 변환함.
        }
    }
}

void solveSystem(double** matrix, int n) {
    performGaussianElimination(matrix, n);
    double* solution = new double[n];
    backSubstitution(matrix, n, solution);

    std::cout << "The solution to the system of linear equations is:" << std::endl;
    std::cout << std::setprecision(6);
    for (int i = 0; i < n; i++) {
        std::cout << "x[" << i << "] = " << solution[i] << std::endl;
    }
    std::cout << std::endl;
    delete[] solution;
}

int main() {
    // create the augmented matrix
    int n = 3; // size of the matrix
    double** A = new double* [n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n + 1];
    }

    // initialize the matrix with values (does not require row exchange)
    A[0][0] = 2; A[0][1] = 3; A[0][2] = -1; A[0][3] = 1;
    A[1][0] = 4; A[1][1] = 4; A[1][2] = 3; A[1][3] = 3;
    A[2][0] = 2; A[2][1] = -3; A[2][2] = 1; A[2][3] = -1;

    // print original matrix
    std::cout << "The original matrix (the last column is augmented) is:" << std::endl;
    printMatrix(A, n);

    // solve the system of linear equations
    solveSystem(A, n);

    // initialize the matrix with values (requires row exchange)
    A[0][0] = 0; A[0][1] = 3; A[0][2] = -1; A[0][3] = 1;
    A[1][0] = 4; A[1][1] = 4; A[1][2] = 3; A[1][3] = 3;
    A[2][0] = 2; A[2][1] = -3; A[2][2] = 1; A[2][3] = -1;

    // print original matrix
    std::cout << "The original matrix (the last column is augmented) is:" << std::endl;
    printMatrix(A, n);

    // solve the system of linear equations
    solveSystem(A, n);

    // free the memory used by the matrix
    for (int i = 0; i < n; i++) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}
