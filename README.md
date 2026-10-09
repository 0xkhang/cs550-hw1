# learnply2

## Configuring and Building

You will need an installation of CMake and a C++ compiler to build the project. Install CMake from their [official website](https://cmake.org/download/), or use your system's package manager. For example, on Debian distributions, you can install CMake with:

```bash
sudo apt-get update
sudo apt-get install cmake
```

After installing CMake, you can build the project by first creating a build directory inside the project directory (i.e. the directory with `CMakeLists.txt`, known as the **source** directory) and navigating into it:

```bash
mkdir build
cd build
```

Then, run CMake to **configure** the project and generate the build files:

```bash
cmake ..
```

**Note**: Some Linux distributions do not have all the required libraries out-of-box to build GLFW. GLFW will report such libraries at this step for which you will need to install as-needed.

Depending on your operating system, the generated build files will differ. On Linux and macOS, CMake will generate Makefiles by default, while on Windows, it will generate Visual Studio solution files.

### Linux and macOS

To build the project on Linux or macOS, you can use the following command from the build directory:

```bash
make
```

### Windows

Open the generated Visual Studio solution file (`.sln` or `.slnx`) in the build directory. Build by right-clicking on `learnply2` in the Solution Explorer and selecting "Build".

### Platform-Independent

To build on any platform and build system from the command line, you may also run the below command from the `build` directory:

```bash
cmake --build .
```

CMake will use whatever build system it configured and build for you there.

**Note**: If you want to change your build system or something significant relating to the build process, deleting `CMakeCache.txt` in the `build` directory or the entire `build` is a good first step if your change did not have any effect.

## Running the Program

The program takes a single command-line argument, which is the path to a PLY file. You can run the program from the command line as follows:

```bash
./learnply2 path/to/your/file.ply
```

The location of the executable file varies per build system. For Unix-like systems, it is generally directly in the `build` directory. You may also run the program in an IDE of your choice. Be sure to set command line arguments there.

**Note**: In Visual Studio, you can set the command-line arguments by right-clicking on the project in the Solution Explorer, selecting "Properties", and then navigating to "Debugging" to set the "Command Arguments". To set the project to be run, right-click on `learnply2` and click "Set as Startup Project". You can then start the program by pressing F5.

### Controls

- Left-click and drag to rotate the model.
- Number keys to switch between different rendering modes.
- R to reset the view.
- Escape to exit.

## Project Structure

The project is organized into the following directories:

- `src/`: Contains the source code files for the project.
- `models/`: Contains the PLY model files used for testing and demonstration.
- `glfw-3.5.1/`: Contains the GLFW library used for creating windows and handling input.
- `glm/`: Contains the GLM library used for mathematics operations in graphics programming.

## Homework 1

You will need to implement the TODOs in the following places:

- Functions `project_to_sphere` and `arcball` in `camera.cpp`
- Function `compute_properties` in `mesh.cpp`
- Function `display` in `main.cpp`

For programming, it will be helpful to understand the source code in the following header files to understand the interface:

- `camera.h`: Defines the `Camera` class, representing a camera in 3D space orbiting a position.
- `edge.h`: Defines the `Edge` class, representing an edge connecting two vertices in a `Mesh`.
- `mesh.h`: Defines the `Mesh` class, representing a triangle mesh.
- `triangle.h`: Defines the `Triangle` class, representing a triangle in a `Mesh`.
- `vertex.h`: Defines the `Vertex` class, representing a vertex in a `Mesh`.

The classes relating to a `Mesh` contain geometric information necessary to complete the homework. Some of these properties are computed for you (such as triangle area and per-triangle/per-vertex normals).

**Note**: some models will not display correctly until you correctly implement `compute_properties` and parts of `display`.

**Note**: When submitting your project, do not include the `build` directory in your submission. If you choose to add files, make sure you add them to the project by modifying the `CMakeLists.txt` file in the root directory of the project. This will ensure that CMake is aware of the new files and can include them in the build process. Be sure to re-run `cmake ..` from the `build` directory to add them to the build process.
