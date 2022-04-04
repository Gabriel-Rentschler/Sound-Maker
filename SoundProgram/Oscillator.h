#include <SFML/Audio.hpp>
#include "Sounds.h"

#define TWOPI 6.283185307
#define AMP_MAX 32767
#define HERTZ 44100

class Oscillator {
public:
	Oscillator() { }

	Oscillator(double frequency, double amplitude) {
		amp = amplitude;
		freq = frequency;
	}

	void setFrequency(double frequency) {
		freq = frequency;
	}

	void setAmplitude(double amplitude) {
		amp = amplitude;
	}

	void play() {
		playSound();
	}

	void stop() {
		sound.stop();
		samples.clear();
	}

private:
	//Sound
	sf::SoundBuffer buffer;
	std::vector<sf::Int16> samples;
	sf::Sound sound;
	double amp;
	double freq;

	void playSound() {

		for (int i = 0; i < HERTZ; i++) {
			samples.push_back(Sounds::SineWave(i, freq, amp));
			//samples.push_back(sound::TriangleWave(i, 440, 0.8));
			//samples.push_back(sound::SquareWave(i, 440, 0.8));
			//samples.push_back(sound::Noise(0.7));
		}

		buffer.loadFromSamples(&samples[0], samples.size(), 1, HERTZ);

		sound.setBuffer(buffer);

		sound.play();
	}
};
