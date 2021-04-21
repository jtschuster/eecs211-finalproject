cmake_minimum_required(VERSION 3.3)
project(final-project CXX)
include(.eecs211/cmake/CMakeLists.txt)

#find_package(SDL2 REQUIRED)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "--emrun -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\", \"jpg\"]' -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s WASM=1 -s EXPORTED_FUNCTIONS=\"['_main']\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
endif()
set(MODEL_SRC
        src/model.cpp)

add_program(words
        src/words.cpp
        src/controller.cpp
        src/view.cpp
        ${MODEL_SRC})
target_link_libraries(words ge211)

add_program(main
    src/main.cpp
    ${MODEL_SRC})
target_link_libraries(main ge211)

add_test_program(model_test
    test/model_test.cpp
    ${MODEL_SRC})
target_link_libraries(model_test ge211)
