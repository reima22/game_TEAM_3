//=============================================================================
//
// �I�u�W�F�N�g�N���X [scene.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Scene.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
vector <CScene*> CScene::m_aSceneVc[SCENE_PRIORITY_MAX];
int CScene::m_nNumAll;

//*****************************************************************************
// �I�u�W�F�N�g�N���X (��{)
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	// �R���e�i�̐擪���炱�̃V�[���̃|�C���^���i�[
	// �S�̐����C���N�������g
	// �D��x���L�^
	// �I�u�W�F�N�g�̎�ނ𖳂��ɐݒ�
	m_aSceneVc[nPriority].push_back(this);
	m_nNumAll++;
	m_nPriority = nPriority;
	m_objType = OBJTYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CScene::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene::Draw(void)
{

}

//=============================================================================
// ���ׂĂ̏I������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++) {
		for (int i = 0; 0 < (signed)m_aSceneVc[nCntPriority].size();) {
			if (m_aSceneVc[nCntPriority][i] != NULL) {
				m_aSceneVc[nCntPriority][i]->Uninit();
			}
		}
	}
}

//=============================================================================
// ���ׂĂ̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++) {
		for (unsigned int i = 0; i < m_aSceneVc[nCntPriority].size(); i++) {
			if (m_aSceneVc[nCntPriority][i] != NULL) {
				m_aSceneVc[nCntPriority][i]->Update();
			}
		}
	}
}

//=============================================================================
// ���ׂĂ̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++) {
		for (unsigned int i = 0; i < m_aSceneVc[nCntPriority].size(); i++) {
			if (m_aSceneVc[nCntPriority][i] != NULL) {
				m_aSceneVc[nCntPriority][i]->Draw();
			}
		}
	}
}

//=============================================================================
// �J������
//=============================================================================
void CScene::Release(void)
{
	for (unsigned int i = 0; i < m_aSceneVc[m_nPriority].size(); i++) {
		if (m_aSceneVc[m_nPriority][i] == this) {
			int nPriority = m_nPriority;
			m_aSceneVc[nPriority].erase(m_aSceneVc[nPriority].begin() + i);
			m_nNumAll--;
			break;
		}
	}
}

//=============================================================================
// �V�[���̃R���e�i���擾
//=============================================================================
vector<CScene*> *CScene::GetSceneList(int nPriority)
{
	return &m_aSceneVc[nPriority];
}

//=============================================================================
// �D��x�̒l�ݒ�
//=============================================================================
void CScene::SetPriority(int nPriority)
{
	CScene *pScene = this;
	for (auto itr = m_aSceneVc[m_nPriority].begin(); itr != m_aSceneVc[m_nPriority].end(); itr++) {
		if ((*itr) == this) {
			m_aSceneVc[m_nPriority].erase(itr);
			break;
		}
	}
	m_aSceneVc[nPriority].push_back(this);
	m_nPriority = nPriority;
}