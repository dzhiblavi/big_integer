/*
    @author dzhiblavi
 */

#include "big_integer.hpp"
#include "vector.hpp"

int main() {
    big_integer a("100000000000000");
    big_integer b("100000000000000");
    std::cout << a * b << '\n';
    return 0;
}
