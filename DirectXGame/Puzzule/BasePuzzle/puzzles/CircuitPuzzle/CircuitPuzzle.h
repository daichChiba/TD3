#pragma once
#include "../../BasePuzzle.h"
class CircuitPuzzle :public BasePuzzle {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CircuitPuzzle();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CircuitPuzzle();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:
	void DrawImGui() override;
};
