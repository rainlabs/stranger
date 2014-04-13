/* 
 * File:   svm.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 13 апреля 2014 г., 12:20
 */

#ifndef SVM_HPP
#define	SVM_HPP

#include "global.hpp"
#include "stranger_exception.hpp"
#include <svm.h>

namespace Stranger {
    
    /**
     * @brief create class of SVM learning
     * @param filename not required
     */
    class STRANGER_EXPORT SVM {
    public:
        SVM(SizeType featuresCount, std::string filename="");
        virtual ~SVM();
        
        /**
         * @brief load svm weights from file
         * @param filename not required
         * @return 
         */
        bool load(std::string filename="");
        
        /**
         * @brief save svm weights into file
         * @param filename not required
         * @return 
         */
        bool save(std::string filename="");
        
        /**
         * @brief set filename directly
         * @param filename
         */
        void setFilename(std::string filename);
        
        /**
         * @brief push features vector into trainData with it class
         * @param features vector
         * @param cls
         */
        void push_back(std::vector<SampleType> features, SampleType cls);
        
        /**
         * @brief train with self train data
         */
        void train();
        
        /**
         * @brief raw predict data
         * @param map
         * @return 
         */
        SampleType predict(std::vector<SampleType> features);
    protected:
        struct svm_problem*   initializeProblem();
        struct svm_parameter* initializeParameter();
        
    private:
        struct svm_model*       mModel;
        SizeType                mFeaturesCount;
        std::string             mFilename;
        std::vector<double>     mTrainData;
        std::vector<double>     mTrainCls;

    };
}

#endif	/* SVM_HPP */

