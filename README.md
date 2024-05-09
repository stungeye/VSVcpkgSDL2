# SDL2 Moving Rectangle for Windows

Written by Kyle Geske ([stungeye.com](https://stungeye.com)) - UNLICENSE 2024 ([unlicense.org](https://unlicense.org))

## Description

This program demonstrates the basics of using SDL2 to create a graphical application in a Windows environment. It creates a resizable window and a renderer, and uses these to display and move a colored sqaure across the screen. The squares's movement is governed by its velocity and it bounces off the edges of the window. The color of the square changes if the user presses a key or clicks the mouse. 

Instructions on how to run the project can be found down below.

## Key Features

- Window creation and management using SDL2.
- Real-time rendering of graphical elements with SDL2, including handling window resize events.
- Collision detection with window boundaries and response (bouncing effect).
- Interaction handling of keyboard and mouse input by way of event polling. 
- Use of standard algorithms (std::clamp) to manage the rectangle's position within the window boundaries.
- The generation of random integers within a specified range. (See util.cpp)

## Technologies Used

- [SDL2](https://www.libsdl.org): A cross-platform library designed to provide low-level access to audio, keyboard, mouse, joystick, and graphics hardware. It is used to handle window creation, rendering graphics, and capturing input events.
- [Vcpkg](https://vcpkg.io): A C++ dependency manager that simplifies the process of acquiring and building 3rd party libraries. Used here to install and link SDL2.
- [Visual Studio 2022 Community Edition](https://visualstudio.microsoft.com/vs/community/): Free C++ development environment with a compiler and build system that support libraries installed using Vcpkg.

## How To Run

- Clone the repository that contains this project.
- Ensure that you have Visual Studio 2022 version 17.6 or later installed.
- Open the project in Visual Studio by double-clicking the `VcpkgSDL2.sln` file.
- Open a command prompt using the View => Terminal menu option.
- Run the following command to integrate vcpkg with Visual Studio: `vcpkg integrate install`
- Build the project by pressing Ctrl+Shift+B or selecting Build => Build Solution.
- Press F5 to run the project in the debugger.
