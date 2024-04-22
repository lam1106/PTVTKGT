#include <iostream>
using namespace std;

#define INF 9999999
#define n 4
int d[] = {20, 2, 30, 12, 8};
int m[n + 1][n + 1] = {0};
int g[n + 1][n + 1] = {0};

void chainMatrixProduct(int i, int j)
{
    if (i == j)
        cout << "M" << i;
    if (i < j)
    {
        cout << "(";
        chainMatrixProduct(i, g[i][j]);
        chainMatrixProduct(g[i][j] + 1, j);
        cout << ")";
    }
}

void matrixChain()
{
    for (int s = 1; s < n; s++)
    {
        cout << "voi d=" << s << endl;
        for (int i = 1; i <= n - s; i++)
        {
            int j = i + s;
            m[i][j] = INF;
            cout << "m[" << i << "," << j << "]\t= min(";
            for (int k = i; k < j; k++)
            {
                if (k != i)
                    cout << "\t\t";
                else
                    cout << "\t";
                cout << "m[" << i << "," << k << "] + m[" << k + 1 << "," << j << "] + " << d[i - 1] << "*" << d[k] << "*" << d[j] << ", {k=" << k << "}";
                if (k != j - 1)
                    cout << ",\n";
                else
                    cout << ")\n";
            }
            cout << "\t= min(";
            for (int k = i; k < j; k++)
            {
                cout << m[i][k] + m[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (k == j - 1)
                    cout << ")\n";
                else
                    cout << ",";
                int temp = m[i][k] + m[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (temp < m[i][j])
                {
                    m[i][j] = temp;
                    g[i][j] = k;
                }
            }
            cout << "\t= " << m[i][j] << endl;
            cout << "g[" << i << "," << j << "]\t= " << g[i][j] << endl;
        }
    }
    // Print the matrices M and h
    cout << "Ma tran M:" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i > j)
            {
                cout << "0 ";
            }
            else
            {
                cout << m[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << "Ma tran h:" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    cout << "ket qua la: " << m[1][n] << endl;
    chainMatrixProduct(1, n);
}

int main()
{
    matrixChain();
}