#pragma once

#include "ofMain.h"
#include "ofxSoundAnalyser.h"

class ofApp : public ofBaseApp, public ofxSoundAnalyserListener{
public:
	void setup();
	void update();
	void draw();
	void exit();

	void onPeakEnergy(std::pair<int, float> & value);
	void onPitch(std::pair<int, float> & value);
	void onRootMeanSquare(std::pair<int, float> & value);
	void onFftMagnitudeSpectrum(std::pair<int, std::vector<float>> & value);
	void onMelFrequencySpectrum(std::pair<int, std::vector<float>> & value);
	
	ofxSoundAnalyser _analyser;
};
