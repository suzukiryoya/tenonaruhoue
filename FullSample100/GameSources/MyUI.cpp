#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void UI_Base::Draw() {

		float X = m_Vertex.x / 2.0f;
		float Y = m_Vertex.y / 2.0f;

		vector<VertexPositionColorTexture> vertices;
		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices.push_back(VertexPositionColorTexture(Vec3(-X, Y, 0), color, Vec2(0.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(X, Y, 0), color, Vec2(1.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(-X, -Y, 0), color, Vec2(0.0f, 1.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(X, -Y, 0), color, Vec2(1.0f, 1.0f)));

		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetTextureResource(m_textures);
		SetDrawLayer(m_layer);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		SetAlphaActive(true);

	}


	void Clear::OnCreate() {
		Draw();
	}

	void Clear::OnUpdate() {
		Vec2 ret;
		Vec3 angle(0, 0, 0);

		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 1.0f;
		ret.y = 1.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			ret.y = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//左
			ret.x = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			ret.y = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//右
			ret.x = 1.0f;
		}
		//if (ret.x != 0 || ret.y != 0) {
		//	//float moveLength = 0;	//動いた時のスピード
		//	//auto ptrTransform = GetComponent<Transform>();
		//	//auto ptrCamera = OnGetDrawCamera();
		//	////進行方向の向きを計算
		//	//auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
		//	//front.y = 0;
		//	//front.normalize();
		//	////進行方向向きからの角度を算出
		//	//float frontAngle = atan2(front.z, front.x);
		//	//コントローラの向き計算
		//	Vec2 moveVec(ret.x, ret.y);
		//	float moveSize = moveVec.length();
		//	//コントローラの向きから角度を計算
		//	float cntlAngle = atan2(-ret.x, ret.y);
		//	////トータルの角度を算出
		//	//float totalAngle = frontAngle + cntlAngle;
		//	////角度からベクトルを作成
		//	//angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
		//	angle = moveVec;
		//	////正規化する
		//	angle.normalize();
		//	////移動サイズを設定。
		//	//angle *= moveSize;
		//	////Y軸は変化させない
		//	//angle.z = 0;
		//}
		Vec3 moveVec(ret.x, ret.y,0);
		moveVec.normalize();

		float elapsedTime = App::GetApp()->GetElapsedTime();

			auto pos = GetComponent<Transform>()->GetPosition();
			pos += moveVec * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
			App::GetApp()->GetScene<Scene>()->SetAngle(pos);


	}


	//テキスト
	void UI_Text::OnCreate() {
		SetDrawLayer(m_layer);
		auto text = AddComponent<StringSprite>();
		text->SetTextAlignment(m_textAlignment);
		text->SetFont(m_fontName, m_fontSize);
		text->SetTextRect(m_rect);
		text->SetFontColor(m_color);
		text->SetText(m_text);
		if (m_isBk) text->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	void UI_Text::UpdateText(const wstring value) {
		auto text = GetComponent<StringSprite>();
		text->SetText(value);
	}
	void UI_Text::Remove() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<UI_Text>());
	}

	void Title_UI::OnCreate() {
		Draw();
	}

	void GameOverTitle_UI::OnCreate() {
		Draw();
	}
	void GameOverTitle_UI2::OnCreate() {
		Draw();
	}
	void Select_UI::OnCreate() {
		Draw();
	}
}