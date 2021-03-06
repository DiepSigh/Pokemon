#include "userInput.h"


UserInput::UserInput(){
	mLevelManager = LevelManager::Instance();
}

void UserInput::Input(MenuManager* menuM, Options* menuO, battle *encounter) {
	while (SDL_PollEvent(&events) != 0) {
		if (events.type == SDL_QUIT) {
				//mQuit = true;
			}
		switch (events.type) {
			case SDL_KEYDOWN:
			switch (events.key.keysym.sym) {

			case SDLK_LEFT:
				// Option Menu Left
				if (menuM->OptsMnuisActive) {
					menuM->mOptions->oCursorLeft();
				}
				//World Control
				else if (menuM->StrtMnuisActive == false) {
					mLevelManager->moveLeft();
				}
				//BATTLES
				if (encounter->battle_getActive()) {
					encounter->left();
				}
				break;

			case SDLK_RIGHT:
				//Option Menu Right
				if (menuM->OptsMnuisActive) {
					menuM->mOptions->oCursorRight();
				}
				//World Control
				if (menuM->StrtMnuisActive == false && menuM->OptsMnuisActive == false) {
					mLevelManager->moveRight();
				}
				//BATTLES
				if (encounter->battle_getActive()) {
					encounter->right();
				}
				break;

			case SDLK_UP:
				//Main Menu Up
				if (menuM->StrtMnuisActive) {
					menuM->CursorMoveUp();
				}
				// Options Menu Up
				if (menuM->OptsMnuisActive) {
					menuM->mOptions->oCursorUp();
				}
				if (menuM->PokedexisActive) {
					menuM->mPokeDex->CursorPMoveUp();
				}
				//World Control Up
				else if (menuM->StrtMnuisActive == false) {
					mLevelManager->moveUp();
				}
				break;

			case SDLK_DOWN:
				//Main Menu Down
				if (menuM->StrtMnuisActive) {
					menuM->CursorMoveDown();
				}
				//Options Menu Down
				if (menuM->OptsMnuisActive) {
					menuM->mOptions->oCursorDown();
				}
				if (menuM->PokedexisActive) {
					menuM->mPokeDex->CursorPMoveDown();
				}
				//World Control Down
				else if (menuM->StrtMnuisActive == false) {
					mLevelManager->moveDown();
				}
				break;
				//BATTLES
			case SDLK_x:
				if (encounter->battle_getActive()) {
					switch (encounter->battle_getState()) {
					case battle::ENCOUNTER:
						encounter->encounter_continue(true);
						break;
					case battle::MENU:
						encounter->menu_continue(true);
						break;
					case battle::MOVES:
						encounter->moves_continue(true);
						break;
					case battle::ATTACK:
						encounter->attack_continue(true);
						break;
					}
					break;
				}
			case SDLK_z:
				if (encounter->battle_getActive()) {
					switch (encounter->battle_getState()) {
					case battle::MOVES:
						encounter->moves_return(true);
						break;
					}
					break;
				}
			case SDLK_ESCAPE:
				//mQuit = true;
				break;
			}
			break;

			case SDL_KEYUP:

			switch (events.key.keysym.sym) {
				case SDLK_a:
					if (menuM->StrtMnuisActive) {
						menuM->StrtMnuisActive = false;
					}
					if (menuM->OptsMnuisActive) {
						menuM->OptsMnuisActive = false;
						menuM->StrtMnuisActive = true;
					}
					if (menuM->PokedexisActive) {
						if (menuM->mPokeDex->Selected) {
							menuM->mPokeDex->PokeDeselect();
						}
						if (menuM->mPokeDex->Selected == false){
							menuM->PokedexisActive = false;
							menuM->StrtMnuisActive = true;
							menuM->mPokeDex->PokeDexReset();
						}
					}
					//World Control
					break;

				case SDLK_s:
					if (menuM->PokedexisActive && menuM->mPokeDex->CursorP->GetPosY() == 315) {
						menuM->mPokeDex->DexData();
					}

					if (menuM->PokedexisActive) {
						menuM->StrtMnuisActive = false;
						menuM->mPokeDex->PokemonSelected();
					}
					if (menuM->StrtMnuisActive) {
						menuM->MenuState();
					}
					else if (menuM->StrtMnuisActive == false && menuM->OptsMnuisActive) {
						if (menuM->mOptions->CursorO->GetPosY() == menuM->mOptions->Cancel->GetPosY() - 5 && menuM->mOptions->CursorO->GetPosX() == menuM->mOptions->Cancel->GetPosX() - 40) {
							menuM->OptsMnuisActive = false;
							menuM->StrtMnuisActive = true;
						}
					}
					
					//World Control
					break;

				case SDLK_c:
					//Opens Menu
					if (menuM->StrtMnuisActive == false) {
						menuM->StrtMnuisActive = true;
					}
					else if (menuM->StrtMnuisActive) {
						menuM->StrtMnuisActive = false;
					}
					if (menuM->OptsMnuisActive == true) {
						menuM->OptsMnuisActive = false;
						menuM->StrtMnuisActive = true;
					}
					if (menuM->PlayerMnuisActive = true) {
						menuM->PlayerMnuisActive = false;
						menuM->StrtMnuisActive = true;
					}
					break;
					//BATTLES
				case SDLK_x:
					if (encounter->battle_getActive()) {
						switch (encounter->battle_getState()) {
						case battle::MENU:
							encounter->menu_continue(false);
							break;
						case battle::MOVES:
							encounter->moves_continue(false);
							break;
						}
					}
				}
				break;
		}
	}

}
