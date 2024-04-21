#include <iostream>
#include <vector>

using namespace std;

const int MOD = 999999937;

vector<vector<long long>> matrixMultiply(const vector<vector<long long>> &A, const vector<vector<long long>> &B)
{
    int n = A.size();
    vector<vector<long long>> C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

vector<vector<long long>> matrixPower(const vector<vector<long long>> &A, long long p)
{
    int n = A.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
    {
        result[i][i] = 1;
    }
    vector<vector<long long>> base = A;
    while (p > 0)
    {
        if (p & 1)
        {
            result = matrixMultiply(result, base);
        }
        base = matrixMultiply(base, base);
        p >>= 1;
    }
    return result;
}

int main()
{
    long long N;
    cin >> N;

    if (N > 4)
    {
        N -= 4;
    }
    else
    {
        cout << 1 << endl;
        return 0;
    }

    vector<vector<long long>> A = {
        {1, 0, 0, 1},
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0}};

    vector<vector<long long>> result = matrixPower(A, N);

    vector<long long> initial = {1, 1, 1, 1};
    vector<long long> finalValues(4, 0);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            finalValues[i] = (finalValues[i] + result[i][j] * initial[j]) % MOD;
        }
    }

    long long answer = finalValues[0];
    cout << answer << "\n";

    return 0;
}