#ifndef CLIQUE
#define CLIQUE
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
///////////////////////variables/////////////////////////////////
char inp[255]={0};
std::ifstream input;
std::ofstream output ("cliques");
int n, i, j, p, q, r, s, min, edge, counter=0;
bool found=false;
std::vector<std::vector<int> > curr_cliques;
std::vector<int> allcurr_clique;
std::vector<std::vector<int> > neighbors;
///////////////////declarations/////////////////////////////////
bool adjoinable(std::vector<int> neighbor, std::vector<int> curr_clique);
int max_adjoinable(std::vector<std::vector<int> > neighbors, std::vector<int> curr_clique);
std::vector<int> add_vertex(std::vector<std::vector<int> > neighbors, std::vector<int> curr_clique);
std::vector<int> expand_vertex(std::vector<std::vector<int> > neighbors, std::vector<int> curr_clique, int k);
int clique_pop_count(std::vector<int> curr_clique);
std::vector<std::vector<int> > find_neighbors(std::vector<std::vector<int> > graph);
void find_cliques(std::vector<std::vector<int> > graph, int k, int K);
void pairwise_intersections(int k, int K);
////////////////////functions///////////////////////////
bool adjoinable(std::vector<int> neighbor, std::vector<int> curr_clique)
{
    bool check=true;
    for(int i=0; i<neighbor.size(); i++)
        //if only one edge is missing, then it is not adjoinable
        //cliques requires every vertex to have edges to all other vertices
        if(curr_clique[neighbor[i]]==0)
        {
            check=false;
            break;
        }
    return check;
}

int max_adjoinable(std::vector<std::vector<int> > neighbors, std::vector<int> curr_clique)
{
    int r=-1, max=-1;
    for(int i=0; i<curr_clique.size(); i++)
    {
        if(curr_clique[i]==1 && adjoinable(neighbors[i],curr_clique)==true)
        {
            std::vector<int> temp_curr_clique=curr_clique;
            temp_curr_clique[i]=0;
            int sum=0;
            for(int j=0; j<temp_curr_clique.size(); j++)
                if(temp_curr_clique[j]==1 && adjoinable(neighbors[j], temp_curr_clique)==true)
                    sum++;
            //new Vmax
            if(sum>max)
            {
                max=sum;
                r=i;
            }
        }
    }
    return r;
}

std::vector<int> add_vertex(std::vector<std::vector<int> > neighbors, std::vector<int> curr_clique)
{
    std::vector<int> temp_curr_clique=curr_clique;
    int r=0;
    //repeat until it has no adjoinable vertices
    while(r!=-1)
    {
        r= max_adjoinable(neighbors,temp_curr_clique);
        if(r!=-1) temp_curr_clique[r]=0;
    }
    return temp_curr_clique;
}

std::vector<int> expand_vertex(std::vector<std::vector<int> > neighbors, std::vector<int> curr_clique, int k)
{
    int count=0;
    std::vector<int> temp_curr_clique=curr_clique;
    int i=0;
    for(int i=0; i<temp_curr_clique.size(); i++)
    {
        if(temp_curr_clique[i]==1)
        {
            int sum=0, index;
            for(int j=0; j<neighbors[i].size(); j++)
                if(temp_curr_clique[neighbors[i][j]]==0) {
                    index=j;
                    sum++;
                }
            //exactly one vertex inside the clique that is not a neighbor
            if(sum==1 && curr_clique[neighbors[i][index]]==0)
            {
                temp_curr_clique[neighbors[i][index]]=1;
                temp_curr_clique[i]=0;
                temp_curr_clique=add_vertex(neighbors,temp_curr_clique);
                count++;
            }
            if(count>k) break;
        }
    }
    return temp_curr_clique;
}

int clique_pop_count(std::vector<int> curr_clique)
{
    int count=0;
    for(int i=0; i<curr_clique.size(); i++)
        if(curr_clique[i]==1) count++;
    return count;
}
std::vector<std::vector<int> > find_neighbors(std::vector<std::vector<int> > graph)
{
    std::vector<std::vector<int> > ret;
    for(i=0; i<graph.size(); i++)
    {
        std::vector<int> neighbor;
        for(j=0; j<graph[i].size(); j++)
            if(graph[i][j]==1) neighbor.push_back(j);
        ret.push_back(neighbor);
    }
    return ret;
}
void find_cliques(std::vector<std::vector<int> > graph, int k,int K)
{
  std::cout<<"Finding Cliques..."<<std::endl;
  min=n+1;
  for(i=0; i<graph.size(); i++)
      allcurr_clique.push_back(1);
  for(i=0; i<allcurr_clique.size(); i++)
  {
      //check if result is found
      if(found) break;
      counter++;
      //std::cout<<counter<<". ";
      //output<<counter<<". ";
      std::vector<int> curr_clique=allcurr_clique;
      curr_clique[i]=0;
      curr_clique=add_vertex(neighbors,curr_clique);
      s=clique_pop_count(curr_clique);
      if(s<min) min=s;
      if(s<=k)
      {
          //TODO remove condition
          if(n-s>=K)
          {
            output<<"Clique of size "<<n-s<<" : ";
            for(j=0; j<curr_clique.size(); j++) if(curr_clique[j]==0) output<<j+1<<" ";
              output<<std::endl;
              //std::cout<<"Clique Size: "<<n-s<<std::endl;
          }
          curr_cliques.push_back(curr_clique);
          found=true;
          break;
      }
      for(j=0; j<n-k; j++)
          curr_clique=expand_vertex(neighbors,curr_clique,j);
      s=clique_pop_count(curr_clique);
      if(s<min) min=s;
      //TODO remove condition
      if(n-s>=K)
      {
        output<<"Clique of size "<<n-s<<" : ";
        for(j=0; j<curr_clique.size(); j++) if(curr_clique[j]==0) output<<j+1<<" ";
          output<<std::endl;
        //std::cout<<"Clique Size: "<<n-s<<std::endl;
      }
      curr_cliques.push_back(curr_clique);
      if(s<=k)
      {
          found=true;
          break;
      }
  }
}
//Qi inter Qj
void pairwise_intersections(int k, int K)
{
    for(p=0; p<curr_cliques.size(); p++)
    {
        if(found) break;
        for(q=p+1; q<curr_cliques.size(); q++)
        {
            if(found) break;
            counter++;
            //std::cout<<counter<<". ";
            //output<<counter<<". ";
            std::vector<int> curr_clique=allcurr_clique;
            for(r=0; r<curr_clique.size(); r++)
                if(curr_cliques[p][r]==0 && curr_cliques[q][r]==0) curr_clique[r]=0;
            curr_clique=add_vertex(neighbors,curr_clique);
            s=clique_pop_count(curr_clique);
            if(s<min) min=s;
            if(s<=k)
            {
                //TODO remove condition
                if(n-s>=K)
                {
                  output<<"Clique of size "<<n-s<<" : ";
                  for(j=0; j<curr_clique.size(); j++) if(curr_clique[j]==0) output<<j+1<<" ";
                    output<<std::endl;
                    //std::cout<<"Clique Size: "<<n-s<<std::endl;
                }
                found=true;
                break;
            }
            for(j=0; j<k; j++)
                curr_clique=expand_vertex(neighbors,curr_clique,j);
            s=clique_pop_count(curr_clique);
            if(s<min) min=s;
            //TODO remove condition
            if(n-s>=K)
            {
              output<<"Clique of size "<<n-s<<" : ";
              for(j=0; j<curr_clique.size(); j++) if(curr_clique[j]==0) output<<j+1<<" ";
                output<<std::endl;
                //std::cout<<"Clique Size: "<<n-s<<std::endl;
            }
            if(s<=k) {
                found=true;
                break;
            }
        }
    }
}
#endif //CLIQUE
