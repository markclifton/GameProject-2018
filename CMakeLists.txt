cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ProjectSane)

file(GLOB SOURCES
    engine/*.h
    engine/*.cpp
    engine/**/*.h
    engine/**/*.cpp
    engine/drawable/**/*.h
    engine/drawable/**/*.cpp
    dependencies/independent/glad/gl.cpp
    main.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/engine)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/independent)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/windows)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/windows/glfw3/include)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/windows/glfw3/glfw3.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/windows/glm/libs/glm_static.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/windows/freeimage/FreeImage.lib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/dependencies/Windows/freeimage/FreeImage.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

file(GLOB RESOURCES_IMAGES resources/images/* )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/images")
foreach( file_i ${RESOURCES_IMAGES})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/images/"
        )
endforeach()

file(GLOB RESOURCES_MODELS resources/models/* )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/models")
foreach( file_i ${RESOURCES_MODELS})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/models/"
        )
endforeach()

file(GLOB RESOURCES_SHADERS resources/shaders/* )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/shaders")
foreach( file_i ${RESOURCES_SHADERS})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/shaders/"
        )
endforeach()
