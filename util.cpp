/*
 * util.cpp: Utility functions used in the VcpkgSDL2 project.
 *
 * Currently only includes a random integer function.
 */

#include <random> // std::random_device, std::mt19937_64, std::uniform_int_distribution

/*
 * randomInt: Returns a random integer between min and max, inclusive.
 * 
 * Two of the local variables in this function are declared static so that they
 * persist for the duration of the program and are initialized only once.
 */
 int randomInt(int min, int max) {
	// Random device used to generate a non-deterministic seed for the random 
	// number generator. Declared static so that it is only initialized once,
	// which avoids the overhead of reinitialization and allows for better
	// random number generation.
	static std::random_device rd;

	// 64 bit Mersenne Twister random number engine seeded with rd().
	// Also delcared static for the same reasons as rd.
	static std::mt19937_64 gen(rd());

	// This creates a distribution that produces integers in the range 
	// [min, max], inclusive. 
	std::uniform_int_distribution<int> dist(min, max);

	// The uniform distribution is used here to transform the output of the
    // random number generator 'gen' into a uniform distribution within the 
	// specified range.
	return dist(gen);
}
