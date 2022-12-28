#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>
//if using gcc 
/*
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
*/
// if using gcc



//// if using c++17

#include <filesystem>
namespace fs = std::filesystem;//C++17 only

using namespace std;

bool endsWith(const std::string& mainStr, const std::string& toMatch) // string manipulation, check if it endswith. 
{
    if (mainStr.size() >= toMatch.size() &&
        mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        return true;
    else
        return false;
}
vector<pair<int, int>> read_file(string path) { //read graph,, store the edges in vector edges of pairs.
    vector<pair<int, int>> edges;
    if (endsWith(path, "txt")) {
        std::ifstream infile(path);
        int a, b;
        while (infile >> a >> b)
        {
            if (a != b) {
                edges.push_back(std::make_pair(a, b));
            }
            // else{
            //     self_loops.push_back(a);
            // }

        }
    }
    else {
        ifstream infile(path);
        string line;
        string str;
        getline(infile, line);
        while (getline(infile, line))
        {
            istringstream ss(line);
            vector <string> record;
            (getline(ss, str, ','));
            int a = std::stoi(str);
            (getline(ss, str, ','));
            int b = std::stoi(str);

            if (a != b) edges.push_back(std::make_pair(a, b));
        }
    }




    //std::cout << "slefloop len : " << self_loops.size() << "\n";

    return edges;
}

vector<int>* list_adjacence(vector<pair<int, int>> edges, int nodes) { // adjacency list
    vector<int>* L = new vector<int>[nodes];
    for (unsigned int i = 0;i < edges.size();i++) {
        (L + edges[i].first)->push_back(edges[i].second);
        (L + edges[i].second)->push_back(edges[i].first);
    }
    //std::cout << "L " << (*(L+2))[1]<< "\n";
    return L;
}

int* degree_function(vector<int>* adj, int nodes) { // returns the degree vector. element at index i gives the degree of node i
    int* degrees = new int[nodes] {0};
    for (int i = 0;i < nodes;i++) {
        *(degrees + i) = (adj + i)->size();
    }

    return degrees;

}

vector<int>* list_nodes_by_degree(int* degrees, int nodes, int max_d) { // gives the list of nodes by degree (list of list) . Element at index i is a list of nodes with degree i.

    vector<int>* L = new vector<int>[max_d + 1];
    for (int i = 0;i < nodes;i++) {

        (L + (*(degrees + i)))->push_back(i);
    }
    return L;
}

void algo(string path) { // the greedy algorithm
    // initialization //

    int nodes = 0;
    vector<pair<int, int>> edges = read_file(path);

    for (unsigned int i = 0; i < edges.size(); i++) {
        nodes = max(max(edges[i].first, edges[i].second), nodes);
    }
    nodes++;
    vector<int> *adjacent = list_adjacence(edges, nodes);
    int E = edges.size();
    int V = nodes;
    vector<pair<int, int>>().swap(edges);
    int *deg = degree_function(adjacent, nodes);

    int d_min = *deg;
    int d_max = 0;
    for (int i = 0; i < nodes; i++) {
        d_max = max(d_max, (*(deg + i)));
        d_min = min(d_min, (*(deg + i)));
    }

    vector<int> *L_degrees = list_nodes_by_degree(deg, nodes, d_max);
    bool *binary_removed = new bool[nodes]{false};
    int *removed = new int[nodes]{0};
    std::pair<int, int> *v_removed = new std::pair<int, int>[E];
    float p, d = (float) E / (float) V;
    int l = 0;
    int m = 0;
    int length_removed = 0;
    int length_v_removed = 0;
    int my_node = 0;
    int card_v = V;
    int card_E = E;

    int final_E = 0;

    //End of  initialization //
    auto t1 = std::chrono::high_resolution_clock::now();
    // LOOP //
    while (length_removed != nodes) {

        while (true) {

            while (d_min < d_max && (L_degrees + d_min)->empty()) {

                d_min++;
            }

            my_node = (L_degrees + d_min)->back();
            (L_degrees + d_min)->pop_back();

            if (!*(binary_removed + my_node)) break;
        }

        *(removed + length_removed) = my_node;
        length_removed++;
        *(binary_removed + my_node) = true;
        float k = 0;

        for (unsigned int i = 0; i < (adjacent + my_node)->size(); i++) {

            int voisin = (*(adjacent + my_node))[i];
            if (!(*(binary_removed + voisin))) {
                k++;
                (L_degrees + (*(deg + voisin)) - 1)->push_back(voisin);
                if ((*(deg + voisin)) == d_min) d_min--;
                (*(deg + voisin))--;
                *(v_removed + length_v_removed) = std::make_pair(voisin, my_node);
                length_v_removed++;
            }
        }

        V--;
        E -= k;
        if (V != 0 && ((float) E / (float) V) > d) {
            l = length_removed;
            m = length_v_removed;
            d = ((float) E / (float) V);
            final_E = E;
        }

    }


    // End of loop

    // clear memory
    delete[] removed;
    delete[] binary_removed;
    delete[] adjacent;
    delete[] deg;
    delete[] L_degrees;
    // end timer
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    //results
    std::cout << "duration (sec) : " << (float)duration / (float)1000000 << "\n";
    std::cout << "n and  m :" << card_v << "   " << card_E << "\n";
    std::cout << "RESULT : density = " << d << ", edges =  " << final_E << "\n";
}

int main()
{
    //algo("../graphs/ego-Facebook.txt");
    //algo("../graphs/CA-AstroPh.txt");
    //algo("../graphs/roadNet-CA.txt");
    algo("../graphs/roadNet-TX.txt");
    return 0;
}
