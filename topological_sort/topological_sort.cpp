#include "stdio.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::vector<bool>> adj; // adjacency matrix
std::vector<size_t> visit;          // record DFS visited nodes
std::vector<size_t> order;          // store the topologically sorted order
size_t N, N_const;
bool cycle;                         // store whether cycle is detected throughout DFS visiting

size_t findGraphSize(std::vector<std::string> G) {
    size_t size = 0, i = 0, j = 0, arrowPos = 0;
    std::string delimstr = " -> ";
    std::vector<size_t> nodes;
    for (auto edge = G.begin(); edge != G.end(); ++edge) {
        arrowPos = edge->find("->");
        if (arrowPos < 10) {
            i = std::atoi(edge->substr(0, edge->find(delimstr)).substr(1).c_str());
            j = std::atoi(edge->substr(edge->find(delimstr) + delimstr.length()).substr(1).c_str());
        }
        else {
            i = std::atoi(edge->substr(1).c_str());
            j = i;
        }
        nodes.push_back(i);
        for (auto n = nodes.begin(); n != nodes.end() - 1; ++n) if (i == *n) { nodes.pop_back(); break; }
        nodes.push_back(j);
        for (auto n = nodes.begin(); n != nodes.end() - 1; ++n) if (j == *n) { nodes.pop_back(); break; }
    }
    size = nodes.size();
    return size;
}

void DFS(size_t s) {
    if (visit[s] == 1) {
        cycle = true;
        return;
    }
    if (visit[s] == 2) {
        return;
    }

    visit[s] = 1;
    for (size_t t = s + 1; t < N_const; ++t) {
        if (adj[s][t]) {
            DFS(t);
        }
    }
    visit[s] = 2;

    order[N--] = s;     // store the topological order
}

void topological_ordering() {
    // initialization
    for (size_t i = 0; i < N_const; ++i) {
        visit[i] = 0;
    }
    cycle = false;

    // DFS
    for (int s = 0; s < N_const; ++s) {
        if (!visit[s]) {
            DFS(s);
        }
    }
    // print out results
    if (cycle) {
        cout << "cycle is detected !\n";
    }
    else {
        // print out results
        for (int i = 0; i < N_const; ++i) {
            std::cout << order[i];
        }
        std::cout << '\n';
    }
}


int main() {
    std::vector<std::string> dGraph; // dependency graph
    dGraph.push_back("n0 -> n1");
    dGraph.push_back("n1 -> n2");
    dGraph.push_back("n0 -> n3");
    dGraph.push_back("n0 -> n4");
    dGraph.push_back("n5");
    dGraph.push_back("n4 -> n6");
    dGraph.push_back("n5 -> n6");
    dGraph.push_back("n6 -> n8");
    dGraph.push_back("n7 -> n8");

    N = findGraphSize(dGraph);
    for (size_t n = 1; n <= N; ++n) {
        std::vector<bool> adj_col(n);
        adj.push_back(adj_col);
        visit.push_back(0);
        order.push_back(0);
    }
    N_const = N--;

    std::string delimstr = " -> ";
    size_t i, j;
    for (auto edge = dGraph.begin(); edge != dGraph.end(); ++edge) {
        size_t arrowPos = edge->find("->");
        if (arrowPos < 10) {
            i = std::atoi(edge->substr(0, edge->find(delimstr)                    ).substr(1).c_str());
            j = std::atoi(edge->substr(   edge->find(delimstr) + delimstr.length()).substr(1).c_str());
        }
        adj[i][j] = true;
    }
    std::cout << "=====================================\n  |\n";
    std::cout << "  | 0  1  2  3  4  5  6  7  8 \n";
    std::cout << "--+---------------------------\n";
    for (size_t ii = 0; ii < N_const; ++ii) {
        std::cout << ii << " | ";
        for (size_t jj = 0; jj < N_const; ++jj) {
            std::cout << adj[ii][jj] << "  ";
        }
        std::cout << '\n';
    }
    std::cout << "--+---------------------------\n";
    topological_ordering();
    return 0;
}
