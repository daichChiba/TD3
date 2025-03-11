// FileJson.h
#pragma once                 // 多重インクルードを防ぐ
#include "nlohmann/json.hpp" // JSONライブラリ
#include <KamataEngine.h>    // KamataEngineのヘッダーファイル (Vector3 など)
#include <fstream>           // ファイルストリーム
#include <iostream>          // 標準入出力
#include <sstream>           // 文字列ストリーム
#include <stdexcept>         // 例外処理
#include <string>            // 文字列

using json = nlohmann::json;  // nlohmann::json を json という名前で使用する
using namespace KamataEngine; // KamataEngineの名前空間を使用

namespace FileJson { // FileJsonという名前空間を定義

class FileAccessor {
public:
	/// <summary>
	/// new　FileJson::FileAccessor(ファイル名)
	/// </summary>
	/// <param name="filename">ファイル名</param>
	FileAccessor(const std::string& filename);
	// デストラクタ
	~FileAccessor();


	/// <summary>
	/// Jsonから値を読み込む関数
	/// </summary>
	/// <typeparam name="T">テンプレート</typeparam>
	/// <param name="desiredClass">ファイルの中でとりたいジャンル名(enemy_1)など</param>
	/// <param name="variableName">ファイルの中でとりたい変数名(Pos)など</param>
	/// <param name="defaultValue">ファイルの中になかった場合の戻り値</param>
	/// <returns></returns>
	template<typename T> T Read(const std::string& desiredClass, const std::string& variableName, const T& defaultValue) const;

	// ための汎用的な関数

	/// <summary>
	/// JSONに値を書き込む関数
	/// </summary>
	/// <typeparam name="T">テンプレート</typeparam>
	/// <param name="desiredClass">ファイルの中でとりたいジャンル名(enemy_1)など</param>
	/// <param name="variableName">ファイルの中でとりたい変数名(Pos)など</param>
	/// <param name="value">書き込む値</param>
	template<typename T> void Write(const std::string& desiredClass, const std::string& variableName, const T& value);

	// Vector3を読み書きするための特殊化

	/// <summary>
	/// 
	/// </summary>
	/// <param name="desiredClass">ファイルの中でとりたいジャンル名(enemy_1)など</param>
	/// <param name="variableName">ファイルの中でとりたい変数名(Pos)など</param>
	/// <param name="defaultValue">ファイルの中になかった場合の戻り値</param>
	/// <returns></returns>
	Vector3 ReadVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& defaultValue) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="desiredClass">ファイルの中でとりたいジャンル名(enemy_1)など</param>
	/// <param name="variableName">ファイルの中でとりたい変数名(Pos)など</param>
	/// <param name="value">書き込む値</param>
	void WriteVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& value);

	// JSONデータをファイルに保存する
	void Save();

private:
	std::string filename_; // JSONファイルの名前
	json jsonData_;        // JSONデータ

	// ファイルからJSONデータをロードする
	void LoadJsonFromFile();
};

// テンプレート関数の定義をヘッダーファイルに移動

/// <summary>
/// 
/// </summary>
/// <typeparam name="T">テンプレート</typeparam>
/// <param name="desiredClass">ファイルの中でとりたいジャンル名(enemy_1)など</param>
/// <param name="variableName">ファイルの中でとりたい変数名(Pos)など</param>
/// <param name="defaultValue">ファイルの中になかった場合の戻り値</param>
/// <returns></returns>
template<typename T> T FileAccessor::Read(const std::string& desiredClass, const std::string& variableName, const T& /*defaultValue*/) const {
	try {
		if (jsonData_.contains(desiredClass) && jsonData_[desiredClass].contains(variableName)) {
			return jsonData_[desiredClass][variableName].get<T>();
		} else {
			std::stringstream ss;
			ss << "Error: Key not found in JSON - Class: " << desiredClass << ", Variable: " << variableName;
			throw std::runtime_error(ss.str());
		}
	} catch (const nlohmann::json::type_error& e) {
		std::stringstream ss;
		ss << "Error: JSON type error - " << e.what() << " Class: " << desiredClass << ", Variable: " << variableName;
		throw std::runtime_error(ss.str());
	} catch (const std::exception& e) {
		std::stringstream ss;
		ss << "Error: Exception during JSON read - " << e.what() << " Class: " << desiredClass << ", Variable: " << variableName;
		throw std::runtime_error(ss.str());
	}
}
/// <summary>
/// 
/// </summary>
/// <typeparam name="T">テンプレート</typeparam>
/// <param name="desiredClass">ファイルの中でとりたいジャンル名(enemy_1)など</param>
/// <param name="variableName">ファイルの中でとりたい変数名(Pos)など</param>
/// <param name="value">書き込む値</param>
template<typename T> void FileAccessor::Write(const std::string& desiredClass, const std::string& variableName, const T& value) {
	try {
		// 指定されたクラスと変数に値を書き込む
		jsonData_[desiredClass][variableName] = value;
	} catch (const std::exception& e) {
		// 例外が発生した場合はエラーメッセージを出力
		std::cerr << "Error: Exception during JSON write - " << e.what() << std::endl;
	}
}

} // namespace FileJson