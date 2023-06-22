// #include <bits/stdc++.h>

// using namespace std;

// int *string2Array(string s)
// {
//     int *ar = new int[s.length()];
//     for (int i = 0; i < s.length(); i++)
//     {
//         if (s[i] == '0')
//             ar[i] = 0;
//         else
//             ar[i] = 1;
//     }
//     return ar;
// }

// int main()
// {

//     // freopen("input.txt", "r", stdin);

//     int fs;
//     cout << "Enter the number of bits in input data: ";
//     cin >> fs;
//     cout << endl;

//     int gs;
//     cout << "Enter the number of bits in the polynomial generator (divisor): ";
//     cin >> gs;
//     cout << endl;

//     int f[fs];

//     cout << "Enter the data:";
//     string s;
//     cin >> s;
//     for (int i = 0; i < fs; i++)
//     {
//         if (s[i] == '0')
//             f[i] = 0;
//         else
//             f[i] = 1;
//     }

//     int g[gs];

//     cout << "\nEnter the divisor:";
//     string s2;
//     cin >> s2;
//     for (int i = 0; i < gs; i++)
//     {
//         if (s2[i] == '0')
//             g[i] = 0;
//         else
//             g[i] = 1;
//     }

//     // Append 0's
//     for (int i = fs; i < fs + gs - 1; i++)
//     {
//         f[i] = 0;
//     }

//     int temp[fs + gs - 1];
//     for (int i = 0; i < fs + gs - 1; i++)
//     {
//         temp[i] = f[i];
//     }

//     // Division
//     for (int i = 0; i < fs; i++)
//     {
//         int j = 0;
//         int k = i;
//         if (temp[k] >= g[j])
//         {
//             // Taking only length of generator key and doing XOR operation.
//             for (j = 0, k = i; j < gs; j++, k++)
//             {
//                 if ((temp[k] == 1 && g[j] == 1) || (temp[k] == 0 && g[j] == 0))
//                 {
//                     temp[k] = 0;
//                 }
//                 else
//                 {
//                     temp[k] = 1;
//                 }
//             }
//         }
//     }

//     // CRC
//     int crc[gs - 1];
//     for (int i = 0, j = fs; i < gs - 1; i++, j++)
//     {
//         crc[i] = temp[j];
//     }

//     cout << "\nCRC value: ";
//     for (int i = 0; i < gs - 1; i++)
//     {
//         cout << crc[i];
//     }
//     cout << endl;

//     cout << "Transmitted data: ";
//     int tf[fs + gs - 1];
//     for (int i = 0; i < fs; i++)
//     {
//         tf[i] = f[i];
//     }
//     for (int i = fs, j = 0; i < fs + gs - 1; i++, j++)
//     {
//         tf[i] = crc[j];
//     }
//     for (int i = 0; i < fs + gs - 1; i++)
//     {
//         cout << tf[i];
//     }

//     cout << "\nEnter the received data: ";
//     cin >> s;
//     int rx[fs + gs - 1];
//     for (int i = 0; i < s.length(); i++)
//     {
//         if (s[i] == '0')
//             rx[i] = 0;
//         else
//             rx[i] = 1;
//     }

//     for (int i = 0; i < fs + gs - 1; i++)
//     {
//         temp[i] = rx[i];
//     }

//     // Division
//     for (int i = 0; i < fs + gs - 1; i++)
//     {
//         int j = 0;
//         int k = i;
//         if (temp[k] >= g[j])
//         {
//             for (j = 0, k = i; j < gs; j++, k++)
//             {
//                 // My own XOR function
//                 if ((temp[k] == 1 && g[j] == 1) || (temp[k] == 0 && g[j] == 0))
//                 {
//                     temp[k] = 0;
//                 }
//                 else
//                 {
//                     temp[k] = 1;
//                 }
//             }
//         }
//     }

//     int rrem[fs + gs - 1];
//     for (int i = fs, j = 0; i < fs + gs - 1; i++, j++)
//     {
//         rrem[j] = temp[i];
//     }

//     int flag = 0;
//     for (int i = 0; i < gs - 1; i++)
//     {
//         if (rrem[i] != 0)
//         {
//             flag = 1;
//         }
//     }

//     flag = 0;
//     for (int i = 0; i < fs + gs - 1; i++)
//     {
//         if (tf[i] != rx[i])
//         {
//             flag = 1;
//             break;
//         }
//     }

//     if (flag == 0)
//     {
//         cout << "\nNo errors detected" << endl;
//     }
//     else
//     {
//         cout << "\nErrors detected" << endl;
//     }

//     return 0;
// }

#include <bits/stdc++.h>

using namespace std;

string xorfinder(string encoded, string divisor){
    for(int i = 0 ; i <= encoded.length() - divisor.length() ; )
    {
        for(int j = 0 ; j < divisor.length();j++){
            encoded[i+j] = encoded[i+j] == divisor[j] ? '0' : '1';
        }
        for(; encoded[i]!='1' && i < encoded.length() ; i++);
    }
    return encoded;
}


int main(){
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    int p;
    cin >> p;
    string data;
    cin >> data;
    string divisor; 
    cin >> divisor;

    string encoded = data;
    for(int i =0;i < p-1; i++){
        encoded +='0';
    }
    encoded = xorfinder(encoded, divisor);

    cout << encoded.substr(encoded.length() - p + 1) << endl;
    cout << data + encoded.substr(encoded.length() - p + 1) << endl;

    string msg;
    cin >> msg;

    msg = xorfinder(msg, divisor);

    for(char i : msg.substr(msg.length()- p + 1)){
        if(i != '0'){
            cout << "Error" <<endl;
            return 0;
        }
    }

    cout << "No Error" << endl;

    return 0;

}



