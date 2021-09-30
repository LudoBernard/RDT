project(RDT_TEST_LIB)


file(GLOB_RECURSE HEADER_FILES *.h)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_library(RDT_TEST_LIB STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(RDT_TEST_LIB RDT_LIB)
target_include_directories(RDT_TEST_LIB PUBLIC .)