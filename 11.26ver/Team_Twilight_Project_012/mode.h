//=============================================================================
//
// �Q�[�����[�h�Ǘ����� [mode.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MODE_H_
#define _MODE_H_

#include "main.h"
#include "scene.h"

// �O���錾
class CTitle;			// �^�C�g���N���X
class CTutorial;		// �`���[�g���A���N���X
class CGame;			// �Q�[���N���X
class CResult;			// ���U���g�N���X
class CRanking;			// �����L���O�N���X	

class CStageSelect;		// �X�e�[�W�I���N���X

//==============================================================================
// �Q�[�����[�h�Ǘ��N���X
//==============================================================================
class CMode : public CScene
{
public:
	// �Q�[�����[�h�̗�
	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_SELECT,	// �X�e�[�W�I��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_RANKING,	// �����L���O
		MODE_MAX
	}MODE;

	CMode(int nPriority = PRIORITY_DEFAULT);
	~CMode();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMode *Create(void);

	// ���[�h�擾�E�ݒ�
	MODE GetMode(void) { return m_mode; }
	void SetMode(MODE mode);

private:
	static CTitle *m_pTitle;				// �^�C�g���|�C���^
	static CStageSelect *m_pStageSelect;	// �X�e�[�W�Z���N�g�|�C���^
	static CTutorial *m_pTutorial;			// �`���[�g���A���|�C���^
	static CGame *m_pGame;					// �Q�[���|�C���^
	static CResult *m_pResult;				// ���U���g�|�C���^
	static CRanking *m_pRanking;			// �����L���O�|�C���^
	static MODE m_mode;						// �V�[�����[�h
};

#endif
