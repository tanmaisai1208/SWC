/*Q2. Given N tiles of given width and height, 
we have to select K out of it, we need to minimise 
the maximum of the difference between any two tiles selected,
 the difference between any two tiles is defined as
 the maximum of the height difference and width difference.*/
#include <bits/stdc++.h>
using namespace std;

struct Tile {
    int w, h;
};

bool check(vector<Tile> &tiles, int K, int D) {
    int N = tiles.size();

    for (int i = 0; i < N; i++) {

        vector<int> heights;

        // Collect all tiles whose width difference <= D
        for (int j = i; j < N && tiles[j].w - tiles[i].w <= D; j++)
            heights.push_back(tiles[j].h);

        if ((int)heights.size() < K)
            continue;

        sort(heights.begin(), heights.end());

        // Sliding window on heights
        int l = 0;
        for (int r = 0; r < (int)heights.size(); r++) {

            while (heights[r] - heights[l] > D)
                l++;

            if (r - l + 1 >= K)
                return true;
        }
    }

    return false;
}

int minimumDifference(vector<pair<int,int>> &arr, int K) {

    vector<Tile> tiles;

    for (auto &x : arr)
        tiles.push_back({x.first, x.second});

    sort(tiles.begin(), tiles.end(),
         [](Tile &a, Tile &b) {
             return a.w < b.w;
         });

    int low = 0, high = 0;

    for (auto &t : tiles)
        high = max(high, max(t.w, t.h));

    int ans = high;

    while (low <= high) {

        int mid = (low + high) / 2;

        if (check(tiles, K, mid)) {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }

    return ans;
}

int main() {

    vector<pair<int,int>> tiles = { };
    int K;
    cout << minimumDifference(tiles, K) << endl;

}
 
 /*
 #define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
using namespace std;
using ll = long long;
ll n, k;
vector<pair<ll, ll>> v;
// TC -> O(log(maxdiff)*(N*N*log(N)))-> N^2log(N)log(maxdiffs)
bool check(ll mid)
{
    int j = 0;
    ll cnt = 0;
    for (int i = 0; i < n; i++) // N
    {
        while (j < i && (v[i].first - v[j].first > mid))
        {
            j++;
        }

        if (i - j + 1 >= k) // mid 4 -> k = 3 //  1 3 6 6 6 6 12 //
        {
            vector<int> width;
            for (int index = j; index <= i; index++)
            {
                width.push_back(v[index].second);
            }
            sort(width.begin(), width.end()); // NlogN
            for (int i = 0; i + k - 1 < width.size(); i++)
            {
                if (width[i + k - 1] - width[i] <= mid)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
void solve()
{
    // first height, second is width
    cin >> n >> k;
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
    }
    sort(v.begin(), v.end());
    ll lo = 0, hi = 1e15;
    ll ans = -1;
    while (lo <= hi)
    {
        ll mid = (lo + hi) / 2;
        if (check(mid))
        {
            ans = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    cout << ans << "\n";
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
}
 */
