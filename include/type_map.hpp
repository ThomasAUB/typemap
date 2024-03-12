/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                     *
 *                                                                                 *
 * Copyright (c) 2023 Thomas AUBERT                                                *
 *                                                                                 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy    *
 * of this software and associated documentation files (the "Software"), to deal   *
 * in the Software without restriction, including without limitation the rights    *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is           *
 * furnished to do so, subject to the following conditions:                        *
 *                                                                                 *
 * The above copyright notice and this permission notice shall be included in all  *
 * copies or substantial portions of the Software.                                 *
 *                                                                                 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
 * SOFTWARE.                                                                       *
 *                                                                                 *
 * github : https://github.com/ThomasAUB/TypeMap/tree/main                         *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include <type_traits>

namespace typemap {

    namespace detail {

        template<auto key, typename ... pairs> struct KeyFinder;

        template<auto key, typename pair_t>
        struct KeyFinder<key, pair_t> {
            using type =
                typename std::conditional<
                key == pair_t::key,
                typename pair_t::type,
                std::false_type
                >::type;
        };

        template<auto key, typename pair1_t, typename ... pairs_rest>
        struct KeyFinder<key, pair1_t, pairs_rest...> {
            using type =
                typename std::conditional<
                key == pair1_t::key,
                typename pair1_t::type,
                typename KeyFinder<key, pairs_rest...>::type
                >::type;
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
