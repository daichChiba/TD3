// FileJson.cpp
#include "FileJson.h"
#include <limits>

namespace FileJson {

FileAccessor::FileAccessor(const std::string& filename) : filename_(filename), inputFile_(filename), outputFile_(filename) {
	// ファイルを読み込みモードで開く
	// inputFile_.open(filename_, std::ios::in);

	// ファイルが開けたかどうかをチェック
	if (inputFile_.is_open()) {
		// JSONデータをファイルからロード
		LoadJsonFromFile();
		inputFile_.close(); // ファイルを閉じる
	} else {
		std::cerr << "Warning: Could not open file for reading: " << filename_ << std::endl;
		// ファイルが存在しないか、開けない場合は、空のJSONオブジェクトで初期化
		jsonData_ = json::object();
	}
}

FileAccessor::~FileAccessor() {
	SaveJsonToFile(); // デストラクタでJSONデータをファイルに保存
}

void FileAccessor::LoadJsonFromFile() {
	try {
		// ファイルストリームからJSONデータを読み込む
		inputFile_ >> jsonData_;
	} catch (const nlohmann::json::parse_error& e) {
		std::cerr << "Error: JSON parse error - " << e.what() << std::endl;
		// パースエラーが発生した場合、jsonData_を空のJSONオブジェクトで初期化
		jsonData_ = json::object();
	} catch (const std::exception& e) {
		std::cerr << "Error: Exception during JSON load - " << e.what() << std::endl;
		// その他のエラーが発生した場合も、jsonData_を空のJSONオブジェクトで初期化
		jsonData_ = json::object();
	}
	/*finally {
	    if (inputFile_.is_open()) {
	        inputFile_.close(); // ファイルを閉じる
	    }
	}*/
}

void FileAccessor::SaveJsonToFile() {
	// ファイルを書き込みモードで開く（上書き）
	outputFile_.open(filename_, std::ios::out | std::ios::trunc); // ファイルをtruncateして開く

	// ファイルが開けたかどうかをチェック
	if (outputFile_.is_open()) {
		try {
			// JSONデータをファイルストリームに書き込む（インデント付き）
			outputFile_ << jsonData_.dump(4); // 4はインデントのスペース数
		} catch (const std::exception& e) {
			std::cerr << "Error: Exception during JSON save - " << e.what() << std::endl;
		}
		/*finally {
		    if (outputFile_.is_open()) {
		        outputFile_.close(); // ファイルを閉じる
		    }
		}*/
	} else {
		std::cerr << "Error: Could not open file for writing: " << filename_ << std::endl;
	}
}

Vector3 FileAccessor::ReadVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& defaultValue) const {
	try {
		if (jsonData_.contains(desiredClass) && jsonData_[desiredClass].contains(variableName)) {
			if (jsonData_[desiredClass][variableName].is_object()) {
				auto& vecData = jsonData_[desiredClass][variableName];
				// x, y, z が存在するか確認
				if (vecData.contains("x") && vecData.contains("y") && vecData.contains("z")) {
					return Vector3(vecData["x"].get<float>(), vecData["y"].get<float>(), vecData["z"].get<float>());
				} else {
					std::cerr << "Warning: x, y, z keys not found in JSON, returning default value." << std::endl;
					return defaultValue;
				}
			} else {
				float value = jsonData_[desiredClass][variableName].get<float>();
				return Vector3(value, value, value);
			}
		} else {
			std::cerr << "Warning: Class or variable not found in JSON, returning default value." << std::endl;
			return defaultValue;
		}
	} catch (const nlohmann::json::type_error& e) {
		std::cerr << "Error: JSON type error - " << e.what() << " Returning default value." << std::endl;
		return defaultValue;
	} catch (const std::exception& e) {
		std::cerr << "Error: Exception during JSON read - " << e.what() << " Returning default value." << std::endl;
		return defaultValue;
	}
}

void FileAccessor::WriteVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& value) {
	try {
		// Vector3をJSONオブジェクトに書き込む
		jsonData_[desiredClass][variableName]["x"] = value.x;
		jsonData_[desiredClass][variableName]["y"] = value.y;
		jsonData_[desiredClass][variableName]["z"] = value.z;
	} catch (const std::exception& e) {
		std::cerr << "Error: Exception during JSON write - " << e.what() << std::endl;
	}
}

template<typename T> T FileAccessor::Read(const std::string& desiredClass, const std::string& variableName, const T& defaultValue) const {
	try {
		if (jsonData_.contains(desiredClass) && jsonData_[desiredClass].contains(variableName)) {
			if (jsonData_[desiredClass][variableName].is_object()) {
				return defaultValue;
			} else {
				return jsonData_[desiredClass][variableName].get<T>();
			}

		} else {
			std::cerr << "Warning: Key not found in JSON, returning default value." << std::endl;
			return defaultValue;
		}
	} catch (const nlohmann::json::type_error& e) {
		std::cerr << "Error: JSON type error - " << e.what() << " Returning default value." << std::endl;
		return defaultValue;
	} catch (const std::exception& e) {
		std::cerr << "Error: Exception during JSON read - " << e.what() << " Returning default value." << std::endl;
		return defaultValue;
	}
}

template<typename T> void FileAccessor::Write(const std::string& desiredClass, const std::string& variableName, const T& value) {
	try {
		jsonData_[desiredClass][variableName] = value;
	} catch (const std::exception& e) {
		std::cerr << "Error: Exception during JSON write - " << e.what() << std::endl;
	}
}

} // namespace FileJson