/*Fast Xor of every pair using fast walsh-hadamard transform (v contains the count of pairs with given xor)*/

#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define ll long long
 
template<class T> ostream& operator<<(ostream &os,vector<T> V){
	os<<"[ ";for(auto v:V)os<<v<<" ";return os<<" ]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
	return os<<"("<<P.first<<","<<P.second<<")";
}
ll mxm(){return LLONG_MIN;}
template<typename... Args>
ll mxm(ll a,Args... args){return max(a,mxm(args...));}
ll mnm(){return LLONG_MAX;}
template<typename... Args>
ll mnm(ll a,Args... args){return min(a,mnm(args...));}
 
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__,__VA_ARGS__)
template<typename Arg1>
void __f(const char* name,Arg1&& arg1){
	cout<<name<<" : "<<arg1<<endl;
}
template<typename Arg1,typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
		const char* comma=strchr(names+1,',');cout.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
#else
#define trace(...) 1
#endif
 
#define ld long double
#define vll vector<ll>
#define pll pair<ll,ll>
#define ii pair<int,int>
#define vi vector<int>
#define vpll vector<pll>
#define vii vector<ii>
#define vvi vector<vi>
#define vvll vector<vll>
#define vvpll vector<vpll>
#define vvii vector<vii>
#define vld vector<ld>
#define vvld vector<vld>
#define I insert
#define F first
#define S second
#define pb push_back
#define all(x) x.begin(),x.end()
#define endl "\n"
#define siz(a)	((int)(a).size())
 
const int mod=1e9+7;
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}
 
const int N=1e5+5;
void FWHT(vll &P, bool inverse) {
    int d=P.size();
    for (int len = 1; 2 * len <= d; len <<= 1) {
        for (int i = 0; i < d; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = P[i + j];
                ll v = P[i + len + j];
                P[i + j] = u + v;
                P[i + len + j] = u - v;
            }
        }
    }
    // for(int i=0;i<d;i++)P[i]*=P[i];
    if (inverse) {
        for (int i = 0; i < d; i++)
            P[i] = P[i] / d;
    }
 
}
vvii adj(N);
vi val(N),vis(N),cnt(3*N);
void dfs(int i){
	vis[i]=1;
	cnt[val[i]]++;
	for(auto j:adj[i]){
		if(vis[j.F])continue;
		val[j.F]=val[i]^j.S;
		dfs(j.F);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	const int lim=1<<18;
	int n;cin>>n;
	for(int i=0;i<n-1;i++){
		int u,v,w;cin>>u>>v>>w;adj[u].pb({v,w});adj[v].pb({u,w});
	}
	dfs(1);
	vll v(lim);for(int i=0;i<lim;i++)v[i]=cnt[i];
	FWHT(v,0);
	for(int i=0;i<lim;i++)v[i]*=v[i];
	FWHT(v,1);
	for(int i=0;i<lim;i++)v[i]%=mod;
	int ans=0;
	for(int i=0;i<lim;i++){
		ans=add(ans,mul(v[i],v[i]));
		for(int j=0;j<18;j++){
			if(!(i&(1<<j)))continue;
			ans=add(ans,mul(mul(2,v[i]),v[i^(1<<j)]));
		}
	}
	cout<<ans<<endl;
}