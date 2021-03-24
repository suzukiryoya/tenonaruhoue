/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
///	物理計算するアクティブなオブジェクトの親
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
			auto PtrDraw = AddComponent<BcPNTStaticDraw>();
			if (b) {
				PtrDraw->SetEmissive(Col4(1.0f, 1.0f, 0, 0));

			}
			else {
				PtrDraw->SetEmissive(Col4(0.0f, 0.0f, 0, 0));
			}

		}
		bool IsSelected() {
			return m_Selected;
		}
		//更新
		virtual void OnUpdate() override;
	};

	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedBox();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void OnPushA();
		//操作
	};


	class TriggerBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		TriggerBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~TriggerBox();
		//初期化
		virtual void OnCreate() override;
		//操作

	};
	//end basecross
}