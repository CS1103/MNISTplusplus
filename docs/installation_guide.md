# Installation Guide

This installation guide will walk you through the steps to install and run MNIST++ on Windows.

## Prerequisites

Before proceeding with the installation, please ensure that you have the following software installed on your Windows machine:

- C++ compiler (e.g., Visual Studio or MinGW)
- CMake (version 3.0 or higher)
- Git (version 2.0 or higher)

## Installation Steps

1. Clone the MNIST++ repository to your local machine:

```bash
git clone https://github.com/CS1103/proyecto-final---te02---202301-pf0220231-grupo1-sub-1.git
```

2. Navigate to the project directory:

```bash
cd MNISTplusplus
```

3. Create a build directory and navigate into it:

```bash
mkdir build
cd build
```

4. Generate the build files using CMake:

```bash
cmake ..
```

5. Build the project using the CMake-generated build files:

```bash
cmake --build .
```

6. After a successful build, you will find the compiled executable file (`MNIST++.exe`) in the build directory.

## Running the Application

To run MNIST++, follow these steps:

1. Open a command prompt or terminal.
2. Navigate to the directory containing the `MNIST++.exe` file.
3. Run the executable:

```bash
./MNIST++.exe
```

Note: Ensure that the dataset files (`t10k-images.idx3-ubyte`, `t10k-labels.idx1-ubyte`, `train-images.idx3-ubyte`, and `train-labels.idx1-ubyte`) are present in the same directory as the executable.

That's it! You have successfully installed and run MNIST++ on your Windows machine.

If you encounter any issues during the installation process, please refer to the team members mentioned in the [README](README.md) for assistance.

Happy digit recognition! 🚀✨
