#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy1::Enemy1(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
		//float UPic,
		//float VPic
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		//m_UPic(UPic),
		//m_VPic(VPic),
		m_Mesh(L"Enemy_robot_3.bmf"),
		m_Texture(L"Tx_Enemy_robot_1.tga")
	{}
	Enemy1::~Enemy1() {}

	void Enemy1::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		auto PtrGra = AddComponent<Gravity>();

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(1.0f);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		//描画するメッシュを設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetMeshResource(m_Mesh);
		//ptrDraw->SetMeshToTransformMatrix(SpanMat);
		ptrDraw->SetTextureResource(m_Texture);
	}

	void Enemy1::OnUpdate() {

	}

	void Enemy1::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"SoundBox")) {
			auto PtrDraw = AddComponent<BcPNTStaticDraw>();

			PtrDraw->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 0.1f));
			auto SoundBoxPos = App::GetApp()->GetScene<Scene>()->GetPosition();


		}
	}

	//敵２
	Enemy2::Enemy2(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		float UPic,
		float VPic
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_UPic(UPic),
		m_VPic(VPic),
		m_Mesh(L"SecurityRobot_Animation_0001.bmf"),
		m_Texture(L"Tx_SecurityRobot.png")
	{}
	Enemy2::~Enemy2() {}

	void Enemy2::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		auto PtrGra = AddComponent<Gravity>();

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(1.0f);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float UCount = m_Scale.x / m_UPic;
		float VCount = m_Scale.z / m_VPic;
		for (size_t i = 0; i < vertices.size(); i++) {
			if (vertices[i].textureCoordinate.x >= 1.0f) {
				vertices[i].textureCoordinate.x = UCount;
			}
			if (vertices[i].textureCoordinate.y >= 1.0f) {
				float FrontBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				float BackBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, -1, 0));
				if (FrontBetween < 0.01f || BackBetween < 0.01f) {
					vertices[i].textureCoordinate.y = VCount;
				}
			}
		}

		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		//描画するメッシュを設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetMeshResource(m_Mesh);
		ptrDraw->SetTextureResource(m_Texture);
		//ptrDraw->SetMeshToTransformMatrix(SpanMat);
	}
}
//end basecross
