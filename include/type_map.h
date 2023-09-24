#pragma once

#include <type_traits>

namespace typemap {

    namespace detail {

        template<auto key, typename ... pairs>
        struct KeyFinder;

        template<auto key, typename pair_t>
        struct KeyFinder<key, pair_t> {
            using type = typename std::conditional<key == pair_t::key, typename pair_t::type, std::false_type>::type;
        };

        template<auto key, typename pair1_t, typename ... pairs_rest>
        struct KeyFinder<key, pair1_t, pairs_rest...> {
            using type = typename std::conditional<key == pair1_t::key, typename pair1_t::type, typename KeyFinder<key, pairs_rest...>::type>::type;
        };

    } // namespace detail

    template<auto _key, typename _type>
    struct Pair {
        static constexpr auto key = _key;
        using type = _type;
    };


    template<typename ... pairs>
    struct Map {
        template<auto key>
        using get = typename detail::KeyFinder<key, pairs...>::type;
    };

} // namespace typemap
