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

const int numberOfSamples = 500000;    // テストケース数
const int numberOfCands = 10;   // 上位何件持つか

// 検索ログデータ構造
struct SearchLog {
    std::string word;
    int score;

    SearchLog()
    :   score(0)
    {}

    SearchLog(const std::string &word, int score)
    :   word(word), score(score)
    {}
};

std::ostream& operator<< ( std::ostream& out, const SearchLog& a )
{ std::cout << "SearchLog(" << a.word << ", " << a.score << ')'; return out; }


// テストケース
using TestCase = std::vector<SearchLog>;
// 検索候補 上位 10 件
using Candidates = std::vector<SearchLog>;
// Redis 用データ prefix(key): cands(value)
using RedisMap = std::map<std::string, Candidates>;

// See: https://algo-logic.info/trie-tree/
/* Trie 木： 文字の種類(char_size)、int型で0に対応する文字(base)
    insert(word): 単語 word を Trie 木に挿入する
    search(word): 単語 word が Trie 木にあるか判定する
    start_with(prefix):  prefix が一致する単語が Trie 木にあるか判定する
    count(): 挿入した単語の数を返す
    size(): Trie 木の頂点数を返す
    計算量：insert, search ともに O(M)（Mは単語の長さ）
*/
template <int char_size, int base>
struct Trie {
    struct Node {            // 頂点を表す構造体
        std::vector<int> next;    // 子の頂点番号を格納。存在しなければ-1
        std::vector<int> accept;  // 末端がこの頂点になる単語の word_id を保存
        int score;             // 検索ログ score
        Candidates cands; // この接頭辞に対応する検索候補上位 10 件
        int c;               // base からの間隔をint型で表現したもの
        int common;          // いくつの単語がこの頂点を共有しているか
        Node(int c_) : c(c_), common(0), score(0) {
            next.assign(char_size, -1);
        }
    };
    std::vector<Node> nodes;  // trie 木本体
    int root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }
    // 単語の挿入
    void insert(const std::string &word, int word_id, int score) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ追加
                next_id = (int)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id);
        nodes[node_id].score = score;
    }
    void insert(const std::string &word, int score) {
        insert(word, nodes[0].common, score);
    }
    // 単語とprefixの検索
    bool search(const std::string &word, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ終了
                return false;
            }
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }
    // prefix を持つ単語が存在するかの検索
    bool start_with(const std::string &prefix) {
        return search(prefix, true);
    }
    // 挿入した単語の数
    int count() const {
        return (nodes[0].common);
    }
    // Trie木のノード数
    int size() const {
        return ((int)nodes.size());
    }
};

TestCase makeTestCases() {
    TestCase tc;

    for (int i = 0; i < numberOfSamples; ++i ) {
        int length = rand() % 20;
        std::string word;

        for (int j = 0; j < length; ++j ) {
            word += char((rand() % 26) + 'a');
        }

        int score = rand() % 1000;

        tc.push_back(SearchLog(word, score));
    }

    return tc;
}

Trie<26, 'a'> trie;
TestCase tc = makeTestCases();

// 二つの候補をマージして全体で上位 10 件を返す
Candidates merge( const Candidates &c1, const Candidates &c2 ) {
    int p1 = 0, p2 = 0;

    Candidates ret;

    for (int i = 0; i < numberOfCands; ++i) {
        if (p1 == numberOfCands) {
            ret.push_back(c2[p2++]);
         
            continue;
        }
        if (p2 == numberOfCands) {
            ret.push_back(c1[p1++]);
         
            continue;
        }

        if (c1[p1].score > c2[p2].score) {
            ret.push_back(c1[p1++]);
        } else {
            ret.push_back(c2[p2++]);
        }
    }

    return ret;
}

// 各接頭辞の検索候補 上位 10 件を計算
Candidates dfs1( int v, int p = -1, const std::string &acc = "" ) {
    Candidates ret(10, SearchLog());

    ret[0] = SearchLog(acc, trie.nodes[v].score);

    for (int i = 0; i < 26; ++i ) {
        int node = trie.nodes[v].next[i];

        if( node == p )
            continue;
        if (node < 0)
            continue;

        ret = merge( ret, dfs1(node, v, acc + std::string(1, char('a' + i))) );
    }

    trie.nodes[v].cands = ret;

    if (ret.size() == 1)
        std::cout << ret << endl;

    return ret;
}

RedisMap redisMap;

// redis 用データ作成
void dfs2( int v, int p = -1, const std::string &acc = "" ) {
    redisMap[acc] = trie.nodes[v].cands;
    
    int count = 0;
    for (int i = 0; i < 26; ++i ) {
        int node = trie.nodes[v].next[i];

        if( node == p )
            continue;
        if (node < 0)
            continue;

        dfs2(node, v, acc + std::string(1, char('a' + i)));

        ++count;
    }

    return;
}

int main(int argc, char* argv[]) {
    bool verbose = false;

    if (argc > 1) {
        verbose = true;
    }

    for ( const SearchLog log : tc ) {
        trie.insert(log.word, log.score);

        if (verbose) {
            std::cout << log.word << ' ' << log.score << endl;
        }
    }

    std::cout << "trie constructed" << endl;
    
    dfs1(0);

    std::cout << "candidates constructed" << endl;

    // ↑ までの計算を feeder でする

    // Redis 用データ集計: RedisMap redisMap
    dfs2(0);

    std::cout << "redis data constructed" << endl;
    std::cout << "size: " << redisMap.size() << endl;

    // assertion (prefix に対応するリストになっているか，score の降順になっているか)
    itr(it, redisMap) {
        std::string prefix = it->first;
        Candidates cands = it->second;

        int score = 1ll<<30;

        for (SearchLog log : cands) {
            if ((log.word != "" && log.word.substr(0, prefix.size()) != prefix) || score < log.score) {
                std::cout << "Invalid!!!!" << endl;
            }

            score = log.score;
        }
    }

    if (verbose) {
        itr(it, redisMap) {
            std::cout << it->first << ": " << endl;
            std::cout << it->second << endl;
        }
    }

    return 0;
}