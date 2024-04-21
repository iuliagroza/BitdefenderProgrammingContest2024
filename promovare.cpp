#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Define a custom comparator function to sort pairs by the second element
struct ComparePairs
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const
    {
        int influenta_a = abs(a.first + a.second);
        int influenta_b = abs(b.first + b.second);

        if (influenta_a == influenta_b)
            return influenta_a;
        return influenta_a < influenta_b;
    }
};

int main()
{
    // Declare a priority queue of pairs with custom comparator
    priority_queue<pair<int, int>, vector<pair<int, int>>, ComparePairs> pq;

    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        v.push_back(x);
    }

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        pq.push(make_pair(v[i], x));
    }

    // Pop elements from the priority queue
    bool andrei = true;
    long long int scor_andrei = 0;
    long long int scor_bogdan = 0;
    while (!pq.empty())
    {
        if (andrei)
        {
            scor_andrei += pq.top().first;
        }
        else
        {
            scor_bogdan += pq.top().second;
        }
        pq.pop();
        andrei = !andrei;
    }

    if (scor_andrei == scor_bogdan)
    {
        cout << "amandoi";
    }
    else if (scor_andrei > scor_bogdan)
    {
        cout << "Andrei";
    }
    else
    {
        cout << "Bogdan";
    }
    return 0;
}