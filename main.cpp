#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>
#include <vector>
#include "Vec2.h"
#include "template.h"
class Example : public olc::PixelGameEngine
{
public:
	stack<int> s;
	std::vector<Vec2>buttonCoordinates;
	Example()
	{
		sAppName = "Tema Pregatire //// Stack Illustrator";
	}

public:
	bool OnUserCreate() override
	{ /// AICI E HARD CODAT CA SI BUTOANELE IS PUSE HARDCODAT 
		buttonCoordinates.push_back({});
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		 Draw();

		 DrawString(10, 690, "Sound ON ", olc::VERY_DARK_CYAN);

		 return true;
	}
	const void Draw() ///GUI AREA CONFIGURATION
	{
		
		DrawString(940, 10, "Stack Illustrator", olc::BLUE, 1); /// App name in the corner
		DrawString(910, 640, "Stack Specifications", olc::WHITE, 1);
		DrawString(910, 660, "Length", olc::WHITE, 1);
		DrawString(910, 680, "Capacity", olc::WHITE, 1);
		DrawLine(100, 0, 100, 700, olc::DARK_RED);
		DrawString(10, 10, "Stack ", olc::DARK_RED);
		DrawString(20, 20, "Functions ", olc::DARK_RED);
		DrawString(10,50,"Construct",olc::WHITE);
		DrawString(10,100,"Top", olc::WHITE);
		DrawString(10,150,"Pop", olc::WHITE);
		DrawString(10,200,"Push", olc::WHITE);
		DrawString(10,250,"Insert", olc::WHITE);
		DrawString(10,300,"OverWrite", olc::WHITE);
		DrawString(10,350,"Find", olc::WHITE);
	}
    

};


int main()//de adaugat blood sugar sex magik si give it away rhcp
{
	Example demo;
	if (demo.Construct(1080, 700, 1, 1))
		
		demo.Start();
	return 0;
}