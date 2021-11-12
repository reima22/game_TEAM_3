//=============================================================================
//
// �X�R�A�`�揈�� [score.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

// �}�N����`
#define NUM_MAX	(8)	// �ő包��

// �O���錾
class CNumber;

//==============================================================================
// �X�R�A�N���X
//==============================================================================
class CScore : public CScene2D
{
public:
	CScore(int nPriority = PRIORITY_UI);
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	
	static void AddScore(int nValue);

	void SetScore(int nScore);
	static int GetScore(void) { return m_nScore; }

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	CNumber *GetNumber(int nNumber) { return m_apNumber[nNumber]; }

	static void SetResultScore(int nScore) { m_nResultScore = nScore; }
	static int GetResultScore(void) { return m_nResultScore; }

private:
	CNumber *m_apNumber[NUM_MAX];	// �i���o�[�N���X�|�C���^
	static int m_nScore;			// �X�R�A���l
	static float m_fSizeX;			// �T�C�YX��
	static float m_fSizeY;			// �T�C�YY��
	static int m_nResultScore;		// ���ʃX�R�A
};

#endif
