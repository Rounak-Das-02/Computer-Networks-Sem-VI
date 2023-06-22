// Author : Rounak
// SE20UCSE149

#include <bits/stdc++.h>
using namespace std;
 


int main()
{

    // Number of node/routers

    cout << "Enter the number of nodes or routers in the network : ";
    int n;  
    cin >> n;


    // cost matrix
    int weightMatrix[n][n];

    cout << "Enter the cost or weight matrix" << endl;

    for(int i = 0 ; i < n; i++)
    {
        for(int j = 0 ;j < n ; j++)
            cin>>weightMatrix[i][j];
    }



    vector<vector<int>> path(n,vector<int>(n));

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            path[i][j] = weightMatrix[i][j];
        }
    }

    int flag = 0;



    // Implementing Distance Vector Algorithm here
    do{
        flag = 0;
        for(int i = 0 ; i < n; i++){
            for(int j = 0 ; j < n ; j++){
                if(i==j){
                    continue;
                }
                
                if(weightMatrix[i][j]!=-1){
                    for(int k = 0 ; k < n; k++){
                        if(path[i][k] == -1 && path[j][k] != -1)
                        {
                            path[i][k] = path[i][j]+path[j][k];
                            flag++;
                        }
                        else if(path[i][k]!=-1 && path[j][k]!=-1)
                        {
                            if(min(path[i][k],path[i][j]+path[j][k]) != path[i][k])
                                flag++;
                            path[i][k] = min(path[i][k],path[i][j]+path[j][k]);
                        }
                    }
                }
            }
        }
    }while(flag!=0);



    // Printing the outputs
    for(int  i= 0 ; i < n ; i++){
        cout << "Final Routing path for router " << i+1 << ":" << endl;
        cout << endl;
        for(int j = 0 ; j < n ; j++){
            cout << "router " << i+1 << " via " << j+1 << ", Distance : " << path[i][j] << endl;
        }
    }
}