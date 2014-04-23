/* 
 * File:   test_helper.h
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 2 апреля 2014 г., 12:11
 */

#ifndef TEST_HELPER_H
#define	TEST_HELPER_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include "gnuplot.hpp";

typedef std::vector< std::vector<double> > vector2d;

class TestHelper {
public:
    static bool savePoints(vector2d vec, std::vector<float> x, const std::string& filename, int color = 0) {
        std::ofstream file;
        file.open((filename + ".dat").data(), std::ios::out | std::ios::app);
        float tmp;
        int i, j;
        tmp = x.size();
//        std::cout << tmp << std::endl;
//        fwrite(&tmp, sizeof(float), 1, file);
        /* write x values */
//        for(i = 0; i < x.size(); i++) {
//            fwrite(&x[i], sizeof(float), 1, file);
//        }
        for(j = 0; j < vec.size(); j++) {
            for(i = 0; i < x.size(); i++) {
                file << x[i] << " " << vec[j][i] << " " << color << std::endl;
//                fwrite(&x[i], sizeof(float), 1, file);
//                tmp = vec[j][i];
//                fwrite(&tmp, sizeof(float), 1, file);
            }
            file << std::endl;
            file << std::endl;
        }
        
        file.close();
        
    }
    static bool plotPoints(const std::string& filename) {
        try {
            Gnuplot g;
            g.cmd("set terminal png size 1920, 1080");
            g.cmd(("set output \"" + filename + ".png\""));
            g.cmd( ("plot \"" + filename + ".dat\" w l") );
        } catch (GnuplotException ge) {
            std::cout << ge.what() << std::endl;
            return false;
        }
        
        return true;
    }
    static bool saveMatrix(vector2d vec, std::vector<float> x, std::vector<float> y, const std::string& filename) {
        FILE * file = fopen((filename + ".dat").data(), "wb");
        float tmp;
        int i;
        
        /* write x size */
        tmp = x.size();
        fwrite(&tmp, sizeof(float), 1, file);
        /* write x values */
        for(float t : x) {
            fwrite(&t, sizeof(float), 1, file);
        }
        /* write y values with matrix */
        for(i = 0; i < y.size(); i++) {
            fwrite(&y[i], sizeof(float), 1, file);
            for(auto list : vec) {
                tmp = (float) list[i];
                fwrite(&tmp, sizeof(float), 1, file);
            }
        }
        
        fclose(file);
    }
    static bool plotMatrix(const std::string& filename) {
        try {
            Gnuplot g;
            g.cmd("set terminal png size 1920, 1080");
            g.cmd(("set output \"" + filename + ".png\""));
            g.cmd( ("plot \"" + filename + ".dat\" binary matrix with image") );
        } catch (GnuplotException ge) {
            std::cout << ge.what() << std::endl;
            return false;
        }
        
        return true;
    }
};

#endif	/* TEST_HELPER_H */

