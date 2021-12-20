#pragma once
//=============================================================================
//
// �e�L�X�g�f�[�^�i�����L���O�I���j�Ǘ� [textdata_rankingselect.h]
// Author : Tatasuki Matsuda
//
//============================================================================= 
#ifndef _TEXTDATA_RANINGSELECT_H_
#define _TEXTDATA_RANINGSELECT_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��i�����L���O�I���j�N���X
//==============================================================================
class CTextDataRankingSelect : public CTextData
{
public:
	// �I���|���S���ꗗ
	typedef enum
	{
		RANKINGPOLY_RETRY = 0,	// ���g���C
		RANKINGPOLY_STAGE,		// �X�e�[�W
		RANKINGPOLY_QUIT,		// �I��	
		RANKINGPOLY_MAX
	}RANKINGPOLY;

	CTextDataRankingSelect();
	~CTextDataRankingSelect();

	void LoadData(void);
	void Unload(void);

	static CTextDataRankingSelect *Create(void);

	int GetTexIdx(int nIdx) { return m_aIdxTex[nIdx]; }			// �e�N�X�`���C���f�b�N�X�擾
	D3DXVECTOR3 GetPosition(int nIdx) { return m_aPos[nIdx]; }	// �ʒu�̎擾
	D3DXVECTOR2 GetSize(int nIdx) { return m_aSize[nIdx]; }		// �T�C�Y�̎擾

private:
	D3DXVECTOR3 m_aPos[RANKINGPOLY_MAX];	// �e�|���S���̔z�u
	D3DXVECTOR2 m_aSize[RANKINGPOLY_MAX];	// �e�|���S���̃T�C�Y
	int m_aIdxTex[RANKINGPOLY_MAX];			// �e�N�X�`���̃C���f�b�N�X
};
#endif

