#ifndef SOUND_H
#define SOUND_H

#include <math.h>
#include <iostream>

namespace Sounds {
#define TWOPI 6.283185307
#define AMP_MAX 32767
#define HERTZ 48000

	short SineWave(double time, double freq, double amp) {
		short result;
		double tpc = HERTZ / freq; //ticks per cycle
		double cycles = time / tpc;
		double rad = TWOPI * cycles;
		short amplitude = AMP_MAX * amp;
		result = amplitude * sin(rad);
		return result;
	}

	short TriangleWave(double time, double freq, double amp) {
		short result;
		double tpc = HERTZ / freq; //ticks per cycle
		double cycles = time / tpc;
		short amplitude = AMP_MAX * amp;
		result = amplitude * cycles;

		return result;
	}

	short SquareWave(double time, double freq, double amp) {
		short result = 0;
		int tpc = HERTZ / freq; //ticks per cycle
		int cyclepart = int(time) % tpc;
		int halfcycle = tpc / 2;
		short amplitude = AMP_MAX * amp;
		if (cyclepart < halfcycle) {
			result = amplitude;
		}
		return result;
	}

	short Noise(double amp) {
		short result;
		short amplitude = AMP_MAX * amp;
		result = rand() % amplitude;
		return result;
	}
}
#endif // !SOUND_H