/*Q2. Given N tiles of given width and height, 
we have to select K out of it, we need to minimise 
the maximum of the difference between any two tiles selected,
 the difference between any two tiles is defined as
 the maximum of the height difference and width difference.*/

 #include <iostream>
 #include <vector>
 
 
 using namespace std;
 
 
 typedef long long ll;
 #define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
 
 
 void solve() {
     int n, k;
     cin >> n >> k;
    
     vector<vector<int>> freq(401, vector<int>(401, 0));
    
     for (int i = 0; i < n; i++) {
         int x, y;
         cin >> x >> y;
         freq[x][y]++;
     }
    
     for (int i = 0; i < 401; i++) {
         for (int j = 0; j < 401; j++) {
             if (i > 0) freq[i][j] += freq[i - 1][j];
             if (j > 0) freq[i][j] += freq[i][j - 1];
             if (i > 0 && j > 0) freq[i][j] -= freq[i - 1][j - 1];
         }
     }
    
     int low = 0, high = 400, ans = 400;
    
     auto isValid = [&](int mid) {
         for (int i = 0; i + mid < 401; i++) {
             for (int j = 0; j + mid < 401; j++) {
                 int cnt = freq[i + mid][j + mid];
                 if (i > 0) cnt -= freq[i - 1][j + mid];
                 if (j > 0) cnt -= freq[i + mid][j - 1];
                 if (i > 0 && j > 0) cnt += freq[i - 1][j - 1];
                 if (cnt >= k) return true;
             }
         }
         return false;
     };
    
     while (low <= high) {
         int mid = (low + high) / 2;
         if (isValid(mid)) {
             ans = mid;
             high = mid - 1;
         } else {
             low = mid + 1;
         }
     }
    
     cout << ans << "\n";
 }
 
 
 int main() {
     fastio;
     solve();
     return 0;
 }
 
#include <bits/stdc++.h>
using namespace std;

struct Tile {
    int h, w;
    Tile(int h, int w) : h(h), w(w) {}
};

bool compare(const Tile& a, const Tile& b) {
    if (a.h == b.h) return a.w < b.w;
    return a.h < b.h;
}

bool canSelect(vector<Tile>& tiles, int k, int diff) {
    int n = tiles.size();
    int count = 1;
    int start = 0;

    for (int end = 1; end < n; end++) {
        while (max(tiles[end].h - tiles[start].h, tiles[end].w - tiles[start].w) > diff) {
            start++;
        }
        if (end - start + 1 >= k) {
            return true;
        }
    }
    return false;
}

int minMaxDifference(vector<int>& height, vector<int>& width, int n, int k) {
    vector<Tile> tiles;
    for (int i = 0; i < n; i++) {
        tiles.push_back(Tile(height[i], width[i]));
    }

    sort(tiles.begin(), tiles.end(), compare);

    int low = 0;
    int high = max(*max_element(height.begin(), height.end()) - *min_element(height.begin(), height.end()),
                  *max_element(width.begin(), width.end()) - *min_element(width.begin(), width.end()));

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canSelect(tiles, k, mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> height(n), width(n);
    for (int i = 0; i < n; i++) {
        cin >> height[i] >> width[i];
    }

    cout << minMaxDifference(height, width, n, k) << endl;
    return 0;
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