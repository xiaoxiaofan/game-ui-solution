#pragma once

#include "TDUISystem.h"
#include "CEGUI.h"
#include "RendererModules/Ogre/CEGUIOgreRenderer.h"

class CUISystem : public tUISystem
{
public:
	CUISystem(VOID);
	virtual ~CUISystem(VOID);
	static CUISystem* getMe(VOID){ return s_pMe};

	virtual VOID Initial(VOID*);
	virtual VOID Release(VOID);
	virtual VOID Tick(VOID);

public:
	// 窗口大小发生改变
	virtual VOID			OnSizeChange(UINT message, WPARAM wParam, LPARAM lParam);


protected:
	Ogre::Root*               m_pOgreRoot; 

	CEGUI::OgreRenderer*      m_pOgreRender;
	CEGUI::System*            m_pCEGUISystem;

	static CUISystem*         s_pMe;
private:
};





