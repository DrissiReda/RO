#include <fstream>
#include <iostream>
#include <set>
#include <string.h>
#include <map>
#include "maxc.hpp"
using namespace std;
void read_dimacs(string name, bool** &graph, int &size)
{
    ifstream f (name.c_str());
    string buffer;
    assert(f.is_open());
    set<int> v;
    bool isls=false;
    multimap<int,int> e;
    getline(f,buffer);
    if(name.substr(name.find_last_of(".")+1)=="ls")
        isls=true;
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
    graph = new bool*[size];
    for (int i=0; i < size; i++)
    {
        graph[i] = new bool[size];
        memset(graph[i], 0, size * sizeof(bool));
    }
    for (multimap<int,int>::iterator it = e.begin(); it != e.end(); it++)
    {
        graph[it->first][it->second] = true;
        graph[it->second][it->first] = true;
    }
    cout << "|E| = " << e.size() << "  |V| = " << v.size() << " p = " << (double) e.size() / (v.size() * (v.size()) / 2) << endl;
    f.close();
}
int read_file(string name,bool** &graph, int &size)
{
    string ext=name.substr(name.find_last_of(".")+1);
    if(ext=="clq" || ext=="ls")
    {
        read_dimacs(name,graph,size);
        return 0;
    }
    else if(ext=="mat")//adjmat format
    {
        ifstream in(name.c_str());
        int esize;
        in >> size >> esize;
        string s;
        graph = new bool*[size];
        getline(in,s);
        for(int i=0; i<size; i++)
        {
            graph[i]=new bool[size];
            memset(graph[i],0,size*sizeof(bool));
        }
        for(int i=0; i<size; i++)
            for(int j=0; j<size; j++)
                in >> graph[i][j];
        in.close();
        cout << "|E| = " << esize << "  |V| = " << size << " p = " << (double) esize / (size * size / 2) << endl;
        return 0;
    }
    else
        return -1;
}

int main(int argc, char *argv[])
{
    if ( argc<2)
    {
        cout << " Usage : ./maxc <fichier.ls|.mat|.clq>" << endl;
        return -1;
    }
    cout << "args = " << argv[1] << endl;
    bool **graph;
    int size, *qmax, cqsize;
    if(read_file(argv[1], graph, size)<0)
    {
        cout << " Usage : ./maxc <fichier.ls|.mat|.clq>" << endl;
        return -1;
    }
    Qmax mc(graph, size, 0.025);
    mc.maxc(qmax, cqsize);
    cout << "Clique Max: ";
    for (int i = 0; i < cqsize; i++)
        cout << qmax[i] << " ";
    cout << endl;
    cout << "Taille = " << cqsize << endl;
    cout << "Nombre d'etapes = " << mc.steps() << endl;
    delete [] qmax;
    for (int i=0; i<size; i++)
        delete [] graph[i];
    delete [] graph;
    return 0;
}
