#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

int row;
int col;

class Hourse {

public:
    int rows;
    int cols;
    int move;
    vector<vector<int> > tour;
    vector<vector<bool> > is_here;

    Hourse(int _rows, int _cols) {
        this->rows = _rows;
        this->cols = _cols;
        this->move = 1;
        this->tour.assign(_rows, vector<int>(_cols, 0));
        this->is_here.assign(_rows, vector<bool>(_cols, false));
    }

    void Hourse_recursive(int indx, int indy) {
        if (indx < 0 || indx >= this->rows ||
            indy < 0 || indy >= this->cols)
            return;

        if (this->is_here[indx][indy])
            return;

        this->is_here[indx][indy] = true;
        this->tour[indx][indy] = this->move++;

        Hourse_recursive(indx + 1, indy + 2);
        Hourse_recursive(indx + 1, indy - 2);
        Hourse_recursive(indx - 1, indy + 2);
        Hourse_recursive(indx - 1, indy - 2);

        Hourse_recursive(indx + 2, indy + 1);
        Hourse_recursive(indx + 2, indy - 1);
        Hourse_recursive(indx - 2, indy + 1);
        Hourse_recursive(indx - 2, indy - 1);
    }

    void print_result() {
        for (int i = 0; i < this->tour.size(); ++i) {
            for (int j = 0; j < this->tour.size(); ++j) {
                printf("\t%i", this->tour[i][j]);
            }
            printf("\n");
        }
    }

};

long long  horse_6(int n, int x, int y) {
    auto millisec_start_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    //________________________________inicia_______________________________
    int row = n;
    col = row;
    double t_Inicio, t_Fin;
    Hourse Hourse(row, col);
    Hourse.Hourse_recursive(x, y);
    Hourse.print_result();
    //finaliza
    auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return millisec_end_epoch - millisec_start_epoch;
}