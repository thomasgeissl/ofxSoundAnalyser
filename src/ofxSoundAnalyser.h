#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include <regex>

class ofxSoundAnalyserListener {
public:
    virtual void onPeakEnergy(std::pair<int, float> & value){}
    virtual void onPitch(std::pair<int, float> & value){}
    virtual void onRootMeanSquare(std::pair<int, float> & value){}
    virtual void onFftMagnitudeSpectrum(std::pair<int, std::vector<float>> & value){}
    virtual void onMelFrequencySpectrum(std::pair<int, std::vector<float>> & value){}
//TODO: spectralCentroid, spectralCrest, spectralDifference, spectralFlatness, zeroCrossingRate
};

class ofxSoundAnalyser {
public:
    ofxSoundAnalyser(int port = 8000){
        _oscReceiver.setup(port);
    }
    void setup(){}
    void update(){
        while(_oscReceiver.hasWaitingMessages()) {
            ofxOscMessage m;
            _oscReceiver.getNextMessage(m);
            
            auto peakEnergyRegex = std::regex("/([0-9]+)/peakEnergy");
            auto pitchRegex = std::regex("/([0-9]+)/pitch");
            auto rmsRegex = std::regex("/([0-9]+)/rms");
            auto fftRegex = std::regex("/([0-9]+)/fft");
            auto melRegex = std::regex("/([0-9]+)/mel");

            smatch peakEnergyResult;
            smatch pitchResult;
            smatch rmsResult;
            smatch fftResult;
            smatch melResult;

            if(regex_search(m.getAddress(), peakEnergyResult, peakEnergyRegex)) {
                auto peakEnergy = m.getArgAsFloat(0);
                auto id = ofToInt(peakEnergyResult[1]);
                std::pair<int, float> value(id, peakEnergy);
                _peakEnergyEvent.notify(value);
            }
            
            if(regex_search(m.getAddress(), pitchResult, pitchRegex)) {
                auto pitch = m.getArgAsFloat(0);
                auto id = ofToInt(pitchResult[1]);
                std::pair<int, float> value(id, pitch);
                _pitchEvent.notify(value);
            }
            
            if(regex_search(m.getAddress(), rmsResult, rmsRegex)) {
                auto rms = m.getArgAsFloat(0);
                auto id = ofToInt(rmsResult[1]);
                std::pair<int, float> value(id, rms);
                _rootMeanSquareEvent.notify(value);
            }
            
            if(regex_search(m.getAddress(), fftResult, fftRegex)) {
                for(auto i = 0; i < m.getNumArgs(); i++){
                    std::vector<float> fft;
                    fft.push_back(m.getArgAsFloat(i));
                    auto id = ofToInt(fftResult[1]);
                    std::pair<int, std::vector<float>> value(id, fft);
                    _fftMagnitudeSpectrumEvent.notify(value);
                }
            }
            
            if(regex_search(m.getAddress(), melResult, melRegex)) {
                for(auto i = 0; i < m.getNumArgs(); i++){
                    std::vector<float> mel;
                    mel.push_back(m.getArgAsFloat(i));
                    auto id = ofToInt(melResult[1]);
                    std::pair<int, std::vector<float>> value(id, mel);
                    _melFrequencySpectrumEvent.notify(value);
                }
            }
        }
    }
    
    void addListener(ofxSoundAnalyserListener* listener){
        ofAddListener(_peakEnergyEvent, listener, &ofxSoundAnalyserListener::onPeakEnergy);
        ofAddListener(_pitchEvent, listener, &ofxSoundAnalyserListener::onPitch);
        ofAddListener(_rootMeanSquareEvent, listener, &ofxSoundAnalyserListener::onRootMeanSquare);
        ofAddListener(_fftMagnitudeSpectrumEvent, listener, &ofxSoundAnalyserListener::onFftMagnitudeSpectrum);
        ofAddListener(_melFrequencySpectrumEvent, listener, &ofxSoundAnalyserListener::onMelFrequencySpectrum);
    }
    
    ofEvent<std::pair<int,float>> _peakEnergyEvent; //(id, value)
    ofEvent<std::pair<int,float>> _pitchEvent; //(id, value)
    ofEvent<std::pair<int,std::vector<float>>> _fftMagnitudeSpectrumEvent; //(id, value)
    ofEvent<std::pair<int,std::vector<float>>> _melFrequencySpectrumEvent; //(id, value)
    ofEvent<std::pair<int,float>> _rootMeanSquareEvent; //(id, value)
    ofEvent<std::pair<int,float>> _spectralCentroidEvent; //(id, value)
    ofEvent<std::pair<int,float>> _spectralCrestEvent; //(id, value)
    ofEvent<std::pair<int,float>> _spectralDifferenceEvent; //(id, value)
    ofEvent<std::pair<int,float>> _spectralFlatnessEvent; //(id, value)
    ofEvent<std::pair<int,float>> _zeroCrossingRateEvent; //(id, value)

    ofxOscReceiver _oscReceiver;
};
