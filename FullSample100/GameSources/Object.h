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
		//更新
		virtual void OnUpdate() override;
	};

	class FixedBox : public ActivePsObject {
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
		virtual void OnUpdate2() override;


		void OnPushA();
		//操作
	};


	class TriggerBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float time;
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
		virtual void OnUpdate() override;
		//操作

	//end basecross

	};

	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Kakuninn : public GameObject {

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//文字列の表示
		void DrawStrings();
	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		Kakuninn(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Kakuninn() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

	};

	//--------------------------------------------------------------------------------------
///	物理計算するアクティブなボックス
//--------------------------------------------------------------------------------------
	class ActivePsBox : public ActivePsObject {
		Vec3 m_Scale;
		Vec3 m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		ActivePsBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Qt,
			const Vec3& Position
		);
		virtual ~ActivePsBox();
		//初期化
		virtual void OnCreate() override;
	};

}