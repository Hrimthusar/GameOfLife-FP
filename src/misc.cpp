#include "misc.hpp"
#include <range/v3/algorithm/is_sorted.hpp>
#include <vector>
#include <iostream>

namespace misc
{
    void test_range()
    {
        std::cout << std::boolalpha;
        std::vector<int> v{1, 2, 3, 4, 5, 6};
        std::cout << "vector:   " << ranges::is_sorted(v) << '\n';

        std::array<int, 6> a{6, 2, 3, 4, 5, 6};
        std::cout << "array:    " << ranges::is_sorted(a) << '\n';
    }

    int meaning_of_life()
    {
        return 42;
    }
}
