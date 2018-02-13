#include <fstream>
#include <iostream>
#include <set>
#include <string.h>
#include <map>
#include <assert.h>
#include "maxc.h"
using namespace std;
void read_dimacs(string name, bool** &conn, int &size)
{
    ifstream f (name.c_str());
    string buffer;
    assert(f.is_open());
    set<int> v;
    bool isls=true;
    multimap<int,int> e;
    getline(f,buffer);
    if(buffer[0]=='c' || buffer[0]=='p')
      isls=false;
    while (!getline(f, buffer).eof())
    {
        int vi, vj;
        //either a list or a .clq starting with e
        if(isls ^ buffer[0]=='e')
        {
          if(isls)
            sscanf(buffer.c_str(), "%d %d", &vi, &vj);
          else
            sscanf(buffer.c_str(), "%*c %d %d", &vi, &vj);
          v.insert(vi);
          v.insert(vj);
          e.insert(make_pair(vi, vj));
        }
    }
    size = *v.rbegin() + 1;
    conn = new bool*[size];
    for (int i=0; i < size; i++)
    {
        conn[i] = new bool[size];
        memset(conn[i], 0, size * sizeof(bool));
    }
    for (multimap<int,int>::iterator it = e.begin(); it != e.end(); it++)
    {
        conn[it->first][it->second] = true;
        conn[it->second][it->first] = true;
    }
    cout << "|E| = " << e.size() << "  |V| = " << v.size() << " p = " << (double) e.size() / (v.size() * (v.size()) / 2) << endl;
    f.close();
}
int main(int argc, char *argv[])
{
    assert(argc == 2);
    cout << "args = " << argv[1] << endl;
    bool **conn;
    int size, *qmax, qsize;
    read_dimacs(argv[1], conn, size);
    cout << "max clique with improved coloring and dynamic sorting of vertices"<<endl;
    Maxclique md(conn, size, 0.025);  //(3rd parameter is optional - default is 0.025 - this heuristics parameter enables you to use dynamic resorting of vertices (time expensive)
    // on the part of the search tree that is close to the root - in this case, approximately 2.5% of the search tree -
    // you can probably find a more optimal value for your graphs
    md.mcqdyn(qmax, qsize);  // run max clique with improved coloring and dynamic sorting of vertices
    cout << "Maximum clique: ";
    for (int i = 0; i < qsize; i++)
        cout << qmax[i] << " ";
    cout << endl;
    cout << "Size = " << qsize << endl;
    cout << "Number of steps = " << md.steps() << endl;
    delete [] qmax;
    for (int i=0; i<size; i++)
        delete [] conn[i];
    delete [] conn;
    return 0;
}
