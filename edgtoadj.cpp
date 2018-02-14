#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out;
    int N,M;
    float den=0.0;
    char inp[255]="edgls/",outp[255]="adjmat/";

    strcat(inp,argv[1]); strcat(inp,".ls"); strcat(outp,argv[1]); strcat(outp,".mat");
    cout <<"input "<< inp << endl;
    cout <<"outp " <<outp <<endl;
    in.open(inp);out.open(outp);
    in >> N;
    string s;
    getline(in,s);
    s=s.substr(s.find_last_of(" ")+1);
    M=atoi(s.c_str());
    den=2*(float)M/((float)N*(float)N);
    int **t,a,b;
    t=(int**)calloc(1,sizeof(int*)*N);
    for(int i=0;i<N;i++)
      t[i]=(int*)calloc(1,sizeof(int)*N);
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
        t[i][j]=0;
    for(int i=0;!in.eof();i++)
    {
        in >> a >> b;
        t[a-1][b-1]=1;
        t[b-1][a-1]=1;
    }
    cout << "|V|="<<N<<"|E|=" << M <<" density is "<<den<< endl;
    out << N <<" "<< M << endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            out << t[i][j] << " ";
        out << endl;
    }
    for(int i=0;i<N;i++)
      free(t[i]);
    free(t);
}
