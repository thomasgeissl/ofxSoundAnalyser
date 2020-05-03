#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include <regex>

namespace ofxSoundAnalyser
{
    class FloatArg
    {
    public:
        FloatArg(int id, float value) : _id(id), _value(value)
        {
        }
        int getId() { return _id; }
        float getValue() { return _value; }
        int _id;
        float _value;
    };
    class FloatVecArg
    {
    public:
        FloatVecArg(int id, std::vector<float> value) : _id(id), _value(value)
        {
        }
        void add(float value)
        {
            _value.push_back(value);
        }
        int getId() { return _id; }
        std::vector<float> getValue() { return _value; }
        int _id;
        std::vector<float> _value;
    };

    class Listener
    {
    public:
        virtual void onPeakEnergy(FloatArg &varg) {}
        virtual void onPitch(FloatArg &arg) {}
        virtual void onRootMeanSquare(FloatArg &arg) {}
        virtual void onFftMagnitudeSpectrum(FloatVecArg &arg) {}
        virtual void onMelFrequencySpectrum(FloatVecArg &arg) {}
        virtual void onSpectralCentroid(FloatArg &varg) {}
        virtual void onSpectralCrest(FloatArg &varg) {}
        virtual void onSpectralDifference(FloatArg &arg) {}
        virtual void onSpectralFlatness(FloatArg &arg) {}
        virtual void onZeroCrossingRate(FloatArg &arg) {}
        virtual void onChord(FloatArg &arg) {}
        virtual void onChromogram(FloatVecArg &arg) {}
    };

    class Analyser
    {
    public:
        Analyser(int port = 8000)
        {
            _oscReceiver.setup(port);
        }
        void setup() {}
        void update()
        {
            while (_oscReceiver.hasWaitingMessages())
            {
                ofxOscMessage m;
                _oscReceiver.getNextMessage(m);

                auto peakEnergyRegex = std::regex("/([0-9]+)/peakEnergy");
                auto pitchRegex = std::regex("/([0-9]+)/pitch");
                auto rmsRegex = std::regex("/([0-9]+)/rms");
                auto fftRegex = std::regex("/([0-9]+)/fft");
                auto melRegex = std::regex("/([0-9]+)/mel");
                auto spectralCentroidRegex = std::regex("/([0-9]+)/spectralCentroid");
                auto spectralCrestRegex = std::regex("/([0-9]+)/spectralCrest");
                auto spectralDifferenceRegex = std::regex("/([0-9]+)/spectralDifference");
                auto spectralFlatnessRegex = std::regex("/([0-9]+)/spectralFlatness");
                auto zcrRegex = std::regex("/([0-9]+)/zrc");
                auto chordDetectorRegex = std::regex("/([0-9]+)/chordDetector");
                auto chromogramRegex = std::regex("/([0-9]+)/chromogram");

                smatch peakEnergyResult;
                smatch pitchResult;
                smatch rmsResult;
                smatch fftResult;
                smatch melResult;
                smatch spectralCentroidResult;
                smatch spectralCrestResult;
                smatch spectralDifferenceResult;
                smatch spectralFlatnessResult;
                smatch zcrResult;
                smatch chordDetectorResult;
                smatch chromogramResult;

                if (regex_search(m.getAddress(), peakEnergyResult, peakEnergyRegex))
                {
                    auto id = ofToInt(peakEnergyResult[1]);
                    auto value = FloatArg(id, m.getArgAsFloat(0));
                    _peakEnergyEvent.notify(value);
                }

                else if (regex_search(m.getAddress(), pitchResult, pitchRegex))
                {
                    auto id = ofToInt(pitchResult[1]);
                    auto value = FloatArg(id, m.getArgAsFloat(0));
                    _pitchEvent.notify(value);
                }

                else if (regex_search(m.getAddress(), rmsResult, rmsRegex))
                {
                    auto value = FloatArg(ofToInt(rmsResult[1]), m.getArgAsFloat(0));
                    _rootMeanSquareEvent.notify(value);
                }

                else if (regex_search(m.getAddress(), fftResult, fftRegex))
                {
                    for (auto i = 0; i < m.getNumArgs(); i++)
                    {
                        std::vector<float> fft;
                        fft.push_back(m.getArgAsFloat(i));
                        auto arg = FloatVecArg(ofToInt(fftResult[1]), fft);
                        _fftMagnitudeSpectrumEvent.notify(arg);
                    }
                }

                else if (regex_search(m.getAddress(), melResult, melRegex))
                {
                    for (auto i = 0; i < m.getNumArgs(); i++)
                    {
                        std::vector<float> mel;
                        mel.push_back(m.getArgAsFloat(i));
                        auto arg = FloatVecArg(ofToInt(melResult[1]), mel);
                        _melFrequencySpectrumEvent.notify(arg);
                    }
                }
                else if (regex_search(m.getAddress(), spectralCentroidResult, spectralCentroidRegex))
                {
                    auto value = FloatArg(ofToInt(spectralCentroidResult[1]), m.getArgAsFloat(0));
                    _spectralCentroidEvent.notify(value);
                }
                else if (regex_search(m.getAddress(), spectralCrestResult, spectralCrestRegex))
                {
                    auto value = FloatArg(ofToInt(spectralCrestResult[1]), m.getArgAsFloat(0));
                    _spectralCrestEvent.notify(value);
                }
                else if (regex_search(m.getAddress(), spectralDifferenceResult, spectralDifferenceRegex))
                {
                    auto value = FloatArg(ofToInt(spectralDifferenceResult[1]), m.getArgAsFloat(0));
                    _spectralDifferenceEvent.notify(value);
                }
                else if (regex_search(m.getAddress(), spectralFlatnessResult, spectralFlatnessRegex))
                {
                    auto value = FloatArg(ofToInt(spectralFlatnessResult[1]), m.getArgAsFloat(0));
                    _spectralFlatnessEvent.notify(value);
                }
                else if (regex_search(m.getAddress(), zcrResult, zcrRegex))
                {
                    auto value = FloatArg(ofToInt(zcrResult[1]), m.getArgAsFloat(0));
                    _zeroCrossingRateEvent.notify(value);
                }
                else if (regex_search(m.getAddress(), chordDetectorResult, chordDetectorRegex))
                {
                    auto value = FloatArg(ofToInt(zcrResult[1]), m.getArgAsFloat(0));
                    _chordEvent.notify(value);
                }
                else if (regex_search(m.getAddress(), chromogramResult, chromogramRegex))
                {
                    for (auto i = 0; i < m.getNumArgs(); i++)
                    {
                        std::vector<float> chromogram;
                        chromogram.push_back(m.getArgAsFloat(i));
                        auto arg = FloatVecArg(ofToInt(melResult[1]), chromogram);
                        _chromogramEvent.notify(arg);
                    }
                }
            }
        }

        void addListener(Listener *listener)
        {
            ofAddListener(_peakEnergyEvent, listener, &Listener::onPeakEnergy);
            ofAddListener(_pitchEvent, listener, &Listener::onPitch);
            ofAddListener(_rootMeanSquareEvent, listener, &Listener::onRootMeanSquare);
            ofAddListener(_fftMagnitudeSpectrumEvent, listener, &Listener::onFftMagnitudeSpectrum);
            ofAddListener(_melFrequencySpectrumEvent, listener, &Listener::onMelFrequencySpectrum);
            ofAddListener(_spectralCentroidEvent, listener, &Listener::onSpectralCentroid);
            ofAddListener(_spectralCrestEvent, listener, &Listener::onSpectralCrest);
            ofAddListener(_spectralDifferenceEvent, listener, &Listener::onSpectralDifference);
            ofAddListener(_spectralFlatnessEvent, listener, &Listener::onSpectralFlatness);
            ofAddListener(_zeroCrossingRateEvent, listener, &Listener::onZeroCrossingRate);
            ofAddListener(_chordEvent, listener, &Listener::onChord);
            ofAddListener(_chromogramEvent, listener, &Listener::onChromogram);
        }

        ofEvent<FloatArg> _peakEnergyEvent;
        ofEvent<FloatArg> _pitchEvent;
        ofEvent<FloatArg> _rootMeanSquareEvent;
        ofEvent<FloatVecArg> _fftMagnitudeSpectrumEvent;
        ofEvent<FloatVecArg> _melFrequencySpectrumEvent;
        ofEvent<FloatArg> _spectralCentroidEvent;
        ofEvent<FloatArg> _spectralCrestEvent;
        ofEvent<FloatArg> _spectralDifferenceEvent;
        ofEvent<FloatArg> _spectralFlatnessEvent;
        ofEvent<FloatArg> _zeroCrossingRateEvent;
        ofEvent<FloatArg> _chordEvent;
        ofEvent<FloatVecArg> _chromogramEvent;

        ofxOscReceiver _oscReceiver;
    };

}; // namespace ofxSoundAnalyser