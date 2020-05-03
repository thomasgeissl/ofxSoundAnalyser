#include "ofApp.h"

void ofApp::setup()
{
	_analyser.addListener(this);
}
void ofApp::update()
{
	_analyser.update();
}
void ofApp::draw()
{
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofMap(_peakEnergy, 0, 1, 0, std::min(ofGetWidth() / 2, ofGetHeight() / 2) / 2));
}
void ofApp::exit() {}

void ofApp::onPeakEnergy(ofxSoundAnalyser::FloatArg &arg)
{
	auto analyserId = arg.getId();
	auto peakEnergyValue = arg.getValue();
	_peakEnergy = peakEnergyValue;
}
void ofApp::onPitch(ofxSoundAnalyser::FloatArg &arg)
{
	auto analyserId = arg.getId();
	auto pitchValue = arg.getValue();
}
void ofApp::onRootMeanSquare(ofxSoundAnalyser::FloatArg &arg)
{
	auto analyserId = arg.getId();
	auto rms = arg.getValue();
}
void ofApp::onFftMagnitudeSpectrum(ofxSoundAnalyser::FloatVecArg &arg)
{
	auto analyserId = arg.getId();
	auto fftValues = arg.getValue();
	for (auto fftValue : fftValues)
	{
	}
}
void ofApp::onMelFrequencySpectrum(ofxSoundAnalyser::FloatVecArg &arg)
{
	auto analyserId = arg.getId();
	auto melValues = arg.getValue();
	for (auto melValue : melValues)
	{
	}
}
void ofApp::onSpectralCentroid(ofxSoundAnalyser::FloatArg &varg) {}
void ofApp::onSpectralCrest(ofxSoundAnalyser::FloatArg &varg) {}
void ofApp::onSpectralDifference(ofxSoundAnalyser::FloatArg &arg) {}
void ofApp::onSpectralFlatness(ofxSoundAnalyser::FloatArg &arg) {}
void ofApp::onZeroCrossingRate(ofxSoundAnalyser::FloatArg &arg) {}
void ofApp::onChord(ofxSoundAnalyser::FloatArg &arg) {}
void ofApp::onChromogram(ofxSoundAnalyser::FloatVecArg &arg) {}