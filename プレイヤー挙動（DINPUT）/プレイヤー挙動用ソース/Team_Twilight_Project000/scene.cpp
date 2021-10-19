//==============================================================================
//
// �I�u�W�F�N�g�`�揈���kscene.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "pause.h"
#include "camera.h"

// �ÓI�����o�ϐ��錾
int CScene::m_nNumAll = 0;
CScene *CScene::m_pTop[PRIORITY_MAX] = {};			// �擪�̃I�u�W�F�N�g�|�C���^
CScene *CScene::m_pCur[PRIORITY_MAX] = {};			// ���݂̃I�u�W�F�N�g�̃|�C���^

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CScene::CScene(int nPriority)
{
	// ���X�g�ւ̒ǉ�
	if (m_pTop[nPriority] == NULL)
	{// �擪����
		// �O��̃|�C���^����
		this->m_pNext = NULL;
		this->m_pPrev = NULL;

		// �擪�|�C���^�֑��
		m_pTop[nPriority] = this;
	}	
	else
	{// ���ȍ~����
		// �Ō�������̃|�C���^�ֈڍs
		m_pCur[nPriority]->m_pNext = this;

		// 1�O�̃I�u�W�F�N�g�̃|�C���^���Ō���Ɏw��
		this->m_pPrev = m_pCur[nPriority];

		// ���̃|�C���^����
		this->m_pNext = NULL;
	}

	// �Ō���̑��
	m_pCur[nPriority] = this;

	m_bDeath = false;			// ���S�t���O
	m_objType = OBJTYPE_NONE;	// �I�u�W�F�N�g�^�C�v
	m_nNumAll++;				// �I�u�W�F�N�g�̑���
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CScene::~CScene()
{
}

//==============================================================================
// �S�J��
//==============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// ���[�v
		while (pScene)
		{// NULL�ŏI��
			// ���ւ̃|�C���^
			CScene *pSceneNext = pScene->m_pNext;

			// ���S�t���O�̐���
			pScene->m_bDeath = true;

			// ���̃|�C���^
			pScene = pSceneNext;
		}
	}
}

//==============================================================================
// �S�X�V
//==============================================================================
void CScene::UpdateAll(void)
{
	// �X�V����
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// ���̏��(m_pNext)��������葱����
		while (pScene)
		{
			if (nCntPriority < PRIORITY_PAUSE && CPause::GetPause() == true)
			{// �|�[�Y���̒�~
				break;
			}

			// ���̏����
			CScene *pSceneNext = pScene->m_pNext;

			// �X�V����
			pScene->Update();

			// ���̏��
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// ���S�t���O�������Ȃ�Δj��
		while (pScene)
		{
			// ���̏����
			CScene *pSceneNext = pScene->m_pNext;

			// ���S�t���O�������Ă���Ƃ�
			if (pScene->m_bDeath == true)
			{
				// ���X�g�̍Č`��
				if (pScene->m_pPrev != NULL)
				{// ���O�̃|�C���^����
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{// ����̃|�C���^����
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (pScene == m_pTop[nCntPriority])
				{// ���X�g�擪
					m_pTop[nCntPriority] = pScene->m_pNext;
				}

				if(pScene == m_pCur[nCntPriority])
				{// ���X�g�Ō��
					m_pCur[nCntPriority] = pScene->m_pPrev;
				}

				// �j��
				delete pScene;
				pScene = NULL;

				m_nNumAll--;
			}

			// ���̏��
			pScene = pSceneNext;
		}	
	}
}

//==============================================================================
// �S�`��
//==============================================================================
void CScene::DrawAll(void)
{
	// �J�����̎擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̎擾
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// ���̏��(m_pNext)��������葱����
		while (pScene)
		{
			// ���̏����
			CScene *pSceneNext = pScene->m_pNext;

			// �X�V����
			pScene->Draw();

			// ���̏��
			pScene = pSceneNext;
		}
	}
}

//==============================================================================
// ��ނ̐ݒ�
//==============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//==============================================================================
// ��ނ̎擾
//==============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//==============================================================================
// �擪�V�[���̎擾
//==============================================================================
CScene *CScene::GetScene(int nPriority)
{
	return m_pTop[nPriority];
}

//==============================================================================
// ���V�[���̎擾
//==============================================================================
CScene *CScene::GetSceneNext(CScene *pScene)
{
	return pScene->m_pNext;
}

//==============================================================================
// �����J��
//==============================================================================
void CScene::Release(void)
{	
	// ���S�t���O�̐���
	this->m_bDeath = true;
}