//=============================================================================
//
// �e�N�X�`���Ǘ� [texture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

class CTextDataTexture;

//==============================================================================
// �e�N�X�`���Ǘ��N���X
//==============================================================================
class CTexture
{
public:
	// �e�N�X�`���̎��
	//typedef enum
	//{
	//	TEXTYPE_NONE = 0,			// �e�N�X�`������
	//	TEXTYPE_PLAYER_0,			// �v���C���[��0
	//	TEXTYPE_PLAYER_1,			// �v���C���[��1
	//	TEXTURE_OBJECT,				// �I�u�W�F�N�g
	//	TEXTYPE_TITLE_BG,			// �^�C�g���w�i
	//	TEXTYPE_TITLE_LOGO,			// �^�C�g�����S
	//	TEXTYPE_TITLE_ENTER,		// �^�C�g���G���^�[�T�C��
	//	TEXTYPE_RESULT_BG,			// ���U���g�w�i
	//	TEXTYPE_RESULT_LOGO,		// ���U���g���S
	//	TEXTYPE_RANKING_BG,			// �����L���O�w�i
	//	TEXTYPE_RANKING_LOGO,		// �����L���O���S
	//	TEXTYPE_RANKING_RANK,		// �����L���O����
	//	TEXTYPE_RANKING_SCORELOGO,	// �����L���O��ʂ̃��U���g�X�R�A���S
	//	TEXTYPE_NUMBER,				// �i���o�[
	//	TEXTYPE_EXPLOSION,			// ����
	//	TEXTYPE_EFFECT,				// �G�t�F�N�g
	//	TEXTYPE_PAUSE_BASE,			// �|�[�Y��ʂ̃x�[�X
	//	TEXTYPE_PAUSE_CONTINUE,		// �|�[�Y�R���e�j���[
	//	TEXTYPE_PAUSE_RETRY,		// �|�[�Y���g���C
	//	TEXTYPE_PAUSE_QUIT,			// �|�[�Y�I��
	//	TEXTYPE_TUTORIAL_0,			// �`���[�g���A��0
	//	TEXTYPE_TUTORIAL_1,			// �`���[�g���A��1
	//	TEXTYPE_TUTORIAL_2,			// �`���[�g���A��2
	//	TEXTYPE_WINDOWEFFECT,		// ��ʃG�t�F�N�g
	//	TEXTYPE_EASY,				// easy
	//	TEXTYPE_NORMAL,				// normal
	//	TEXTYPE_HARD,				// hard
	//	TEXTYPE_METEOR,				// 覐�
	//	TEXTYPE_PANEL,				// �\�[���[�p�l��
	//	TEXTYPE_MAX					// �ő吔
	//}TEXTYPE;

	CTexture();
	~CTexture();

	HRESULT LoadAll(void);
	void UnloadAll(void);

	static CTexture *Create(void);

	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return *(LPDIRECT3DTEXTURE9*)&m_pTexture[nIdx]; }

	// 3D���f���ւ̃e�N�X�`�����蓖��
	LPDIRECT3DTEXTURE9 GetAddress3D(char *pTexFilename);

	CTextDataTexture *GetData(void) { return m_pDataTexture; }

private:
	CTextDataTexture *m_pDataTexture;
	char **m_pFileName;				// �ۊǗp�|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;	// �|�C���^�z��i�[�A�h���X
	int m_nTexMax;					// �e�N�X�`���̍ő吔
};

#endif
