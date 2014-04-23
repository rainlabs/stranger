/* 
 * File:   svm.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 13 апреля 2014 г., 12:20
 */

#include "stranger/svm.hpp"

namespace Stranger {
    SVM::SVM(SizeType featuresCount, std::string filename) {
        if (featuresCount == 0) {
            throw StrangerException("Features vector must have size greater than zero");
        }
        mModel = nullptr;
        mFeaturesCount = featuresCount;
        setFilename(filename);
    }
    
    SVM::~SVM() {}
    
    bool SVM::load(std::string filename) {
        setFilename(filename);
        mModel = svm_load_model(mFilename.c_str());
        return true;
    }
    
    bool SVM::save(std::string filename) {
        setFilename(filename);
        int flag = svm_save_model(mFilename.c_str(),mModel);
        return true;
    }
    
    void SVM::setFilename(std::string filename) {
        if (filename.size() > 0)
            mFilename = filename;
    }
    
    void SVM::push_back(std::vector<SampleType> features, SampleType cls) {
        if (features.size() != mFeaturesCount) {
            throw StrangerException("Features vector have incorrect size");
        }
        for(SampleType f : features) {
            mTrainData.push_back( double(f) );
        }
        mTrainCls.push_back( cls );
    }
    
    void SVM::train() {
        if (mTrainData.size() < 2) {
            throw StrangerException("Train data size must be greater than 1");
        }
        struct svm_problem* problem = initializeProblem();
        struct svm_parameter* param = initializeParameter();
        const char* errorMsg;
        
        errorMsg = svm_check_parameter(problem,param);
        if(errorMsg) {
            throw StrangerException(errorMsg);
        }
        
        mModel = svm_train(problem,param);
        free(problem);
    }
    
    SampleType SVM::predict(std::vector<SampleType> features) {
        struct svm_node* xSpace;
        int i;
        xSpace = Malloc(struct svm_node, mFeaturesCount + 1);

        for(i = 0; i < mFeaturesCount; i++) {
            xSpace[i].index = i + 1;
            xSpace[i].value = features[i];
        }
        xSpace[i].index = -1;

        return (SampleType) svm_predict(mModel, xSpace);
    }

    struct svm_problem* SVM::initializeProblem() {
        struct svm_problem* problem = Malloc(svm_problem, 1);
        int i, j, n = 0, k = 0;
        struct svm_node* xSpace;
        
        problem->l = (int) mTrainCls.size();
        problem->y = mTrainCls.data();
        problem->x = Malloc(struct svm_node*,problem->l);
        xSpace = Malloc(struct svm_node, mFeaturesCount * problem->l + problem->l); // + l (add -1 index to end)

        for(i = 0; i < problem->l; i++)
        {
            problem->x[i] = &xSpace[n];
            for(j = 0; j < mFeaturesCount; j++) {
                xSpace[n].index = j + 1;
                xSpace[n++].value = mTrainData[k++];
            }
            xSpace[n++].index = -1;
        }
        
        return problem;
    }
    
    struct svm_parameter* SVM::initializeParameter() {
        struct svm_parameter* parameter = Malloc(svm_parameter, 1);
        parameter->svm_type     = C_SVC;                // C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR
        parameter->kernel_type  = RBF;                  // LINEAR, POLY(!), RBF, SIGMOID, PRECOMPUTED
        parameter->degree       = 4;                    // POLY
        parameter->gamma        = 1. / mFeaturesCount;  // POLY, RBF, SIGMOID
        parameter->coef0        = 0;                    // POLY
        parameter->nu           = 0.5;                  // NU_SVC, ONE_CLASS, NU_SVR
        parameter->cache_size   = 100;                  // in MB
        parameter->C            = 4;                    // C_SVC, EPSILON_SVR, NU_SVR
        parameter->eps          = 0.001;               // stopping criteria
        parameter->p            = 0.1;                  // EPSILON_SVR
        parameter->shrinking    = 1;                    // use the shrinking heuristics
        parameter->probability  = 0;                    // do probability estimates
        parameter->nr_weight    = 0;                    // C_SVC
        parameter->weight_label = nullptr;              // C_SVC
        parameter->weight       = nullptr;              // C_SVC
        return parameter;
    }
}