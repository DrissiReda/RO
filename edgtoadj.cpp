#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out;
    int N;
    char inp[255]="edgls/",outp[255]="adjmat/";

    strcat(inp,argv[1]); strcat(inp,".ls"); strcat(outp,argv[1]); strcat(outp,".mat");
    cout << "choose input " << inp << endl;
    cout << endl << "choose outp "<<outp<<endl;
    in.open(inp);out.open(outp);
    in.seekg(-2,ios::end);
    char ch;
    in.get(ch);
    while(ch!='\n')
    {
      in.seekg(-2,ios::cur);
      in.get(ch);
    }
    in >> N;
    in.seekg(0,ios::beg);
    cout << "choose size " <<N;
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
