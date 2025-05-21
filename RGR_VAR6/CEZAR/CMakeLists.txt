# Сначала определяем библиотеку
add_library(cezar_library SHARED CEZAR.c)

# Теперь, когда cezar_library известна, можно добавить включаемые директории
# Добавляем наш заголовочный файл к включаемым директориям,
# чтобы другие цели могли найти cezar.h
target_include_directories(cezar_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Устанавливаем свойства для динамической библиотеки:
# RPATH позволяет найти библиотеку при запуске из директории сборки
set_target_properties(cezar_library PROPERTIES
    POSITION_INDEPENDENT_CODE ON # Эквивалент -fPIC
    # CXX_VISIBILITY_PRESET hidden # Это для C++, для C не нужно
    # GNUtoMS_EXTENSIONS OFF # Это тоже специфично для компиляторов, не обязательно
)

# Если вы хотите установить библиотеку в системные пути:
# install(TARGETS cezar_library DESTINATION lib)
# install(FILES cezar.h DESTINATION include)