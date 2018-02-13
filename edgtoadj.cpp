#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out;
    int N,M;
    float den=0.0;
    char inp[255]="edgls/",outp[255]="adjmat/";

    strcat(inp,argv[1]); strcat(inp,".ls"); strcat(outp,argv[1]); strcat(outp,".mat");
    cout << "choose input " << inp << endl;
    cout << endl << "choose outp "<<outp<<endl;
    in.open(inp);out.open(outp);
    in >> N >> M;
    den=2*(float)M/((float)N*(float)N);
    int t[N][N]={0},a,b;
    for(int i=0;!in.eof();i++)
    {
        in >> a >> b;
        t[a-1][b-1]=1;
        t[b-1][a-1]=1;
    }
    cout << "size is " << M <<" density is "<<den<< endl;
    out << N <<" "<< den << endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            out << t[i][j] << " ";
        out << endl;
    }
}
