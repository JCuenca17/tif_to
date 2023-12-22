cmake_minimum_required(VERSION 3.6.0)
project(Tetris VERSION 0.1.0 LANGUAGES CXX)

include_directories(include)

# Colocar la ruta de la biblioteca deacuerdo con su sistema
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

add_executable(ADNeroids 
    main.cpp
    Entity.h
    Game.h
    Game.cpp
    Fisicas.h
    Fisicas.cpp
    Jugador.h
    Jugador.cpp
    Proyectil.h
    Proyectil.cpp
    BaseNitrogenada.h
    BaseNitrogenada.cpp
    Bases.h
    Global.h)

target_include_directories(ADNeroids PUBLIC include)

target_link_libraries(ADNeroids PUBLIC sfml-graphics)


# Copiar DLLs a la carpeta de salida
add_custom_command(TARGET ADNeroids POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "C:/SFML-2.6.1/bin"
                   $<TARGET_FILE_DIR:ADNeroids>)
                