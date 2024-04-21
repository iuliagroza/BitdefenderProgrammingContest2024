#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define fin cin
#define fout cout

const float INF = std::numeric_limits<float>::max();

class HungarianAlgorithm
{
private:
    int n;
    std::vector<std::vector<float>> cost;
    std::vector<float> u, v;
    std::vector<int> p, way;

public:
    HungarianAlgorithm(const std::vector<std::vector<float>> &costMatrix)
    {
        n = costMatrix.size();
        cost = costMatrix;
        u.resize(n + 1);
        v.resize(n + 1);
        p.resize(n + 1);
        way.resize(n + 1);
    }

    float hungarian()
    {
        p[0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            p[0] = i;
            int j0 = 0;
            std::vector<float> minv(n + 1, INF);
            std::vector<bool> used(n + 1, false);
            do
            {
                used[j0] = true;
                int i0 = p[j0], j1;
                float delta = INF;
                for (int j = 1; j <= n; ++j)
                {
                    if (!used[j])
                    {
                        float cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                        if (cur < minv[j])
                            minv[j] = cur, way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j], j1 = j;
                    }
                }
                for (int j = 0; j <= n; ++j)
                {
                    if (used[j])
                    {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    }
                    else
                    {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do
            {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        return -v[0];
    }

    std::vector<std::pair<int, int>> getAssignments()
    {
        std::vector<std::pair<int, int>> assignments;
        for (int j = 1; j <= n; ++j)
        {
            assignments.emplace_back(p[j] - 1, j - 1);
        }
        return assignments;
    }
};

float l2Distance(std::pair<float, float> point1, std::pair<float, float> point2)
{
    float x1 = point1.first;
    float y1 = point1.second;
    float x2 = point2.first;
    float y2 = point2.second;

    float dx = x2 - x1;
    float dy = y2 - y1;

    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    int n, x, y;
    fin >> n;
    vector<pair<float, float>> v1;
    vector<pair<float, float>> v2;
    for (int i = 0; i < n; i++)
    {
        fin >> x >> y;
        v1.push_back({x, y});
    }
    for (int i = 0; i < n; i++)
    {
        fin >> x >> y;
        v2.push_back({x, y});
    }

    vector<vector<float>> costMatrix(v1.size(), vector<float>(v2.size(), 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            costMatrix[i][j] = l2Distance(v1[i], v2[j]);
        }
    }

    HungarianAlgorithm hungarian(costMatrix);
    float minCost = hungarian.hungarian();
    // fout << "Minimal total moving distance: " << minCost << std::endl;

    std::vector<std::pair<int, int>> assignments = hungarian.getAssignments();
    // fout << "Assignments:\n";
    // for (const auto& assignment : assignments) {
    //     fout << "Point from set 1: " << assignment.first << ", Point from set 2: " << assignment.second << std::endl;
    // }

    vector<int> sol(v1.size());
    for (auto el : assignments)
    {
        sol[el.first] = el.second;
    }
    for (int i = 0; i < n; i++)
        fout << sol[i] + 1 << "\n";

    return 0;
}