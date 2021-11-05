//=============================================================================
//
// チュートリアルモード処理 [tutorial.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"

// 前方宣言
class CTutorialPage;	// チュートリアルページポインタ

//==============================================================================
// チュートリアルモードクラス
//==============================================================================
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorial *Create(void);

private:
	static CTutorialPage *m_pTutorialPage;	// チュートリアルページポインタ
};

#endif
