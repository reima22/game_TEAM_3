//--------------------------------------------------------------------------------
//
// �Q�[������[title.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "bg.h"
#include "logo.h"

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CBg;
//class CLogo;
class CTitleLogo;
class CTitleEnter;

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CTitle : CScene
{
public:
	CTitle();						//�R���X�g���N�^
	~CTitle();						//�f�X�g���N�^

	HRESULT Init(void);				//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����
	void Draw(void);				//�`�揈��

	static CTitle *Create(void);	// ��������

	static CBg*GetBg(void);			//�w�i���̌Ăяo��
	//static CLogo*GetLogo(void);		//���S���̌Ăяo��

private:

	static CBg*m_pBg;				//�w�i���̃|�C���^

	static CTitleLogo *m_pTitleLogo;	// �^�C�g�����S�|�C���^
	static CTitleEnter *m_pTitleEnter;	// �G���^�[�T�C���|�C���^

	//static CLogo*m_pLogo[2];		//���S���̃|�C���^

};

#endif


