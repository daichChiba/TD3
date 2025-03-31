#pragma once

#include "KamataEngine.h"
#include "../ActorManager.h"

using namespace KamataEngine;

class ActorManager;

class EnemyActor {
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="model">モデル</param>
    /// <param name="position">モデルの座標</param>
    void Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager);

    /// <summary>
    /// アップデート
    /// </summary>
    virtual void Update();

    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="camera">カメラ</param>
    void Draw(Camera& camera);

    virtual void DrawImGui();

    WorldTransform* GetWorldTransfrom() { return &worldTransform_; }

    virtual void SetMove(Vector3 move) { move_ = move; }

    Vector3 GetWorldPosition() { return worldTransform_.translation_; }
    float GetRadius() { return radius_; }
    void OnCollision();
    bool IsDelete() { return isDelete_; }

protected:
    virtual void Move() { return; }
    virtual void Attack() { return; }

    virtual void ApproachPlayer();

    Model* model_ = nullptr;
    Model* BulletModel_ = nullptr;
    WorldTransform worldTransform_;
    const WorldTransform* PlayerWorldTransform_ = nullptr;

    ActorManager* actorManager_ = nullptr;

    Vector3 enemyStartPos;
    Vector3 distance_ = {1.0f, 0.0f, 1.0f};
    static inline const float kMinDistanceX_ = 8.0f;
    static inline float kMinDistanceY_ = 0.0f;
    static inline const float kMaxDistance_ = 5.0f;
    static inline const float kApproachDistance_ = 3.0f;

    float radius_ = 1.0f;

    bool isDelete_ = false;

    Vector3 direction;

    // プレイヤーとの距離を測る変数
    float distanceToPlayer_ = 1.0f;

    Vector3 move_;
    static inline const float kSpeed_ = 0.05f;
};
