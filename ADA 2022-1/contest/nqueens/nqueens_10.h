#include <iostream>
#include <chrono>
#include <sys/time.h>
#include <ctime>


using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

using namespace std;


int module(int a, int b)
{
    if (a < 0)
        return b + a;
    return a % b;
}

void print(int  *queens, int n)
{
    cout << "\n";
    for (unsigned int i = 0; i < n; i++)
    {   for (unsigned int j = 0; j < n; j++)
        {
            if (queens[i] == j)
            {
                cout << "\t" << "X"; 
                continue;
            }
            cout << "\t" << ".";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool check(int *queens, int size, int pos, int n)
{

    int i = module(pos + 1 - size, n);

    while(i != pos)
    {
        if ((queens[i] == queens[pos]) || (abs(queens[i] - queens[pos]) == abs(i - pos)))
            return false;
        i = (i + 1) % n;
    }
    return true;
}

bool move_in_table( int  *queens, int size,  int n, int  x, int y)
{
    bool inserted = false;
    size++;
    int move = 0;
    do
    {
        queens[x] = (y + move) % n;
        if (check(queens, size, x, n))
        {
            if (size != n)
                inserted = move_in_table(queens, size, n, (x + 1) % n, (y + 2) % n);
            else
                inserted = true;
        }
        move++;
    }while(move != n && !inserted);

    return inserted;
}

long long int nqueens_10(int n, int x, int y)
{   
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    // init array
    
    int *queens = new int [n];
    int size = 0;

    if(!move_in_table(queens, size, n, x, y))
        for(int i = 0; i < n; i++)
            queens[i] = -1;
    print(queens, n);
    
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;;
}   