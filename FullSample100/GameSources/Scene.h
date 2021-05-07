/*!
@file Scene.h
@brief �V�[��
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
	///	�Q�[���V�[��
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
		int m_check;
		bool m_UpdateCheck;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		void SetGameStage(GameStageKey key) {
			m_gameStageKey = key;
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), m_stageKey[m_gameStageKey]);
		}

		Vec3 SetAngle(Vec3 angle);
		Vec3 GetAngle();
		Vec3 SetPosition(Vec3 position);
		Vec3 GetPosition();
		Vec3 SetSoundPosition(Vec3 position);
		Vec3 GetSoundPosition();

		int SetCheck(int check);
		int GetCheck();

		bool SetUpdateBool(bool check);
		bool GetUpdateBool();


		//SE�̊֐�
		void PlaySE(wstring key, float vol) {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}

		//BGM
		void PlayBGM(wstring key, float vol) {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

		//BGM���~�߂�
		void StopBGM() {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			bgm->Stop(m_bgm);
		}


	};



}

//end basecross