#include "SDL2/SDL.h"
#include <windows.h> // WinMain
#include <random> // std::random_device, std::mt19937_64, std::uniform_int_distribution
#include <algorithm> // std::clamp

// I started this project as a console app, so to use WinMain() instead of
// main() I needed to change: Properties -> Linker -> System -> SubSystem 
// from Console(/SUBSYSTEM:CONSOLE) to Windows(/SUBSYSTEM:WINDOWS)

const int screenWidth = 1280;
const int screenHeight = 720;

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	// Random device used to seed the random number engine.
	std::random_device rd;

	// 64 bit Mersenne Twister random number engine seeded with rd()
	std::mt19937_64 gen(rd());

	// Uniform distribution of short integers from 0 to max int:
	std::uniform_int_distribution<int> dist(1, RAND_MAX);

	// Initialize SDL with video and keyboard input support
	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_CreateWindowAndRenderer(screenWidth, screenHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	SDL_Rect rect { 0, 0, 100, 100};

	// Randomize the starting position and velocity of the rectangle
	rect.x = dist(gen) % (w - rect.w);
	rect.y = dist(gen) % (h - rect.h);
	
	int xVelocity{ dist(gen) % 3 + 1 };
	int yVelocity{ dist(gen) % 3 + 1 };

	bool running{ true };
	bool constrainFPS{ true };

	while (running) {
		SDL_Event event;

		// Process all pending events.
		while (SDL_PollEvent(&event) != 0) { 
			if (event.type == SDL_QUIT) {
				running = false;
			} else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
				constrainFPS = false;
			} else if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP) {
				constrainFPS = true;
			}
		}

		// Move our rectangle
		rect.x += xVelocity;
		rect.y += yVelocity;

		SDL_GetWindowSize(window, &w, &h);

		// Bounce off the walls
		if (rect.x + rect.w > w || rect.x < 0) {
			rect.x = std::clamp(rect.x, 0, w - rect.w);
			xVelocity *= -1;
		}
		if (rect.y + rect.h > h || rect.y < 0) {
			rect.y = std::clamp(rect.y, 0, h - rect.h);
			yVelocity *= -1;
		}

		// Clear the screen to black.
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		// Draw in blue if we are constraining the frame rate, green if not.
		if (constrainFPS) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
		} else {
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
		}

		// Draw the rectangle.
		SDL_RenderFillRect(renderer, &rect);

		// Render!
		SDL_RenderPresent(renderer);

		if (constrainFPS) {
			// Sleep for 4ms to cap the frame rate at 250 FPS-ish
			SDL_Delay(4);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}