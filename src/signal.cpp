#include "stranger/signal.hpp"

namespace Stranger {
    
    Signal::Signal() {
        mSoundFile = nullptr;
        mSoundInfo = nullptr;
    }

    Signal::~Signal() {
        clean();
    }

    Signal::iterator Signal::begin() {
        return mSamples.begin();
    }

    Signal::iterator Signal::end() {
        return mSamples.end();
    }

    bool Signal::isLoaded() {
        return (mSoundFile != nullptr);
    }

    bool Signal::loadFromFile(const std::string& filename) {
        SampleType *value = new SampleType(0.0);
        clean();
        mSoundInfo = new SF_INFO;
        mSoundInfo->format = 0;

        mSoundFile = sf_open(filename.data(), SFM_READ, mSoundInfo);
        if (mSoundFile == 0)
            return false;

        while(sf_read_double(mSoundFile, value, 1)) {
            mSamples.push_back( *value );
        }
        sf_seek(mSoundFile, 0, SEEK_SET);

        return true;
    }

    vector2d Signal::split(SizeType size, SizeType shift) {
        vector2d ret;
        std::size_t i, j;
        SizeType step;
        step = shift;
        
        if (size == 0) {
            throw StrangerException("Split size can't be zero");
        }
        
        /* set default shift as size */
        if (step == 0) {
            step = size;
        }

        // TODO add zeros elements
        for(i = 0; i < mSamples.size() - size; i+= step) {
            std::vector<SampleType> vec;
            vec.insert(vec.end(), mSamples.begin() + i, mSamples.begin() + i + size);
//            if (vec.size() < size) {
//                for(j = vec.size(); j < size; j++) {
//                    vec.push_back(0.0);
//                }
//            }
            ret.push_back(vec);
        }

        return ret;
    }
    
    vector2d Signal::split(float length, float shift) {
        return split( Misc::msToFrameSize(length, getSampleRate()), Misc::msToFrameSize(shift, getSampleRate()) );
    }
    
    std::size_t Signal::getChannelCount() {
        if (mSoundInfo == nullptr)
            return 0;
        return mSoundInfo->channels;
    }

    std::size_t Signal::getSampleCount() {
    //    return mSoundInfo->frames;
        return mSamples.size();
    }

    std::size_t Signal::getSampleRate() {
        if (mSoundInfo == nullptr)
            return 0;
        return mSoundInfo->samplerate;
    }

    void Signal::clean() {
        if(mSoundFile != nullptr) {
            sf_close(mSoundFile);
    //        delete mSoundFile;
        }

        if(mSoundInfo != nullptr)
            delete mSoundInfo;
    }
}