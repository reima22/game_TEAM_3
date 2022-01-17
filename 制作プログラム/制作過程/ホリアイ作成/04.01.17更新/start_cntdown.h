//=============================================================================
//
// �J�n���J�E���g�_�E���`�揈�� [start_cntdown.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _START_CNTDOWN_H_
#define _START_CNTDOWN_H_

#include "main.h"
#include "scene2D.h"

// �}�N����`
#define START_CNT_SIZE	(D3DXVECTOR2(100.0f,100.0f))

//==============================================================================
// �J�n���J�E���g�_�E���N���X
//==============================================================================
class CStartCntdown : public CScene
{
public:
	typedef enum
	{
		CNTDOWN_GO = 0,	// �e�N�X�`���uGO�v
		CNTDOWN_ONE,	// �e�N�X�`���u1�v
		CNTDOWN_TWO,	// �e�N�X�`���u2�v
		CNTDOWN_THREE,	// �e�N�X�`���u3�v
		CNTDOWN_MAX
	}CNTDOWN;

	CStartCntdown(int nPriority = PRIORITY_UI);
	~CStartCntdown();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStartCntdown *Create(void);

	//void TimerDecrease(void);		// �^�C�}�[����

	// �^�C�}�[���l�̎擾�E�ݒ�
	//int GetNumber(void) { return m_nTimer; }
	//void SetNumber(int nTimer);

	// �^�C�}�[�J�E���g�J�n�t���O�ݒ�
	bool GetStartCntdown(void) { return m_bStartCntdown; }
	void SetStartCntdown(bool bStartCntdown) { m_bStartCntdown = bStartCntdown; }

	bool GetCntDown(void) { return m_bCntDowning; }

private:
	CScene2D *m_pScene2D;							// 2D�|���S���N���X�|�C���^
	//LPDIRECT3DTEXTURE9 m_pTexture[CNTDOWM_MAX];	// �J�E���g�e�N�X�`��
	int m_nCntDown;									// �^�C�}�[���l
	int m_nDecereaseCnt;							// �����J�E���^�[
	CNTDOWN m_cntDown;								// ���݂̃J�E���g
	bool m_bStartCntdown;							// �J�E���g�J�n�̃t���O
	bool m_bCntDowning;								// �J�E���g�_�E����
};

#endif
