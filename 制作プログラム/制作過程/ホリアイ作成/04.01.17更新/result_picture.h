//=============================================================================
//
// ���U���g�ɕ`�悷��}�̏��� [result_picture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_PICTURE_H_
#define _RESULT_PICTURE_H_

#include "main.h"
#include "scene.h"
#include "result.h"

// �}�N����`
#define R_PICT_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f))	// �Q�[�����ʕ\���̈ʒu
#define R_PICT_SIZE				(D3DXVECTOR2(480.0f, 80.0f))					// �Q�[�����ʕ\���̃T�C�Y
		  
#define R_PICT_SCORE_POS		(D3DXVECTOR3(250.0f, 260.0f, 0.0f))				// �X�R�A���S�̈ʒu
#define R_PICT_SCORE_SIZE		(D3DXVECTOR2(160.0f, 50.0f))					// �X�R�A���S�̃T�C�Y

#define R_PICT_TIMER_POS		(D3DXVECTOR3(100.0f, 400.0f, 0.0f))				// �^�C�}�[���S�̈ʒu
#define R_PICT_TIMER_SIZE		(D3DXVECTOR2(100.0f, 50.0f))						// �^�C�}�[���S�̃T�C�Y
#define R_PICT_TIMER_MARK_POS_0	(D3DXVECTOR3(440.0f, 400.0f, 0.0f))				// �^�C�}�[�Z�p�L���O�̈ʒu
#define R_PICT_TIMER_MARK_POS_1	(D3DXVECTOR3(550.0f, 400.0f, 0.0f))				// �^�C�}�[�Z�p�L���P�̈ʒu
#define R_PICT_TIMER_MARK_POS_2	(D3DXVECTOR3(840.0f, 400.0f, 0.0f))				// �^�C�}�[�Z�p�L���Q�̈ʒu

#define R_PICT_COUNT_POS		(D3DXVECTOR3(100.0f, 525.0f, 0.0f))				// �J�E���g���S�̈ʒu
#define R_PICT_COUNT_SIZE		(D3DXVECTOR2(100.0f, 50.0f))						// �J�E���g���S�̃T�C�Y
#define R_PICT_COUNT_MARK_POS_0	(D3DXVECTOR3(440.0f, 525.0f, 0.0f))				// �J�E���g�Z�p�L���O�̈ʒu
#define R_PICT_COUNT_MARK_POS_1	(D3DXVECTOR3(550.0f, 525.0f, 0.0f))				// �J�E���g�Z�p�L���P�̈ʒu
#define R_PICT_COUNT_MARK_POS_2	(D3DXVECTOR3(840.0f, 525.0f, 0.0f))				// �J�E���g�Z�p�L���Q�̈ʒu

#define R_PICT_BONUS_POS		(D3DXVECTOR3(100.0f, 650.0f, 0.0f))				// �{�[�i�X���S�̈ʒu
#define R_PICT_BONUS_SIZE		(D3DXVECTOR2(100.0f, 50.0f))						// �{�[�i�X���S�̃T�C�Y
#define R_PICT_BONUS_MARK_POS_0	(D3DXVECTOR3(440.0f, 650.0f, 0.0f))				// �{�[�i�X�Z�p�L���O�̈ʒu
#define R_PICT_BONUS_MARK_POS_1	(D3DXVECTOR3(550.0f, 650.0f, 0.0f))				// �{�[�i�X�Z�p�L���P�̈ʒu
#define R_PICT_BONUS_MARK_POS_2	(D3DXVECTOR3(840.0f, 650.0f, 0.0f))				// �{�[�i�X�Z�p�L���Q�̈ʒu

#define R_PICT_MARK_SIZE		(D3DXVECTOR2(40.0f, 40.0f))						// �Z�p�L���̃T�C�Y

// �O���錾
class CScene2D;	// 2D�|���S���`��N���X

//==============================================================================
// ���U���g��ʂɕ`�悷��}�̃N���X
//==============================================================================
class CResultPicture : public CResult
{
public:
	CResultPicture(int nPriority = PRIORITY_UI);
	~CResultPicture();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, char *pTypeCheck);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ��������
	static CResultPicture *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, char *pTypeCheck);

private:
	CScene2D *m_pScene2D;	// 2D�|���S���N���X
};
#endif