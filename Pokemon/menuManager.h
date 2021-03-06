#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "menu.h"
#include "PokeDex.h"
#include "PkmnState.h"
#include "Options.h"
#include "PlayerMenu.h"

class MenuManager : public Menu{
public:
	static void Release();
	Graphics* mGraphics;
	static MenuManager* sInstance;
	static MenuManager* Instance();

	void StartMenu();

	Menu* mMenu;
	Options* mOptions;
	PlayerMenu* mPlayerMenu;
	PokeDex* mPokeDex;


	void MenuState();

	void Update();
	void Render();

	void LoadOptions();
	void LoadPlayerM();
	void LoadPokeDex();
	void DataDraw();
private:
	MenuManager();
	~MenuManager();
};
#endif // !MENUMANAGER_H
