CMAKE_MINIMUM_REQUIRED ( VERSION 3.7 )

project(KCompilerInC)


SET(SRC_FILES main.c lexer.cpp lexer.h)

ADD_EXECUTABLE( kcc.out ${SRC_FILES} )