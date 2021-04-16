/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	enum class CellSearchFlg {
		Failed,
		Seek,
		Arrived
	};

	class Player : public GameObject
	{
	public:
		Player(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<StageCellMap>& CellMap
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
		virtual void OnUpdate() override;

		void playerMove(bool flag);
		void SoundBoxSearch();
		void OnCollisionEnter(shared_ptr<GameObject>& other);

		void PlayerRestart();			  // �v���C���[�̃��X�|�[��

		const Vec3& GetStartPosition()const {
			return m_StartPosition;
		}

		// �ړI�̏ꏊ���T�[�`����
		// TargetPos	�ړI�̉ӏ�
		bool Search(const Vec3& TargetPos);

		// �ړI�̏ꏊ���T�[�`��Seek�s��������
		// TargetPos	�ړI�̉ӏ�
		CellSearchFlg SeekBehavior(const Vec3& TargetPos);

		// �ړI�̏ꏊ��arrive�s�����Ƃ�
		// TargetPos	�ړI�̉ӏ�
		void ArriveBehavior(const Vec3& TargetPos);

	private:
		Vec3 GetInputState() const;

		std::shared_ptr<Player> m_Player;

		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotation;
		Vec3 m_CameraAt;

		std::shared_ptr<Action> m_PtrAction;

		vector<Vec3> m_Checkpoints = 
		{
			{ 0, 1.0f, 6.0f },
			{ 0, 1.0f, 11.0f },
			{ 0, 1.0f, 6.0f },
			{12.0f, 1.0f, -9.5f}
		};
		Vec3 m_GoPointPos;
 
		wstring m_Mesh;

		float m_NowPosX;
		float m_NowPosZ;
		float m_Speed;

		bool m_HomingFlag = false;

		// �o�H�T���p
		Vec3 m_StartPosition;
		Vec3 m_Force;
		Vec3 m_Velocity;
		weak_ptr<StageCellMap> m_CelMap;
		vector<CellIndex> m_CellPath;
		//���݂̎����̃Z���C���f�b�N�X
		int m_CellIndex;
		//�߂����i���́j�̃Z���C���f�b�N�X
		int m_NextCellIndex;
		//�^�[�Q�b�g�̃Z���C���f�b�N�X
		int m_TargetCellIndex;
	};
}
//end basecross

