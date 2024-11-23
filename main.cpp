#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;

ll n;

pair<ll, ll> Add(ll p, ll q, ll x, ll y) {
  auto np = p * y + x * q;
  auto nq = q * y;

  const auto& d = gcd(np, nq);

  return {np / d, nq / d};
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ll t = 1;
  while (true) {
    cin >> n;
    if (n == 0) break;

    ll p = 0;
    ll q = 1;

    for (auto i = 0; i < n; ++i) {
      string s;
      cin >> s;

      const auto& cm = s.find(',');
      const auto& sl = s.find('/');

      if (sl == s.npos) {
        auto iss = istringstream{s};
        ll w;
        iss >> w;

        const auto& [np, nq] = Add(p, q, w, 1);
        p = np;
        q = nq;

        continue;
      }

      if (cm == s.npos) {
        auto iss = istringstream{s.substr(0, sl)};
        ll x;
        iss >> x;

        iss = istringstream{s.substr(sl + 1)};
        ll y;
        iss >> y;

        const auto& [np, nq] = Add(p, q, x, y);
        p = np;
        q = nq;

        continue;
      }

      if (cm != s.npos) {
        auto iss = istringstream{s.substr(0, cm)};
        ll w;
        iss >> w;

        iss = istringstream{s.substr(cm + 1, sl - cm)};
        ll x;
        iss >> x;

        iss = istringstream{s.substr(sl + 1)};
        ll y;
        iss >> y;

        const auto& [np, nq] = Add(p, q, w * y + x, y);
        p = np;
        q = nq;

        continue;
      }
    }

    cout << "Test " << t << ": ";
    if (0 == p) {
      cout << "0";
    } else {
      const auto& w = p / q;
      p -= w * q;
      if (w > 0) {
        cout << w;
        if (p != 0) {
          cout << ",";
        }
      }

      if (p > 0) {
        cout << p << "/" << q;
      }
    }

    cout << '\n';
    ++t;
  }

  return 0;
}