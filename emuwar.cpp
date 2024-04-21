#include <iostream>
#include <string>

using namespace std;

string extractKey(const string &input)
{
    int n = input.length();

    for (int i = 1; i <= n / 2; i++)
    {
        string key = input.substr(0, i);
        string key2 = input.substr(i, key.length());
        string prefix = input.substr(i + key.length());
        string prefix_key = key.substr(0, prefix.length());

        if (key == key2 && prefix.length() < key.length() && prefix == prefix_key)
        {
            return key;
        }
    }

    return "-1";
}

int main()
{
    string input;
    cin >> input;

    string key = extractKey(input);
    cout << key << "\n";

    return 0;
}