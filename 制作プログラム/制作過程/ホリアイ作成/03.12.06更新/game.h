
//=============================================================================
//
// �Q�[�����[�h���� [game.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// �O���錾
class CSceneX;			// �V�[��X�N���X
class CPlayer;			// �v���C���[�N���X
class CObject;			// �I�u�W�F�N�g�N���X
class CPause;			// �|�[�Y�N���X
class CTerrain;			// ���b�V��
class CTimer;			// �^�C�}�[�N���X
class CFall;			// �������N���X
class CSound;			// �T�E���h�N���X
class CMeshfield;		// ���b�V���t�B�[���h�N���X
class CStartCntdown;	// �J�n���J�E���g�_�E���N���X
class CFog;				// �t�H�O���ʃN���X

//==============================================================================
// �Q�[�����[�h�N���X
//==============================================================================
class CGame : public CMode
{
public:
	CGame(int nPriority = PRIORITY_DEFAULT);
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	void SetStageObject(void);

	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CTerrain *GetTerrain(void) { return m_pTerrain; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CFall *GetFall(void) { return m_pFall; }
	static CObject *GetPointObject(int nCnt) { return m_pObject[nCnt]; }
	static CMeshfield *GetMeshField(int nIdx) { return m_pMeshField[nIdx]; }	// ���b�V���t�B�[���h�|�C���^
	static CStartCntdown *GetStartCntdown(void) { return m_pStartCntdown; }		// �J�n���J�E���g�_�E���N���X
	static CFog *GetFog(void) { return m_pFog; }								// �t�H�O�擾

private:
	int m_nNumObject;						// �I�u�W�F�N�g��
	int m_nNumMeshfield;					// ���b�V���t�B�[���h�̐�
	static CPause *m_pPause;				// �|�[�Y�̃|�C���^
	static CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^

	static CTimer *m_pTimer;				// �^�C�}�[�̃|�C���^
	static CFall *m_pFall;					// �������̃|�C���^
	static CTerrain *m_pTerrain;			// ���b�V��	

	static CObject **m_pObject;				// �I�u�W�F�N�g�̃|�C���^
	static CMeshfield **m_pMeshField;		// �I���W�i�����b�V��
	static CStartCntdown *m_pStartCntdown;	// �J�n���J�E���g�_�E���N���X
	static CFog *m_pFog;					// �t�H�O���ʃN���X
};

#endif