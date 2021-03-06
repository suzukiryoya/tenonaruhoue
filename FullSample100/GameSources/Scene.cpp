
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{


	void Scene::CreateResourses() {
		wstring dataDir;
		//mediaディレクトリ取得用
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		FindFile(dataDir);
		FindFile(mediaDir + L"Textures/");
		FindFile(mediaDir + L"Model/");
		FindFile(mediaDir + L"Sounds/");
	}

	void Scene::FindFile(wstring dir) {
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;

		wstring newdir = dir + L"*.*";
		const wchar_t* dirExtension = newdir.c_str();

		hFind = FindFirstFile(dirExtension, &win32fd);

		do {
			// 属性がFILE_ATTRIBUTE_DIRECTORYなら
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// ディレクトリ名を取得
				wstring ditectoryName = win32fd.cFileName;
				// 新しいフォルダの場所
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// その中を検索
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//画像ファイルだった場合
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// ファイルの場所
					wstring texture = dir + fileName;
					// テクスチャーを登録
					App::GetApp()->RegisterTexture(fileName, texture);
				}
				//音だった場合
				if (exe == L".wav") {
					wstring wav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, wav);
				}


				//例外(bmf)
				if (exe == L".bmf") {
					// 例外登録
					//ボーンモデルの場合
					if ((fileName == L"Protagonist_Robot_5.bmf") ||
						(fileName == L"Goal_Spot_2.bmf") ||
						(fileName == L"SecurityRobot_Animation_0002.bmf") ||
						(fileName == L"Enemy_robot_4.bmf") ||
						(fileName == L"Door_Animation.bmf")
					) 
					{
						auto modelMesh = MeshResource::CreateBoneModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
					else
						//スタティックモデル
					{
						auto modelMesh = MeshResource::CreateStaticModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
				}
			}
		} while (FindNextFile(hFind, &win32fd));

		// 後処理
		FindClose(hFind);

	}
	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			Col4 Col;
			Col.set(200.0f / 255.0f, 200.0f / 255.0f, 100.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			m_check = 3;
			m_UpdateCheck = false;
			//クリアする色を設定

			//リソース作成
			CreateResourses();
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");

			SetGameStage(GameStageKey::title);
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}


	void Scene::OnEvent(const shared_ptr<Event>& event) {

		switch (m_gameStageKey)
		{
		case GameStageKey::title:
			ResetActiveStage<TitleStage>();
			break;
		case GameStageKey::stageSelect:
			ResetActiveStage<SelectStage>();
			SetSoundFlag(true);
			break;
		case GameStageKey::game:
			ResetActiveStage<GameStage>();
			break;
		case GameStageKey::result:
			ResetActiveStage<ResultStage>();
			break;
		}

	}


	Vec3 Scene::SetAngle(Vec3 angle) {
		m_getangle = angle;
		return angle;
	}
	Vec3 Scene::GetAngle() {
		
		return m_getangle;
	}
	Vec3 Scene::SetPosition(Vec3 position) {
		m_getposition = position;
		return position;
	}
	Vec3 Scene::GetPosition() {
		return m_getposition;
	}

	Vec3 Scene::SetSoundPosition(Vec3 position) {
		m_getsoundposition = position;
		return position;
	}
	Vec3 Scene::GetSoundPosition() {
		return m_getsoundposition;
	}

	int Scene::SetCheck(int check) {
		m_check = check;
		return check;
	}

	int Scene::GetCheck() {
		return m_check;
	}

	bool Scene::SetUpdateBool(bool check) {
		m_UpdateCheck = check;
		return check;
	}

	bool Scene::GetUpdateBool() {
		return m_UpdateCheck;
	}

	int Scene::SetStageNum(int Snum){
		m_snum = Snum;
		return Snum;
	}

	int Scene::GetStageNum()	{
		return m_snum;
	}

	void Scene::SetCameraPos(Vec3 start, Vec3 goal)
	{
		m_PlayerPos = start;
		m_GoalPos = goal;
	}

	Vec3 Scene::GetStartCameraPos()
	{
		return m_PlayerPos;
	}

	Vec3 Scene::GetEndCameraPos()
	{
		return m_GoalPos;
	}
}
//end basecross
