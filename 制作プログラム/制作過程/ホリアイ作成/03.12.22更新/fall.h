//=============================================================================
//
// ������UI�`�揈�� [fall.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _FALL_H_
#define _FALL_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define FALL_UIBASE_POS		(D3DXVECTOR3(1130.0f, 50.0f, 0.0f))	// UI�x�[�X�̈ʒu
#define FALL_UIBASE_SIZE	(D3DXVECTOR2(150.0f, 50.0f))		// UI�x�[�X�̃T�C�Y

#define FALL_LOGO_POS		(D3DXVECTOR3(1070.0f, 50.0f, 0.0f))	// ���S�̈ʒu
#define FALL_LOGO_SIZE		(D3DXVECTOR2(60.0f, 40.0f))			// ���S�̃T�C�Y

// �O���錾
class CFallCount;		// �������J�E���g�N���X
class CFallLogo;		// ���������S�N���X

//==============================================================================
// ������UI�N���X
//==============================================================================
class CFall : public CScene
{
public:
	CFall(int nPriority = PRIORITY_UI);
	~CFall();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFall *Create(void);

	CFallCount *GetFallCount(void) { return m_pFallCount; }

private:
	CFallCount *m_pFallCount;	// �������J�E���g�N���X�|�C���^
	CFallLogo *m_pFallLogo;		// ���������S�N���X�|�C���^
};

#endif