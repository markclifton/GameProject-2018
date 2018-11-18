# ProjectSane

## What is Project Sane?
ProjectSane is a game engine being developed in a Linux environment and making use of C++ and OpenGL. This could be expanded to other operating systems in the future, but the focus will be linux. The goal of the project is to write a game engine that can be used to write a game(s).

Recently added support for Windows 10. On Windows, the project should be self-contained and not need anything beyond CMake and a compiler. Linux requires some libraries to be installed by the user.

### Things completed (mostly):
* 2D Rendering (Rectangle, Triangles, other simple shapes)
* 3D Rendering (Models)
* Batch Rendering (Supports both 2D and 3D)
* Transformation Stack (Needs validation still)
* Game State/Context Management
* Shader System (Allows reuse by uid)
* Texture System (Allows reuse by uid)
* Callback System for the Window (register handlers that allow the handling of GLFW Callbacks)
* Basic Real-time Shadows
* Audio Handling

### Things to do:
* Level Loading
* Text System
* Interaction System
* Physics System
* Advanced Lighting
* Improved Shadows
* Networking

### Development Environment
* Linux Mint 19 (Windows 10)
* CMake
* QtCreator 4.8
* Modern OpenGL
* GLSL 450
* FreeImage
* GLFW
* GLM
* GLAD
