set(TYPEMAP_UNIT_TESTS typemap_tests)

include(CTest)

file(GLOB TARGET_SRC "./tests.cpp" )

add_executable(${TYPEMAP_UNIT_TESTS} ${TARGET_SRC})

add_test(${TYPEMAP_UNIT_TESTS} ${TYPEMAP_UNIT_TESTS})