find_package(Catch2 CONFIG REQUIRED)

add_executable(tests test.cpp)

target_link_libraries(tests PRIVATE ChessedGame Catch2::Catch2)