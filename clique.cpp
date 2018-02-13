#ifdef VERBOSE
#include "clique_verbose.hpp"
#else
#include "clique.hpp"
#endif
int main(int argc,char* argv[])
{
   int K,k;
//Read Graph (note we work with the complement of the input graph)
    std::cout<<"Graph "<<argv[1]<<std::endl;
    std::strcpy(inp,argv[1]);
    //Remove folders
    strsep(&argv[1],"/");
    while(true)
    {
      for(i=0;i<strlen(argv[1]);i++)
      { // if there is still nested folders
        if(argv[1][i]=='/')
        {
          strsep(&argv[1],"/");
          break;
        }
      }
      break;
    }
    //remove the extension if it exists
    int lc=-1;
    for(i=0;i<strlen(argv[1]);i++)
    {
      if(argv[1][i]=='.')
        lc=i;
    }
    if(lc>0)
      argv[1][lc]='\0';
    std::strcat(outp,argv[1]); std::strcat(outp,".out");
    K=atoi(argv[2]);
    input.open(inp);
    output.open(outp);
    input>>n;
    std::vector< std::vector<int> > graph;

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
    std::cout<<"Find a Clique of size at least k = "<<K<< std::endl;
    k=n-K;
//Find Cliques
    find_cliques(graph, k, K);
//Find Additional Cliques through Pairwise Intersections
    pairwise_intersections(k, K);
    if(found) std::cout<<"Found Clique of size at least "<<K<<"."<<std::endl;
    else std::cout<<"Could not find Clique of size at least "<<K<<"."<<std::endl
                      <<"Maximum Clique size found "<<n-min<<"."<<std::endl;
    std::cout<<"Results are stored in "<<outp <<" file"<<std::endl;
    return 0;
}
