// A.M.D.G.
/*
this algorithm iterates through the array and checks if the number x has already appeared.
if so, it calculates the number of arrays formed by the numbers since the beginning of the subarray
up to the last occurrence of x.
in the end it does the same pretending there is another number at position n+1 with the same value as the nth number.
i tried to calculate it by adding ((n-i+1)*(n-i+2))/2 but it went completely wrong. no idea why but ok. maybe it was something related to integer overflow
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second
const ll m=1e9+7;
ll qtdarray(ll i, ll j, ll k){ // cálculo da qtd de subarrays 
    return ((j-i+1)*(j-i))/2 - ((j-k)*(j-k-1))/2;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    ll ans=0, x;
    map<ll, ll> mp; // ultima vez que apareceu no array
    ll n, i=1; cin>>n;
    for (ll j=1; j<=n; j++){
        cin>>x;
        if (mp[x]>=i){
            ans+=qtdarray(i, j, mp[x]);
            i=mp[x]+1;
        }
        mp[x]=j;
    }
    ans+=qtdarray(i, n+1, n);
    cout<<ans<<endl;
    return 0;
}
