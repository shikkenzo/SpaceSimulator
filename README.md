# Space Simulator

A small C++23 / OpenGL 3.3 project exploring real-time 3D rendering and basic game-engine architecture.

The current demo renders a simple solar-system-style scene with textured objects, hierarchical transformations, orbital movement, and a controllable free camera.

This is an ongoing learning project, and the architecture and implementation may change as development continues.

![Image](https://github.com/shikkenzo/SpaceSimulator/blob/main/RESOURCES/Screenshot0.png
)

---

## Features

The project currently provides a simple 3D rendering environment built around OpenGL 3.3.

The current implementation includes:

* OpenGL 3.3 rendering
* GLFW window and input management
* Textures and materials
* Mesh rendering
* Basic resource management
* Component-based object architecture
* Scene and object management
* Parent/child object relationships
* Transform hierarchies
* Perspective cameras
* Free-camera controls
* Basic orbital movement

The current demo uses these systems to create a simple solar-system-style scene containing a central object and several orbiting bodies.

---

## Project Goals

The main purpose of this project is not to create a complete game engine, but to develop a practical understanding of the concepts involved in building a simple real-time 3D application by implementing them directly.

---

## Architecture

### Project Structure

The repository is currently organized approximately as follows:

```text
Project/
│
├── Core/
│   ├── assets/
│   │   ├── shaders/
│   │   └── textures/
│   │
│   ├── src/
│   │   ├── Components/
│   │   ├── Graphics/
│   │   ├── Debug/
│   │   ├── Application.h
│   │   ├── Core.cpp
│   │   ├── Core.h
│   │   ├── Object.cpp
│   │   ├── Object.h
│   │   ├── ResourceManager.cpp
│   │   ├── ResourceManager.h
│   │   ├── Scene.cpp
│   │   ├── Scene.h
│   │   ├── Transform.h
│   │   ├── Window.cpp
│   │   └── Window.h
│   │
│   └── vendor/
│       ├── glm/
│       └── stb/
│
├── Game/
│   └── src/
│       ├── Game.cpp
│       ├── Game.h
│       └── main.cpp
│
├── vendor/
│   ├── glad/
│   ├── glfw/
│   └── premake/
│
├── build.bat
├── build-vs2022.bat
├── clean-vs2022.bat
└── premake5.lua
```

### Core

Contains the general-purpose systems used by the application, including rendering, objects, components, scenes, transforms, windows, and resource management.

### Game

Contains the application-specific code used to create and configure the current demo.

---

## Objects and Components

The project uses a simple component-based object architecture.

Objects can be composed from different components depending on their role. For example, a renderable object may use `TransformComponent` and `StaticMeshComponent`, while a camera may use `TransformComponent` and `CameraComponent`

Components can be added and accessed through the object:

```cpp
object.AddComponent<TransformComponent>();
```

and:

```cpp
auto* camera = object.GetComponent<CameraComponent>();
```

---

## Transform Hierarchy

Objects can be arranged in a parent/child hierarchy.

For example:

```text
Sun
└── Planet
    └── Moon
```

An object's world transformation takes its parent's transformation into account.

This allows objects to be positioned relative to other objects while still producing the correct world-space transformation.

---

## Rendering

Rendering is implemented using OpenGL 3.3.

The project currently works with the following OpenGL concepts:

* Vertex Array Objects
* Vertex Buffer Objects
* Element Buffer Objects
* GLSL shaders
* Textures
* Depth testing
* Indexed drawing
* Transformation matrices

The general rendering flow is:

```text
Scene
  │
  ├── Camera
  │     ├── View Matrix
  │     └── Projection Matrix
  │
  └── Renderable Objects
        │
        ├── Transform
        ├── Mesh
        └── Material
              │
              ├── Shader
              └── Texture
```

The renderer currently uses a simple forward rendering approach.

---

## Shaders

The project currently contains a basic vertex and fragment shader:

```text
Core/assets/shaders/
├── default.vert
└── default.frag
```

Shaders are loaded and managed through the resource system.

---

## Camera

The project includes a perspective camera system.

The camera uses the object's transform to calculate its view matrix and provides a perspective projection.

The current camera system includes:

* Position
* Rotation
* Field of view
* Near clipping plane
* Far clipping plane
* Aspect ratio
* View matrix
* Projection matrix

A simple free-camera controller is included for navigating the scene.

### Controls

| Input               | Action                  |
| ------------------- | ----------------------- |
| `W`                 | Move forward            |
| `S`                 | Move backward           |
| `A`                 | Move left               |
| `D`                 | Move right              |
| `Q`                 | Move downward           |
| `E`                 | Move upward             |
| `Left Shift`        | Increase movement speed |
| `Left Mouse Button` | Enable camera look      |
| Mouse               | Look around             |

---

## Orbital Movement

The project includes an `OrbitComponent` for basic orbital movement.

An object can be configured to orbit around another object's transform.

The component currently supports properties such as:

* Orbit axis
* Orbit radius
* Angular speed
* Attractor transform

---

## Procedural Geometry

The project includes a small utility for generating sphere geometry procedurally.

For example:

```cpp
auto sphere = GenerateSphere(1.0f, 16, 16);
```

The generated geometry can then be used as a mesh for rendering.

---

## Resource Management

A basic `ResourceManager` is used for loading and accessing commonly shared resources.

Resources currently include:

* Shaders
* Textures
* Materials
* Meshes

For example:

```cpp
auto texture = ResourceManager::LoadTexture("assets/textures/planet.png");
```

The resource system is intended to avoid unnecessarily loading multiple copies of the same resource.

---

## Assets

Runtime assets are located under:

```text
Core/assets/
```

### Shaders

```text
Core/assets/shaders/
├── default.vert
└── default.frag
```

### Textures

```text
Core/assets/textures/
├── checkerboard.png
├── planet.jpg
├── rock.png
└── sun.png
```

The build configuration copies the assets into the appropriate application output directory.

---

## Building

### Requirements

The current project is configured primarily for Windows development.

You will need:

* Windows
* Visual Studio 2022
* C++ desktop development tools
* Windows SDK
* A GPU supporting OpenGL 3.3
* Premake 5

The repository contains the main third-party dependencies used by the project.

---

## Visual Studio 2022

To generate the Visual Studio project files, run:

```bat
build-vs2022.bat
```

Then:

1. Open the generated Visual Studio solution.
2. Select `Game` as the startup project.
3. Select the `x64` platform.
4. Choose either `Debug` or `Release`.
5. Build the solution.
6. Run the application.

---

## Build Scripts

The repository includes a general build script:

```bat
build.bat
```

For Visual Studio 2022:

```bat
build.bat vs2022
```

To clean generated files:

```bat
clean-vs2022.bat
```

The project uses Premake to generate the appropriate project files.

---

## Build Configurations

Two configurations are currently provided:

### Debug

Used primarily during development and debugging.

### Release

Uses compiler optimizations for a more optimized build.

Both configurations currently target:

```text
Architecture: x64
C++ Standard: C++23
```

---

## Dependencies

The project uses the following libraries:

### GLFW

Used for window creation, OpenGL context management, and input.

### GLAD

Used for loading OpenGL functions.

### GLM

Used for vector, matrix, quaternion, and other mathematical operations.

### stb_image

Used for loading image files as textures.

### Premake

Used to generate the project's build files.

The relevant dependencies are included in the repository under `vendor`.

---

## Third-Party Licenses

Third-party libraries included in this repository are distributed under their respective licenses.

Please refer to the license files included with each dependency for their specific terms.

---

## Acknowledgements

This project was developed while learning from OpenGL documentation, tutorials, examples, and other educational resources.

---
