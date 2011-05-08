What is this?
=============

This is a stand alone package for GLTools. According to the OpenGL SuperBible, written by the author of GLTools: 

>GLTools began life in the third edition of this
>book. Over time it has grown and provides a lot of shortcuts and handy tools, much like
>the OpenGL utility library (GLU) used to. GLTools includes a 3D math library to manipulate
>matrices and vectors and relies on GLEW for full OpenGL 3.3 support of functions
>that generate and render some simple 3D objects and manage your view frustum, camera,
>and transformation matrices

GLTools is incredibly useful, however, it is a real pain to get set up under Linux. The makefiles provided with the
companion source code for the book all rebuild GLTools from scratch and statically link it to the executable. 

For this distribution, I removed the included copy of GLEW and wrote some CMake files to make it easier to use
with your own programs.

The official repository is available at http://code.google.com/p/oglsuperbible5/

**NOTE**: I only tested the build process under Ubuntu 10.04, if there are any issues on other platforms, patches are appreciated.

COMPILATION AND INSTALLATION
============================

List of packages needed for compilation on Ubuntu:

    build-essential g++ cmake libx11-dev freeglut3-dev libglu1-mesa-dev libxcb1-dev libxext-dev libxxf86vm-dev libxi-dev libxmu-dev glew-utils libglew1.5-dev

To compile and install GLTools:

    cd build
    cmake ..
    make
    sudo make install
    sudo ldconfig

By default, headers will be in */usr/local/include* and libraries will be in */usr/local/lib*
