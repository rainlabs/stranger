#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <sndfile.h>
#include "global.hpp"

namespace Stranger {
    /**
    * @brief The Signal class as sound reader
    */
   class STRANGER_EXPORT Signal
   {
   public:
       Signal();
       virtual ~Signal();

       typedef std::vector<SampleType>::iterator iterator;
       typedef std::vector<SampleType>::const_iterator const_iterator;

       iterator begin();
       iterator end();

       bool isLoaded();

       /**
        * @brief get channel count (mono, stereo, etc.)
        * @return unsigned int
        */
       std::size_t getChannelCount();

       /**
        * @brief get sample (frame) count
        * @return unsigned int (size_t)
        */
       std::size_t getSampleCount();

       /**
        * @brief get sample rate in Hz
        * @return unsigned int
        */
       std::size_t getSampleRate();

       /**
        * @brief load sound from file
        * @param filename
        * @return bool success
        */
       bool loadFromFile(const std::string& filename );

       /**
        * @brief split samples by size with overlap
        * @param size
        * @param overlap
        * @return 2d vector
        */
       vector2d split(std::size_t size, std::size_t overlap);
   private:
       void clean();
       std::vector<SampleType> mSamples;
       SNDFILE* mSoundFile;
       SF_INFO* mSoundInfo;
   };
}

#endif // SIGNAL_HPP
