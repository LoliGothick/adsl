#include <cstdint>
#include <algorithm>
#include <string>
#include <iostream>
#include "adsl/segtree/lazy_segtree.hpp"

#include <optional>
#include <limits>

using i32 = std::int32_t;
using u32 = std::uint32_t;

constexpr i32 Inf = std::numeric_limits<i32>::max();

int main() {
    int n, q;
    std::cin >> n >> q;

    using O = adsl::make_monoid<std::optional<i32>, std::nullopt, [](auto&& x, auto&& y) { return (y ? y : x); }, true>;
    using M = adsl::make_monoid<i32, Inf, [](i32 x, i32 y) { return std::min(x, y); }, true>;
    using Act = adsl::make_action<O, M, [](auto&& p, i32 x) { return (p ? *p : x); }>;

    adsl::lazy_segtree<Act> seg{static_cast<size_t>(n)};

    for (int i = 0; i < q; ++i) {
        i32 k, s, t;
        std::cin >> k >> s >> t;
        ++t;

        if (k == 0) {
            i32 x;
            std::cin >> x;

            seg.append(s, t, x);
        }
        else
            std::cout << *seg.accumulate(s, t) << std::endl;
    }
}