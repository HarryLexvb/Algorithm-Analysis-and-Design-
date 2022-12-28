#include <iostream>
#include <vector>
#include <chrono>
#include <sys/time.h>
#include <ctime>


using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


using namespace std;

bool isSafe(int x, int y,int n){
    return (x < n && x >= 0 && y < n && y >= 0);
}

void horse(vector<vector<int> >& tour,vector<vector<bool> >& ref_visit, unsigned int& move, unsigned int X, unsigned int Y )
{
    if(!isSafe(X,Y,tour.size())) return;

    if(ref_visit[X][Y])
        return;

    ref_visit[X][Y] = true;
    tour[X][Y] = move++;



    // backtracking 8 movimientos
    horse(tour, ref_visit, move, X - 2, Y - 1);
    horse(tour, ref_visit, move, X - 2, Y + 1);
    horse(tour, ref_visit, move, X - 1, Y + 2);
    horse(tour, ref_visit, move, X + 1, Y + 2);
    horse(tour, ref_visit, move, X + 2, Y + 1);
    horse(tour, ref_visit, move, X + 2, Y - 1);
    horse(tour, ref_visit, move, X + 1 , Y - 2);
    horse(tour, ref_visit, move, X - 1 , Y - 2);

}

void print_tour(vector< vector<int> > tour_checked){
    for (int i = 0; i < tour_checked.size(); ++i) {
        for (int j = 0; j < tour_checked[0].size(); ++j) {
            printf("%i\t",tour_checked[i][j]);
        }
        printf("\n");
    }
}

long long int horse_10(int n, int x, int y){

    
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    
    unsigned int move = 1;
    vector<vector<int> > tour(n, vector<int>(n, 0));
    vector<vector<bool> > ref_visit(n, vector<bool>(n, false));

    horse(tour, ref_visit, move,x, y);
    
    print_tour(tour);
    
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;;
}