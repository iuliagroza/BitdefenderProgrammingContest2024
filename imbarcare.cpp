#include <iostream>
using namespace std;
int nr_pasageri(int inceput, int final, int v[], int suma)
{
    if (inceput >= final)
    {
        return 0;
    }

    int p1, p2, p3;
    p1 = p2 = p3 = 0;
    if (v[inceput] + v[final] == suma)
    {
        p1 = nr_pasageri(inceput + 1, final - 1, v, suma) + 2;
    }
    else if (v[inceput] + v[inceput + 1] == suma)
    {
        p2 = nr_pasageri(inceput + 2, final, v, suma) + 2;
    }
    else if (v[final] + v[final - 1] == suma)
    {
        p3 = nr_pasageri(inceput, final - 2, v, suma) + 2;
    }
    return max(max(p1, p2), p3);
}

int main()
{
    int n;
    cin >> n;
    int v[n + 1];
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    int p1 = nr_pasageri(1, n - 2, v, v[0] + v[n - 1]);
    int p2 = nr_pasageri(2, n - 1, v, v[0] + v[1]);
    int p3 = nr_pasageri(0, n - 3, v, v[n - 1] + v[n - 2]);

    cout << max(max(p1, p2), p3) + 2;
    return 0;
}
