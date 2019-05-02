/*
    @author dzhiblavi
 */

#include "big_integer.hpp"
#include "vector.hpp"

int main() {
    vector<size_t> a, b;
    for (size_t i = 0; i < 100; ++i) {
        a.push_back(i);
        b.push_back(2 * i);
    }
    a.swap(b);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}
