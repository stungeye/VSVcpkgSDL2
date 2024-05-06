#include <random> // std::random_device, std::mt19937_64, std::uniform_int_distribution

// Returns a random integer between min and max, inclusive.
int randomInt(int min, int max) {
	// Random device used to seed the random number engine.
	static std::random_device rd;
	// 64 bit Mersenne Twister random number engine seeded with rd().
	static std::mt19937_64 gen(rd());
	// Uniform distribution of  integers from min to max, inclusive.
	std::uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}
