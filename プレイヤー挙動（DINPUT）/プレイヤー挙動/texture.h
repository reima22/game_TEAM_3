//=============================================================================
//
// �e�N�X�`���Ǘ� [texture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//==============================================================================
// �e�N�X�`���Ǘ��N���X
//==============================================================================
class CTexture
{
public:
	// �e�N�X�`���̎��
	typedef enum
	{
		TEXTYPE_NONE = 0,			// �e�N�X�`������
		TEXTYPE_PLAYER_0,			// �v���C���[��0
		TEXTYPE_PLAYER_1,			// �v���C���[��1
		TEXTURE_OBJECT,

		TEXTYPE_TITLE_BG,			// �^�C�g���w�i
		TEXTYPE_TITLE_LOGO,			// �^�C�g�����S
		TEXTYPE_TITLE_ENTER,		// �^�C�g���G���^�[�T�C��
		TEXTYPE_RESULT_BG,			// ���U���g�w�i
		TEXTYPE_RESULT_LOGO,		// ���U���g���S
		TEXTYPE_RANKING_BG,			// �����L���O�w�i
		TEXTYPE_RANKING_LOGO,		// �����L���O���S
		TEXTYPE_RANKING_RANK,		// �����L���O����
		TEXTYPE_RANKING_SCORELOGO,	// �����L���O��ʂ̃��U���g�X�R�A���S
		TEXTYPE_LIFE,				// ���C�t
		TEXTYPE_ITEM_0,				// �A�C�e��0(�g�`)
		TEXTYPE_ITEM_1,				// �A�C�e��1(�~�T�C��)
		TEXTYPE_ITEM_2,				// �A�C�e��2(�t�g�`)
		TEXTYPE_ITEM_3,				// �A�C�e��3(��)
		TEXTYPE_NUMBER,				// �i���o�[
		TEXTYPE_EXPLOSION,			// ����
		TEXTYPE_EFFECT,				// �G�t�F�N�g
		TEXTYPE_LINE,				// �{�[�_�[���C��
		TEXTYPE_PAUSE_BASE,			// �|�[�Y��ʂ̃x�[�X
		TEXTYPE_PAUSE_CONTINUE,		// �|�[�Y�R���e�j���[
		TEXTYPE_PAUSE_RETRY,		// �|�[�Y���g���C
		TEXTYPE_PAUSE_QUIT,			// �|�[�Y�I��
		TEXTYPE_TUTORIAL_0,			// �`���[�g���A��0
		TEXTYPE_TUTORIAL_1,			// �`���[�g���A��1
		TEXTYPE_TUTORIAL_2,			// �`���[�g���A��2
		TEXTYPE_MESSAGE_WINDOW,		// ���b�Z�[�W�E�B���h�E
		TEXTYPE_MESSAGE_TEXT,		// ���b�Z�[�W�e�L�X�g
		TEXTYPE_CAUTION,			// �x�����
		TEXTYPE_WINDOWEFFECT,		// ��ʃG�t�F�N�g
		TEXTYPE_EASY,				// easy
		TEXTYPE_NORMAL,				// normal
		TEXTYPE_HARD,				// hard
		TEXTYPE_METEOR,				// 覐�
		TEXTYPE_PANEL,				// �\�[���[�p�l��
		TEXTYPE_MAX					// �ő吔
	}TEXTYPE;

	CTexture();
	~CTexture();

	static HRESULT LoadAll(void);
	static void UnloadAll(void);
	static LPDIRECT3DTEXTURE9 BindTexture(TEXTYPE texType) { return m_pTexture[texType]; }
	
	// 3D���f���ւ̃e�N�X�`�����蓖��
	static LPDIRECT3DTEXTURE9 BindTex3D(char *pTexFilename);

private:
	static char *m_pFileName[TEXTYPE_MAX];				// �ǂݍ��ރt�@�C�����p�X
	static LPDIRECT3DTEXTURE9 m_pTexture[TEXTYPE_MAX];	// �e�N�X�`���ւ̃|�C���^
};

#endif
