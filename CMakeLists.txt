cmake_minimum_required(VERSION 3.8)

project(TEMTC)

# Especifica a pasta de build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if(NOT DEFINED ENV{VCPKG_ROOT})
    message(FATAL_ERROR "VCPKG_ROOT is not set. Please make sure it is defined.")
endif()

# Configuração do VCPKG
set(DCMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# Configuração do C++ para o projeto
set(CMAKE_CXX_STANDARD 20)

# Localiza a biblioteca dlib
# find_path(MLPACK_INCLUDE_DIRS "mlpack/mlpack.hpp")
find_package(OpenCV CONFIG REQUIRED)
find_package(OpenCV 4 REQUIRED)
find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")


# Adiciona os arquivos do código fonte
file(GLOB SOURCES_1 "src/method_1.cpp")
file(GLOB SOURCES_2 "src/method_2.cpp")
file(GLOB SOURCES_3 "src/method_3.cpp")
file(GLOB SOURCES_SPLIT "src/split.cpp")

file(GLOB KNN_SOURCES "src/knn.cpp")  # Adapte o caminho do diretório comum
file(GLOB KNN_HEADERS "src/knn.hpp")  # Adapte o caminho do diretório comum

file(GLOB COMMON_SOURCES "src/common.cpp")  # Adapte o caminho do diretório comum
file(GLOB COMMON_HEADERS "src/common.hpp")  # Adapte o caminho do diretório comum

# Cria o executável e vincula a biblioteca dlib
add_executable(method_1 ${SOURCES_1} ${COMMON_SOURCES} ${KNN_SOURCES})
target_link_libraries(method_1 PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann)
target_include_directories(method_1 PRIVATE ${RAPIDCSV_INCLUDE_DIRS})

add_executable(method_2 ${SOURCES_2} ${COMMON_SOURCES} ${KNN_SOURCES})
target_link_libraries(method_2 PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann)
target_include_directories(method_2 PRIVATE ${RAPIDCSV_INCLUDE_DIRS})

add_executable(method_3 ${SOURCES_3} ${COMMON_SOURCES} ${KNN_SOURCES})
target_link_libraries(method_3 PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann)
target_include_directories(method_3 PRIVATE ${RAPIDCSV_INCLUDE_DIRS})

add_executable(split ${SOURCES_SPLIT})
target_include_directories(split PRIVATE ${RAPIDCSV_INCLUDE_DIRS})