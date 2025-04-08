#include "DeadScene.h"

void DeadScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	deadTexture_ = TextureManager::Load("Scene/gameOver.png");
	deadSprite_ = Sprite::Create(deadTexture_, {0, 0});
	pushTexture_ = TextureManager::Load("PushReturn.png");
	pushSprite_ = Sprite::Create(pushTexture_, {320, 600});
}

void DeadScene::Update() {
	if (Input::GetInstance()->ReleseKey(DIK_RETURN)) {
		finished_ = true;
	}
	DrawImGui();
}

void DeadScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	deadSprite_->Draw();
	pushSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void DeadScene::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("DeadScene");
	ImGui::Text("DeadScene");
	ImGui::End();
#endif
}
