cmake_minimum_required(VERSION 3.10)

project(Perterpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_compile_definitions(STANDALONE)
include_directories(inc)

set(FLEXFILE src/lexer.l)
set(BISONFILE src/parser.y)

set(BISON bison)
set(FLEX flex)

if (UNIX)
message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
message("This is a Windows System")
endif()


set(YACC "${BISON} -v -g -d -t --color -Wall -o src/parser.cpp --defines=inc/parser.h ${BISONFILE}")
set(LEX "${FLEX} -o src/lexer.cpp ${FLEXFILE}")

add_custom_command(OUTPUT parser.cpp COMMAND ${YACC})
add_custom_command(OUTPUT lexer.cpp COMMAND ${LEX})


set(SOURCES src/ast.cpp
            src/symbol-table.cpp 
            src/perterpreter.cpp 
            src/parser.cpp 
            src/lexer.cpp 
            src/stringify.cpp 
            src/type-checker.cpp 
            src/synterr.cpp)


add_executable("perterpreter" ${SOURCES})

