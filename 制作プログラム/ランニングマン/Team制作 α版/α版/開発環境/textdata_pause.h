//=============================================================================
//
// �e�L�X�g�f�[�^�i�|�[�Y�j�Ǘ� [textdata_pause.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_PAUSE_H_
#define _TEXTDATA_PAUSE_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��i�|�[�Y�j�N���X
//==============================================================================
class CTextDataPause : public CTextData
{
public:
	// �|�[�Y�|���S���ꗗ
	typedef enum
	{
		PAUSEPOLY_BASE = 0,	// �|�[�Y�E�B���h�E
		PAUSEPOLY_CONTINUE,	// �R���e�j���[
		PAUSEPOLY_RETRY,	// ���g���C
		PAUSEPOLY_QUIT,		// �I��
		PAUSEPOLY_MAX
	}PAUSEPOLY;

	CTextDataPause();
	~CTextDataPause();

	void LoadData(void);
	void Unload(void);

	static CTextDataPause *Create(void);

	int GetTexIdx(int nIdx) { return m_aIdxTex[nIdx]; }			// �e�N�X�`���C���f�b�N�X�擾
	D3DXVECTOR3 GetPosition(int nIdx) { return m_aPos[nIdx]; }	// �ʒu�̎擾
	D3DXVECTOR2 GetSize(int nIdx) { return m_aSize[nIdx]; }		// �T�C�Y�̎擾

private:
	D3DXVECTOR3 m_aPos[PAUSEPOLY_MAX];	// �e�|���S���̔z�u
	D3DXVECTOR2 m_aSize[PAUSEPOLY_MAX];	// �e�|���S���̃T�C�Y
	int m_aIdxTex[PAUSEPOLY_MAX];		// �e�N�X�`���̃C���f�b�N�X
};
#endif
