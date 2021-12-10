//--------------------------------------------------------------------------------
//
// �Q�[������[logo.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LOGO_H_
#define _LOGO_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define MAX_GAMELOGO			(2)									//	�Q�[�����Ŏg���郍�S�̍ő吔
#define MAX_LOGO				(5)									//	���S�̍ő吔
#define TIME_COLOR				(50)								//	�F�ω�����
#define MOVE_SPEED				(15.0f)								//	���x�l
#define GRAVITY					(0.4f)								//	�d�͒l

#define POS_TITLE_Y				(230.0f)							//	�^�C�g���@	Y���̈ʒu
#define POS_TITLE_X				(630.0f)							//	�^�C�g���@	X���̈ʒu
#define MOVE_TITLE_Y			(0.0f)								//	�^�C�g���@	Y���̈ړ��l
#define MOVE_TITLE_X			(0.014f)							//	�^�C�g���@	X���̈ړ��l

#define POS_START_Y				(550.0f)							//	START�@		Y���̈ʒu
#define POS_START_X				(640.0f)							//	START�@		X���̈ʒu
#define MOVE_START_Y			(-8.0f)								//	START�@		Y���̈ړ��l
#define MOVE_START_X			(0.0f)								//	START�@		X���̈ړ��l

//================================================================================
//�I�u�W�F�N�g�N���X(���S)
//================================================================================
class CLogo :public CScene
{
public:

	//�e���蕪��
	typedef enum
	{
		LOGOTYPE_NONE = 0,
		LOGOTYPE_START,												//	�X�^�[�g
		LOGOTYPE_TITLENAME,											//	�^�C�g����
		LOGOTYPE_MAX						    

	}LOGOTYPE;

	CLogo(int nPriority = OBJTYPE_LOGO);							//	�R���X�g���N�^
	~CLogo();														//	�f�X�g���N�^

	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		LOGOTYPE logoType);											//	���S�̐���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//	����������
	void Uninit(void);												//	�I������
	void Update(void);												//	�X�V����
	void Draw(void);												//	�`�揈��

	static HRESULT Load(void);										//	�ǂݍ��ݏ���
	static void Unload(void);										//	�j������

	LOGOTYPE GetInfoType(void) { return m_LogoType; }				//	���S�^�C�v���̌Ăяo��
	void SetInfoType(LOGOTYPE logoType) {m_LogoType = logoType;}	//	���S�^�C�v���̎擾

private:

	LOGOTYPE m_LogoType;											//  ���S�^�C�v

	bool m_bEnter;													//  �G���^�[�����������ǂ���
	bool m_bTutorial;												//  �`���[�g���A����ʂɈړ����邩�ǂ���
	bool m_bJump;													//  �W�����v����
		
	int m_nCntColor;												//	�ҋ@�_�ŃJ�E���g
	int m_nTimeColor;												//	����_�ŃJ�E���g
	int m_nTimer;													//	�^�C�}�[
	int m_nJumpCnt;													//	�W�����v�J�E���g
	int m_nAppearanceCnt;											//	�o���J�E���g

	float m_fSpd;													//  �ړ����x

	D3DXVECTOR3 m_scale;											//	�傫��
	D3DXVECTOR3 m_move;												//	�ړ��l
	D3DXCOLOR	m_Color;											//	�F
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_LOGO];				//	�e�N�X�`��
	CScene2D*m_apScene2D[5];										//	CScene2D�̃|�C���^
};
#endif
