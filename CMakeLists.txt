cmake_minimum_required (VERSION 3.5.1)

project (BRICK VERSION 1.0 LANGUAGES CXX)
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set (CMAKE_CXX_STANDARD 17)


set (CMAKE_CXX_FLAGS "-Wall -O3")
set (CMAKE_CXX_FLAGS_DEBUG "-Wall -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/Debug/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/Debug/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/Debug/bin")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/Release/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/Release/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/Release/bin")
set (TEST_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin")

SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
SET(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")

set (include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories (${include_dir})

set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/jars/antlr-4.7.1-complete.jar)

option (MAKE_TESTS "MAKE_TESTS" OFF)

include(ExternalAntlr4Cpp)

include_directories(${ANTLR4CPP_INCLUDE_DIRS})
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")
link_directories(${ANTLR4CPP_LIBS})
set(ANTLR4CPP_LIBS ${ANTLR4CPP_LIBS} PARENT_SCOPE)

antlr4cpp_process_grammar(algebra brick
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/Math.g4
  ""
)
# include generated files in project environment
include_directories(${antlr4cpp_include_dirs_brick})

# this block is one big terrible hack to deal with linking these grammar dependent sources on first cmake run
set (grammar_dependencies_unpathed MathBaseListener.cpp MathLexer.cpp MathListener.cpp
  MathParserGrammarBaseListener.cpp MathParserGrammar.cpp MathParserGrammarVisitor.cpp 
  MathBaseVisitor.cpp MathLexerGrammar.cpp MathParser.cpp MathParserGrammerBaseVisitor.cpp
  MathParserGrammarListener.cpp MathVisitor.cpp
)
set (grammar_dependencies)
foreach (grammar_dep ${grammar_dependencies_unpathed})
  list (APPEND grammar_dependencies ${ANTLR4CPP_GENERATED_SRC_DIR}/brick/${grammar_dep})
endforeach()
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src)
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src/brick)
foreach (gd ${grammar_dependencies})
  file (WRITE ${gd} "")
endforeach()

if (MAKE_TESTS)
    enable_testing()
    set (test_data_dir "${CMAKE_CURRENT_SOURCE_DIR}/test/data")
    set (test_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/test/include")
    add_subdirectory("./deps/googletest")
    add_subdirectory("./test")
endif()

add_subdirectory("./src")
