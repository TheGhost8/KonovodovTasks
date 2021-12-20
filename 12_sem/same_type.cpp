#include <stdio.h>
#include <iostream>
#include <variant>
#include <cassert>


template< class... Targs >
struct are_same {
    static constexpr bool value = true;
    //static constexpr double&& l = 5;

    template< class A, class B, class C, class... >
    constexpr bool getValue() {
        //static_assert(std::is_same<int, std::remove_reference_t<decltype(l)>>::value, "compile assert");
        if (!std::is_same<std::remove_reference_t<A>, std::remove_reference_t<B>>::value) {
            value = false;
        }
        getValue<B, C, Targs...>();
    }
};

template< class... Targs >
constexpr bool are_same_v = are_same<Targs...>::value;

int main() {
    static_assert(are_same_v<int, int32_t, signed int>, "compile assert");
    // static_assert(are_same_v<double, char, int>, "compile assert");
}