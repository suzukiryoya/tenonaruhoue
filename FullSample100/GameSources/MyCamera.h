/*!
@file MyCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class MyCamera : public Camera {
		float m_RadY;
		float m_RadXZ;
		//カメラの上下スピード
		float m_CameraUpDownSpeed;
		//カメラを下げる下限角度
		float m_CameraUnderRot;
		//腕の長さの設定
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		//回転スピード
		float m_RotSpeed;
		//ズームスピード
		float m_ZoomSpeed;
		//左右スティック変更のモード
		bool m_LRBaseMode;
		//上下スティック変更のモード
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
	//	//カメラを下げる下限角度
	//	float m_CameraUnderRot;
	//	//腕の長さの設定
	//	float m_ArmLen;
	//	float m_MaxArm;
	//	float m_MinArm;
	//	//回転スピード
	//	float m_RotSpeed;
	//	//ズームスピード
	//	float m_ZoomSpeed;

	//public:

	//	StartCamera();
	//	virtual ~StartCamera() {}
	//	void OnUpdate();
	//	void SetEye(const bsm::Vec3& Eye)override;
	//};
}
//end basecross
