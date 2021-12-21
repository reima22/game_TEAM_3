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
	CTexture();
	~CTexture();

	HRESULT LoadAll(void);			// �S�ǂݍ���
	void UnloadAll(void);			// �S�j��
	static CTexture *Create(void);	// ��������

	// �e�N�X�`���̊��蓖��(������)
	LPDIRECT3DTEXTURE9 GetAddress(char *pTypeCheck);

	// �e�N�X�`���̊��蓖��(���l)
	LPDIRECT3DTEXTURE9 GetAddressNum(int nTexNum);

	// 3D���f���ւ̃e�N�X�`�����蓖��
	LPDIRECT3DTEXTURE9 GetAddress3D(char *pTexFilename);

	// �e�N�X�`���e�L�X�g�̃f�[�^�擾
	CTextDataTexture *GetData(void) { return m_pDataTexture; }

private:
	CTextDataTexture *m_pDataTexture;	// �e�N�X�`���f�[�^�|�C���^
	char **m_pFileName;					// �ۊǗp�|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;		// �|�C���^�z��i�[�A�h���X
	int m_nTexMax;						// �e�N�X�`���̍ő吔
};
#endif
