#include "Game01.h"
#include "Ground.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

	bool Game01::Init()
	{
		// 最初に1回動作する
		// ただし trueを返さなければ Initに何回も来る仕様。
		//プレイヤーオブジェクト
		Scene::Object::Create<Player>();
		Scene::Object::Create<Camera>() /*/->SetName("Camera")*/;
		//camera->SetName(/*u8*/ "Camera");                                              //名前の変更   u8をつけると日本語対応になる
		//auto cam_comp = camera->AddComponent<ComponentCamera>();                       //コンポーネントを追加
		//cam_comp->SetPositionAndTarget({0.0f, 20.0f, -50.0f}, {0.0f, 10.0f, 0.0f});    //ポジションの設定

		//グラウンドオブジェクト
		Scene::Object::Create<Ground>();
		constexpr int enemy_max = 10;
		for(int i = 0; i < enemy_max; i++) {
			Scene::Object::Create<Enemy>();
		}
		//ground->SetName("Ground");
		//ground->AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/Stage00.mv1");
		//ground->AddComponent<ComponentCollisionModel>()->AttachToModel();

		//player->SetName("Player");
		//player->SetTranslate({0.0f, 5.0f, 0.0f});
		//
		//auto model_comp = player->AddComponent<ComponentModel>("data/Sample/Player/Model.mv1");
		//
		//model_comp->SetAnimation({
		//    {"idle", "data/Sample/Player/Anim/Idle.mv1", 1, 1.0f},
		//    //  {"jump",   "data/Sample/Player/Anim/Jump.mv1", 1, 1.0f},
		//    {"walk", "data/Sample/Player/Anim/Walk.mv1", 1, 1.0f},
		//    //        {"walk2",  "data/Sample/Player/Anim/Walk2.mv1", 1, 1.0f},
		//    //  {"dance1", "data/Sample/Player/Anim/Dance1.mv1", 0, 1.0f},
		//    //  {"dance2", "data/Sample/Player/Anim/Dance2.mv1", 0, 1.0f},
		//    //  {"dance3", "data/Sample/Player/Anim/Dance3.mv1", 0, 1.0f},
		//    //  {"dance4", "data/Sample/Player/Anim/Dance4.mv1", 0, 1.0f},
		//    //  {"dance5", "data/Sample/Player/Anim/Dance5.mv1", 0, 1.0f}
		//});
		////model_comp->PlayAnimation("walk", true);
		//auto pla_move = player->AddComponent<ComponentObjectController>();
		//pla_move->SetMoveSpeed(0.3f);
		//pla_move->SetRotateSpeed(20.0f);
		//
		//auto pla_coll = player->AddComponent<ComponentCollisionCapsule>();
		//pla_coll->SetRadius(3.0f);
		//pla_coll->SetHeight(13.0f);
		//pla_coll->UseGravity(true);

		//player->SetScaleAxisXYZ({2.0f, 2.0f, 2.0f});

		// auto cam_lock = camera->AddComponent<ComponentSpringArm>();
		// cam_lock->SetSpringArmObject(player);
		{
			//auto obj = Scene::Object::Create<Object>()->SetName("Sky");
			//obj->AddComponent<ComponentModel>("data/Samle/SwordBout");
		}
		return true;
	}

	//! @brief 更新
	void Game01::Update()
	{
		// 毎フレーム動作する
	}
}	 // namespace Game01
