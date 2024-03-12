# TypeMap

Compile-time link types to key

## Exemple

```cpp
// define the type map
using map_t = typemap::Map<
    typemap::Pair<789, int>, // link the key 789 to the type int
    typemap::Pair<12, bool>, // link the key 12 to the type bool
    typemap::Pair<45, float> // link the key 45 to the type float
>;

// retrieve the types
map_t::get<789> i = 4;
map_t::get<12> b = true;
map_t::get<45> f = 951.2f;

// calling get on an undefined key will compile and return an std::false_type
map_t::get<1> w;

```
