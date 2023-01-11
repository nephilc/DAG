#add_subdirectory(src)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(main ${SOURCE_FILES})
target_include_directories(main PUBLIC ./include)
target_link_libraries(
  main
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main)