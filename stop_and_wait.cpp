#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
using namespace std;

int main()
{
    cout << "Enter the number of frames to be transmitted: ";
    int n;
    cin >> n;
    cout << "Frame_No\tData\tWaiting_Time(Sec)\tAcknowledgement\tResend" << endl;

    srand(time(0));
    int frame = 1;

    while (n--)
    {
        int data = rand() % 100;
    start:
        int count_time = rand() % 4; // random time generator
        cout << frame << "\t\t" << data << "\t\t";
        for (int i = 0; i <= 2; i++) // for only 3 seconds
        {
            if (i <= count_time)
            {
                cout << i + 1 << ",";
                usleep(1000000);
            }
            else
            {
                cout << "  ";
            }
        }

        cout << "\t\t";

        if (count_time >= 2) // For 3 seconds
        {
            cout << "No\t\tYes" << endl;
            goto start;
        }
        else
            cout << "Yes\t\tNo" << endl;

        frame++;
    }
}