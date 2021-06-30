#ifndef PATHEXTRACT_H
#define PATHEXTRACT_H



#include <stdio.h>
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>


using namespace std;
vector< vector<int> > GRAPH(100); 

inline void print_path(vector<int>path)
{
    cout<<"[ ";
    for(int i=0;i<path.size();++i)
    {
        cout<<path[i]<<" ";
    }
    cout<<"]"<<endl;
}

bool isadjacency_node_not_present_in_current_path(int node,vector<int>path)
{
    for(int i=0;i<path.size();++i)
    {
        if(path[i]==node)
        return false;
    }
    return true;
}
vector< vector<int>> extract_path_from_tps(int source ,int target ,int totalnode,int totaledge, vector< vector<int> > tmp_GRAPH )
{	
    GRAPH = tmp_GRAPH;
    vector<int>path;
    vector< vector<int>> output;
    path.push_back(source);
    queue<vector<int> >q;
    q.push(path);

    while(!q.empty())
    {
        path=q.front();
        q.pop();

        int last_nodeof_path=path[path.size()-1];
        if(last_nodeof_path==target)
        {
            //cout<<"The Required path is:: ";
            //print_path(path);
            output.push_back(path);
        }
        //else
        //{
        //  print_path(path);
        //}

        for(int i=0;i<GRAPH[last_nodeof_path].size();++i)
        {
            if(isadjacency_node_not_present_in_current_path(GRAPH[last_nodeof_path][i],path))
            {

                vector<int>new_path(path.begin(),path.end());
                new_path.push_back(GRAPH[last_nodeof_path][i]);
                q.push(new_path);
            }
        }



    }
    return output;
}

#endif
/*
int main()
{
    //freopen("out.txt","w",stdout);
    int T,N,M,u,v,source,target;
    scanf("%d",&T);
    while(T--)
    {
        printf("Enter Total Nodes & Total Edges\n");
        scanf("%d%d",&N,&M);
        for(int i=1;i<=M;++i)
        {
            scanf("%d%d",&u,&v);
            GRAPH[u].push_back(v);
        }
        printf("(Source, target)\n");
        scanf("%d%d",&source,&target);
        findpaths(source,target,N,M); //extract_path_from_tps(int source ,int target ,int totalnode,int totaledge, vector< vector<int> > tmp_GRAPH(100) );
    }
    //system("pause");
    return 0;
}
*/
