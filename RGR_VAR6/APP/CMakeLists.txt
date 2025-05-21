add_executable(cezar_app main.c)

# Указываем, что наше приложение зависит от библиотеки cezar_library
# target_link_libraries автоматически добавит правильные флаги линковки и RPATH, если настроено
target_link_libraries(cezar_app PRIVATE cezar_library)

# Добавляем путь к заголовочным файлам библиотеки cezar_library
target_include_directories(cezar_app PRIVATE ${CMAKE_SOURCE_DIR}/cezar)
