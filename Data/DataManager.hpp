#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include "Includes/nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;
struct BinLoadReturn {

};

class DataManager{
public:
    BinLoadReturn BinLoadData(const std::string& FileName, const std::string& DataKey);
    int BinUpdateData(const std::string& FileName, const std::string& DataKey, const std::string& DataItem);
    int BinCreateFile(const std::string& FileName, const std::string& DataItem);
    void BinDeleteFile(const std::string& FileName, const std::string& VerifyCode);

    std::vector<std::vector<std::string>> CsvLoadData(const std::string& FileName, const int& Line, const int& Length, const std::string& Type);
    int CsvUpdateData(const std::string& FileName, const std::vector<std::string>& DataItem);
    int CsvCreateFile(const std::string& FileName, const std::vector<std::string>& DataItem);
    void CsvDeleteFile(const std::string& FileName, const std::string& VerifyCode);
    void CsvJsonLog(const std::string& FileName, const std::string& Type, const std::string& DataKey, const std::string& DataItem);
    

    json JsonLoadData(const std::string& FileName, const std::string& DataKey);
    int JsonUpdateData(const std::string& FileName, const std::string& DataKey, const std::string& DataItem);
    int JsonCreateFile(const std::string& FileName, const std::string& DataItem);
    void JsonDeleteFile(const std::string& FileName, const std::string& VerifyCode);

};
/*
DATA [uint8_t A = PartsID, uint8_t B = alpha, TagID]
RGB = [RGB1 = 01, RGB2 = 02]
RR AA
*/