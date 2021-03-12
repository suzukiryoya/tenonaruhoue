
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{


	void Scene::CreateResourses() {
		wstring dataDir;
		//media�f�B���N�g���擾�p
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
			// ������FILE_ATTRIBUTE_DIRECTORY�Ȃ�
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// �f�B���N�g�������擾
				wstring ditectoryName = win32fd.cFileName;
				// �V�����t�H���_�̏ꏊ
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// ���̒�������
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//�摜�t�@�C���������ꍇ
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// �t�@�C���̏ꏊ
					wstring texture = dir + fileName;
					// �e�N�X�`���[��o�^
					App::GetApp()->RegisterTexture(fileName, texture);
				}
				//���������ꍇ
				if (exe == L".wav") {
					wstring wav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, wav);
				}


				//��O(bmf)
				if (exe == L".bmf") {
					// ��O�o�^
					//�{�[�����f���̏ꍇ
					if ((fileName == L"Player_11.bmf") ||
						(fileName == L"Goal_Spot_2.bmf")
						) {
						auto modelMesh = MeshResource::CreateBoneModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
					else
						//�X�^�e�B�b�N���f��
					{
						auto modelMesh = MeshResource::CreateStaticModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
				}

			}
		} while (FindNextFile(hFind, &win32fd));

		// �㏈��
		FindClose(hFind);

	}
	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//�N���A����F��ݒ�

			//���\�[�X�쐬
			CreateResourses();
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
