#include "../include/type_map.h"

int main() {

    using map_t = typemap::Map<
        typemap::Pair<55, char>,
        typemap::Pair<22, float>,
        typemap::Pair<4, bool>
    >;

    static_assert(std::is_same_v<map_t::get<55>, char>, "Type map error");
    static_assert(std::is_same_v<map_t::get<22>, float>, "Type map error");
    static_assert(std::is_same_v<map_t::get<4>, bool>, "Type map error");

    // check unknown types
    static_assert(!std::is_same_v<map_t::get<78>, int>, "Type map error");
    static_assert(std::is_same_v<map_t::get<1048>, std::false_type>, "Type map error");

    return 0;
}
