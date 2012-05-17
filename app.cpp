#include "app.h"
#include "Timer.h"

#include "WindowManager.h"
#include "RenderLogic.h"
/*
// Hacky test objects
Terrain g_terrain;
MeshBasic g_teapot;
MeshX g_dwarf;
Triangle g_triangle;
*/
//Line g_line(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,0.0f));
//Cube g_cube;

cApp::cApp(HINSTANCE a_hInst) 
:	res_manager(ResMgr::GetInstance())
,	window_manager(WndwMgr::GetInstance(a_hInst))
,	render_logic(RenderLogic::GetInstance())
,	m_Timer(new Timer())
,	m_CountDown(0.0f)
,	m_LastT(0.0f)
,	m_AutoRunThrough(true)
{
	//create renderer
	m_Renderer = new Renderer(DXMgr::GetInstance().GetDevice());
	//tell res manager about renderer
	res_manager.Init(m_Renderer);

	//render logic handles moving between different demos and subdemos
	render_logic.Init(m_Renderer);
	render_logic.ShowDemo(1);
}

// this is the function used to update everything, using a_dt forces the update rate to 0.3
bool cApp::update(float a_dt)
{
	float dt = m_Timer->GetTime() - m_LastT;
	m_LastT = m_Timer->GetTime();
	if(m_AutoRunThrough)
	{
		if(m_CountDown > 3)
		{
			render_logic.ShowNextSubDemo();
			m_CountDown = 0.0f;
		}
		else
		{
			m_CountDown += 0;//dt;
		}
	}
	return m_Renderer->Render(dt);
}

void cApp::cleanUp()
{
	render_logic.CleanUp();
	window_manager.cleanUp();
}
