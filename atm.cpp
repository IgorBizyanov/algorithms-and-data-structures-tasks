#include <iostream>
#include <random>
#include <stdexcept>
#include <fstream>
#include <unistd.h>
using namespace std;

int uniform_random(int min,int max) {
    static std::mt19937 prng(std::random_device{}());
    return std::uniform_int_distribution<>(min,max)(prng);
}

class automat {
public:
    automat() {
        mtrx = {};
        num_rows = num_cols = 0;
    }
    automat(int n, int m) {
        if (n < 1 || m < 1) {
            throw out_of_range("ERROR: out_of_range");
        }   
        num_rows = n;
        num_cols = m;
        for (int i = 0; i < num_rows; ++i) {
            mtrx.push_back({});
            for (int j = 0; j < num_cols; ++j) {
                mtrx[i].push_back(0);
            }
        }
    }

    int numRows() const{
        return num_rows;
    }
    int numCols() const{
        return num_cols;
    }

    int At(int row, int col) const {
        if (row < 0 || col < 0 || row >= num_rows || col >= num_cols) {
            throw out_of_range("ERROR: out_of_range"); 
        }
        return mtrx[row][col]; 
    }

    int& At(int row, int col) {
        if (row < 0 || col < 0 || row >= num_rows || col >= num_cols) {
            throw out_of_range("ERROR: out_of_range");
        }
        int& l = mtrx[row][col];
        return l;
    }

    void change() {
        vector<vector<int>> newState(num_rows, vector<int>(num_cols,0));
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                int count = countAliveNeighbours(i,j);
                if (mtrx[i][j] == 1 && (count == 2 || count == 3)) {
                    newState[i][j] = 1;
                }
                else if (mtrx[i][j] == 0 && count == 3) {
                    newState[i][j] = 1;
                }
            }
        }
        mtrx = newState;
    }

private:
    vector<vector<int>> mtrx;
    int num_rows, num_cols;
    int countAliveNeighbours(int row, int col) {
        int count = 0;
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j) {
                if (isValidRow(i) && isValidCol(j)) {
                    if (i != row || j != col)
                        count += mtrx[i][j];
                }
            }
        }
        return count;
    }
    bool isValidRow(int row) {
        return row >= 0 && row < num_rows;
    }
    bool isValidCol(int col) {
        return col >= 0 && col < num_cols;
    }
};


automat generate(int n, int m) {
    automat atm(n,m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            atm.At(i,j) = uniform_random(0,1);
        }
    }
    return atm;
}

istream& operator>>(istream& is, automat& atm) {
    int n, m;
    is >> n >> m;
    automat a(n,m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            is >> a.At(i,j);
        }
    }
    atm = a;
    return is;
}

ostream& operator<<(ostream& os, const automat& atm) {
    bool first = true;
    for (int i = 0; i < atm.numRows(); ++i) {
        if (!first) os << endl;
        first = false;
        for (int j = 0; j < atm.numCols(); ++j)
            os << atm.At(i, j) << " ";
    }
    return os;
}


int main(int argc, char** argv) {
    try {
        automat atm;
        if (argc > 1) {
            ifstream is(argv[1]); //assume, that your data format is valid...
            if (!is.is_open()) {
                cerr << "File not found.\nTry another one\n";
                exit(1);
            }
            is >> atm;
        }
        else {
            cout << "Enter n and m (with space): ";
            int n,m;
            cin >> n >> m;
            atm = generate(n,m);
        }
        cout << atm << endl;
        while (true) {
            cout << "------------------" << endl;
            atm.change();
            usleep(1'000'000);
            cout << atm << endl;
        }
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }
}