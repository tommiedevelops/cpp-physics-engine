# Scope
- Develop a 3D physics engine with collisions, gravity, friction, restitution.
- Render the scene with a basic renderer using OpenGL
- Write the engine in C++

# Initial System Design
- It will use an App / Core architecture
- App contains application specific code and the main function
- Core is remains constant regardless of the application and contains a renderer and physics solver

# Dependencies
- For WSL2

```
sudo apt update
```

installing OpenGL:
```
sudo apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

installing g++ (cpp compiler)
```
sudo apt install -y build-essential
```

installing cmake
```
sudo apt install -y cmake
```

