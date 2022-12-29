#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;

//bubbly sort using list
void bubbleSort1(list<int> &l) {
    list<int>::iterator it;
    for (it = l.begin(); it != l.end(); it++) {
        list<int>::iterator it2 = it;
        it2++;
        while (it2 != l.end()) {
            if (*it > *it2) {
                int temp = *it;
                *it = *it2;
                *it2 = temp;
            }
            it2++;
        }
    }
}

//merge sort using queue
void mergeSort(queue<int> &q) {
    if (q.size() == 1) {
        return;
    }
    queue<int> q1, q2;
    while (q.size() > 1) {
        q1.push(q.front());
        q.pop();
    }
    q2.push(q.front());
    q.pop();
    mergeSort(q1);
    mergeSort(q2);
    while (!q1.empty() && !q2.empty()) {
        if (q1.front() < q2.front()) {
            q.push(q1.front());
            q1.pop();
        } else {
            q.push(q2.front());
            q2.pop();
        }
    }
    while (!q1.empty()) {
        q.push(q1.front());
        q1.pop();
    }
    while (!q2.empty()) {
        q.push(q2.front());
        q2.pop();
    }
}

//selection sort uding stack
void selectionSort(stack<int> &s) {
    stack<int> s1;
    while (!s.empty()) {
        int temp = s.top();
        s.pop();
        while (!s1.empty() && s1.top() > temp) {
            s.push(s1.top());
            s1.pop();
        }
        s1.push(temp);
    }
    while (!s1.empty()) {
        s.push(s1.top());
        s1.pop();
    }
}

int main(){


    list<int> l;

    l.push_front(90);
    l.push_front(10);
    l.push_back(40);
    l.push_back(50);

    bubbleSort1(l);
    cout << "\n sorted list: ";
    for (auto arr1 : l)
        cout << arr1 << " ";
    cout << "\n";

    stack<int> s;

    s.push(23);
    s.push(33);
    s.push(43);
    s.push(53);

    cout << "sorted stack: ";
    selectionSort(s);
    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    cout << "\n";

    queue<int> q;

    q.push(32);
    q.push(45);
    q.push(87);
    q.push(18);

    cout << "sorted queue: ";
    mergeSort(q);
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }

}