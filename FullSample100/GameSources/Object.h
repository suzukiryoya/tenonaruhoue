/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
///	�����v�Z����A�N�e�B�u�ȃI�u�W�F�N�g�̐e
//--------------------------------------------------------------------------------------
	class ActivePsObject : public GameObject {
		bool m_Selected;
	protected:
		ActivePsObject(const shared_ptr<Stage>& StagePtr) :
			GameObject(StagePtr), m_Selected(false) {}
		virtual ~ActivePsObject() {}
	public:
		void SetSelected(bool b) {
			m_Selected = b;
			//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
			//if (b) {
			//	PtrDraw->SetEmissive(Col4(1.0f, 1.0f, 0, 0));

			//}
			//else {
			//	PtrDraw->SetEmissive(Col4(0.0f, 0.0f, 0, 0));
			//}

		}
		bool IsSelected() {
			return m_Selected;
		}
		//�X�V
		virtual void OnUpdate() override;
	};

	class FixedBox : public ActivePsObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;


		void OnPushA();
		//����
	};


	class TriggerBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float time;
	public:
		//�\�z�Ɣj��
		TriggerBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~TriggerBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����

	//end basecross

	};

	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Kakuninn : public GameObject {

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//������̕\��
		void DrawStrings();
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		Kakuninn(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Kakuninn() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

	};

	//--------------------------------------------------------------------------------------
///	�����v�Z����A�N�e�B�u�ȃ{�b�N�X
//--------------------------------------------------------------------------------------
	class ActivePsBox : public ActivePsObject {
		Vec3 m_Scale;
		Vec3 m_Qt;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		ActivePsBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Qt,
			const Vec3& Position
		);
		virtual ~ActivePsBox();
		//������
		virtual void OnCreate() override;
	};

}