#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../../Data/DataManager.hpp"

struct Data {
    std::string ImageType;
    std::string ImagePath;
    std::vector<std::vector<tuple<uint8_t, uint8_t, uint8_t, std::string>>> ImageMask;
    std::vector<std::string> ImageTags;
    std::vector<tuple<int, int, int, int>> BCHW;
};

class Base {
public:
    struct Shaping(Data data); // 宣言
};