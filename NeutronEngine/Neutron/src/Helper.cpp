//
// Created by aw1lt on 03/12/22.
//
#include "Neutron/Helper.h"
#include "Logger.h"

namespace Neutron {
    std::vector<int> range(unsigned int start, unsigned int end, int step) {
        Logger::Assert(!((end < start) && (step > 0)), "end is smaller than start and step is positive", 5);

        std::vector<int> res = {};

        for(int x = start; x != end; x+=step) {
            res.push_back(x);
        }

        return res;
    }

    std::vector<int> range(unsigned int end) {
        return range(0, end, 1);
    }
    std::vector<std::string> split(std::string string, std::string delimiter) {
        std::vector<std::string> results;
        size_t pos = 0;
        while (true) {
            size_t next = string.find(delimiter, pos);
            results.push_back(string.substr(pos, next - pos));
            if (next == std::string::npos) break;
            pos = next + delimiter.size();
        }

        return results;
    }

    int parseInt(std::string str) {
        int temp = 0;
        for (int i = 0; i < str.length(); i++) {
            temp = temp * 10 + (str[i] - '0');
        }
        return temp;
    }
}