// In the name of Allah.
// We're nothing and you're everything.
// Ya MAALIK-UL-MULK!!!
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using namespace __gnu_pbds;
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
 
#define ll long long
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
struct custom_hash {
static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}
 
size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
}
};
 
ll binpow(ll a,ll b,ll m){ll res=1;while(b>0){if(b&1)res=(res*a)%m;a=(a*a)%m;b/=2;}return res;}
ll INV(ll x, ll m){x %= m;return binpow(x , m - 2, m);}
 
#define int   ll
#define pii   pair <int, int>
#define pll   pair <ll, ll>
#define vi    vector<int>
#define vl    vector<ll>
#define ump   unordered_map<ll,ll,custom_hash>
#define pqgi  priority_queue<int,vector<int>,greater<int>>
#define endl  '\n'
#define mk    make_pair
#define pb    push_back
#define ft    first
#define sd    second
#define TestCase    int TT=1;for(int zz=1;zz<=TT;zz++)
#define FASTIO  ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define all(a)   a.begin(),a.end()
#define FOR(i,a,b)  for(int i=a;i<b;i++)
#define FORN(i,a,b)  for(int i=b-1;i>=a;i--)
#define rep(i,a,b)  for(int i=a;i<=b;i++)
#define rev(i,a,b)  for(int i=b;i>=a;i--)
#define fs(val,y)   fixed<<setprecision(y)<<val
const long long N = 5005, M = 1e9 + 7, mod = 998244353, INF = 1e18, inf = INT_MAX;
int fx[] = {1, -1, 0, 0, 1, -1, 1, -1};
int fy[] = {0, 0, 1, -1, 1 , -1, -1, 1};
 
 
pii fun(string &s){
    int u = 0, v = 0;
    for(int i = 0; i < (int)s.size(); i++){
        u = u*26 + s[i] - 'a' + 1;
        v = v*26 + s[i] - 'a' + 1;
        u %= M;
        v %= mod;
    }
    return {u,v};
}
 
void solve(){
    string s;
    cin >> s;
    int n = s.size();
    
    int k;
    cin >> k;
    vector < vector < pii > > words(n+2);
    while(k--){
        string w;
        cin >> w;
        auto v = fun(w);
        words[(int)w.size()].pb(v);
    } 
    for(int i = 1; i <= n; i++) sort(all(words[i]));
    
    s = "#" + s;
    vector < pii > hsh(n+2);
    for(int i = 1; i <= n; i++){
        hsh[i].ft = hsh[i-1].ft*26 + s[i] - 'a' + 1;
        hsh[i].sd = hsh[i-1].sd*26 + s[i] - 'a' + 1;
        hsh[i].ft %= M;
        hsh[i].sd %= mod;
    }
    
    vi p26M(n+2), p26mod(n+2);
    p26M[0] = p26mod[0] = 1;
    for(int i = 1; i <= n; i++){
        p26M[i] = (p26M[i-1] * 26) % M;
        p26mod[i] = (p26mod[i-1] * 26) % mod;
    }
 
    vi dp(n + 2);
    dp[0] = 1;
    for(int i = 0; i <= n; i++){
        for(int len = 1; len <= n; len++){
            if(i + len > n) break;
            int u = (hsh[i].ft * p26M[len]) % M;
            int v = (hsh[i].sd * p26mod[len]) % mod;
            u = (hsh[i+len].ft - u + M) % M;
            v = (hsh[i+len].sd - v + mod) % mod;
            pii x = {u, v};
            auto it = lower_bound(all(words[len]), x);
            if(it != words[len].end() && (*it) == x){
                dp[i + len] = (dp[i + len] + dp[i]) % M;
            }
        }
    }
    cout << dp[n] << endl;
}
 
int32_t main()
{ 
    FASTIO
    TestCase{
        solve();
    }
    return 0;
}