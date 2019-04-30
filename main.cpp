/*
    @author dzhiblavi
 */

#include "big_integer.hpp"
#include "vector.hpp"

int main() {
    vector<size_t> a;
    for (size_t i = 0; i < 100; ++i) {
        a.push_back(i);
        for (size_t j = 0; j < a.size(); ++j)
            std::cout << a[j] << ' ' ;
        std::cout << '\n';
    }
    a.resize(1000);
    return 0;
}
