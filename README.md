# SEHH2042 Group Project - Student Management System

This project is a simple student management system created for the SEHH2042 course. It allows users to manage student records, including adding, deleting, and editing student information, as well as generating student transcripts.

## Features

*   **Load Student Data:** Load a default set of student and subject data.
*   **Show Student Records:** Display a list of all students, with options to sort by name or GPA.
*   **Edit Student Information:** Modify a student's name, major, and subject list.
*   **Add/Delete Students:** Add new students to the system or remove existing ones.
*   **Generate Transcript:** Create a transcript for a specific student, showing their subjects, credits, and grades.

## Compilation and Execution

This project uses CMake to manage the build process, allowing it to be compiled on various operating systems.

### Prerequisites

*   A C++ compiler (e.g., GCC, Clang, MSVC)
*   CMake (version 3.10 or later)

### Windows

**Method 1: Using Visual Studio (Recommended)**

1.  **Install Prerequisites:**
    *   Install Visual Studio with the "Desktop development with C++" and "CMake development with C++" workloads.

2.  **Open and Build the Project:**
    *   Launch Visual Studio.
    *   Go to `File > Open > Folder` and select the root directory of this project.
    *   Visual Studio will automatically detect the `CMakeLists.txt` file and configure the project.
    *   To build the project, go to `Build > Build All`.
    *   The executable, `SMS.exe`, will be located in a subdirectory within the `out/build` folder (e.g., `out/build/x64-Debug`).

**Method 2: Using the Command Line**

1.  **Install Prerequisites:**
    *   Install Visual Studio with the "Desktop development with C++" workload (for the compiler).
    *   Install CMake from the official website: [https://cmake.org/download/](https://cmake.org/download/)

2.  **Build the Project:**
    Open a command prompt and navigate to the project's root directory. Then, run the following commands:

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

3.  **Run the Application:**
    The executable, `SMS.exe`, will be located in the `build\Debug` or `build\Release` directory.

### Linux

1.  **Install Prerequisites:**
    *   **Debian/Ubuntu:**
        ```bash
        sudo apt-get update
        sudo apt-get install build-essential cmake
        ```
    *   **Arch Linux:**
        ```bash
        sudo pacman -Syu base-devel cmake
        ```
    *   **Fedora:**
        ```bash
        sudo dnf install @development-tools cmake
        ```

2.  **Generate Build Files and Build:**
    Open a terminal and navigate to the project's root directory. Then, run the following commands:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3.  **Run the Application:**
    The executable, `SMS`, will be located in the `build` directory. To run it, use the following command:

    ```bash
    ./SMS
    ```

### macOS

1.  **Install Prerequisites:**
    *   Install the Xcode Command Line Tools and CMake (e.g., using Homebrew):
        ```bash
        xcode-select --install
        brew install cmake
        ```

2.  **Generate Build Files and Build:**
    Open a terminal and navigate to the project's root directory. Then, run the following commands:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3.  **Run the Application:**
    The executable, `SMS`, will be located in the `build` directory. To run it, use the following command:

    ```bash
    ./SMS
    ```
