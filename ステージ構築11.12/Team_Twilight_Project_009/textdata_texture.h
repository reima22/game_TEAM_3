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

	int GetIdxNumber(void) { return m_nIdxNumber; }
	int GetIdxShadow(void) { return m_nIdxShadow; }
	int GetIdxEffect(void) { return m_nIdxEffect; }

private:
	int m_nNumTexture;			// �e�N�X�`���̐�
	char **m_pFileTextureName;	// �t�@�C�������i�[����|�C���^
	int *m_pIdx;				// �e�N�X�`���̃C���f�b�N�X
	int m_nIdxNumber;			// ���l�e�N�X�`���̃C���f�b�N�X
	int m_nIdxShadow;			// �e�e�N�X�`���̃C���f�b�N�X
	int m_nIdxEffect;			// �G�t�F�N�g�̃C���f�b�N�X
};
#endif
