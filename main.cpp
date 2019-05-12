#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>
#include "template.h"
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Tema Pregatire";
	}

public:
	bool OnUserCreate() override
	{
	    
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		 for (size_t i = 0; i < 200; i++)
		 {
			 DrawTriangle(10, 10, 20, 20, 100, 100, olc::RED);
		 }
		 std::string s{ "Text" };
		 
		// DrawRect(15, 15, 128, 24);
		 DrawString(20, 20, "PlaySample",olc::WHITE,1);
		 return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(1080, 700, 1, 1))
		
		demo.Start();


	return 0;
}