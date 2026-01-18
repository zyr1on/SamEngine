# SamEngine

**SamEngine** is a **hobby project** I started to learn game engine architecture and OpenGL graphics programming from the ground up. This project is a personal development area where I apply the techniques I learned while searching for answers to the question, “How does a game engine work in the background?” It is developed without any commercial purpose, focusing entirely on clean coding principles and understanding the logic of graphics programming.

## My Learning Goals
* Deeply understand the OpenGL render pipeline process.
* Apply memory management and RAII principles with C++.
* Understand shader management and mathematical lighting models (Phong, etc.).
* Build efficient resource management systems.

## What Have I Done So Far?
* **Modern Window Structure:** A modular `Window` class that encapsulates GLFW, offers static callback support, and complies with the RAII principle.
* **DeltaTime System:** Time management for smooth motion independent of frame rate.
* **Smart Shader System:** A professional structure that easily loads shaders, caches uniform locations, and performs detailed logging.
* **Texture Manager:** A system that manages textures using the singleton pattern with `std::unordered_map`, preventing duplicate loads and improving performance.
* **Basic Lighting:** Integration of the Phong lighting model consisting of Ambient, Diffuse, and Specular components. 


## Technical Tools
* **Language:** C++20 (mingw64 15.2.0) [C++ ==> MinGW-w64 binaries](https://github.com/niXman/mingw-builds-binaries)
* **Graphics API:** OpenGL 3.3 (Core Profile)  [Glad](https://glad.dav1d.de/)
* **Libraries:** GLFW, GLAD, GLM, stb_image
* **Build System:** CMake (Cmake for windows with mingw64 make)

## Development Process (WIP)
This project is constantly evolving. I plan to add the following in the next stages:
- [ ] Material class for shader and mesh management (could be json-based)
- [ ] Transform Component and Entity system
- [ ] Simple scene management for entities as active/inactive (could also be JSON-based)
- [ ] Model Loader system to load `.obj` files.
- [ ] A more advanced and centralized Input Manager.
- [ ] ImGui integration for debugging and scene management.
- [ ] Different light types (Directional, Point, Spot Light).
- [ ] Entity Component System
- [ ] Sahne Yönetimi
