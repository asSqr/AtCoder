#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#define repi(i,a,b) for(ll i=(a);i<(b);++i)
#define rep(i,a) repi(i,0,a)
#define repdi(i,a,b) for(ll i=(a)-1;i>=(b);--i)
#define repd(i,a) repdi(i,a,0)
#define itr(it,a) for( auto it = (a).begin(); it != (a).end(); ++it )
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define endl '\n'
#define debug(x) std::cerr << #x << " = " << (x) << endl;

using ll = long long;
using P = std::pair<ll, ll>;

constexpr ll INF = 1ll<<60;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<class S, class T>
std::ostream& operator<< ( std::ostream& out, const std::pair<S,T>& a )
{ std::cout << '(' << a.first << ", " << a.second << ')'; return out; }

template<class T>
std::ostream &operator<< ( std::ostream& out, const std::vector<T>& a )
{ std::cout << '['; rep( i, a.size() ){ std::cout << a[i]; if( i != a.size()-1 ) std::cout << ", "; } std::cout << ']'; return out; }

ll N, Q, X;
ll W[200010], SW[200010];

ll sum(ll l, ll cnt) {
    ll ret = 0;
    ll r = l + cnt;

    ret -= SW[l];

    if( r > N ) {
        ret += SW[r % N] + SW[N];
    } else {
        ret += SW[r];
    }

    return ret;
}

bool used[200010];

ll binary_search(ll p, ll w) {
    ll lb = 0, ub = N;

    while( ub - lb > 1 ) {
        ll mid = (lb + ub) >> 1;

        if( sum(p, mid) < w ) {
            lb = mid;
        } else {
            ub = mid;
        }
    }

    return ub;
}

std::vector<ll> ans;
std::map<ll, ll> mp;

int main() {
    std::cin >> N >> Q >> X;
    rep( i, N ) {
        std::cin >> W[i];
        SW[i+1] += SW[i] + W[i];
    }

    ll p = 0;
    ll all = SW[N];

    while( !used[p] ) {
        ll cnt = X / all * N;
        ll rest = X % all;
        
        ll ncnt = binary_search(p, rest);

        if( !rest )
            ncnt = 0;

        cnt += ncnt;

        ll nextP = (p + ncnt) % N;

        mp[p] = ans.size();
        ans.emplace_back(cnt);
        used[p] = true;

        p = nextP;
    }

    ll beg = mp[p];
    ll len = ans.size() - beg;

    rep( q, Q ) {
        ll K;
        std::cin >> K;
        --K;

        if( K >= ans.size() ) {
            K -= beg;
            K %= len;
            K += beg;

            std::cout << ans[K] << endl;
        } else {
            std::cout << ans[K] << endl;
        }
    }

    return 0;
}