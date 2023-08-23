const int MAXN = 2e5 + 4;
vector<int> g[MAXN];
bool vis[MAXN];
int tim;
int beg[MAXN];
int ind[MAXN];
int tour[MAXN];
int lev[MAXN];

void init(int n) {
    tim = 1;
    for (int i = 0; i <= 2 * n + 2; i++) {
        vis[i] = false;
        g[i].clear();
        beg[i] = 0;
        ind[i] = 0;
        tour[i] = 0;
        lev[i] = 0;
    }
}

//create an euler tourof the tree having the level of each element as the array element
void dfs(int s) {
    vis[s] = true;
    beg[s] = tim;
    tour[tim] = lev[s];
    tim++;

    for (auto x : g[s])
        if (!vis[x]) { // if it is unvisited 
            lev[x] = lev[s] + 1;
            dfs(x);
        }

    ind[s] = tim;
    tour[tim] = lev[s];
    tim++;
}

class Solution {
  public:
    vector<int> solve(int N, int Q, vector<vector<int> > &Edge,
                      vector<vector<int> > &query) {
        // initialize and clear all the vector and variable
        init(N);
        
        // build graph
        for (auto it : Edge) {
            g[it[0]].push_back(it[1]);
            g[it[1]].push_back(it[0]);
        }
        tim = 1;
        dfs(0);

        vector<int> pref(tim + 1), suf(tim + 1);
        for (int i = 1; i < tim; i++) {
            pref[i] = max(pref[i - 1], tour[i]);
        }
        for (int i = tim - 1; i >= 1; i--) {
            suf[i] = max(suf[i + 1], tour[i]);
        }

        vector<int> answer(Q);
        
       // check maximum of some prefix and suffix to answer the query.
        for (int i = 0; i < Q; i++) {
            int node = query[i][0];
            if (lev[query[i][1]] > lev[query[i][0]]) node = query[i][1];

            answer[i] = max(pref[beg[node] - 1], suf[ind[node] + 1]);
        }
        return answer;
    }
};