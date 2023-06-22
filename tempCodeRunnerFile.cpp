#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
using namespace std;

int main()
{
    
    // Window size taken as 4
    // Simulated using time and seconds. So, wait for sometime for outputs to display.

    cout << "Enter the number of frames to be transmitted: ";
    int n;
    cin >> n;

    srand(time(0));
    cout << "Frame_No\tData\tWaiting_Time(Sec)\tAcknowledgement\tResend" << endl;

    vector<int> data(n);

    for (int i = 0; i < n; i++)
        data[i] = rand() % 100;

    int ACK = 0;
    int main_ACK = -1;

    while (main_ACK != (n - 1))
    {
        if (main_ACK != -1)
            ACK = main_ACK + 1;

        for (int i = ACK; i < ACK + 4 && i < n; i++) // Sliding window is of size 4
        {
            int currFrame_time = rand() % 5;
            if (currFrame_time <= 2 && (main_ACK == i - 1))
            {
                main_ACK = i;
            }
            cout << "\t" << i + 1 << "\t" << data[i] << "\t";
            for (int j = 0; j <= 2; j++) // 3 seconds or more, send it again !
            {
                if (j <= currFrame_time)
                {
                    cout << j + 1 << ',';
                    usleep(1000000);
                }
                else
                    cout << "  ";
            }
            cout << "\t\t\t";

            if (currFrame_time > 2 || main_ACK != i)
            {
                cout << "No\t\tResend\n";
            }
            else
            {
                cout << "Yes\t\tNo\n";
            }
        }
        // cout << "\nAcknowledgement sent: " << main_ACK << endl;
    }
}