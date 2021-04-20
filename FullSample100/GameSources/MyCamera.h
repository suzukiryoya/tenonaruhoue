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
	};
}
//end basecross
