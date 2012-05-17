#ifndef RENDERSUBDEMO_HPP
#define RENDERSUBDEMO_HPP

#include "Renderer.h"
#include <vector>
#include <string>

class Cube;
typedef std::pair<std::string, RECT*> Title;

class RenderSubDemo
{
public:
	RenderSubDemo(Cube* a_pCube);
	~RenderSubDemo();
	void AddTitle(Title* a_pTitle);
	void SetMaterial(D3DMATERIAL9 a_Mat);
	void SetLight(Light* a_pLight);
	//
	void Update(float Dt);
	//
	void Enable();
	void Disable();
	//
private:
	std::vector<Title*> Titles;
	Light* m_pLight;
	Cube* m_pCube;
	//
};

#endif	//RENDERSUBDEMO_HPP