// FileJson.cpp
#include "FileJson.h" // FileJson.hをインクルード
#include <limits>     // 数値の限界値

namespace FileJson { // FileJson名前空間を使用

// コンストラクタ: ファイル名を指定して初期化し、JSONファイルをロード
FileAccessor::FileAccessor(const std::string& filename) : filename_(filename) {
	// ファイルを開く
	std::ifstream inputFile(filename_);
	// ファイルが開けなかった場合
	if (!inputFile.is_open()) {
		// ファイルが存在しない場合
		throw std::runtime_error("Error: Could not open file for reading: " + filename_);
	}
	inputFile.close();  // ファイルが存在することを確認したら閉じる
	LoadJsonFromFile(); // ファイルが存在する場合のみロード
}
// デストラクタ
FileAccessor::~FileAccessor() {}

// ファイルからJSONデータをロードする
void FileAccessor::LoadJsonFromFile() {
	std::ifstream inputFile(filename_);
	if (inputFile.is_open()) {
		// ファイルは存在する
		if (inputFile.peek() == std::ifstream::traits_type::eof()) {
			// ファイルが空の場合
			inputFile.close();
			throw std::runtime_error("Error: JSON file is empty: " + filename_);
		}
		try {
			jsonData_ = json::parse(inputFile);
		} catch (const nlohmann::json::parse_error& e) {
			std::cerr << "Error: JSON parse error - " << e.what() << std::endl;
			throw; // 例外を再スローする
		} catch (const std::exception& e) {
			std::cerr << "Error: Exception during JSON load - " << e.what() << std::endl;
			throw; // 例外を再スローする
		}
		inputFile.close();
	} else {
		// ファイルが存在しない場合
		throw std::runtime_error("Error: Could not open file for reading: " + filename_);
	}
}
// JSONデータをファイルに保存する
void FileAccessor::Save() {
	std::ofstream outputFile(filename_); // ファイルを開く
	if (outputFile.is_open()) {          // ファイルが開けたか確認
		try {
			outputFile << jsonData_.dump(4); // JSONデータを整形してファイルに書き込む
		} catch (const std::exception& e) {
			// 例外が発生した場合、エラーメッセージを出力
			std::cerr << "Error: Exception during JSON save - " << e.what() << std::endl;
		}
		outputFile.close(); // ファイルを閉じる
	} else {
		// ファイルが開けなかった場合、エラーメッセージを出力
		std::cerr << "Error: Could not open file for writing: " << filename_ << std::endl;
	}
}

// Vector3を読み込むための特殊化
Vector3 FileAccessor::ReadVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& /*defaultValue*/) const {
	try {
		// 指定されたクラスと変数から値を読み込む
		if (jsonData_.contains(desiredClass) && jsonData_[desiredClass].contains(variableName)) {
			// 値を返す
			if (jsonData_[desiredClass][variableName].is_object()) {
				auto& vecData = jsonData_[desiredClass][variableName];
				// x, y, z が存在するか確認
				if (vecData.contains("x") && vecData.contains("y") && vecData.contains("z")) {
					// x, y, z の値を取得
					return Vector3(vecData["x"].get<float>(), vecData["y"].get<float>(), vecData["z"].get<float>());
					// キーが見つからない場合
				} else {
					// 例外が発生した場合、エラーメッセージを出力
					std::stringstream ss;
					ss << "Error: x, y, z keys not found in JSON - Class: " << desiredClass << ", Variable: " << variableName;
					throw std::runtime_error(ss.str());
				}
				// オブジェクトでない場合
			} else {
				float value = jsonData_[desiredClass][variableName].get<float>();
				return Vector3(value, value, value);
			}
		} else {
			// キーが見つからない場合
			std::stringstream ss;
			// 例外が発生した場合、エラーメッセージを出力
			ss << "Error: Class or variable not found in JSON - Class: " << desiredClass << ", Variable: " << variableName;
			// 例外をスローする
			throw std::runtime_error(ss.str());
		}
		// 例外が発生した場合
	} catch (const nlohmann::json::type_error& e) {
		std::stringstream ss;
		ss << "Error: JSON type error - " << e.what() << " Class: " << desiredClass << ", Variable: " << variableName;
		// 例外をスローする
		throw std::runtime_error(ss.str());
	} catch (const std::exception& e) {
		std::stringstream ss;
		ss << "Error: Exception during JSON read - " << e.what() << " Class: " << desiredClass << ", Variable: " << variableName;
		// 例外をスローする
		throw std::runtime_error(ss.str());
	}
}
// Vector3を書き込むための特殊化
void FileAccessor::WriteVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& value) {
	try {
		// Vector3をJSONオブジェクトに書き込む
		jsonData_[desiredClass][variableName]["x"] = value.x;
		jsonData_[desiredClass][variableName]["y"] = value.y;
		jsonData_[desiredClass][variableName]["z"] = value.z;
	} catch (const std::exception& e) {
		// 例外が発生した場合、エラーメッセージを出力
		std::cerr << "Error: Exception during JSON write - " << e.what() << std::endl;
	}
}

} // namespace FileJson