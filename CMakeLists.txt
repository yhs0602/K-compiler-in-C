CMAKE_MINIMUM_REQUIRED ( VERSION 3.7 )
set (CMAKE_CXX_STANDARD 17)

project(KCompilerInC)


SET(SRC_FILES main.cpp lexer.cpp lexer.h parser.cpp parser.h)

ADD_EXECUTABLE( kcc.out ${SRC_FILES} )