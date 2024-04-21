#include <array>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

constexpr auto SZ{101};

struct AhoCorasick
{
    struct PatternNode
    {
        array<int, SZ> ch;
        vector<int> idx;
        int par{-1};
        int int_par{-1};
        int suff{-1};
        int word_suff{-1};
        array<int, SZ> next;
        int cnt{0};

        PatternNode(int parent, int int_to_parent)
            : par(parent), int_par(int_to_parent)
        {
            fill(begin(ch), end(ch), -1);
            fill(begin(next), end(next), -1);
        }
    };

    AhoCorasick()
    {
        table.emplace_back(-1, -1);
    }

    void insert_pattern(const vector<int> &v)
    {
        static auto cnt = 0;

        auto i = 0;

        for (auto j : v)
        {
            if (table[i].ch[j] == -1)
            {
                table[i].ch[j] = table.size();
                table.emplace_back(i, j);
            }

            i = table[i].ch[j];
        }

        table[i].idx.push_back(cnt);
        ++cnt;
    }

    int get_suffix(int i)
    {
        if (table[i].suff == -1)
        {
            if (i == 0 || table[i].par == 0)
                table[i].suff = 0;
            else
                table[i].suff = advance(get_suffix(table[i].par),
                                        table[i].int_par);
        }

        return table[i].suff;
    }

    int advance(int i, int j)
    {
        if (table[i].next[j] == -1)
        {
            if (table[i].ch[j] != -1)
                table[i].next[j] = table[i].ch[j];
            else
                table[i].next[j] = i == 0 ? 0 : advance(get_suffix(i), j);
        }

        return table[i].next[j];
    }

    int get_word_suffix_link(int i)
    {
        if (i == -1 || i == 0)
            return table.size();

        if (!table[i].idx.empty())
            return i;

        if (table[i].word_suff != -1)
            return table[i].word_suff;

        if (table[i].suff == -1)
            table[i].suff = get_suffix(i);

        table[i].word_suff = get_word_suffix_link(table[i].suff);

        return table[i].word_suff;
    }

    void mark_counts(int i)
    {
        auto j = i;

        while (j != -1 && j != static_cast<int>(table.size()))
        {
            ++table[j].cnt;

            if (table[j].suff == -1)
                table[j].suff = get_suffix(j);

            table[j].word_suff = get_word_suffix_link(table[j].suff);

            j = table[j].word_suff;
        }
    }

    void add_scores(vector<int> &counts)
    {
        for (auto &node : table)
            for (auto x : node.idx)
                counts[x] += node.cnt;
    }

    vector<PatternNode> table;
};

auto algo_solve(int n, const vector<vector<int>> &patterns, const vector<int> &text)
{
    AhoCorasick ac;
    for (const auto &p : patterns)
        ac.insert_pattern(p);

    auto i = 0;
    for (auto x : text)
        i = ac.advance(i, x);

    i = 0;
    for (auto x : text)
    {
        i = ac.advance(i, x);
        ac.mark_counts(i);
    }

    vector<int> counts(n, 0);
    ac.add_scores(counts);

    auto score = 0;
    for (auto i = 0; i < n; ++i)
        score += counts[i] * patterns[i].size();

    return score;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    unordered_map<string, int> strings_map;

    vector<vector<int>> patterns(n);
    for (auto &p : patterns)
    {
        string line;
        getline(cin, line);
        stringstream ss{line};

        string s;
        while (ss >> s)
            if (auto it = strings_map.find(s); it != strings_map.end())
            {
                p.push_back(it->second);
            }
            else
            {
                auto i = strings_map.size();
                p.push_back(i);
                strings_map.emplace(move(s), i);
            }
    }

    vector<int> text;
    string line;
    getline(cin, line);
    stringstream ss{line};
    string s;
    while (ss >> s)
    {
        if (auto it = strings_map.find(s); it != strings_map.end())
            text.push_back(it->second);
        else
            text.push_back(strings_map.size());
    }

    cout << algo_solve(n, patterns, text) << '\n';

    return 0;
}