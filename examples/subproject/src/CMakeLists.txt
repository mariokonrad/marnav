set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(marnav-demo main.cpp)
target_link_libraries(marnav-demo PRIVATE marnav::marnav)
