#include <iostream>
#include <vector>
using namespace std;

/**
 * Displays the augmented matrix for the linear system.
 *
 * @param mat The coefficient matrix of the linear system.
 * @param constants The constants vector of the linear system.
 */
void display_system(vector<vector<double>> &mat, vector<double> &constants) {
    int n = mat.size();

    cout << "\nThe augmented matrix for the system: \n\n";
    for (int i = 0; i < n; i++) {
        int plus_count = 1;
        for (int j = 0; j < n; j++) {
            cout << "(" << mat[i][j] << ") x" << j + 1;
            if (plus_count <= n - 1) {
                cout << " + ";
                plus_count++;
            }
        }
        cout << " = " << constants[i] << endl;
    }
}

/**
 * Gets the constants vector from the user.
 *
 * @param n The dimension of the constants vector.
 * @return The constants vector.
 */
vector<double> get_const(int n) {
    vector<double> ret(n);
    cout << endl << "Please enter all of your constant matrix elements in order (0,0), (0,1), .. (0, n)\n";
    for (int i = 0; i < n; i++)
        cin >> ret[i];

    return ret;
}

/**
 * Gets the coefficient matrix from the user.
 *
 * @param n The dimension of the coefficient matrix.
 * @return The coefficient matrix.
 */
vector<vector<double>> get_input(int n) {
    vector<vector<double>> ret(n, vector<double>(n));

    cout << "Please enter all of your coefficient matrix elements in order (0,0), (0,1), .. (0, n), (1,0), (1,1), ... (1,n), ... (n,n)\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> ret[i][j];

    return ret;
}

/**
 * Displays the constants vector.
 *
 * @param constants The constants vector to be displayed.
 */
void display_const(vector<double> &constants) {
    for (auto &&entry : constants)
        cout << entry << endl;
}

/**
 * Displays the matrix.
 *
 * @param mat The matrix to be displayed.
 */
void display(vector<vector<double>> &mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

/**
 * Computes the minor matrix obtained by eliminating a specific row and column from the input matrix.
 *
 * @param mat The input matrix.
 * @param dim The dimension of the input matrix.
 * @param row_eliminated The row to be eliminated.
 * @param col_eliminated The column to be eliminated.
 * @return The minor matrix.
 */
vector<vector<double>> minor(vector<vector<double>> &mat, int dim, int row_eliminated, int col_eliminated) {
    vector<vector<double>> ret(dim, vector<double>(dim));
    int i = 0, j = 0;
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            if (r != row_eliminated && c != col_eliminated) {
                ret[i][j] = mat[r][c];
                j++;
                if (j == dim - 1) { // If we reached the end of the matrix
                    j = 0; // Reset the columns
                    i++; // Increase the row (go down one row)
                }
            }
        }
    }
    return ret;
}

/**
 * Computes the determinant of the input matrix using recursion.
 *
 * @param mat The input matrix.
 * @param dim The dimension of the input matrix.
 * @return The determinant of the matrix.
 */
double det(vector<vector<double>> &mat, int dim) {
    double res = 0;
    if (dim == 2) return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1])); // Base case for 2x2 matrix

    int multiplier = 1;

    for (int i = 0; i < dim; i++) {
        // Note: Using the first row for expansion
        vector<vector<double>> minor_mat = minor(mat, dim, 0, i); // Minor matrix of matrix[0][i]
        res += multiplier * mat[0][i] * det(minor_mat, dim - 1);
        multiplier *= -1; // To alternate sign
    }

    return res;
}

/**
 * Checks if the given matrix is invertible (i.e., has a non-zero determinant).
 *
 * @param mat The input matrix.
 * @return True if the matrix is invertible, false otherwise.
 */
bool invertible(vector<vector<double>> &mat) {
    return det(mat, mat.size()) != 0;
}

/**
 * Checks if the matrix is invertible. If not, allows the user to enter the matrix again or exit the program.
 *
 * @param mat The input matrix.
 */
void check(vector<vector<double>> &mat) {
    int ans, n = mat.size();
    while (!invertible(mat)) {
        cout << "The matrix you entered is not invertible. Enter 1 to try again or 0 to exit: ";
        cin >> ans;
        if (ans == 1)
            mat = get_input(n);
        else {
            cout << "Thank you for coming!" << endl;
            exit(1);
        }
    }
}

/**
 * Computes the determinant of a matrix with a specific column replaced by the constants vector.
 *
 * @param mat The input matrix.
 * @param n The dimension of the matrix.
 * @param idx The index of the column to be replaced.
 * @param constants The constants vector.
 * @return The determinant of the resulting matrix.
 */
double get_Dn(vector<vector<double>> &mat, int n, int idx, vector<double> constants) {
    vector<vector<double>> temp(n, vector<double>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (j != idx)
                temp[i][j] = mat[i][j];
            else
                temp[i][j] = constants[i];
        }
    return det(temp, n);
}

/**
 * Solves the linear system and returns the solution vector.
 *
 * @param mat The coefficient matrix of the linear system.
 * @param constants The constants vector of the linear system.
 * @return The solution vector.
 */
vector<int> solve(vector<vector<double>> &mat, vector<double> constants) {
    int n = mat.size();
    vector<int> ret(n);
    double determinant = det(mat, n);

    for (int i = 0; i < constants.size(); i++) {
        double Di = get_Dn(mat, n, i, constants);
        ret[i] = Di / determinant;
    }

    return ret;
}

int main() {
    int n;
    cout << "Enter the dimension of the matrix: ";
    cin >> n;

    vector<vector<double>> mat = get_input(n); // Getting the input
    check(mat); // Checking that the matrix is invertible

    cout << "\nThe coefficient matrix you entered is: " << endl;
    display(mat); // Displaying the matrix

    vector<double> constants = get_const(n); // Input for the constants vector
    cout << "\nThe constants matrix you entered is: " << endl;
    display_const(constants);

    display_system(mat, constants); // Displaying the augmented matrix for the linear system

    vector<int> solution = solve(mat, constants); // Solving the linear system

    cout << endl;
    cout << "The solutions for the matrix: " << endl;
    for (int i = 0; i < solution.size(); i++)
        cout << "X" << i + 1 << " = " << solution[i] << endl;

    return 0;
}
