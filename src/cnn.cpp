/* 
 * File:   cnn.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 13 апреля 2014 г., 11:47
 */

#include "stranger/cnn.hpp"
//
//namespace Stranger {
//    CNN::CNN(std::string filename) {
//        cCNN_boot();
//        mNetwork = nullptr;
//        mFilename = "";
//        load(filename);
//    }
//    
//    bool CNN::load(std::string filename) {
//        if(filename.size() > 0) {
//            mFilename = filename;
//        }
//        if (mFilename.size() == 0) {
//            return false;
//        }
//        mNetwork = cCNN_load(mFilename.c_str());
//        return true;
//    }
//    
//    bool CNN::load(std::string filename) {
//        if(filename.size() > 0) {
//            mFilename = filename;
//        }
//        if (mFilename.size() == 0) {
//            return false;
//        }
//        mNetwork = cCNN_save(mFilename.c_str());
//        return true;
//    }
//
//    CNN::~CNN() {
//    }
//    
//    /**
//     * AS IS
//     */
//    void CNN::getcurrenttime(char* outstr) {
//
//        time_t rawtime;
//        struct tm * timeinfo;
//
//        time (&rawtime);
//        timeinfo = localtime(&rawtime);
//
//        strftime(outstr, 23, "%Y-%m-%d %H:%M:%S", timeinfo);
//    }
//
//    void CNN::hessian_reest_begin_callback(unsigned i, unsigned N) {
//
//        char datetime[24];
//        getcurrenttime(datetime);
//
//        printf("[%s][Epoch:%2u/%2u] Reestimating Hessian diagonal elements:             ", datetime, i+1, N);
//        fflush(stdout);
//    }
//
//    void CNN::hessian_reest_step_callback(unsigned j, unsigned n_sub) {
//
//        printf("\b\b\b\b\b\b\b\b\b\b\b\b%4u/%4u...", j+1, n_sub);
//    }
//
//    void CNN::hessian_reest_end_callback(unsigned i, unsigned N) {
//
//        printf("\b\b\b\b\b\b\b\b\b\b\b\bdone.         \n");
//    }
//
//    void CNN::train_begin_callback(unsigned i, unsigned N, double eta) {
//
//        char datetime[24];
//        getcurrenttime(datetime);
//
//        printf("[%s][Epoch:%2u/%2u] Training network (eta = %.5f):               ", datetime, i+1, N, eta);
//        fflush(stdout);
//    }
//
//    void CNN::train_step_callback(unsigned j, unsigned n_train) {
//
//        printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b%5u/%5u...", j+1, n_train);
//    }
//
//    void CNN::train_end_callback(unsigned i, unsigned N) {
//
//        char datetime[24];
//        getcurrenttime(datetime);
//
//        printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\bdone.         \n");
//        printf("[%s][Epoch:%2u/%2u] Evaluating performance... ", datetime, i+1, N);
//        fflush(stdout);
//    }
//
//    void CNN::perf_callback(unsigned i, unsigned N,
//                       double MCR_train, double MCR_test)
//    {
//        printf("MCR_train = %3.2f%%, MCR_test = %3.2f%%\n\n", MCR_train, MCR_test);
//    }
//
//}