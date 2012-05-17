#ifndef RENDERDEMO_HPP
#define RENDERDEMO_HPP

#include <vector>

class RenderSubDemo;
class Cube;

class RenderDemo
{
public:
	RenderDemo();
	~RenderDemo();
	//
	void Enable();
	void Disable();
	//
	bool ShowNextSubDemo();
	bool ShowPreviousSubDemo();
	//
private:
	unsigned short CurSubDemo;
	std::vector<RenderSubDemo*> SubDemos;
	//
	Cube* m_pCube;
};

#endif	//RENDERDEMO_HPP