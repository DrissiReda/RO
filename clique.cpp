#include "clique.hpp"

int main()
{
//Read Graph (note we work with the complement of the input graph)
    std::cout<<"Choose graph"<<std::endl;
    std::cin >> inp;
    input.open(inp);
    input>>n;
    std::vector< std::vector<int> > graph;
    int K,k;
    for(i=0; i<n; i++)
    {
        std::vector<int> row;
        for(j=0; j<n; j++)
        {
            input>>edge;
            if(edge==0)row.push_back(1);
            else row.push_back(0);
        }
        graph.push_back(row);
    }
//Find Neighbors for each vertex
    neighbors=find_neighbors(graph);
    std::cout<<"Graph has n = "<<n<<" vertices."<<std::endl;
//Read maximum size of Clique wanted
    std::cout<<"Find a Clique of size at least k = ";
    std::cin>>K;
    k=n-K;
//Find Cliques
    find_cliques(graph, k, K);
//Find Additional Cliques through Pairwise Intersections
    pairwise_intersections(k, K);
    if(found) std::cout<<"Found Clique of size at least "<<K<<"."<<std::endl;
    else std::cout<<"Could not find Clique of size at least "<<K<<"."<<std::endl
                      <<"Maximum Clique size found "<<n-min<<"."<<std::endl;
    std::cout<<"Results are stored in 'cliques' file"<<std::endl;
    return 0;
}
