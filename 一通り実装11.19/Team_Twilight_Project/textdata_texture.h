//=============================================================================
//
// �e�L�X�g�f�[�^�i�e�N�X�`���j�Ǘ� [textdata_texture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_TEXTURE_H_
#define _TEXTDATA_TEXTURE_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��i�e�N�X�`���j�N���X
//==============================================================================
class CTextDataTexture : public CTextData
{
public:
	CTextDataTexture();
	~CTextDataTexture();

	void LoadData(void);
	void Unload(void);

	static CTextDataTexture *Create(void);

	int GetNumTexture(void) { return m_nNumTexture; }
	char *GetFileName(int nIdx) { return m_pFileTextureName[nIdx]; }

	char *GetTypeCheck(int nIdx){ return m_pTypeCheck[nIdx]; }

private:
	int m_nNumTexture;			// �e�N�X�`���̐�
	char **m_pFileTextureName;	// �t�@�C�������i�[����|�C���^
	int *m_pIdx;				// �e�N�X�`���̃C���f�b�N�X

	char **m_pTypeCheck;		// ��ގ��ʗp������
};
#endif