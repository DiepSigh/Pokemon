#include "userInput.h"


UserInput::UserInput(){
	mLevelManager = LevelManager::Instance();
	//mMenu = 
}

void UserInput::Input(MenuManager* menuM) {
	if (StrtMnuisActive) {
	while (SDL_PollEvent(&events) != 0) {
		if (events.type == SDL_QUIT) {
			//mQuit = true;
		}

		//Example of keyboard/mouse functionality

		switch (events.type) {
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym) {

			case SDLK_LEFT:
				mLevelManager->moveLeft();
				printf("You pressed left arrow\n");
				break;

			case SDLK_RIGHT:
				mLevelManager->moveRight();
				//printf("You pressed right arrow\n");
				break;

			case SDLK_UP:
				//mLevelManager->moveUp();
				//Cursor->CursorMoveUp();
				//mMenu->Cursor->CursorMoveUp();
				//printf("You pressed up arrow\n");
				menuM->CursorMoveUp();
				break;

			case SDLK_DOWN:
				menuM->CursorMoveDown();
				//mLevelManager->moveDown();
				//Cursor->CursorMoveDown();
				//mMenu->Cursor->CursorMoveDown();
				//printf("You pressed down arrow\n");
				break;

			case SDLK_ESCAPE:
				//mQuit = true;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (events.key.keysym.sym) {

			case SDLK_a:
				//printf("You pressed 'a'\n");
				break;

			case SDLK_s:
				//printf("You pressed 's'\n");
				break;

			case SDLK_c:
				//printf("You pressed 'c'\n");
				break;

			}
			break;
			}
		}
	}
}

void UserInput::Input(){
		
	while (SDL_PollEvent(&events) != 0) {
		if (events.type == SDL_QUIT) {
			//mQuit = true;
		}

		//Example of keyboard/mouse functionality

		switch (events.type) {
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym) {
			
			case SDLK_LEFT:
				mLevelManager->moveLeft();
				printf("You pressed left arrow\n");
				break;

			case SDLK_RIGHT:
				mLevelManager->moveRight();
				//printf("You pressed right arrow\n");
				break;

			case SDLK_UP:
				//mLevelManager->moveUp();
				//Cursor->CursorMoveUp();
				mMenu->Cursor->CursorMoveUp();
				//printf("You pressed up arrow\n");
				break;

			case SDLK_DOWN:
				//mLevelManager->moveDown();
				//Cursor->CursorMoveDown();
				mMenu->Cursor->CursorMoveDown();
				//printf("You pressed down arrow\n");
				break;

			case SDLK_ESCAPE:
				//mQuit = true;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (events.key.keysym.sym) {

			case SDLK_a:
				//printf("You pressed 'a'\n");
				break;

			case SDLK_s:
				//printf("You pressed 's'\n");
				break;

			case SDLK_c:
				//printf("You pressed 'c'\n");
				break;

			}
			break;
		}

	}
}