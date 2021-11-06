# ==========================================
#            Various definitions
# ==========================================

cmake_minimum_required(VERSION 3.15)
project(nasapi-cpp VERSION 1.0.0 LANGUAGES CXX)

#Verbose option
set(CMAKE_VERBOSE_MAKEFILE OFF)

#Test option
option(ENABLE_TESTS "Build tests along with the library" ON)


set(SOURCE_ROOT "${PROJECT_SOURCE_DIR}/src")
set(EXC_TST "${PROJECT_SOURCE_DIR}/build")
set(SOURCE_ROOT "${PROJECT_SOURCE_DIR}/src")
set(EXC_TST "${PROJECT_SOURCE_DIR}/build")
set(CXX_FLAGS -Wextra -Werror -pedantic -std=c++17)
set(LDFLAGS -lcrypto -lssl -ldl -lboost_system -lboost_thread -lboost_filesystem -ljsoncpp -lpthread)

include_directories(
        "includes/"
        "/usr/include/openssl"
        "/usr/include/boost"
        ${JSONC_INCLUDE_DIRS}
)

# ==========================================
#             Libraries
# ==========================================

# The name of all the libs in the project.
# If you want to add a lib, add its name to this variable
set(LIBS
        client
        logger
        query
        )

# Client
file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Client/*.cpp")
add_library(client STATIC ${CLIENT_SOURCES})
target_compile_options(client PRIVATE ${CXX_FLAGS})

# Logger
file(GLOB_RECURSE LOGGER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Logger/*.cpp")
add_library(logger STATIC ${LOGGER_SOURCES})
target_compile_options(logger PRIVATE ${CXX_FLAGS})

# Query
file(GLOB_RECURSE QUERY_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/Query/*.cpp")
add_library(query STATIC ${QUERY_SOURCES})
target_compile_options(query PRIVATE ${CXX_FLAGS})

find_package(OpenSSL REQUIRED)
link_libraries(${OPENSSL_LIBRARIES})

find_package(Boost REQUIRED COMPONENTS system program_options)

set(BOOST_LIBRARIES Boost::system Boost::program_options ${CMAKE_DL_LIBS})
find_package(PkgConfig)
pkg_check_modules(JSONC REQUIRED json-c)


# ==========================================
#             Test executables
# ==========================================

if (ENABLE_TESTS)
    include (CTest)

    ######Lib2
    ####file(GLOB_RECURSE#LIB2_TESTS#RELATIVE#${CMAKE_SOURCE_DIR}
    ########"tests/unit_tests/lib2/*.c")
    ####add_executable(lib2_unit#${LIB2_TESTS})
    ####target_compile_options(lib2_unit#PRIVATE#${CFLAGS})
    ####target_link_libraries(lib2_unit#PRIVATE#lib2#lib1)
    ####target_link_options(lib2_unit#PRIVATE#${LDFLAGS_TEST})
    ####add_test(NAME#lib2_unit#COMMAND#${EXC_TST}/lib2_unit)

endif()

# ==========================================
#           Final executable
# ==========================================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(nasapi-cpp src/main.cpp)
target_link_libraries(nasapi-cpp PRIVATE ${LDFLAGS} ${JSONC_LIBRARIES} ${OPENSSL_LIBRARIES} ${BOOST_LIBRAIRIES} ${LIBS}) # you can add other librairies path if necessary
target_compile_options(nasapi-cpp PRIVATE ${CXX_FLAGS} ${LDFLAGS})