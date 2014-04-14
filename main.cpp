/* 
 * File:   main.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 10 апреля 2014 г., 19:55
 */

#include "stranger.hpp"
#include <iostream>
#include <fstream>

using namespace Stranger;

std::string gFile       = "";
std::string gSvmDb      = "data/svm.model";
SizeType gDuration      = 30;
SizeType gShift         = 15;
SizeType gFrameSize     = 1;
int gLifter             = 16;
SizeType gMode          = Vad::PREDICT;

void processArguments(int argc, char *argv[]);

void progress(float percent) {
    std::cout << "\r" << percent << "% completed." << std::flush;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main(int argc, char* argv[]) {
    processArguments(argc, argv);
    
    Vad vad(gSvmDb, gMode);
    std::size_t i;
    std::vector<SampleType> values;
    
    vad.setDuration(gDuration)
            .setFrame(gFrameSize)
            .setShift(gShift)
            .setLifterIndex(gLifter);
    
    if (gMode == Vad::PREDICT) {
        vad.loadSignal(gFile);
        values = vad.process();
        for(i = 0; i < values.size(); i++) {
            std::cout << i << "\t" << values[i] << std::endl;
        }
    } else {
        std::ifstream file(gFile);
        int type;
        SizeType procent = 100.0 / std::count(std::istreambuf_iterator<char>(file), 
             std::istreambuf_iterator<char>(), '\n');
        int n = 0;
        file.close();
        file.open(gFile);
        
        for (std::string line; std::getline(file, line); ) {
            progress(procent * n++);
            auto x = split(line, '\t');
            type = atoi(x.front().c_str());
            vad.loadSignal(x[1]).destroyMfcc();
            if (type > 0) {
                vad.setVoice();
            } else {
                vad.setSilence();
            }
            vad.process();
        }
        vad.saveSVM();
    }
    
    return 0;
}

/**
 * -m     - mode (0-TRAIN|1-PREDICT, default: PREDICT)
 * -t     - duration in ms (default: 30)
 * -s     - shift in ms (default: 15)
 * -d     - svm model db (default: "svm.model")
 * -f     - frame size (default: 1)
 * -l     - lifter coefficient (default: 16, without liftering)
 * @param argc
 * @param argv
 */
void processArguments(int argc, char *argv[]) {
    char* s1;
    
    if (argc <= 1) {
        fprintf(stderr, "arguments are not found\n");
        exit(1);
    }
    
    for(int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != 0) {
            s1 = "";
            if (i + 1 >= argc) {
                fprintf(stderr, "not valid argument %s\n", argv[i]);
                exit(2);
            }
            s1 = argv[i + 1];
            switch (argv[i][1]) {
                case 't':
                    gDuration = atoi(s1);
                    break;
                case 'd':
                    gSvmDb = s1;
                    break;
                case 's':
                    gShift = atoi(s1);
                    break;
                case 'f':
                    gFrameSize = atoi(s1);
                    break;
                case 'l':
                    gLifter = atoi(s1);
                    break;
                case 'm':
                    gMode = atoi(s1);
                    break;
            }
        } else {
            gFile = argv[i];
        }
    }
    
    if (gFile.size() == 0) {
        fprintf(stderr, "sound file is not specified for PREDICT mode\n");
        exit(3);
    }
}