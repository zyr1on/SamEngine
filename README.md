# SamEngine

SamEngine is a small **hobby game / rendering engine project** developed mainly for learning purposes.  
The goal of this project is **not to be perfect or production-ready**, but to explore and understand how
modern rendering engines work internally (inspired by systems like Unity URP or Unreal Engine, at a very
simplified level).

I am not an expert, but I enjoy building things step by step, experimenting with **modern OpenGL**, engine
architecture, rendering pipelines, shaders, materials, and ECS-based design.  
This repository reflects an ongoing learning process rather than a finished engine.

---

## Development Environment

- **Compiler Toolchain**
  - MSYS2 with **UCRT64** toolchain
  - Using the UCRT-based GCC/Clang environment for better C/C++ standard compliance
  ```bash
  $ pacman -S mingw-w64-ucrt-x86_64-toolchain
  $ pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
  ```
- **Build System**
  - **CMake** as the build system
  - **Ninja** as the build generator for fast incremental builds

- **IDE / Editor**
  - **Visual Studio Code**
  - CMake Tools extension for configuring and building
  - **VSCode Extensions**
    - **C/C++** (Microsoft)  
    - **CMake Tools**  
    - **WebGL GLSL Editor**  
      - https://marketplace.visualstudio.com/items?itemName=raczzalan.webgl-glsl-editor  


## TODO

- [ ] Implement a proper **Input Handling** system and a dedicated **Window** class  
  - Centralize keyboard, mouse, and window events  
  - Decouple platform-specific code from the engine core  

- [ ] Upgrade the rendering backend to **OpenGL 4.6 Core Profile**  
  - Remove legacy OpenGL usage  
  - Ensure compatibility with modern buffer and shader features  

- [ ] Introduce **Uniform Buffer Objects (UBO)**  
  - Create shared UBOs for Camera, Lights, and other global data  
  - Bind UBOs consistently across all shaders  

- [ ] Implement an **Uber Shader** system with **Shader Permutations**  
  - Use compile-time defines for features (e.g. lighting, textures, shadows)  
  - Add a shader cache to reuse compiled permutations  
  - Select shader variants automatically based on material features  

- [ ] Design a clean **Renderer API**  
  - Separate rendering logic from game logic  
  - Provide a clear interface for submitting meshes, materials, and lights  

- [ ] Implement lighting calculations for **three light types**  
  - Directional Light  
  - Point Light  
  - Spot Light  
  - Support multiple lights via a shared light buffer  

- [ ] Build a **Component-based architecture using EnTT (ECS)**  
  - Use EnTT as the core entity-component system  
  - Light, Camera, and MeshRenderer should be components  
  - Store and iterate components efficiently using EnTT views and systems  

- [ ] Add **model loading with Assimp**  
  - Support common formats (OBJ, FBX, GLTF, etc.)  
  - Convert loaded meshes into engine Mesh and Material representations  
  - Integrate Assimp-loaded models with the ECS and Renderer
  

## Project Direction

After completing the **core systems** and reaching a stable, usable state (possibly with **ImGui**
integration), this project will already be a success for its purpose.

The next personal goal is to **learn Deferred Rendering** and gain practical understanding of how it fits
into a real rendering pipeline. Once this topic is reasonably understood and implemented at a basic level,
it will likely be time to **let go of SamEngine**.

At that point, focusing on **large-scale, production-grade engines** and studying their workflows and
architectures will be the most valuable next step.
