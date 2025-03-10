// FileJson.h
#pragma once
#include "nlohmann/json.hpp"
#include <KamataEngine.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using json = nlohmann::json;
using namespace KamataEngine;

namespace FileJson {

class FileAccessor {
public:
	FileAccessor(const std::string& filename);
	~FileAccessor();

	/// <summary>
	// JSONから値を読み込むための汎用的な関数
	/// </summary>
	/// <typeparam name="T">テンプレ</typeparam>
	/// <param name="desiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="defaultValue">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <returns></returns>
	template<typename T> T Read(const std::string& desiredClass, const std::string& variableName, const T& defaultValue) const;

	

	/// <summary>
	// JSONに値を書き込むための汎用的な関数
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="desiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="value">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	template<typename T> void Write(const std::string& desiredClass, const std::string& variableName, const T& value);

	
	
	/// <summary>
	// Vector3を読み書きするための特殊化
	/// </summary>
	/// <param name="desiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="defaultValue">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <returns></returns>
	Vector3 ReadVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& defaultValue) const;
	void WriteVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& value);

	// ファイルからJSONデータをロードする
	void LoadJsonFromFile();

	// JSONデータをファイルに保存する
	void SaveJsonToFile();

private:
	std::string filename_;
	std::ifstream inputFile_;
	std::ofstream outputFile_;
	json jsonData_;
};

} // namespace FileJson