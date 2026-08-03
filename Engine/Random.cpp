#include "pch.h"
#include "Random.h"

#include <cstdlib>

namespace nu
{
	int RandomInt() {
		return rand();
	}

	/// <summary>
	/// Returns a random integer [0, max)
	/// </summary>
	/// <param name="max">exclusive max value</param>
	/// <returns></returns>
	int RandomInt(int max) {
		return rand() % max;
	}

	/// <summary>
	/// Returns a random integer [min, max]
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	int RandomInt(int min, int max) {
		return RandomInt(max + 1 - min) + min;
	}

	float RandomFloat() {
		return rand() / (float) RAND_MAX;
	}

	float RandomFloat(float max) {
		return RandomFloat() * max;
	}

	float RandomFloat(float min, float max) {
		return min + RandomFloat() * (max - min);
	}
}