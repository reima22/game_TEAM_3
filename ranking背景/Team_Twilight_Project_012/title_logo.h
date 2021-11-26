//=============================================================================
//
// �^�C�g�����S�`�揈�� [title_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

// �}�N����`
#define T_LOGO_POS		(D3DXVECTOR3(300.0f, -1000.0f, 0.0f))			// ���S�̊J�n�ʒu
#define T_LOGO_SIZE		(D3DXVECTOR2(900.0f / 2.0f, 450.0f / 2.0f))		// ���S�̃T�C�Y
#define T_LOGO_SETPOS	(D3DXVECTOR3(630.0f, 230.0f, 0.0f))				// ���S�̍ŏI�n�_
//#define COLOR_CNT		(50)

//#define POS_START_Y		(550.0f)								//	START,Y���̈ʒu
//#define MOVE_START_Y	(-8.0f)							//	START,Y���̈ړ��l
//#define POS_TITLE_Y				(230.0f)							//	�^�C�g���@	Y���̈ʒu
//#define POS_TITLE_X				(630.0f)							//	�^�C�g���@	X���̈ʒu

#define MOVE_TITLE_Y			(0.0f)								//	�^�C�g���@	Y���̈ړ��l
#define MOVE_TITLE_X			(0.014f)
#define MOVE_SPEED				(15.0f)								//	���x�l
#define GRAVITY					(0.4f)	

// �O���錾
//class CPolygon;

//==============================================================================
// �^�C�g�����S�N���X
//==============================================================================
class CTitleLogo : public CScene2D
{
public:
	CTitleLogo(int nPriority = PRIORITY_UI);
	~CTitleLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleLogo *Create(D3DXVECTOR3 pos);

	static bool GetLogoState(void) { return m_bLogoMoveEnd; }

private:
	CScene2D *m_pScene2D;		// 2D�|���S���N���X�|�C���^

	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXCOLOR m_col;			// �F

	int m_nJumpCnt;				//	�W�����v�J�E���g
	float m_fSpead;				// ���x

	static bool m_bLogoMoveEnd;	// ���S�ړ��̏I��
};
#endif
