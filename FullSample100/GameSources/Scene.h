/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{


	enum GameStageKey {
		title,
		stageSelect,
		game,
		result,
		Max
	};

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		vector<wstring> m_stageName;

		void CreateResourses();
		void FindFile(wstring dir);
		shared_ptr<SoundItem> m_bgm;

		wstring m_stageKey[GameStageKey::Max];
		GameStageKey m_gameStageKey;
		Vec3 m_getangle;
		Vec3 m_getposition;
		Vec3 m_getsoundposition;
		Vec3 m_PlayerPos;
		Vec3 m_GoalPos;
		int m_check;
		int m_snum;
		bool m_UpdateCheck;

		//音の管理用
		bool m_SoundFlag = true;

		//ToMyCamera用
		bool MyCamaraFlag = false;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		void SetGameStage(GameStageKey key) {
			m_gameStageKey = key;
			PostEvent(0.0f,
				GetThis<ObjectInterface>(),
				GetThis<Scene>(),
				m_stageKey[m_gameStageKey]);
		}

		Vec3 SetAngle(Vec3 angle);
		Vec3 GetAngle();
		Vec3 SetPosition(Vec3 position);
		Vec3 GetPosition();
		Vec3 SetSoundPosition(Vec3 position);
		Vec3 GetSoundPosition();

		int SetCheck(int check);
		int GetCheck();

		int SetStageNum(int Snum);
		int GetStageNum();

		bool SetUpdateBool(bool check);
		bool GetUpdateBool();

		void SetCameraPos(Vec3 start, Vec3 goal);
		Vec3 GetStartCameraPos();
		Vec3 GetEndCameraPos();

		//SEの関数
		void PlaySE(wstring key, float vol) {
			auto &se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}

		//BGM
		void PlayBGM(wstring key, float vol) {
			auto &bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

		//BGMを止める
		void StopBGM() {
			auto &bgm = App::GetApp()->GetXAudio2Manager();
			bgm->Stop(m_bgm);
		}

		//音の管理用
		bool GetSoundFlag()
		{
			return m_SoundFlag;
		};

		void SetSoundFlag(bool soundFlag)
		{
			m_SoundFlag = soundFlag;
		}

		//MyCamara用
		bool SetToMyCameraFlag(bool flag)
		{
			MyCamaraFlag = flag;
			return MyCamaraFlag;
		}

		bool GetToMyCamara()
		{
			return MyCamaraFlag;
		}
	};



}

//end basecross