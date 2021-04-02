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
		: GameObject(StagePtr), m_Speed(5.0f), m_GoPointPos(0.0f,2.0f,14.0f), m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_Mesh(L"Protagonist_Robot_3.bmf")
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

		m_NowPosX = m_Position.x;
		m_NowPosZ = m_Position.z;

		//CollisionObb衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();

		ptrColl->SetDrawActive(true);
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

		////描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"Tx_Protagonist_Robot.tga");


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
		auto controller = App::GetApp()->GetInputDevice().GetControlerVec();
		if (controller[0].wPressedButtons & XINPUT_GAMEPAD_A)
		{
			SoundBoxSearch();
		}

		if (m_Position.x >= m_NowPosX)
		{
			playerMove(true);
		}
		else
		{
			playerMove(false);
		}
	}

	void Player::playerMove(bool flag)
	{
		auto trans = GetComponent<Transform>();
		m_Position = trans->GetPosition();

		auto elapsedTime = App::GetApp()->GetElapsedTime();

		auto controller = App::GetApp()->GetInputDevice().GetControlerVec();

		auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);

		if (m_SoundBoxFlag == true)
		{
			m_Position = trans->GetPosition();

			GoPointToNowPos.x = m_Position.x - m_GoPointPos.x;
			GoPointToNowPos.z = m_Position.z - m_GoPointPos.z;


			GoPointToNowPos.y = -XM_PI;
			m_Rotation.y += GoPointToNowPos.y;

			GoPointToNowPos.normalize();

			//m_Speed += 1.0f;

			m_Position -= GoPointToNowPos * elapsedTime * m_Speed;
			trans->SetPosition(m_Position.x, 2.0f, m_Position.z);
		}
		else if (flag == true)
		{
			GoPointToNowPos.x = m_Position.x + m_GoPointPos.x;
			GoPointToNowPos.z = m_Position.z + m_GoPointPos.z;

			GoPointToNowPos.normalize();

			m_Position -= GoPointToNowPos * elapsedTime * m_Speed;

			trans->SetRotation(0, m_Rotation.y, 0);

			trans->SetPosition(m_Position.x, 2.0f, m_NowPosZ);
		}

		if (m_SoundBoxFlag == true)
		{
			m_Position = trans->GetPosition();

			GoPointToNowPos.x = m_Position.x - m_GoPointPos.x;
			GoPointToNowPos.z = m_Position.z - m_GoPointPos.z;

			GoPointToNowPos.y = -XM_PI;
			m_Rotation.y += GoPointToNowPos.y;

			GoPointToNowPos.normalize();

			//m_Speed += 1.0f;

			m_Position -= GoPointToNowPos * elapsedTime * m_Speed;
			trans->SetPosition(m_Position.x, 2.0f, m_Position.z);
		}
		else if (flag == false)
		{
			GoPointToNowPos.x = m_Position.x + m_GoPointPos.x;
			GoPointToNowPos.z = m_Position.z + m_GoPointPos.z;

			GoPointToNowPos.normalize();

			m_Position -= GoPointToNowPos * elapsedTime * m_Speed;

			trans->SetRotation(0, m_Rotation.y, 0);

			trans->SetPosition(m_NowPosX, 2.0f, m_Position.z);
		}

	}

	void Player::SoundBoxSearch()
	{
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		auto gameObjects = stage->GetChileStageVec();
		auto ElapsedTime = App::GetApp()->GetElapsedTime();
		auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);

		auto soundPosition = scene->GetPosition();

		m_GoPointPos = soundPosition;
		m_Position = GetComponent<Transform>()->GetPosition();

		GoPointToNowPos.x = m_Position.x - m_GoPointPos.x;
		GoPointToNowPos.z = m_Position.z - m_GoPointPos.z;

		if (GoPointToNowPos.length() <= 6.0f)
		{
			m_SoundBoxFlag = true;
		}
		else
		{
			m_SoundBoxFlag = false;
		}
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//auto ptr = GetStage()->CreateSharedObjectGroup(L"Wall");
		auto trans = GetComponent<Transform>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		if (other->FindTag(L"Wall"))
		{
			auto pos = trans->GetPosition();

			m_GoPointPos = other->GetComponent<Transform>()->GetPosition();

			auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);
			GoPointToNowPos.x = m_Position.x + m_GoPointPos.x;
			GoPointToNowPos.z = m_Position.z + m_GoPointPos.z;

			GoPointToNowPos.y = -XM_PI;
			m_Rotation.y += GoPointToNowPos.y;

			GoPointToNowPos.normalize();

			//m_Speed += 1.0f;

			m_Position -= GoPointToNowPos * elapsedTime * m_Speed;
		}
		if (other->FindTag(L"FixedBox1"))
		{
			auto pos = trans->GetPosition();

			m_GoPointPos = other->GetComponent<Transform>()->GetPosition();

			auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);
			GoPointToNowPos.x = m_Position.x + m_GoPointPos.x;
			GoPointToNowPos.z = m_Position.z + m_GoPointPos.z;

			GoPointToNowPos.y = -XM_PI;
			m_Rotation.y += GoPointToNowPos.y;

			GoPointToNowPos.normalize();

			//m_Speed += 1.0f;

			m_Position -= GoPointToNowPos * elapsedTime * m_Speed;
		}
		if (other->FindTag(L"Goal"))
		{
			App::GetApp()->GetScene<Scene>()->SetCheck(true);
		}
	}

}
//end basecross

