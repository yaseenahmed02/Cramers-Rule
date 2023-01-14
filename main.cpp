#include <iostream>
#include <vector>
using namespace std;

void display_system(vector<vector<double>> &mat, vector<double> &constants) {
    int n = mat.size();

    cout << "\nThe augmented matrix for the system: \n\n";
    for (int i=0; i<n; i++) {
        int plus_count = 1;
        for (int j=0; j<n; j++) {
            cout << "(" << mat[i][j] << ") x" << j+1;
            if (plus_count <= n-1) {
                cout << " + ";
                plus_count++;
            }
        }
        cout << " = " << constants[i] << endl;

    }

}

vector<double> get_const(int n) {
    vector<double> ret(n);
    cout << endl << "Please go ahead and enter all of your constant matirx elements in order (0,0), (0,1), .. (0, n)\n";
    for (int i=0; i<n; i++)
        cin >> ret[i];

    return ret;
}
vector<vector<double>> get_input(int n) {
    vector<vector<double>> ret(n, vector<double>(n));

    cout << "Please go ahead and enter all of your coefficient matirx elements in order (0,0), (0,1), .. (0, n), (1,0), (1,1), ... (1,n), ... (n,n)\n";
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> ret[i][j];

    return ret;
}

void display_const(vector<double> &constants) {

    for( auto&& entry : constants )
        cout << entry << endl;

}
void display(vector<vector<double>> &mat) {

    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

vector<vector<double>> minor(vector<vector<double>> &mat, int dim, int row_eliminated, int col_eliminated) {

    vector<vector<double>> ret(dim, vector<double>(dim));
    int i = 0, j = 0;
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            if (r != row_eliminated && c != col_eliminated) {
                ret[i][j] = mat[r][c];
                j++;

                if (j == dim-1) { //if we reached the end of the matrix
                    j = 0; //reset the columns
                    i++; //increase the row (go down one row)
                }
            }

        }
    }

    return ret;
}
double det(vector<vector<double>> &mat, int dim) {

    double res = 0;
    //if (dim == 1) return mat[0][0]; //base case 1
    if (dim == 2) return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1])); //base case

    //(dim, vector<double>(dim));
    int multiplier = 1;

    for (int i=0; i<dim; i++) {
        //note: using the first row for expansion
        vector<vector<double>> minor_mat = minor(mat, dim, 0, i); //minor matrix of matrix[0][i]
        res += multiplier * mat[0][i] * det(minor_mat, dim-1);
        multiplier *= -1; //to alternate sign
    }

    return res;

}

bool invertible(vector<vector<double>> &mat) {
    return det(mat, mat.size()) != 0;
}

void check(vector<vector<double>> &mat) {

    int ans, n = mat.size();

    while (!invertible(mat)) {
        cout << "The matrix you entered is not-invertible.. enter 1 to try again or 0 to exit: ";
        cin >> ans;
        if (ans == 1)
            get_input(n);
        else {
            cout << "Thank you for coming!" << endl;
            exit(1);
        }
    }
}

double get_Dn(vector<vector<double>> &mat, int n, int idx, vector<double> constants) {

    vector<vector<double>> temp(n, vector<double>(n));

    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) {
            if (j != idx)
                temp[i][j] = mat[i][j];
            else
                temp[i][j] = constants[i];
        }
    //cout << "The determinant of D " << idx << "is: " << det(temp, n);
    return det(temp, n);

}
vector<int> solve(vector<vector<double>> &mat, vector<double> constants) {
    int n = mat.size();
    vector<int> ret(n);
    double determinant = det(mat, n);
    //cout << "The determinant of the coefficient matrix is: " << determinant << endl;

    for (int i=0; i<constants.size(); i++) {
        double Di = get_Dn(mat, n, i, constants);
        ret[i] = Di / determinant;
    }

    return ret;
}

int main() {

    int n;
    cout << "Enter the dimension of the matrix: ";
    cin >> n;
    vector<vector<double>> mat = get_input(n); //getting the input
    check(mat); //checking that the matrix is invertible
    cout << "\nThe coefficient matrix you entered is: " << endl;
    display(mat); //displaying the matrix
    vector<double> constants = get_const(n); //input for coefficient matrix
    cout << "\nThe constants matrix you entered is: " << endl;
    display_const(constants);
    display_system(mat, constants);
    vector<int> solution = solve(mat, constants);
    cout << endl;
    cout << "The solutions for the matrix: " << endl;
    for (int i=0; i<solution.size(); i++)
        cout << "X" << i+1 << " = " << solution[i] << endl;


    return 0;
}
