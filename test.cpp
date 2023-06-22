#include <bits/stdc++.h>

using namespace std;

int *string2Array(string s)
{
    int *ar = new int[s.length()];
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
            ar[i] = 0;
        else
            ar[i] = 1;
    }
    return ar;
}

int main()
{

    int *f;
    string s;
    cin >> s;
    cout << s << endl;
    string s1;
    cin >> s;
    cout << s;
    // f = string2Array(s);
    // // cout << f[1];
    // for (int i = 0; i < s.length(); i++)
    // {
    //     cout << f[i] << " ";
    // }

    return 0;
}