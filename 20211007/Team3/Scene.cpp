//=============================================================================
//
// �I�u�W�F�N�g�N���X [scene.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "scene.h"


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
list<CScene*> CScene::m_apScene[SCENE_PRIORITY_MAX];
int CScene::m_nNumAll;

//*****************************************************************************
// �I�u�W�F�N�g�N���X (��{)
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	// �w�肳�ꂽ�D��x�̏ꏊ��
	// �󂢂Ă���ꏊ��CScene�̃|�C���^���i�[
	// �����C���N�������g
	// ID���L�^
	m_apScene[nPriority].push_front(this);
	m_nNumAll++;
	m_nPriority = nPriority;

	//for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//{
	//	if (m_apScene[nPriority][nCntScene] == NULL)
	//	{
	//		m_apScene[nPriority][nCntScene] = this;
	//		m_nNumAll++;
	//		m_nID = nCntScene;
	//		m_nPriority = nPriority;

	//		break;
	//	}
	//}
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
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	{
		for (auto itr = m_apScene[nCntPriority].begin(); itr != m_apScene[nCntPriority].end(); itr++) {
			if ((*itr) != NULL)
				(*itr)->Uninit();
		}
	}

	//for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//	{
	//		if (m_apScene[nCntPriority][nCntScene] != NULL)
	//		{
	//			m_apScene[nCntPriority][nCntScene]->Uninit();
	//		}
	//	}
	//}
}

//=============================================================================
// ���ׂĂ̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{

	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	{
		for (auto itr = m_apScene[nCntPriority].begin(); itr != m_apScene[nCntPriority].end(); itr++) {
			if ((*itr) != NULL)
				(*itr)->Update();
		}
	}

	//for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//	{
	//		if (m_apScene[nCntPriority][nCntScene] != NULL)
	//		{
	//			m_apScene[nCntPriority][nCntScene]->Update();
	//		}
	//	}
	//}
}

//=============================================================================
// ���ׂĂ̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	{
		for (auto itr = m_apScene[nCntPriority].begin(); itr != m_apScene[nCntPriority].end(); itr++) {
			if ((*itr) != NULL)
				(*itr)->Draw();
		}
	}
}

//=============================================================================
// �J������
//=============================================================================
void CScene::Release(void)
{
	auto itr = next(m_apScene[m_nPriority].begin(), m_nID);
	if ((*itr) != NULL)
	{
		delete (*itr);
		(*itr) = NULL;
		m_nNumAll--;
	}
}

//=============================================================================
// �I�u�W�F�N�g���������|�C���^���擾
//=============================================================================
CScene *CScene::GetScene(int nPriority, int nScene)
{
	auto itr = next(&m_apScene[nPriority], nScene);
	return (CScene*)(itr);

	//return m_apScene[nPriority][nScene];
}

//=============================================================================
// �I�u�W�F�N�g�̃|�C���^�i�[
//=============================================================================
void CScene::SetScene(int nPriority, int nScene, CScene *obj)
{
	auto itr = m_apScene[nPriority].begin();
	advance(itr, nScene);
	if ((*itr) == NULL)
		m_apScene[nPriority].emplace(itr, obj);
	

	//if (m_apScene[nPriority][nScene] == NULL)
	//{ 
	//	m_apScene[nPriority][nScene] = obj;
	//}
}

//=============================================================================
// �D��x�̒l�ݒ�
//=============================================================================
void CScene::SetPriority(int nPriority)
{
	//for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//{
	//	if (m_apScene[nPriority][nCntScene] == NULL)
	//	{
	//		m_apScene[nPriority][nCntScene] = this;	// �V�����ꏊ�Ƀ|�C���^�ۑ�
	//		m_apScene[m_nPriority][m_nID] = NULL;	// ���̏ꏊ�����
	//		m_nID = nCntScene;						// �V����ID�ݒ�
	//		m_nPriority = nPriority;				// �V�����D��x�ݒ�
	//		m_nNumAll++;							// ����������߂�
	//	}
	//}
}