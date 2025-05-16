/*
A.M.D.G.
segtree with lazy propagation (ranges update queries - cses)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <cstring>
#define ll long long
#define f first
#define s second
using namespace std;
ll arr[200000];
ll segtree[800005];
ll lz[800005];
void build(int l, int r, int node){ // building the segtree
    if (l>r) return;
    lz[node]=0;
    if (l==r){
        segtree[node]=arr[l];
        return;
    }
    int mid=(l+r)/2;
    build(l, mid, 2*node+1);
    build(mid+1, r, 2*node+2);
    segtree[node]=segtree[2*node+1]+segtree[2*node+2];
}
void unlazy(int l, int r, int node){
    if (lz[node]==0) return;
    segtree[node]+=lz[node]*(r-l+1);
    if (l!=r){ // if the node has children, its lz value will be passed to them
        lz[2*node+1]+=lz[node];
        lz[2*node+2]+=lz[node];
    }
    lz[node]=0;
}
void upd(int l, int r, int cl, int cr, int node, ll v){
    if (cl>cr || cl>r || cr<l) return; // out of range
    unlazy(cl, cr, node);
    if (l<=cl && cr<=r){ // completely contained in the range
        lz[node]+=v;
        unlazy(cl, cr, node);
        return;
    }
    int mid=(cl+cr)/2;
    upd(l, r, cl, mid, 2*node+1, v); // update its children
    upd(l, r, mid+1, cr, 2*node+2, v);
    segtree[node]=segtree[2*node+1]+segtree[2*node+2]; // update the values in the segtree bottom-up
}
ll query(int idx, int l, int r, int node){
    if (l>r || r<idx || l>idx) return 0;
    unlazy(l, r, node);
    if (l==r && l==idx) return segtree[node]; // we have found the index
    int mid=(l+r)/2;
    if (l<=idx && idx<=mid) return query(idx, l, mid, 2*node+1); // idx is within range [left, mid]
    else return query(idx, mid+1, r, 2*node+2); // idx is within range [mid+1, right]
}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    ll u;
    int n, q, op, a, b, k;
    cin>>n>>q;
    for (int i=0; i<n; i++) cin>>arr[i];
    build(0, n-1, 0);
    for (int i=0; i<q; i++){
        cin>>op;
        if (op==1){
            cin>>a>>b>>u;
            upd(a-1, b-1, 0, n-1, 0, u);
        }
        else{
            cin>>k;
            cout << query(k-1, 0, n-1, 0) << endl;
        }
    }
    return 0;
}
