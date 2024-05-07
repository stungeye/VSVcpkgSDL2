/*
 * SDL2 Moving Rectangle Example for Windows and Visual Studio
 *
 * Written by Kyle Geske (https://stungeye.com)
 * UNLICENSE 2024 <unlicense.org> 
 *
 * This program demonstrates the basics of using SDL2 to create a graphical 
 * application in a Windows environment. It creates a resizable window and a 
 * renderer, and uses these to display and move a colored sqaure across the
 * screen. The squares's movement is governed by its velocity and it bounces
 * off the edges of the window. The color of the square changes if the user
 * presses a key or clicks the mouse.
 *
 * Key Features:
 * - Window creation and management using SDL2.
 * - Real-time rendering of graphical elements with SDL2, including handling 
     window resize events.
 * - Collision detection with window boundaries and response (bouncing effect).
 * - Interaction handling of keyboard and mouse input by way of event polling. 
 * - Use of standard algorithms (std::clamp) to manage the rectangle's position 
 *   within the window boundaries.
 * - The generation of random integers within a specified range. (See util.cpp)
 *
 * Technologies used:
 * - SDL2: A cross-platform library designed to provide low-level access to 
 *   audio, keyboard, mouse, joystick, and graphics hardware. It is used to 
 *   handle window creation, rendering graphics, and capturing input events.
 *   https://www.libsdl.org
 * - Windows API: Used here to define the WinMain entry point for the Windows
 *   subsystem, allowing the program to run without a separate console window. 
 * - Vcpkg: A C++ dependency manager that simplifies the process of acquiring 
 *   and building 3rd party libraries. Used here to install and link SDL2.
 *   https://vcpkg.io
 * - Visual Studio 2022 Community Edition: Free C++ development environment 
 *   with a compiler and build system that support vcpkg installed libraries.
 *   https://visualstudio.microsoft.com/vs/community/
 * 
 * How to Run:
 * - Clone the repository that contains this project.
 * - Ensure that you have Visual Studio 2022 version 17.6 or later installed.
 * - Open the project in Visual Studio by double-clicking: VcpkgSDL2.sln
 * - Open a command prompt using the View => Terminal menu option.
 * - Run the following command to integrate vcpkg with Visual Studio:
 *     vcpkg integrate install
 * - Build the project using Ctrl+Shift+B or selecting Build => Build Solution
 * - Press F5 to run the project in the debugger.
 */

#include "SDL2/SDL.h" // Include the SDL2 library header file.
#include <windows.h>  // Included for the WinMain(...) entry point.
#include <algorithm>  // Inluded for std::clamp for the square's boundary check.
#include "util.h"     // Included for randomInt(...) function. (See util.cpp)

// Constants for the screen width and height.
const int screenWidth = 1280;
const int screenHeight = 720;

// I started this project as a console app, so to use WinMain() instead of
// main() I needed to change: Properties -> Linker -> System -> SubSystem 
// from Console(/SUBSYSTEM:CONSOLE) to Windows(/SUBSYSTEM:WINDOWS)

// WinMain: the main entry point for Windows applications.
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	// Initialize the SDL video subsystem (returns 0 on success).
	if (SDL_Init(SDL_INIT_VIDEO)) {
		// Log an error message if SDL fails to initialize and exit
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3; // Return 3 to indicate an error occurred.
	}

	// Create an SDL window: centered with the title 'Hello, SDL2!' and resizable	
	SDL_Window* window = SDL_CreateWindow("Hello, SDL2!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);

	if (!window) { // If the window could not be created, log the error and exit
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return 3;
	}

	// Create a renderer for the window created above with hardware acceleration and VSync enabled.
	// VSync is a feature that prevents screen tearing by synchronizing the frame rate with the monitor's refresh rate.
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// If the rendered could not be created, log the error and exit.
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return 3;
	}

	// Query the current window size
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	// Define a 100x100 pixel sqaure: { x, y, width, height }
	// The squares's location will start at a random position on the screen.
	int squareSize = 100;
	SDL_Rect square { randomInt(0, w - squareSize), 
					  randomInt(0, h - squareSize), 
		              squareSize, 
				      squareSize };
	
	// Random x and y velocities for our bounding rectangle.
	int xVelocity{ randomInt(1,3) };
	int yVelocity{ randomInt(1,3) };

	// Our main loop will continue to execute until running is set to false.
	bool running{ true };
	// This flag will be set to true if the user presses a key or clicks the mouse.
	bool userInput{ false };

	// The main application loop.
	while (running) {
		SDL_Event event;

		// Loop until there are no more pending events to process. 
		while (SDL_PollEvent(&event) != 0) { 
			if (event.type == SDL_QUIT) {
				running = false; // Stop running if the window is closed
			} else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
				userInput = true; 
			} else if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP) {
				userInput = false;
			}
		}

		// Move our square by updating its x and y position using the velocity.
		square.x += xVelocity;
		square.y += yVelocity;

		// Get the window size again, in case it has been resized by the user.
		SDL_GetWindowSize(window, &w, &h);

		// Check for collision with window side edges and bounce off if needed.
		if (square.x + square.w > w || square.x < 0) {
			// Clamp the square's x position to the window's boundaries.
			square.x = std::clamp(square.x, 0, w - square.w);
			// Reverse the x velocity to bounce off the edge.
			xVelocity *= -1;
		}

		// Check for collision with top/bottom of window and bounce if needed.
		if (square.y + square.h > h || square.y < 0) {
			// Clamp the square's y position to the window's boundaries.
			square.y = std::clamp(square.y, 0, h - square.h);
			// Reverse the y velocity to bounce off the edge.
			yVelocity *= -1;
		}

		// Clear the screen to black.
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		// Draw in green if the user is pressing a key or mouse button.
		if (userInput) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
		} else { // Draw in blue if there is no user input. 
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
		}

		// Draw the rectangle.
		SDL_RenderFillRect(renderer, &square);

		// Render everything to the screen.
		SDL_RenderPresent(renderer);

	}

	// Cleanup SDL components and quit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	// Return 0 to the OS to indicate success.
	return 0;
}