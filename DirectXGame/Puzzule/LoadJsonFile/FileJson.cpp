// FileJson.cpp
#include "FileJson.h" // FileJson.hをインクルード
#include <limits>     // 数値の限界値

namespace FileJson { // FileJson名前空間を使用

// コンストラクタ: ファイル名を指定して初期化し、JSONファイルをロード
FileAccessor::FileAccessor(const std::string& filename) : filename_(filename) { LoadJsonFromFile(); }

// デストラクタ
FileAccessor::~FileAccessor() {}

// ファイルからJSONデータをロードする
void FileAccessor::LoadJsonFromFile() {
	std::ifstream inputFile(filename_); // ファイルを開く
	if (inputFile.is_open()) {          // ファイルが開けたか確認
		try {
			jsonData_ = json::parse(inputFile); // JSONファイルを解析してjsonData_に格納
		} catch (const nlohmann::json::parse_error& e) {
			// JSON解析エラーが発生した場合、エラーメッセージを出力して空のJSONオブジェクトを作成
			std::cerr << "Error: JSON parse error - " << e.what() << std::endl;
			jsonData_ = json::object();
		} catch (const std::exception& e) {
			// その他の例外が発生した場合、エラーメッセージを出力して空のJSONオブジェクトを作成
			std::cerr << "Error: Exception during JSON load - " << e.what() << std::endl;
			jsonData_ = json::object();
		}
		inputFile.close(); // ファイルを閉じる
	} else {
		// ファイルが開けなかった場合、警告メッセージを出力して空のJSONオブジェクトを作成
		std::cerr << "Warning: Could not open file for reading: " << filename_ << std::endl;
		jsonData_ = json::object();
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
Vector3 FileAccessor::ReadVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& defaultValue) const {
	try {
		// 指定されたクラスと変数がJSONデータに存在するか確認
		if (jsonData_.contains(desiredClass) && jsonData_[desiredClass].contains(variableName)) {
			// 変数がオブジェクト（x, y, zを持つ）かどうか確認
			if (jsonData_[desiredClass][variableName].is_object()) {
				auto& vecData = jsonData_[desiredClass][variableName]; // JSONオブジェクトへの参照を取得
				// x, y, z が存在するか確認
				if (vecData.contains("x") && vecData.contains("y") && vecData.contains("z")) {
					// JSONオブジェクトからx, y, zの値を取得してVector3を作成
					return Vector3(vecData["x"].get<float>(), vecData["y"].get<float>(), vecData["z"].get<float>());
				} else {
					// x, y, z のいずれかが存在しない場合は警告メッセージを出力してデフォルト値を返す
					std::cerr << "Warning: x, y, z keys not found in JSON, returning default value." << std::endl;
					return defaultValue;
				}
			} else {
				// 変数がオブジェクトでない場合は、単一の値として読み込んで全ての要素に適用
				float value = jsonData_[desiredClass][variableName].get<float>();
				return Vector3(value, value, value);
			}
		} else {
			// クラスまたは変数がJSONデータに存在しない場合は警告メッセージを出力してデフォルト値を返す
			std::cerr << "Warning: Class or variable not found in JSON, returning default value." << std::endl;
			return defaultValue;
		}
	} catch (const nlohmann::json::type_error& e) {
		// JSONの型が一致しない場合はエラーメッセージを出力してデフォルト値を返す
		std::cerr << "Error: JSON type error - " << e.what() << " Returning default value." << std::endl;
		return defaultValue;
	} catch (const std::exception& e) {
		// その他の例外が発生した場合はエラーメッセージを出力してデフォルト値を返す
		std::cerr << "Error: Exception during JSON read - " << e.what() << " Returning default value." << std::endl;
		return defaultValue;
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