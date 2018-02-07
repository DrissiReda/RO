#include<iostream>

using namespace std;

int main()
{
    int T[12][12];
    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
            cin >> T[i][j] ;
    for(int i=0;i<12;i++)
    {    
        for(int j=0;j<12;j++)
            cout << ((T[i][j]!=0 && i!=j || i==j)?"0":"1") << " ";
        cout << endl;
    }
} 
