#include <bits/stdc++.h>

using namespace std;

int main()
{
    // int ar[] = {1, 1, 1, 1, 1, 0, 1};
    // int ar[] = {1, 0, 1, 0, 1, 0};
    int ar[] = {0, 1, 1, 1, 1, 1, 0, 1, 0};

    vector<int> ans;

    int flag = 0;

    for (int i = 0; i < sizeof(ar) / sizeof(int); i++)
    {
        if (flag >= 5)
        {
            flag = 0;
            continue;
        }
        ans.push_back(ar[i]);
        if (ar[i] == 1)
        {
            flag++;
        }
        else
            flag = 0;
    }

    for (int i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
