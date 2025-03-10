#include "Puzzles15.h"

Puzzles15::Puzzles15() {}

Puzzles15::~Puzzles15() {}

void Puzzles15::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	camera_.Initialize();

	// 2D背景
	puzzles15_ = TextureManager::Load("puzzle15_Tile/1.png");
	puzzles_ = Sprite::Create(puzzles15_, {0, 0});

	worldTransform_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformFont_.scale_ = {1, 1, 1};
}

void Puzzles15::Update() {

}

void Puzzles15::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	puzzles_->Draw();

	// 3Dオブジェクト描画処理後
	Model::PostDraw();
}
