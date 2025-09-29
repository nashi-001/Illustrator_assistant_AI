#include <iostream>
#include "DataManager.hpp"



json GetJson(const std::string& FilePath) {
    json j;
    if (fs::exists(FilePath)) {
        std::ifstream File(FilePath);
        if (!File.is_open()) {
            std::cerr << "ファイルを開けません\n";
            return {};
        }
        File >> j;
        File.close();
    } else {
        std::cerr << "ファイルが存在しません\n";
    }
    return j;
}


void SaveJson(const std::string& FilePath, const std::string& Data) {
    json j;
    json NewJson;

    try {
        auto NewJson = json::parse(Data);
    } catch (const json::parse_error& e) {
        NewJson = Data;
    }

    if (fs::exists(FilePath)) {
        std::ofstream File(FilePath);
        if (!File.is_open()) {
            std::cerr << "ファイルを開けません\n";

        }
        File << NewJson.dump(4);
        File.close();
    } else {
        std::cerr << "ファイルが存在しません\n";
    }
}



json DataManager::JsonLoadData(const std::string& FileName, const std::string& DataKey) {
    std::string FilePath = "Json/" + FileName + ".json";
    json j = GetJson(FilePath);

    auto Item = j.find(DataKey);
    if (Item != j.end()) {
        return *Item;
    } else {
        std::cout << DataKey << "is not found" << std::endl;
    }

    
}


int DataManager::JsonUpdateData(const std::string& FileName, const std::string& DataKey, const std::string& DataItem) {
    const std::string& FilePath = "Json/" + FileName + ".json";
    json j = GetJson(FilePath);

    auto Item = j.find(DataKey);

    if (Item != j.end()) {
        j[DataKey] = DataItem;
        SaveJson(FilePath, j);
        DataManager::CsvJsonLog(FilePath, "Update", DataKey, DataItem);
        return true;
    } else {
        std::cout << DataKey << "is not found" << std::endl;
        DataManager::CsvJsonLog(FilePath, "UpdateError", DataKey, DataItem);
        return false;
    }


}

int DataManager::JsonCreateFile(const std::string& FileName, const std::string& DataItem) {

    std::string FilePath = "Json/" + FileName + ".json";
    std::ofstream NewJsonFile(FilePath);

    if (!NewJsonFile.is_open()) {
        std::cerr << "ファイルを作成できませんでした\n";
        return false;
    }

    SaveJson(FilePath, DataItem);
    DataManager::CsvJsonLog(FilePath, "Create", "CreateJsonFile", DataItem);
    return true;
}

void DataManager::JsonDeleteFile(const std::string& FileName, const std::string& VerifyCode) {
    
    std::string FilePath = "Json/" + FileName + ".json";

    if (fs::exists(FilePath)) {
        if (fs::remove(FilePath)) {
            std::cout << "ファイルを削除しました\n";
        } else {
            std::cerr << "削除に失敗しました\n";
        }
    } else {
        std::cout << "ファイルが存在しません\n";
    }
    DataManager::CsvJsonLog(FilePath, "Delete", "DeleteJsonFile", "None");
}