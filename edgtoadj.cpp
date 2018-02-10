#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in;
    ofstream out;
    int N;
    char inp[255]={0},outp[255]={0};
    cout << "choose input " ;
    cin >> inp;
    cout << endl << "choose outp "; 
    cin >> outp;
    in.open(inp);out.open(outp);
    cout << "choose size " ;
    cin >> N;
    cout << endl;
    int t[N][N]={0},a,b;
    int z=0;
    for(int i=0;!in.eof();i++,z++)
    {
        in >> a >> b;
        t[a-1][b-1]=1;
        t[b-1][a-1]=1;
    }
    cout << "size is " << z << endl;
    out << N << endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            out << t[i][j] << " ";
        out << endl;
    }
}
