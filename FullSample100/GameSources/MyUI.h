#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_Base :public GameObject {
		Vec2 m_Vertex;
		float m_size;
		Vec3 m_pos;
		Vec3 m_scale;
		Col4 m_color;
		int m_layer;
		wstring m_textures;

	public:

		UI_Base(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			GameObject(StagePtr),
			m_Vertex(vertex),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer),
			m_color(color),
			m_textures(textures)

		{}
		~UI_Base() {}
		void Draw();

	};

	class Clear : public UI_Base {

		// コントローラから方向ベクトルを得る

		float m_Speed=600.0f;

	public:

		Clear(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Clear() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		


	};

	//テキスト
	class UI_Text :public GameObject {
		wstring m_fontName;
		float m_fontSize;
		Col4 m_color;
		Rect2D<float> m_rect;
		StringSprite::TextAlignment m_textAlignment;
		wstring m_text;
		int m_layer;
		bool m_isBk;

	public:
		UI_Text(const shared_ptr<Stage>& StagePtr,
			const wstring& fontName,
			const float fontSize,
			const Col4& color,
			const Rect2D<float>& rect,
			const StringSprite::TextAlignment textAlignment,
			const wstring& text,
			const int layer,
			const bool isBk
		) :
			GameObject(StagePtr),
			m_fontName(fontName),
			m_fontSize(fontSize),
			m_color(color),
			m_rect(rect),
			m_textAlignment(textAlignment),
			m_text(text),
			m_layer(layer),
			m_isBk(isBk)
		{}
		~UI_Text() {}

		virtual void OnCreate() override;

		void UpdateText(const wstring value);

		void Remove();
	};

	class Title_UI : public UI_Base {
	public:

		Title_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Title_UI() {}

		virtual void OnCreate() override;

	};


	class GameOverTitle_UI : public UI_Base {
	public:

		GameOverTitle_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~GameOverTitle_UI() {}

		virtual void OnCreate() override;

	};
	class GameOverTitle_UI2 : public UI_Base {
	public:

		GameOverTitle_UI2(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~GameOverTitle_UI2() {}

		virtual void OnCreate() override;

	};

}