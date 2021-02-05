FIND_PACKAGE(Catch2 REQUIRED)

ADD_EXECUTABLE(tests test.cpp)

TARGET_LINK_LIBRARIES(tests ChessedGame Catch2::Catch2)