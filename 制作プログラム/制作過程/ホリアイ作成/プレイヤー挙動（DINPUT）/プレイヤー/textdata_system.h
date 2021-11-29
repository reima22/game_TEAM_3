//=============================================================================
//
// �e�L�X�g�f�[�^�i�V�X�e���j�Ǘ� [textdata_system.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_SYSTEM_H_
#define _TEXTDATA_SYSTEM_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��isystem�j�N���X
//==============================================================================
class CTextDataSystem : public CTextData
{
public:
	// �V�X�e���f�[�^�̎��
	typedef enum
	{
		SYSTEMDATA_DEFEAT_EASY = 0,			// ���j�K�萔�C�[�W�[
		SYSTEMDATA_DEFEAT_NORMAL,			// ���j�K�萔�m�[�}��
		SYSTEMDATA_DEFEAT_HARD,				// ���j�K�萔�n�[�h
		SYSTEMDATA_INVASION_EASY,			// �N���K�萔�C�[�W�[
		SYSTEMDATA_INVASION_NORMAL,			// �N���K�萔�m�[�}��
		SYSTEMDATA_INVASION_HARD,			// �N���K�萔�n�[�h
		SYSTEMDATA_HEALITEM_CNT_EASY,		// �񕜃A�C�e���o���Ԋu���j���C�[�W�[
		SYSTEMDATA_HEALITEM_CNT_NORMAL,		// �񕜃A�C�e���o���Ԋu���j���m�[�}��
		SYSTEMDATA_HEALITEM_CNT_HARD,		// �񕜃A�C�e���o���Ԋu���j���n�[�h
		SYSTEMDATA_MAX
	}SYSTEM;

	CTextDataSystem();
	~CTextDataSystem();

	static void LoadData(void);

	static int SetData(int nDataNum) { return m_aSystemData[nDataNum]; }

private:
	static int m_aSystemData[SYSTEMDATA_MAX];
};

#endif