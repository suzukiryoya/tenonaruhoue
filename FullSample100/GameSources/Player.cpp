/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position)
		: GameObject(StagePtr), m_Speed(5.0f), m_GoalPos(12.0f,1.0f,-9.5f), m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_Mesh(L"Protagonist_Robot_2_ver2.bmf")
	{
	}

	Player::~Player()
	{
	}

	void Player::OnCreate()
	{
		//初期位置などの設定
		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetRotation(m_Rotation);
		PtrTrans->SetPosition(m_Position);

		//CollisionObb衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		
		ptrColl->SetMakedSize(1.5f);
		//重力をつける
		auto PtrGra = AddComponent<Gravity>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(m_Mesh);
		ptrDraw->SetOwnShadowActive(true);
		//ptrDraw->AddAnimation(L"Wait", 0, 1, true, 20);
		//ptrDraw->AddAnimation(L"Walk", 10, 30, true, 110);
		//ptrDraw->ChangeCurrentAnimation(L"Wait");

		//////描画するテクスチャを設定
		//ptrDraw->SetTextureResource(L"PLAYER_TX");


		//SetAlphaActive(true);

		//カメラを得る
		auto ptrCamera = dynamic_pointer_cast<Camera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			//ptrCamera->SetTargetObject(GetThis<GameObject>());
			//ptrCamera->SetTargetToAt(GetComponent<Transform>()->GetPosition());
		}
	}

	void Player::OnUpdate()
	{
		playerMove();
	}

	void Player::playerMove()
	{
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		float elapsedTime = App::GetApp()->GetElapsedTime();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//auto ptr = GetStage()->CreateSharedObjectGroup(L"Wall");
		auto trans = GetComponent<Transform>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		if (other->FindTag(L"Wall"))
		{
			auto pos = trans->GetPosition();
			auto GoalToNowPos = pos - m_GoalPos;
			GoalToNowPos.normalize();

			pos -= GoalToNowPos * elapsedTime * m_Speed;

			trans->SetRotation(-GoalToNowPos.x, 0, 0);
			trans->SetPosition(pos);
		}
	}

}
//end basecross

