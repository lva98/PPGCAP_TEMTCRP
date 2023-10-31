cmake_minimum_required(VERSION 3.8)

project(TEMTC)

# Configuração do VCPKG
set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/.local/share/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("/home/leonardo/.local/share/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Configuração do C++ para o projeto
set(CMAKE_CXX_STANDARD 17)

# Localiza a biblioteca dlib
find_path(MLPACK_INCLUDE_DIRS "mlpack/mlpack.hpp")
find_package(OpenCV CONFIG REQUIRED)

# Adiciona os arquivos do código fonte
file(GLOB SOURCES "src/*.cpp")

# Cria o executável e vincula a biblioteca dlib
add_executable(main ${SOURCES})
target_include_directories(main PRIVATE ${MLPACK_INCLUDE_DIRS})
target_link_libraries(main PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann)