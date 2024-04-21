#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

int findMinTicketNumber(int N, int M, int source, int destination, vector<int> &costs, vector<vector<int>> &edges)
{
    vector<vector<int>> graph(N + 1);
    for (const auto &edge : edges)
    {
        int x = edge[0], y = edge[1];
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<int> minCost(N + 1, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    minCost[source] = costs[source - 1];
    pq.push({minCost[source], source});

    while (!pq.empty())
    {
        int currCost = pq.top().first;
        int currVertex = pq.top().second;
        pq.pop();

        if (currVertex == destination)
        {
            return currCost;
        }

        if (currCost > minCost[currVertex])
        {
            continue;
        }

        for (int neighbor : graph[currVertex])
        {
            int newCost = max(currCost, costs[neighbor - 1]);
            if (newCost < minCost[neighbor])
            {
                minCost[neighbor] = newCost;
                pq.push({newCost, neighbor});
            }
        }
    }

    return -1;
}

int main()
{
    int N, M, source, destination;
    cin >> N >> M >> source >> destination;

    vector<int> costs(N);
    for (int i = 0; i < N; i++)
    {
        cin >> costs[i];
    }

    vector<vector<int>> edges(M, vector<int>(2));
    for (int i = 0; i < M; i++)
    {
        cin >> edges[i][0] >> edges[i][1];
    }

    int minTicketNumber = findMinTicketNumber(N, M, source, destination, costs, edges);
    cout << minTicketNumber << endl;

    return 0;
}