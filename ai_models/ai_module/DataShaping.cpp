#include "DataShaping.hpp"
#include <iostream>


/*
struct Data {
    std::string ImageType;
    std::string ImagePath;
    std::vector<std::vector<tuple<uint8_t, uint8_t, uint8_t, std::string>>> ImageMask;
    std::vector<std::string> ImageTags;
    std::vector<tuple<int, int, int, int>> BCHW;
};
*/
struct Base::Shaping(Data data) {
    int32_t ImageSize = data.BCHW[2] * data.BCHW[3];
    int64_t RGBAImageSize = data.BCHW[1] * ImageSize;
    int64_t BatchImageSize = data.BCHW[0] * RGBAImageSize;
    int8_t Batch = data.BCHW[0];
    uint8_t MaxRGBA = 255;
    uint16_t H = data.BCHW[2];
    uint16_t W = data.BCHW[3];
    uint8_t C = data.BCHW[1];
    std::map<std::string, int> MaskIDMap;

    struct ReturnStruct {
        std::vector<float> ImageMap(BatchImageSize, 0.0f);
        std::vector<int64_t> MaskMap(ImageSize, 0);
        std::vector<float> TagList;
    }

    std::unordered_set<std::string> Extensions = {".png", ".jpg", ".bmp", ".tif", ".tiff", ".gif"};

    // 画像の拡張子判定
    if (Extensions.find(data.ImageType) != Extensions.end()) {
        cv::Mat Image = cv::imread(data.ImagePath, cv::IMREAD_UNCHANGED);
        
        // 画像のピクセルごとの数値を取得
        for(int h = 0; h < img.rows; ++h){
            for(int w = 0; w < img.cols; ++w){
                cv::Vec4b pixel = img.at<cv::Vec4b>(h, w); // BGRA順

                // ピクセルの取得
                unsigned char B = pixel[0];
                unsigned char G = pixel[1];
                unsigned char R = pixel[2];
                unsigned char A = pixel[3];

                // RGBAのfloat化
                float RFloat = R / MaxRGBA;
                float GFloat = G / MaxRGBA;
                float BFloat = B / MaxRGBA;
                float AFloat = A / MaxRGBA;

                // 色の位置計算
                int32_t RPosIs = Batch * (C * H * W) + 0 * (H * W) + h * W + w;
                int32_t GPosIs = Batch * (C * H * W) + 1 * (H * W) + h * W + w;
                int32_t BPosIs = Batch * (C * H * W) + 2 * (H * W) + h * W + w;
                int32_t APosIs = Batch * (C * H * W) + 3 * (H * W) + h * W + w;
                
                // ImageMapへの保存
                ReturnStruct.ImageMap[RPosIs] = RFloat;
                ReturnStruct.ImageMap[GPosIs] = GFloat;
                ReturnStruct.ImageMap[BPosIs] = BFloat;
                ReturnStruct.ImageMap[APosIs] = AFloat;
                
                if (!data.ImageMask.empty() && !data.ImageMask[h].empty()) {
                    std::string CurrentTagID = std::to_string(R) << std::to_string(G) << std::to_string(B);

                    if (MaskIDMap.find(CurrentTagID) != MaskIDMap.end()) {
                        int32_t MaskMapPos = Batch * (H * W) + h * W + w;
                        ReturnStruct.MaskMap[MaskMapPos] = MaskIDMap[CurrentTagID];
                    } else {
                        uint16_t MaskID = CsvLoadData("TagIDList", data.ImageMask[h][w][3]);
                        MaskIDMap[CurrentTagID] = MaskID;
                        int32_t MaskMapPos = Batch * (H * W) + h * W + w;
                        ReturnStruct.MaskMap[MaskMapPos] = MaskID;
                    }
                }
            }
        }
        
        for (size_t i = 0; i < data.ImageTags.size(); ++i) {
            uint16_t TagID = CsvLoadData("TagIDList", data.ImageTags[i]);
            if (TagID) {
            ReturnStruct.TagList[i] = 1.0f;
            }
        }
    }
    return ReturnStruct
}