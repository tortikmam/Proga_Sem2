cmake_minimum_required(VERSION 3.10)
project(CEZAR_Project C)

# Устанавливаем стандарт C11 и включаем предупреждения
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Добавляем поддиректории
add_subdirectory(CEZAR)
add_subdirectory(APP)
add_subdirectory(TESTs)

# Добавляем возможность запускать тесты с помощью `make test` или `ctest`
enable_testing()