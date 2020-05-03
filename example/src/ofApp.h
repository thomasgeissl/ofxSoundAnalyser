#pragma once

#include "ofMain.h"
#include "ofxSoundAnalyser.h"

class ofApp : public ofBaseApp, public ofxSoundAnalyser::Listener
{
public:
	void setup();
	void update();
	void draw();
	void exit();

	void onPeakEnergy(ofxSoundAnalyser::FloatArg &arg);
	void onPitch(ofxSoundAnalyser::FloatArg &arg);
	void onRootMeanSquare(ofxSoundAnalyser::FloatArg &arg);
	void onFftMagnitudeSpectrum(ofxSoundAnalyser::FloatVecArg &arg);
	void onMelFrequencySpectrum(ofxSoundAnalyser::FloatVecArg &arg);
	void onSpectralCentroid(ofxSoundAnalyser::FloatArg &varg);
	void onSpectralCrest(ofxSoundAnalyser::FloatArg &varg);
	void onSpectralDifference(ofxSoundAnalyser::FloatArg &arg);
	void onSpectralFlatness(ofxSoundAnalyser::FloatArg &arg);
	void onZeroCrossingRate(ofxSoundAnalyser::FloatArg &arg);
	void onChord(ofxSoundAnalyser::FloatArg &arg);
	void onChromogram(ofxSoundAnalyser::FloatVecArg &arg);

	ofxSoundAnalyser::Analyser _analyser;

	float _peakEnergy;
};
