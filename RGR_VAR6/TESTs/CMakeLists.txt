add_executable(run_tests run_tests.c test_cezar.c)

# Тестовое приложение зависит от библиотеки cezar_library
target_link_libraries(run_tests PRIVATE cezar_library)

# Добавляем путь к заголовочным файлам библиотеки cezar_library
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/cezar)

# Добавляем тест для ctest
add_test(NAME CezarTests COMMAND run_tests)