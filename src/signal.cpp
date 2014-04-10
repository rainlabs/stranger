#include "signal.hpp"

Signal::Signal() {
    mSoundFile = nullptr;
    mSoundInfo = nullptr;
}

Signal::~Signal() {
    clean();
}

Signal::iterator Signal::begin() {
    mSamples.begin();
}

Signal::iterator Signal::end() {
    mSamples.end();
}

bool Signal::loadFromFile(const std::string& filename) {
    SAMPLE_TYPE *value = new SAMPLE_TYPE(0.0);
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

vector2d Signal::split(std::size_t size, std::size_t overlap) {
    vector2d ret;
    int i, step;
    step = size - overlap;
    
    // TODO add zeros elements
    for(i = 0; i < mSamples.size() - size; i+= step) {
        std::vector<double> vec;
        vec.insert(vec.end(), mSamples.begin() + i, mSamples.begin() + i + size);
        ret.push_back(vec);
    }
    
    return ret;
}

std::size_t Signal::getChannelCount() {
    return mSoundInfo->channels;
}

std::size_t Signal::getSampleCount() {
//    return mSoundInfo->frames;
    return mSamples.size();
}

std::size_t Signal::getSampleRate() {
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