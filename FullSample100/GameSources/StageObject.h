/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//-----------------------------------------------------------------
	//  床
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
	//  壁
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
	//  一階入り口
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
	//  ステージ　ゴール
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
	//  ステージ　２階以降のスタート地点
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
