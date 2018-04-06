#include "DisplayText.h"

using namespace std;

TextScreen::TextScreen(){
	mGraphics = Graphics::Instance();
	mAssetManager = AssetManager::Instance();
}

TextScreen::TextScreen(int x, int y, string name) {
	mGraphics = Graphics::Instance();
	mAssetManager = AssetManager::Instance();
	mPos.x = x;
	mPos.y = y;
	Talk(name);
	Speech();
	mTex = new Texture(Dialouge[0], "PKMNSOLID.ttf", 25);
}

TextScreen::~TextScreen()
{
}

string TextScreen::Talk(string NPC){
	
	string Name;
	bool Found = false;
	
	std::ifstream src("../Debug/Assets/pokemonblue_text.csv");
	if (!src.is_open()) {
		cout << "Couldn't open file: pokemonblue_text.csv" << endl;
	} 
	else {
		do {
			getline(src, Name, ',');
			if (NPC == Name) {
				Found = true;
				do {
					getline(src, mSpeech, ',');
					Dialouge.push_back(mSpeech);
					cout << mSpeech << std::endl;
				} while (mSpeech != "$$$");
			}
			else {
				src.ignore(500, '\n');
			}
		} while (!Found && !src.eof());
	} 
	src.close();
	return Dialouge[0];
}

void TextScreen::Update()
{
}

void TextScreen::Render()
{
	GetmTex()->SetRenderRectX(GetPosX());
	GetmTex()->SetRenderRectY(GetPosY());

	mGraphics->DrawTexture(GetmTex()->GetSDLTex(), (GetClipped()) ? &GetmClipRect() : NULL, &GetmTex()->GetmRenderRect());

}

void TextScreen::Speech() {
	//for (int i = 0; i < Dialouge.size(); i++){
		//cout << Dialouge[i] << std::endl;
	//}
}
