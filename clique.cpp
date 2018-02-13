#ifdef VERBOSE
#include "clique_verbose.hpp"
#else
#include "clique.hpp"
#endif
int main(int argc,char* argv[])
{
    if(argc<2)
    {
      std::cout << "Usage : ./clique <input> [0-1] [wanted clique size]" << std::endl;
      std::cout << "Enter 0 for deep search, or 1 for fast (default is fast)" << std::endl;
      std::cout << "You can choose your clique size, or let the program find the max for you" << std::endl;
      return 0;
    }
    int K,k;
    bool fast=1,givenK=0;
    float den;
    std::vector< std::vector<int> > graph;
    if(argc>2)
      fast=atoi(argv[2]);
//Read Graph (note we work with the complement of the input graph)
    std::cout<<"Graph "<<argv[1]<<std::endl;
    std::strcpy(inp,argv[1]);
    //Remove folders
    strsep(&argv[1],"/");
    while(true)
    {
      for(int i=0;i<strlen(argv[1]);i++)
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
    for(int i=0;i<strlen(argv[1]);i++)
    {
        if(argv[1][i]=='.')
            lc=i;
    }
    if(lc>0)
        argv[1][lc]='\0';
    std::strcat(outp,argv[1]);
    std::strcat(outp,".out");
    input.open(inp);
    output.open(outp);
    input>>n>>den;
    for(int i=0; i<n; i++)
    {
        std::vector<int> row;
        for(int j=0; j<n; j++)
        {
            input>>edge;
            if(edge==0)row.push_back(1);
            else row.push_back(0);
        }
        graph.push_back(row);
    }
    std::cout << "density is " << den << std::endl;
    if(argc>3)
    {
      K=atoi(argv[3]);
      givenK=1;
    }
    else if(argc==3 && atoi(argv[2])>1)
    {
      K=atoi(argv[2]);
      givenK=1;
    }
    else
    {
    //Lower bound
      K= ceil((float)(1/(1-(float)den)));
    }
//Find Neighbors for each vertex
    neighbors=find_neighbors(graph);
    std::cout<<"Graph has n = "<<n<<" vertices, "<<((fast)?"fast":"deep")<<" mode"<<std::endl;
//Read maximum size of Clique wanted
    std::cout<<"Finding Cliques..."<<std::endl;

//Find Cliques
    do
    {
      //empty vectors
      init();
      //init at false
      found=false;
      k=n-K;
      std::cout<<"Find a Clique of size at least k = "<<K<< std::endl;
      //find cliques
      find_cliques(graph, k, K);
      //only for deep search
      if(!fast && !found)
        pairwise_intersections(k, K);
      //init our new K as the max found +1
      K=curr_max+1;
    }while(found && !givenK);// repeat while finding graphs
//Find Additional Cliques through Pairwise Intersections
    //
    if(found)
      std::cout<<"Found Clique of size at least "<<curr_max<<std::endl;
    else
    std::cout<<"Could not find Clique of size at least "<<K<<std::endl
                      <<"Maximum Clique size found "<<n-min<<std::endl;
    std::cout<<"Results are stored in "<<outp <<" file"<<std::endl;
    return 0;
}
