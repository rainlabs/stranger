#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <sndfile.h>
#include "global.hpp"
#include "stranger_exception.hpp"
#include "misc.hpp"

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
        * @brief split samples by size with shift
        * @param size
        * @param shift
        * @return 2d vector
        */
       vector2d split(SizeType size, SizeType shift = 0);
       
       /**
        * @brief split samples by length and shift in ms
        * @param length time length in ms
        * @param shift time length in ms
        */
       vector2d split(float length, float shift = 0);
   private:
       void clean();
       std::vector<SampleType> mSamples;
       SNDFILE* mSoundFile;
       SF_INFO* mSoundInfo;
   };
}

#endif // SIGNAL_HPP
