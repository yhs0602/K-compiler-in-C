CMAKE_MINIMUM_REQUIRED ( VERSION 3.7 )

project(KCompilerInC)


SET(SRC_FILES main.cpp lexer.cpp lexer.h parser.cpp parser.h)

ADD_EXECUTABLE( kcc.out ${SRC_FILES} )