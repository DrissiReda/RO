#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("brock200_2");
    ofstream out("outtt");
    int t[200][200]={0},a,b;
    for(int i=0;i<200;i++)
    {
        in >> a >> b;
        t[a][b]=1;
    }
    for(int i=0;i<200;i++)
    {
        for(int j=0;j<200;j++)
            out << t[i][j] << " ";
        out << endl;
    }
}
