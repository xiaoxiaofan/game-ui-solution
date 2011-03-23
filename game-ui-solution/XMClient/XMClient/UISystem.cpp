#include "UISystem.h"




CUISystem* CUISystem::s_pMe = NULL;

CUISystem::CUISystem( VOID )
{
	s_pMe = this;
}

CUISystem::~CUISystem( VOID )
{

}



VOID CUISystem::Initial( VOID* )
{
	m_pOgreRender = Ogre::Root
	m_pOgreRender = new CEGUI::OgreRenderer();
}

VOID CUISystem::OnSizeChange( UINT message, WPARAM wParam, LPARAM lParam )
{

}
