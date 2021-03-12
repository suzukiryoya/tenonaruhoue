/*!
@file Player.h
@brief �v���C���[�Ȃ�
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

		virtual void OnCreate() override; // �v���C���[�̍쐬
		void PlayerRestart();			  // �v���C���[�̃��X�|�[��

		//virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;   // �Փ˔���Ɏg��
		//virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override; // �Փ˔���Ɏg��
		//virtual void OnCollisionExit(shared_ptr<GameObject>& other) override;  // �Փ˔���Ɏg�� 

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

