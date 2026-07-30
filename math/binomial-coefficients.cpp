// A.M.D.G.
// problem from cses
/* basically it works like this:
in order to calculate large combinations, you need to use divisions with mod.
thus, we need to use something called MODULAR INVERSE.
a modular inverse of a%m is x such that (a*x)%m = 1. 
instead of calculating (a/b)%m, we do (a*(modular inverse of b))%m. in regular division,
it's the equivalent of doing a*(b⁻¹) instead of a/b
btw it's possible to multiplicate modular inverses successively to get the appropriate denominator
I used arrays to store all factorials and their modular inverses from 0 to 1000000
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll m=1e9+7;
ll invmod(int n){
    return n<=1 ? n : m-(ll)(m/n)*invmod(m%n)%m;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    vector<ll> fatorial(1000001);
    vector<ll> invfatorial(1000001);
    int n, a, b;
    fatorial[0]=1; fatorial[1]=1;
    invfatorial[0]=m+1; invfatorial[1]=m+1;
    for (int i=2; i<=1000000; i++){
        fatorial[i]=(fatorial[i-1]*i)%m;
        invfatorial[i]=(invfatorial[i-1]*invmod(i))%m;
    }
    cin>>n;
    for (int i=0; i<n; i++){
        cin>>a>>b;
        cout<<(((fatorial[a]*invfatorial[b])%m)*invfatorial[a-b])%m<<endl;
    }
    return 0;
}
