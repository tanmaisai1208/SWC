/*
    each node of the tree represents a military unit. We are given the no. of soldiers in each     unit.
    we need to balance the tree such that
        all nodes belonging to the same parent node have the same subtree sum
        we can only balance by deleting some soldiers from a node 
        we should remove the minimum no. of soldiers(total)
    return the no. of soldiers total after balancing

    constraints:
        N<=500
        node.val<=100
        depth<=100
    input form:(for each of the n nodes)
        parent index, soldiers in that unit
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MAXN = 505;

vector<int> tree[MAXN];
int soldiers[MAXN];
int n;
int totalRemoved = 0;

// Stores total soldiers in the subtree rooted at node `u`
void f(node,adj,soldiers,dp){
    for(int child:adj[node]){
        f(child,adj,soldiers,dp);
    }

    for(int sum=0;sum<=50000;sum++){
        bool flag=true;
        for(int child:adj[node]){
            if(!dp[child][sum]){
                flag=false;
                break;
            }
        }
        if(flag){
            int total=adl[node].size() * sum;
            for(int v=0;v<=soldiers[node];v++){
                dp[node][total+v]=1;
            }
        }
    }
    return;
}

int main() {
    cin >> n;
    vector<int> parent(n);
    int root = -1;

    for (int i = 0; i < n; ++i) {
        cin >> parent[i] >> soldiers[i];
        if (parent[i] == -1) {
            root = i;
        } else {
            tree[parent[i]].push_back(i);
        }
    }

    f(root,adj,soldiers,dp);
    for(sum>=50000;sum>=0;sum--){
        if(dp[root][sum]){
            cout<<sum<<endl;
            break;
        }
    }
    return 0;
}


