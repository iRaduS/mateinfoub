#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

ifstream fin("input.txt");

unsigned int n, m, x;
const unsigned int N_MAX = 1e2;
struct Node {
    int info;
    Node* next;
} *L[N_MAX];

unsigned int visited[N_MAX], nodes_in_component[N_MAX];
queue<unsigned int> q;

void add_first(Node* &p, int value) {
    Node *c = new Node;
    c->info = value;
    c->next = p;
    p = c;
}

void list(Node *p) {
    for (Node *i = p; i; i = i->next) {
        cout << i->info << ' ';
    }
}

void BFS(unsigned int x) {
    q.push(x);
    visited[x] = 1;

    while (!q.empty()) {
        unsigned int topNode = q.front();
        q.pop();

        for (Node *i = L[topNode]; i; i = i->next) {
            if (!visited[i->info]) {
                q.push(i->info);
                visited[i->info] = visited[topNode] + 1;
            }
        }
    }
}

void lant(unsigned int node) {
    if (node != x) {
        Node *i;
        for (i = L[node]; visited[i->info] != visited[node] - 1; i = i->next);

        lant(i->info);
        cout << node << ' ';
    }
    else cout << x << ' ';
}

void DFS(unsigned int node, unsigned int comp_conex) {
    visited[node] = comp_conex;
    nodes_in_component[comp_conex]++;
    for (Node *i = L[node]; i; i = i->next) {
        if (!visited[i->info]) {
            DFS(i->info, comp_conex);
        }
    }
}

int main() {
    fin >> n >> m;
    for (unsigned int i = 1, x, y; i <= m; i++) {
        fin >> x >> y;
        add_first(L[x], y);
        add_first(L[y], x);
    }

    for (unsigned int i = 1; i <= n; i++) {
        list(L[i]);
        cout << '\n';
    }

    fin >> x;
    BFS(x);
    for (unsigned int i = 1; i <= n; i++) {
        cout << visited[i] << ' ';
    }
    cout << '\n';

    for (unsigned int i = 1; i <= n; i++) {
        if (i != x) lant(i);
        cout << '\n';
    }

    unsigned int conex_comp = 0;
    for (unsigned int i = 1; i <= n; i++) {
        if (!visited[i]) {
            conex_comp++;
            DFS(i, conex_comp);
        }
    }
    cout << "Avem " << conex_comp << " componente conexe." << '\n';
    for (unsigned int i = 1; i <= conex_comp; i++) {
        cout << "Componenta conexa cu numarul " << i << " are " << nodes_in_component[i] << " noduri.\n";
    }
    return 0;
}