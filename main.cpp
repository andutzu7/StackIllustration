#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>
#include <vector>
#include "Vec2.h"
#include "template.h"

std::vector<std::string> vec;
std::vector<std::string> utilityNumbers;
bool overWrite = false;
std::string str = "";
enum class State
{
	Pending,
	Reading
};

State state = State::Pending;

class Example : public olc::PixelGameEngine
{
private:
	const void ClearScreen()//aparent graphic engineul asta n are clear screen dupa fiecare update...
	{
		FillRect(0, 0, 1080, 700, olc::BLACK); //valori hardcodate,determinate din main
	}
public:///fac un enum classpt switch ca sa vad ce functie ilustrez
enum class FunctionsToShow    
{
		Sound,
		Top,
		Construct,
		Pop,
		Push,
		Insert,
		OverWrite,
		Find,
		Nothing
   };
	//stack<std::string> s;
	FunctionsToShow nextAction = FunctionsToShow::Nothing;
	std::vector<Vec2>buttonCoordinates;
	
	Example()
	{
		sAppName = "Tema Pregatire //// Stack Illustrator";
	}
	void DrawNumbers()
	{
		std::string output = "";
		for (auto i : vec)
		{
			output += i;
			output += " ";
		}
		if (str != "")
		{
			output += str;
		}
		DrawString(105, 600, output);
	}

public:
	void KeyboardInput()
	{
		bool digitHasBeenPressed = false;
		char c;
		if (GetKey(olc::K0).bPressed)
		{
			digitHasBeenPressed = true;
			c = '0';
		}
		else if (GetKey(olc::K1).bPressed)
		{
			digitHasBeenPressed = true; c = '1';
		}
		else if (GetKey(olc::K2).bPressed)
		{
			digitHasBeenPressed = true; c = '2';
		}
		else if (GetKey(olc::K3).bPressed)
		{
			digitHasBeenPressed = true; c = '3';
		}
		else if (GetKey(olc::K4).bPressed)
		{
			digitHasBeenPressed = true; c = '4';
		}
		else if (GetKey(olc::K5).bPressed)
		{
			digitHasBeenPressed = true; c = '5';
		}
		else if (GetKey(olc::K6).bPressed)
		{
			digitHasBeenPressed = true; c = '6';
		}
		else if (GetKey(olc::K7).bPressed)
		{
			digitHasBeenPressed = true; c = '7';
		}
		else if (GetKey(olc::K8).bPressed)
		{
			digitHasBeenPressed = true; c = '8';
		}
		else if (GetKey(olc::K9).bPressed)
		{
			digitHasBeenPressed = true; c = '9';
		}

		if (digitHasBeenPressed)
		{
			str += c;
			state = State::Reading;
		}
		else if (GetKey(olc::SPACE).bPressed)
		{
			if (overWrite)
			{
				utilityNumbers.push_back(str);
			}
			else
			{
				vec.push_back(str);
			}
			str = "";
		}
		else if (GetKey(olc::ENTER).bPressed)
		{
			if (str != "")
			{

		
				if (overWrite)
				{
					utilityNumbers.push_back(str);
				}
				else
				{
					vec.push_back(str);
				}
				str = "";
			}
			state = State::Pending;
			nextAction = FunctionsToShow::Nothing;
			
			//vec.clear();
		}
	}
	void DrawStack(const std::vector<std::string> stack)
	{
		DrawString(150, 150, "Your Stack ", olc::RED, 2);
		const int unit= 40;
		
		int lastTime=150;
		for (int i = 0; i < stack.size(); i++)
		{
			DrawString(lastTime, 250, stack[i], olc::WHITE, 4);
			lastTime += stack[i].size()*unit;
			lastTime +=  unit;
		}
	}
	const int GetUnitNumber(const std::vector<std::string> stack,int index)
	{
		const int unit = 40;

		int lastTime = 150;
		for (int i = 0; i < stack.size(); i++)
		{
			if (index > 0)
				index--;
			else
				return lastTime;
			lastTime += stack[i].size()*unit;
			lastTime += unit;
		}
	}
	bool OnUserCreate() override
	{ /// AICI E HARD CODAT CA SI BUTOANELE IS PUSE HARDCODAT 
		///ADAUGAM IN VECTOR COORDONATELE BUUTOANELOR
		buttonCoordinates.push_back({10,690});///sound button
		buttonCoordinates.push_back({10,100});///TOP
		buttonCoordinates.push_back({10,50});///CONSTRUCT
		buttonCoordinates.push_back({10,150});///POP
		buttonCoordinates.push_back({10,200});///PUSH
		buttonCoordinates.push_back({10,250});///INSERT
		buttonCoordinates.push_back({10,300});///OVERWRITE
		buttonCoordinates.push_back({10,350});///FIND

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		ClearScreen();
		
		auto Contains = [](const Vec2 &Point, const Vec2& mousePos)->bool///lambda ca sa calculam daca mouseul se afla in proximitatea unui buton. Presupunem L al oricarui buton 30 si l 20
		{
			return (mousePos.x >= Point.x && mousePos.x <= (Point.x + 60) && mousePos.y >= Point.y && mousePos.y <= (Point.y + 30));
		};
		for (size_t i = 0; i < buttonCoordinates.size(); i++) ///BRUTE FORCE.... NU SUNT MANDRU DELOC...
		{


			if (GetMouse(0).bPressed)//GetMouse ia ca parametru 0 daca verificam click stanga 
					///in caz ca am apasat mouseul verificam in ce zona ne aflam
				if (Contains(buttonCoordinates[i], Vec2(GetMouseX(), GetMouseY())))///testam fiecare buton sa vedem daca am dat click pe el
				{
					if (i == 0)
						nextAction = FunctionsToShow::Sound;///punem actiunea corespunzatoare din enumclass
					if (i == 1)
						nextAction = FunctionsToShow::Top;///punem actiunea corespunzatoare din enumclass
					if (i == 2)
					{
						nextAction = FunctionsToShow::Construct;///punem actiunea corespunzatoare din enumclass
						vec.clear();
					}
					if (i == 3)
						nextAction = FunctionsToShow::Pop;///punem actiunea corespunzatoare din enumclass
					if (i == 4)
						nextAction = FunctionsToShow::Push;///punem actiunea corespunzatoare din enumclass
					if (i == 5)
						nextAction = FunctionsToShow::Insert;///punem actiunea corespunzatoare din enumclass
					if (i == 6)
						nextAction = FunctionsToShow::OverWrite;///punem actiunea corespunzatoare din enumclass
					if (i == 7)
						nextAction = FunctionsToShow::Find;///punem actiunea corespunzatoare din enumclass
					break;//putem sa apasam doar cate un buton deodata

				}
		}
		switch (nextAction)
		{
		case FunctionsToShow::Sound:  ///o sa adaug later
			DrawString(110, 650, "Am aflat ca , din pacate, frameworkul nu permite melodii intregi , asa ca renunt la sunet cu totul. ", olc::YELLOW);
			break;
		case FunctionsToShow::Pop:
		{
			if(vec.size()>0)
			vec.erase(vec.end()-1);
			nextAction = FunctionsToShow::Nothing;
			ClearScreen();
		}
			break;
		case FunctionsToShow::Top:
		{
			if(!(vec.empty()))
			DrawLine(GetUnitNumber(vec,vec.size()-1), 285, GetUnitNumber(vec, vec.size() - 1)+25, 285, olc::RED);
		}
			break;
		case FunctionsToShow::Construct:///sa apelez clear screen dupa?

		{
			DrawString(100, 650," Introduceti numerele.\n Dupa ce tastati un numar apasati tasta SPACE. \n Pentru a incheia apasati tasta ENTER", olc::WHITE);
			KeyboardInput();
		    DrawNumbers();
		}
		break;
		case FunctionsToShow::Insert:
		{
			DrawString(100, 650, "Function under construction, too lazy... ", olc::RED);
		}
			break;
		case FunctionsToShow::Push:
		{
			DrawString(100, 650, " Introduceti numarul dorit.\n\n Pentru a incheia apasati tasta ENTER", olc::WHITE);
			KeyboardInput();
			DrawNumbers();
			
		}
			break;
		case FunctionsToShow::OverWrite:
		{
			DrawString(100, 650, "Function under construction, too lazy... ", olc::YELLOW);

		}
			break;
		case FunctionsToShow::Find:
		{
			DrawString(100, 650, "Function under construction, too lazy... ", olc::BLUE);

		}
			break;
		default: //cand e nothing
			break;
		}
		Draw();
	    return true;
	}
	const void Draw() ///GUI AREA CONFIGURATION
	{
		DrawStack(vec);
		DrawString(940, 10, "Stack Illustrator", olc::BLUE, 1); /// App name in the corner
		DrawString(910, 640, "Stack Specifications", olc::WHITE, 1);
		DrawString(910, 660, "Length", olc::WHITE, 1);
		DrawLine(100, 0, 100, 700, olc::DARK_RED);
		DrawString(10, 10, "Stack ", olc::DARK_RED);
		DrawString(20, 20, "Functions ", olc::DARK_RED);
		DrawString(10, 50, "Construct", olc::WHITE);
		DrawString(10, 100, "Top", olc::WHITE);
		DrawString(10, 150, "Pop", olc::WHITE);
		DrawString(10, 200, "Push", olc::WHITE);
		DrawString(10, 250, "Insert", olc::WHITE);
		DrawString(10, 300, "OverWrite", olc::WHITE);
		DrawString(10, 350, "Find", olc::WHITE);
		DrawString(10, 690, "Sound ", olc::VERY_DARK_CYAN);
		std::string length = std::to_string(vec.size());
		DrawString(980, 660, length, olc::WHITE, 1);
	}
};


int main()
{///DE ADAUGAT COMENTARII
	Example demo;
	if (demo.Construct(1080, 700, 1, 1))
		
		demo.Start();
	return 0;
}