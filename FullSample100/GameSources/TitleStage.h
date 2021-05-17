/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateUI();
		wstring m_title_image;
		wstring m_Push_image;

		//BGM
		shared_ptr<SoundItem>m_BGM;
	public:
		//構築と破棄
		TitleStage() :Stage(),
			m_title_image(L"title.png"),
			m_Push_image(L"ButtonPush.png")
		{}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy();
	};


}
//end basecross

