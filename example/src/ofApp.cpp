#include "ofApp.h"

void ofApp::setup(){
	_analyser.addListener(this);
}
void ofApp::update(){}
void ofApp::draw(){}
void ofApp::exit(){}

void ofApp::onPeakEnergy(std::pair<int, float> & value){
	auto analyserId = value.first;
	auto peakEnergyValue = value.second;
}
void ofApp::onPitch(std::pair<int, float> & value){
	auto analyserId = value.first;
	int note = std::round((value.second > 0 ? 17.3123405046 * log(.12231220585 * value.second) : -1500));
}
void ofApp::onRootMeanSquare(std::pair<int, float> & value){
	auto analyserId = value.first;
	auto rms = value.second;
}
void ofApp::onFftMagnitudeSpectrum(std::pair<int, std::vector<float>> & value){
	auto analyserId = value.first;
	auto fftValues = value.second;
	for(auto fftValue : fftValues){

	}
}
void ofApp::onMelFrequencySpectrum(std::pair<int, std::vector<float>> & value){ 
	auto analyserId = value.first;
	auto melValues = value.second;
	for(auto melValue : melValues){

	}
}