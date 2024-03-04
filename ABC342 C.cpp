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
using P = std::pair<char, char>;

constexpr ll INF = 1ll<<60;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<class S, class T>
std::ostream& operator<< ( std::ostream& out, const std::pair<S,T>& a )
{ std::cout << '(' << a.first << ", " << a.second << ')'; return out; }

template<class T>
std::ostream &operator<< ( std::ostream& out, const std::vector<T>& a )
{ std::cout << '['; rep( i, a.size() ){ std::cout << a[i]; if( i != a.size()-1 ) std::cout << ", "; } std::cout << ']'; return out; }

ll N;
std::string S;
ll Q;
std::map<char, char> chMap;
std::map<char, std::vector<char>> nvChMap;
bool tused[1000], fused[1000];

int main() {
    std::cin >> N >> S >> Q;

    rep( q, Q ) {
        std::string cS, dS;

        std::cin >> cS >> dS;

        char c = cS[0], d = dS[0];

        std::map<char, char> newChMap;

        itr (it, chMap) {
            if (it->second == c) {
                newChMap[it->first] = d;
            } else {
                newChMap[it->first] = it->second;
            }
        }

        if (!newChMap.count(c)) {
            newChMap[c] = d;
        }

        chMap = newChMap;
    }

    rep( i, S.size() ) {
        if (chMap.count(S[i])) {
            std::cout << chMap[S[i]];
        } else {
            std::cout << S[i];
        }
    }

    std::cout << endl;

    return 0;
}