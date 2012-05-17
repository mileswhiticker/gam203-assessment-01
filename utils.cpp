#include <iostream>

#include "RenderLogic.h"
#include "utils.h"

//#include "Line.h"

namespace utils
{
	//short maxSubDemoNum = 0;//maxSubDemoNum = MathLogic::GetInstance().m_DemoDrawables[1].size();
	void keypress_q()
	{
		//MathLogic::GetInstance().debugLine->SetAdd(D3DXVECTOR3(0.0f,-0.1f,0.0f));
		//((Line*)MathLogic::GetInstance().m_DemoDrawables[1][0])->SetAdd(D3DXVECTOR3(0.1f,0.0f,0.0f));
	}
	void keypress_a()
	{
		//MathLogic::GetInstance().debugLine->SetAdd(D3DXVECTOR3(0.0f,-0.1f,0.0f));
		//((Line*)MathLogic::GetInstance().m_DemoDrawables[1][0])->SetAdd(D3DXVECTOR3(-0.1f,0.0f,0.0f));
	}
	void keypress_w()
	{
		//MathLogic::GetInstance().debugLine->SetAdd(D3DXVECTOR3(0.0f,-0.1f,0.0f));
		//((Line*)MathLogic::GetInstance().m_DemoDrawables[1][0])->SetAdd(D3DXVECTOR3(0.0f,0.1f,0.0f));
	}
	void keypress_s()
	{
		//MathLogic::GetInstance().debugLine->SetAdd(D3DXVECTOR3(0.0f,-0.1f,0.0f));
		//((Line*)MathLogic::GetInstance().m_DemoDrawables[1][0])->SetAdd(D3DXVECTOR3(0.0f,-0.1f,0.0f));
	}
	void keypress_e()
	{
		//MathLogic::GetInstance().debugLine->SetAdd(D3DXVECTOR3(0.0f,-0.1f,0.0f));
		//((Line*)MathLogic::GetInstance().m_DemoDrawables[1][0])->SetAdd(D3DXVECTOR3(0.0f,0.0f,0.1f));
	}
	void keypress_d()
	{
		//MathLogic::GetInstance().debugLine->SetAdd(D3DXVECTOR3(0.0f,-0.1f,0.0f));
		//((Line*)MathLogic::GetInstance().m_DemoDrawables[1][0])->SetAdd(D3DXVECTOR3(0.0f,0.0f,-0.1f));
	}
	void keypress_r()
	{
		//MathLogic::GetInstance().RandomisePrimaryMatrix();
	}
	void keypress_t()
	{
		//MathLogic::GetInstance().RandomiseSecondaryMatrix();
	}
	//
	void keypress_1()
	{
		//app->LoadDemo(1);
	}
	void keypress_2()
	{
		//app->LoadDemo(2);
	}
	//
	void keypress_shift()
	{
		//MathLogic::GetInstance().ToggleDebugLine();
		/*
		std::cout << "Display rotation toggled." << std::endl;
		std::vector<Drawable*>* subDemo = &MathLogic::GetInstance().m_DemoDrawables[1];
		for(unsigned short n=0;n<subDemo->size();n++)
		{
			((Line*)subDemo->at(n))->ToggleRotating();
		}
		*/
	}
	void keypress_ctrl()
	{
		//
	};
	void keypress_space()
	{
		RenderLogic::GetInstance().ShowNextSubDemo();
	};
	void keypress_up()
	{
		//
	};
	void keypress_down()
	{
		//
	};
	void keypress_left()
	{
		//
	};
	void keypress_right()
	{
		//
	};
	void keypress_tab()
	{
		//
	};
}
