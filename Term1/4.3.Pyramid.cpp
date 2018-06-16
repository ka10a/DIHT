    #include <bits/stdc++.h>

    using namespace std;

    void count_ans(vector<vector<long long int> >& dp, int blocks, int limit) {
        dp[blocks][limit] = 0;
        if (blocks == 0)
            return;
        if (blocks < limit) {
            dp[blocks][limit]= 1;
        }
        if (blocks <= 2) {
            return;
        }

        for (int now_blocks = 1; now_blocks < min(limit, blocks); ++now_blocks) {
            if (dp[blocks - now_blocks][now_blocks] == -1)
                count_ans(dp, blocks - now_blocks, now_blocks);
            dp[blocks][limit] += dp[blocks - now_blocks][now_blocks];
        }
    }

    int main() {
        int blocks;
        cin >> blocks;

        vector <vector<long long int> > dp(blocks + 1, vector<long long int> (blocks + 2, -1));
        count_ans(dp, blocks, blocks + 1);

        cout << dp[blocks][blocks + 1] << endl;

        return 0;
    }
