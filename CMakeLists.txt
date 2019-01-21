cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ProjectSane)

file(GLOB SOURCES
    ps/*.h
    ps/*.cpp
    ps/**/*.h
    ps/**/*.cpp
    ps/**/**/*.h
    ps/**/**/*.cpp
)

file(GLOB HEADERS
    ps/*.h
    ps/**/*.h
    ps/**/**/*.h
)

#add_executable(${PROJECT_NAME} ${SOURCES})
add_library(${PROJECT_NAME} STATIC ${SOURCES} )

INSTALL(TARGETS ${PROJECT_NAME}
    DESTINATION ProjectSane/lib
)

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/ps/
    DESTINATION ProjectSane/includes/ps
    FILES_MATCHING PATTERN "*.h*"
)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/dependencies/independent)

IF (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/windows)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/windows/glfw3/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/windows/freeimage/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/windows/irrKlang/include)

    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/windows/glfw3/lib/glfw3.lib)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/windows/glm/libs/glm_static.lib)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/windows/freeimage/lib/FreeImage.lib)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/dependencies/Windows/freeimage/FreeImage.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
ELSEIF(APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/glm/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/glfw/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/freeimage/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/irrKlang/include)

    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/mac/glfw/lib/libglfw.3.3.dylib)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/mac/irrKlang/lib/libirrklang.dylib)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/mac/freeimage/lib/libfreeimage.a)

ELSE()
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/glm/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/GLFW/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/freeimage/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/irrKlang/include)

    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/linux/irrKlang/lib/libIrrKlang.so)

    target_link_libraries(${PROJECT_NAME} glfw3)
    target_link_libraries(${PROJECT_NAME} GLU)
    target_link_libraries(${PROJECT_NAME} GL)
    target_link_libraries(${PROJECT_NAME} X11)
    target_link_libraries(${PROJECT_NAME} Xrandr)
    target_link_libraries(${PROJECT_NAME} Xxf86vm)
    target_link_libraries(${PROJECT_NAME} Xinerama)
    target_link_libraries(${PROJECT_NAME} Xcursor)
    target_link_libraries(${PROJECT_NAME} rt)
    target_link_libraries(${PROJECT_NAME} m)
    target_link_libraries(${PROJECT_NAME} pthread)
    target_link_libraries(${PROJECT_NAME} dl)
    target_link_libraries(${PROJECT_NAME} freeimage)
ENDIF()
