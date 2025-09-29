#include <iostream>
#include "DataManager.hpp"
/*
画像、マスク付き
文字データ

*/

std::tuple<int,std::string> ToBinary(int Number) {
    std::string BinaryText = "";
    int BinarySize = 0;
    while (Number > 0) {
        BinaryText = (Number % 2 ? "1" : "0") + BinaryText;
        Number /= 2;
        BinarySize += 1;
    }
    std::tuple<int, std::string> ReturnData = {BinarySize, BinaryText};
    std::tuple<int, std::string> None = {0, "0"};
    return BinaryText.empty() ? None : ReturnData;
}
std::string Filename = "Test";
std::vector<std::vector<std::vector<uint32_t>>> data = {{{22,23,23,22}, {22,23,22,20}}};

int StaticImageSave(std::string FileName, std::vector<std::vector<std::vector<uint32_t>>> Data) {
    std::string FilePath = "Binary/" + FileName + ".bin";
    std::string FileInfoPath = "Binary/" + FileName + "Info.bin";
    std::ofstream Binary(FilePath, std::ios::binary);

    std::map<int, int> R;
    std::map<int, int> G;
    std::map<int, int> B;
    std::map<int, int> A;
    std::map<int, int> Layer;

    for (size_t i = 0; i < Data.size(); i++) {
        for (size_t i2 = 0; i2 < Data[i].size(); i2++) {
            R[Data[i][i2][0]] += 1;
            G[Data[i][i2][1]] += 1;
            B[Data[i][i2][2]] += 1;
            A[Data[i][i2][3]] += 1;
            Layer[Data[i][i2][4]] += 1;
            
        }   
    }
}

