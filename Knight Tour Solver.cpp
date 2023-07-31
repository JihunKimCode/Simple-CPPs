#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Knight {
public:
    Knight(int r, int c); // Constructor with input validation
    bool Find(int row, int col, int order);
    void Print();

private:
    int rows, cols;
    vector<vector<int>> move;
    vector<int> tour;
};

Knight::Knight(int r, int c) {
    if (r <= 0 || c <= 0) {
        cout << "Invalid board size. Setting default size: 8x8" << endl;
        rows = 8;
        cols = 8;
    }
    else {
        rows = r;
        cols = c;
    }

    tour.resize(rows * cols, -1); // Initialize the tour vector with -1 for each square
    move = {
        { 2,1 },{ 1,2 },{ -1,2 },{ -2,1 },{ -2,-1 },{ -1,-2 },{ 1,-2 },{ 2,-1 }
    };
}

bool Knight::Find(int row, int col, int order) {
    if (row >= rows || row < 0 || col >= cols || col < 0) return false;
    if (tour[row * cols + col] != -1) return false;

    tour[row * cols + col] = order;
    if (order == rows * cols-1) return true;

    for (int i = 0; i < move.size(); i++) {
        int nextRow = row + move[i][0];
        int nextCol = col + move[i][1];
        if (Find(nextRow, nextCol, order + 1)) return true;
    }

    tour[row * cols + col] = -1;
    return false;
}

void Knight::Print() {
    cout << " ";
    for (int i = 0; i < cols; i++) {
        cout << "   " << char(97 + i);
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << rows - i;
        for (int j = 0; j < cols; j++) {
            if (tour[i * cols + j] < 10 && tour[i * cols + j] >= 0) printf("   %d", tour[i * cols + j]);
            else printf("  %d", tour[i * cols + j]);
        }
        cout << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int r, c, rp, cp;
    cout << "What is the size of the board (r*c)? ";
    cin >> r >> c;

    Knight k(r, c);

    cout << "Where do you want to start (-1 to Random)? ";
    cin >> rp >> cp;

    if (rp == -1) rp = rand() % r;
    if (cp == -1) cp = rand() % c;

    k.Find(rp, cp, 0);
    k.Print();

    return 0;
}
