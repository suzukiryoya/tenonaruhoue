/*!
@file MyCamera.h
@brief �J����
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class MyCamera : public Camera {
		float m_RadY;
		float m_RadXZ;
		//�J�����̏㉺�X�s�[�h
		float m_CameraUpDownSpeed;
		//�J�����������鉺���p�x
		float m_CameraUnderRot;
		//�r�̒����̐ݒ�
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		//��]�X�s�[�h
		float m_RotSpeed;
		//�Y�[���X�s�[�h
		float m_ZoomSpeed;
		//���E�X�e�B�b�N�ύX�̃��[�h
		bool m_LRBaseMode;
		//�㉺�X�e�B�b�N�ύX�̃��[�h
		bool m_UDBaseMode;
	public:

		MyCamera();
		//MyCamera(float ArmLen);
		virtual ~MyCamera() {}
		virtual void SetEye(const bsm::Vec3& Eye)override;
		virtual void SetEye(float x, float y, float z)override;


		//void UpdateArmLengh();
	};

	//class StartCamera :public Camera
	//{
	//	float m_RadY;
	//	float m_RadXZ;
	//	//�J�����������鉺���p�x
	//	float m_CameraUnderRot;
	//	//�r�̒����̐ݒ�
	//	float m_ArmLen;
	//	float m_MaxArm;
	//	float m_MinArm;
	//	//��]�X�s�[�h
	//	float m_RotSpeed;
	//	//�Y�[���X�s�[�h
	//	float m_ZoomSpeed;

	//public:

	//	StartCamera();
	//	virtual ~StartCamera() {}
	//	void OnUpdate();
	//	void SetEye(const bsm::Vec3& Eye)override;
	//};
}
//end basecross
