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
const long long N = 2e5 + 5, M = 1e9 + 7, mod = 998244353, INF = 1e18, inf = INT_MAX;
int fx[] = {1, -1, 0, 0, 1, -1, 1, -1};
int fy[] = {0, 0, 1, -1, 1 , -1, -1, 1};
 
//Suffix Array and LCP
struct suffix{
    int index;
    int rank[2];
};
 
int cmp(struct suffix a, struct suffix b){
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
        (a.rank[0] < b.rank[0] ?1: 0);
}
 
vector<int> buildSuffixArray(string txt, int n){
    struct suffix suffixes[n];
    for (int i = 0; i < n; i++){
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }
    sort(suffixes, suffixes+n, cmp);
    int ind[n];
    for (int k = 4; k < 2*n; k = k*2){
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;
        for (int i = 1; i < n; i++){
            if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1]){
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else{
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }
        for (int i = 0; i < n; i++){
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?
                                suffixes[ind[nextindex]].rank[0]: -1;
        }
        sort(suffixes, suffixes+n, cmp);
    }
    vector<int>suffixArr;
    for (int i = 0; i < n; i++)
        suffixArr.push_back(suffixes[i].index);
    return suffixArr;
}
 
/* To construct and return LCP */
vector<int> kasai(string txt, vector<int> suffixArr){
    int n = suffixArr.size();
    vector<int> lcp(n, 0);
    vector<int> invSuff(n, 0);
    for (int i=0; i < n; i++)
        invSuff[suffixArr[i]] = i;
    int k = 0;
    for (int i=0; i<n; i++){
        if (invSuff[i] == n-1){
            k = 0;
            continue;
        }
        int j = suffixArr[invSuff[i]+1];
        while (i+k<n && j+k<n && txt[i+k]==txt[j+k])
            k++;
        lcp[invSuff[i]] = k;
        if (k>0)
            k--;
    }
    return lcp;
}
//vector<int>suffixArr = buildSuffixArray(s, s.length());
//vector<int>lcp = kasai(s, suffixArr);
 
 
 
void solve(){
    string s;
    cin >> s;
    int n = s.size();
    vector<int>suffixArr = buildSuffixArray(s, s.length());
    vector<int>lcp = kasai(s, suffixArr);
    
    int ans = 0, pos = 0;
    for(int i = 0; i < n; i++){
        if(lcp[i] > ans){
            ans = lcp[i];
            pos = i;
        }
    }
    if(ans == 0){
        cout << -1 << endl;
        return;
    }
    for(int i = suffixArr[pos]; i < suffixArr[pos] + ans; i++){
        cout << s[i];
    }
}
 
int32_t main()
{ 
    FASTIO
    TestCase{
        solve();
    }
    return 0;
}