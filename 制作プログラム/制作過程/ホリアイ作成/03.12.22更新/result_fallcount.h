//=============================================================================
//
// ���U���g�̗����J�E���g�`�揈�� [result_fallcount.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_FALLCOUNT_H_
#define _RESULT_FALLCOUNT_H_

#include "main.h"
#include "scene.h"
#include "result.h"
#include "ranking.h"
#include "score.h"

// �}�N����`
#define RESULT_FC_POS	(D3DXVECTOR3(250.0f, 550.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RESULT_FC_SIZE	(D3DXVECTOR2(20.0f, 30.0f))			// �ꌅ���̃T�C�Y

// �O���錾
class CFallCount;	// �����J�E���g�N���X

//==============================================================================
// ���U���g�̗����J�E���g�`��N���X
//==============================================================================
class CResultFallCount : public CResult
{
public:
	CResultFallCount(int nPriority = PRIORITY_UI);
	~CResultFallCount();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultFallCount *Create();

private:
	CFallCount *m_pFallCount;	// �����J�E���g�N���X
	int m_nFall;				// ���ʗ����J�E���g
};
#endif