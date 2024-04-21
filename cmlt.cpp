#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
    int n;
    cin >> n;
    priority_queue<long long int, vector<long long int>, greater<long long int>> que;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        que.push(x);
    }

    long long int timp = 0;

    while (que.size() != 1)
    {
        long long int t1 = que.top();
        que.pop();
        long long int t2 = que.top();
        que.pop();

        long long int legatura = t1 + t2;

        timp += legatura;

        que.push(legatura);
    }
    cout << timp;
    return 0;
}