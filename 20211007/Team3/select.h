//=============================================================================
//
// �X�e�[�W�Z���N�g [select.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

//*****************************************************************************
// �w�b�_�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "Scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SELECT_BG_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0))			// �w�i�ʒu
#define SELECT_BG_SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0))				// �w�i�T�C�Y

#define SELECT_TEXT_SIZE (D3DXVECTOR3(300, 80, 0))						// �e�L�X�g�|���S���̃T�C�Y
#define SELECT_TEXT_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 150, 0))	// �@�@�@�@�@�@�@�@�@�@�ʒu

#define SELECT_MAP_SIZE (D3DXVECTOR3(250, 250, 0))			// �X�e�[�W�̃T�C�Y
#define SELECT_MAP_SIZE_SELECTED (D3DXVECTOR3(300, 300, 0))	// �I�����̃T�C�Y
#define SELECT_MAP_SIZE_AMPLITUDE (10)						// �I�����̃T�C�Y�̐U�ꕝ
#define SELECT_MAP_SIZE_FREQUENCY (0.01f)					// �T�C�Y�̕ύX���鑬�x
#define SELECT_MAP_BLINK_FREQUENCY (1.0f)					// �|���S���_�ł̑��x

#define SELECT_MAP_ARROW_SIZE (D3DXVECTOR3(40, 60, 0))		// ���̃T�C�Y
#define SELECT_MAP_ARROW_OFFSET (D3DXVECTOR3(0, -380, 0))	// ���̈ʒu�I�t�Z�b�g
#define SELECT_MAP_ARROW_AMPLITUDE (10)						// ���̗h��̐U�ꕝ
#define SELECT_MAP_ARROW_FREQUENCY (0.01f)					// ���̗h��̕p�x

#define SELECT_MAP_OFFSET (D3DXVECTOR3(600, 150, 0))		// �}�b�v�̃|���S���ʒu�I�t�Z�b�g
#define SELECT_MAP1_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 - SELECT_MAP_OFFSET.x, SCREEN_HEIGHT / 2 + SELECT_MAP_OFFSET.y, 0))	// �X�e�[�W�P�ʒu
#define SELECT_MAP2_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SELECT_MAP_OFFSET.y, 0))						// �X�e�[�W�Q�ʒu
#define SELECT_MAP3_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 + SELECT_MAP_OFFSET.x, SCREEN_HEIGHT / 2 + SELECT_MAP_OFFSET.y, 0))	// �X�e�[�W�R�ʒu

//*****************************************************************************
// �X�e�[�W�Z���N�g�N���X
//*****************************************************************************
class CStageSelect : public CScene
{
public:
	// �X�e�[�W�̎��
	typedef enum {
		STAGE_SELECT_1 = 0,
		STAGE_SELECT_2,
		STAGE_SELECT_3,
		
		STAGE_SELECT_MAX,
	} STAGE_SELECT;

	CStageSelect();
	~CStageSelect();

	STAGE_SELECT GetSelectingStage(void) { return m_currentStage; }	// �I�����Ă���X�e�[�W���擾

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	typedef enum {	// �z��̓Y�����p�C���f�b�N�X
		SELECT_IDX_BG = 0,
		SELECT_IDX_TEXT,
		SELECT_IDX_MAP1,
		SELECT_IDX_MAP2,
		SELECT_IDX_MAP3,
		SELECT_IDX_ARROW,

		SELECT_IDX_MAX,
	} SELECT_IDX;

	void SelectStage(STAGE_SELECT stage);	// �X�e�[�W�I��
	void StageScale(STAGE_SELECT stage);	// �X�e�[�W�̊g�k
	void StageBlink(STAGE_SELECT stage);	// �X�e�[�W�̓_��
	void WaveArrow(void);					// ����h�ꂳ����

	SELECT_IDX ToIdx(STAGE_SELECT stage);

	CScene2D *m_apScene[SELECT_IDX_MAX];	// 2D�I�u�W�F�N�g
	STAGE_SELECT m_currentStage;			// ���ݑI�����Ă���X�e�[�W
	bool m_bSelected;
};

#endif

