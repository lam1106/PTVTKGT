#include<iostream>
#include<vector>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
    int a, b;
    int w;

    edge(int x, int y, int z)
    {
        this->a = x;
        this->b = y;
        this->w = z;
    }
};
vector<edge> canhs;
int n = 6, m = 9;
const int maxn = 1001;
int parent[maxn], sz[maxn];
void make_set()
{
    for (int i = 0; i <= n; i++)
    {
        parent[i] = i;
        sz[i] = 1;
    }
}
void printCycle(int a, int b, int parent[])
{
    cout << "Cycle found: ";
    vector<int> cycleNodes;
    cycleNodes.push_back(a);
    int current = b;
    while (current != a)
    {
        cycleNodes.push_back(current);
        current = parent[current];
    }
    cycleNodes.push_back(a); // Add the starting node to close the cycle
    for (int i = 0; i < cycleNodes.size(); ++i)
    {
        if (i != cycleNodes.size() - 1)
            cout << cycleNodes[i] << " -> ";
        else
            cout << cycleNodes[i];
    }
    cout << endl;
}

int find(int v)
{
    if (v == parent[v])
        return v;

    return parent[v] = find(parent[v]);
}

bool Union(int a, int b)
{
    int atest = a;
    int btest = b;
    a = find(a);
    b = find(b);

    if (a == b)
    {

        cout << "Vi canh (" << atest << ";" << btest << ") tao thanh chu trinh nen giu nguyen T";

        return false;
    }

    if (sz[a] < sz[b])
    {
        swap(a, b);
    }

    parent[b] = a;
    sz[a] + sz[b];
    return true;
}
bool cmp(edge a, edge b)
{
    return a.w < b.w;
}

void kruskal()
{
    vector<edge> mst;
    int d = 0;

    sort(canhs.begin(), canhs.end(), cmp);
    cout << "Canh e sau khi sap xep: {";
    for (auto s : canhs)
    {
        cout << "(" << s.a << "," << s.b << "," << s.w << "),";
    }
    cout << "}";
    for (int i = 0; i < m; i++)
    {
        if (mst.size() == m - 1)
            break;
        cout << "\n|T| = " << mst.size() << " <= " << n - 1 << endl;
        edge e = canhs[i];
        if (Union(e.a, e.b))
        {
            cout << "\n E  = E \\ (" << e.a << ";" << e.b << ") = {";
            for (int j = i + 1; j < m; j++)
            {
                cout << "(" << canhs[j].a << "," << canhs[j].b << "," << canhs[j].w << "),";
            }
            cout << "}";
            mst.push_back(e);
            cout << "\n T  = {";
            for (auto mstnode : mst)
            {
                cout << "(" << mstnode.a << "," << mstnode.b << "," << mstnode.w << "),";
            }
            cout << "}";
            d += e.w;
        }
    }
    if (mst.size() != n - 1)
    {
        cout << "Do thi khong ton tai";
    }
    else
    {
        cout << "\nMST: " << d << endl;
        for (auto x : mst)
        {
            cout << x.a << " " << x.b << " " << x.w << endl;
        }
    }
}

int main()
{
    canhs.push_back(edge(1, 2, 33));
    canhs.push_back(edge(1, 3, 17));
    canhs.push_back(edge(2, 3, 18));
    canhs.push_back(edge(2, 4, 20));
    canhs.push_back(edge(3, 4, 16));
    canhs.push_back(edge(3, 5, 4));
    canhs.push_back(edge(4, 6, 8));
    canhs.push_back(edge(5, 6, 14));
    canhs.push_back(edge(4, 5, 9));

    // for (int i = 0; i < m; i++)
    // {
    //     int x, y, z;
    //     cout << "Nhap dinh dau: ";
    //     cin >> x;
    //     cout << "Nhap dinh cuoi: ";
    //     cin >> y;
    //     cout << "Nhap trong so: ";
    //     cin >> z;

    //     canhs.push_back(e);
    // }
    make_set();
    kruskal();
}
using namespace std;
struct Edge {
    int u, v, w;
    Edge(int _u, int _v, int _w) {
        u = _u;
        v = _v;
        w = _w;
    }
};

void printArr(vector<Edge> arr) {
    for (int i=0; i<arr.size(); i++) {
        cout << "\t(" << arr[i].u << ", " << arr[i].v << ")";
    }
    cout << endl;
}

void sort(vector<Edge> &E) {
    for (int i=0; i<E.size()-1; i++) {
        for (int j=i+1; j<E.size(); j++) {
            if (E[i].w > E[j].w) {
                Edge temp = E[i];
                E[i] = E[j];
                E[j] = temp;
            }
        }
    }
}

int find_set(int parent[], int i) {
    if (parent[i] == i) return i;
    return find_set(parent, parent[i]);
}

void union_set(int parent[], int uPar, int vPar) {
    parent[uPar] = parent[vPar];
}

void kruskal(int V, vector<Edge> &E) {
    vector<Edge> T;
    int step = 2;

    int parent[V+1];
    for (int i=1; i<V+1; i++) {
        parent[i] = i;
    }

    int current = 0;
    while (E.size() > 0 && T.size() < V-1) {
        cout << "step " << step << ":\n";
        Edge e = E[current];
        /**
         * check has cycle
        */
        int uPar = find_set(parent, e.u);
        int vPar = find_set(parent, e.v);
        // cout << uPar << " - " << v
        if (uPar != vPar) {
            union_set(parent, uPar, vPar);
            T.push_back(e);
            E.erase(E.begin()+current);
            cout << "E = E\\" << "(" << e.u << ", " << e.v << "): ";
            printArr(E);
            cout << "T: \t";
            printArr(T);
        } else {
            current++;
            cout << "(" << e.u << ", " << e.v << ") tao thanh chu trinh\n";
        }
        step++;
    }

    cout << "Result:\nT: ";
    printArr(T);
    cout << "E: ";
    printArr(E);
    cout << endl;
}

int main() {
    int V = 6;
    vector<Edge> E;
    E.push_back(Edge(3, 5, 4));
    E.push_back(Edge(4, 5, 9));
    E.push_back(Edge(2, 4, 20));
    E.push_back(Edge(2, 3, 18));
    E.push_back(Edge(3, 4, 16));
    E.push_back(Edge(5, 6, 14));
    E.push_back(Edge(4, 6, 8));
    E.push_back(Edge(1, 2, 33));
    E.push_back(Edge(1, 3, 17));

    cout << "E: ";
    printArr(E);
    cout << "\t";
    for (int i=0; i<E.size(); i++) {
        cout << E[i].w << "\t";
    }
    cout << endl;

    sort(E);
    cout << "step 1: E sau khi sap xep \nE: ";
    printArr(E);
    cout << "\t";
    for (int i=0; i<E.size(); i++) {
        cout << E[i].w << "\t";
    }
    cout << endl;

    kruskal(V, E);
}