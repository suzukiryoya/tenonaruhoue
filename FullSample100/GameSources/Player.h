/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Player : public GameObject
	{
	public:
		Player(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Player();
		auto SetPad()
		{
			auto& app = App::GetApp();
			auto device = app->GetInputDevice();
			auto pad = device.GetControlerVec()[0];

			return pad;
		}

		virtual void OnCreate() override; // プレイヤーの作成
		void PlayerRestart();			  // プレイヤーのリスポーン

		//virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;   // 衝突判定に使う
		//virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override; // 衝突判定に使う
		//virtual void OnCollisionExit(shared_ptr<GameObject>& other) override;  // 衝突判定に使う 

	private:
		Vec3 GetInputState() const;
		Vec3 GetWallRunState();

		std::shared_ptr<Player> m_Player;

		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotation;
		Vec3 m_CameraAt;

		wstring m_Mesh;

		float m_Speed;

	};

}
//end basecross

