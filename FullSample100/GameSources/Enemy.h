#pragma once
#include "stdafx.h"

namespace basecross {

	//“G‚P
	class Enemy1 : public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texture;
		wstring m_Mesh;

	public:
		Enemy1(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Enemy1();
		virtual void OnCreate()override;
		//void OnUpdate();

	};
}
//end basecross
