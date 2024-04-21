#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

// #define cin fin
// #define cout fout
const long long modulo = 1e9 + 7;

int firstGreaterThan(std::vector<int> &vec, int x)
{
    int left = 0, right = vec.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (vec[mid] <= x)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return right;
}

int main()
{
    int n, x;
    cin >> n;
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        v1.push_back(x);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        v2.push_back(x);
    }
    vector<int> dif;
    for (int i = 0; i < n; i++)
    {
        dif.push_back(v1[i] - v2[i]);
    }
    sort(dif.begin(), dif.end());
    // for(int i=0; i<n; i++)
    // {
    //     cout<<dif[i]<<" ";
    // }
    // cout<<"\n";
    vector<int> aux;
    long long int gandalf_total_win = 0;
    for (int i = 0; i < n; i++)
    {
        x = -dif[i];
        int index = firstGreaterThan(aux, x);
        int gandalf_win = aux.size() - index;
        if (index < aux.size())
        {
            gandalf_total_win += gandalf_win;
            gandalf_total_win %= modulo;
        }
        aux.push_back(dif[i]);
    }
    cout << gandalf_total_win;

    return 0;
}