#include <iostream>
#include "DataManager.hpp"



std::vector<std::vector<std::string>> LoadCsvFileData(const std::string FilePath, const int Line, const int Length) {

    std::ifstream File(FilePath);
    if (!File.is_open()) {
        std::cerr << "failed open";
        std::vector<std::vector<std::string>> None = {{None}};
        return None;
    }
    
    std::string GetLine;
    std::vector<std::vector<std::string>> CsvData;
    std::vector<std::vector<std::string>> ReturnCsvData;

    while(std::getline(File, GetLine)) {
        std::stringstream CsvLine(GetLine);
        std::string Cell;
        std::vector<std::string> Items;

        while (std::getline(CsvLine, Cell, ',')) { // カンマ区切りで分割
            Items.push_back(Cell);
        }
        CsvData.push_back(Items);
    }

    for (size_t i = Line; i < Line + Length; i++) {
        ReturnCsvData.push_back(CsvData[i]);
    }

    return ReturnCsvData;
    
}


void SaveData(std::string FilePath, std::vector<std::string> Data) {
    std::ofstream File(FilePath, std::ios::app);
    if (!File.is_open()){
        std::cout << "can't open File" << std::endl;
    }

    for(size_t i = 0; i < Data.size(); i++) {
        File << Data[i];
        if (i != Data.size() - 1) File << ",";
    }

    File << "\n";
    File.close();
}


std::vector<std::vector<std::string>> CsvLoadData(const std::string& FileName, const int& Line, const int& Length) {
    std::string FilePath = "Csv/" + FileName + ".csv";
    std::vector<std::vector<std::string>> CsvData =  LoadCsvFileData(FilePath, Line, Length);

    return CsvData;
    
}

int CsvUpdateData(const std::string& FileName, const std::vector<std::string>& DataItem) {
    std::string FilePath = "Csv/" + FileName + ".csv";
    SaveData(FilePath, DataItem);
}

int CsvCreateFile(const std::string& FileName, const std::vector<std::string>& DataItem) {
    std::string FilePath = "Csv/" + FileName + ".csv";
    std::ofstream NewCsvFile(FilePath);
    if (!NewCsvFile.is_open()) {
       std::cout << "this file is None" << std::endl;
    }

    SaveData(FilePath, DataItem);

}

void CsvDeleteFile(const std::string& FileName, const std::string& VerifyCode) {
    std::string FilePath = "Csv/" + FileName + ".csv";
    
    if (fs::exists(FilePath) && VerifyCode == "DeleteThisFile") {   
        fs::remove(FilePath)
    }
}

void CsvJsonLog(const std::string& FileName, const std::string& Type, const std::string& DataKey, const std::string& DataItem) {
    std::string FilePath = "Csv/JsonCreateUpdateDeleteLogs.csv";
    std::vector<std::string> Data = {FileName, Type, DataKey, DataItem};
    SaveData(FilePath, Data);
}