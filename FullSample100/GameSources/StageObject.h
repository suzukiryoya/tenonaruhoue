/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//-----------------------------------------------------------------
	//  ��
	//-----------------------------------------------------------------
	class Floor : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texture;
	public:
		Floor(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic);
		virtual ~Floor();
		virtual void OnCreate();
	};
	//-----------------------------------------------------------------
	//  ��
	//-----------------------------------------------------------------
	class Wall : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texture;
	public:
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic);
		virtual ~Wall();
		virtual void OnCreate();
		//void OnCollisionEnter(shared_ptr<GameObject>& other);
	};
	//-----------------------------------------------------------------
	//  ��K�����
	//-----------------------------------------------------------------
	class Door : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texture;
		wstring m_Mesh;
	public:
		Door(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic);
		virtual ~Door();
		virtual void OnCreate();
	};
	//-----------------------------------------------------------------
	//  �X�e�[�W�@�S�[��
	//-----------------------------------------------------------------
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texture;
		wstring m_Mesh;
	public:
		Goal(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic);
		virtual ~Goal();
		virtual void OnCreate();
	};
	//-----------------------------------------------------------------
	//  �X�e�[�W�@�Q�K�ȍ~�̃X�^�[�g�n�_
	//-----------------------------------------------------------------
	class Start : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texture;
		wstring m_Mesh;
	public:
		Start(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic);
		virtual ~Start();
		virtual void OnCreate();
	};

}
//end basecross
