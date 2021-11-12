//=============================================================================
//
// �}�l�[�W�� [manager.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "sound.h"

//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;		// �����_���[�N���X
class CInputKeyboard;	// �L�[�{�[�h�N���X
class CGamepad;			// �Q�[���p�b�h�N���X
class CFade;			// �t�F�[�h�N���X
class CMode;			// �Q�[�����[�h�N���X
class CCamera;			// �J�����N���X
class CLight;			// ���C�g�N���X
class CTextData;		// �e�L�X�g�f�[�^�N���X
class CTexture;			// �e�N�X�`���N���X
class CCollision;		// �����蔻��N���X

//=============================================================================
// �}�l�[�W���N���X
//=============================================================================
class CManager
{
public:
	CManager();
	 ~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �N���X�̎擾
	static CRenderer *GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CGamepad *GetInputGamepad(void) { return m_pGamepad; }

	// �t�F�[�h�|�C���^�̎擾
	static CFade *GetFade(void) { return m_pFade; }

	// ���[�h�N���X�|�C���^�̎擾
	static CMode *GetModePoint(void) { return m_pMode; }

	// ���|�C���^�̎擾
	static CSound *GetSound(void) { return m_pSound; }

	// BGM�̍Đ��ݒ�
	static bool GetBGMPlay(CSound::BGMTYPE type) { return m_bBGM[type]; }

	// �J�����|�C���^�̎擾
	static CCamera *GetCamera(void) { return m_pCamera; }
	
	// �e�N�X�`���|�C���^�̎擾
	static CTexture *GetTexture(void) { return m_pTexture; }

	// �����蔻��̎擾
	static CCollision *GetCollision(void) { return m_pCollision; }

private:
	static CRenderer* m_pRenderer;				// �����_�����O�N���X
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�N���X
	static CGamepad *m_pGamepad;				// �Q�[���p�b�h�N���X

	//static CTitle *m_pTitle;					// �^�C�g���|�C���^
	//static CTutorial *m_pTutorial;				// �`���[�g���A���|�C���^
	//static CGame *m_pGame;						// �Q�[���|�C���^
	//static CResult *m_pResult;					// ���U���g�|�C���^
	//static CRanking *m_pRanking;				// �����L���O�|�C���^
	//static MODE m_mode;							// �V�[�����[�h

	static CFade *m_pFade;						// �t�F�[�h�N���X�|�C���^
	static CMode *m_pMode;						// �Q�[�����[�h�Ǘ��|�C���^

	static CSound *m_pSound;					// �T�E���h�̃|�C���^

	static CCamera *m_pCamera;					// �J�����̃|�C���^
	static CLight *m_pLight;					// ���C�g�̃|�C���^

	static CTextData *m_pTextData;				// �e�L�X�g�f�[�^�N���X�̃|�C���^
	static CTexture *m_pTexture;				// �e�N�X�`���N���X�̃|�C���^
	static CCollision *m_pCollision;			// �����蔻��N���X�̃|�C���^

	static bool m_bBGM[CSound::BGMTYPE_MAX];	// BGM�̃I���I�t
};

#endif