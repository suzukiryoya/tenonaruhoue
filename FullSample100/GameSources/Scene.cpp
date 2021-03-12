
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
		//App::GetApp()->GetAssetsDirectory(dataDir);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		FindFile(dataDir);
		FindFile(mediaDir + L"Textures/");
		FindFile(mediaDir + L"Model/");
		//FindFile(mediaDir + L"BGM/");
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
					if ((fileName == L"Player_11.bmf") ||
						(fileName == L"Goal_Spot_2.bmf")
						) {
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
			//クリアする色を設定

			//リソース作成
			CreateResourses();
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
