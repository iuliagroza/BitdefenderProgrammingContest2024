#include <iostream>
#include <map>
#include <fstream>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define fin cin
#define fout cout

map<string, string> mapa;
map<string, string> mapaShort;

string current_url = "0000";

string get_next_url()
{
    string next_url = current_url;
    int pos = 3;
    int rest = 1;
    while (rest)
    {
        if (next_url[pos] == '9')
        {
            next_url[pos] = 'A';
            rest = 0;
        }
        else if (next_url[pos] == 'Z')
        {
            next_url[pos] = 'a';
            rest = 0;
        }
        else if (next_url[pos] == 'z')
        {
            next_url[pos] = '0';
            pos -= 1;
        }
        else
        {
            next_url[pos] = next_url[pos] + 1;
            rest = 0;
        }
    }
    string aux = current_url;
    current_url = next_url;
    return aux;
}

void solve(int type)
{
    if (type == 1)
    {
        string long_url;
        fin >> long_url;
        mapa[long_url] = get_next_url();
        string aux = "https://ShortURL.ro/" + mapa[long_url];
        mapaShort[aux] = long_url;
        // cout<<"pun: " << aux<<"\n";
        fout << aux << "\n";
    }
    else
    {
        string short_url;
        fin >> short_url;
        // cout<<"Caut " << short_url<<"\n";
        if (mapaShort.find(short_url) != mapaShort.end())
        {
            fout << mapaShort[short_url] << "\n";
        }
        else
        {
            fout << "nu exista\n";
        }
    }
}

int main(int argc, char *argv[])
{
    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int type;
        fin >> type;
        solve(type);
    }

    return 0;
}