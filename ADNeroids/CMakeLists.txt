cmake_minimum_required(VERSION 3.6.0)
project(ADNeroids VERSION 0.1.0 LANGUAGES CXX)

# Lista de archivos fuente
set(SOURCES
    main.cpp
    Game.cpp
    Fisicas.cpp
    Jugador.cpp
    Proyectil.cpp
    BaseNitrogenada.cpp
)

# Lista de archivos de recursos
set(RESOURCES
    font.ttf
    shoot.wav
)

# Agregar los archivos fuente al ejecutable
add_executable(ADNeroids ${SOURCES})

# Copiar archivos de recursos al directorio de salida del ejecutable
foreach(RESOURCE ${RESOURCES})
    configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR}/Debug/${RESOURCE} COPYONLY)
endforeach()

# Configuración de SFML (reemplaza con tu configuración actual)
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics audio window system network REQUIRED)
include_directories("C:/SFML-2.6.1/include")

# Obtener las bibliotecas de SFML sin el sufijo -d
set(SFML_LIBRARIES
    sfml-graphics
    sfml-window
    sfml-audio
    sfml-system
    sfml-network
)

# Enlazar SFML con el ejecutable
target_link_libraries(ADNeroids PRIVATE ${SFML_LIBRARIES})

# Copiar DLLs a la carpeta de salida
add_custom_command(TARGET ADNeroids POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "C:/SFML-2.6.1/bin"
                   $<TARGET_FILE_DIR:ADNeroids>)
