//Stephen
#include "Pokemon.h"

//default constructor / empty
Pokemon::Pokemon() {
	/*m_pokedex = MISSINGNO;
	m_nickname = "MISSINGNO";
	m_level = 33;
	m_status = OK;
	m_baseHP = 33;
	m_baseAtk = 136;
	m_baseDef = 0;
	m_baseSpd = 6;
	m_baseSpe = 29;
	emptyEV();
	m_type1 = FLYING;
	m_type2 = NORMAL;
	m_expGroup = 2;
	m_evolve = 0;
	m_catchRate = 29;
	m_expYield = 1;
	m_numMoves = 2;
	setIV();
	setStats();
	setEXP();
	move[0].populateMove(WATER_GUN);*/
}

Pokemon::Pokemon(int pokemon, int level) {
	m_type2 = BLANK;
	//Pokebase->seen(pokemon);
	//Pokebase->seenUpdate(pokemon);
	retrievePokemon(pokemon);
	retrieveMoves(pokemon);
	m_level = level;
	m_status = OK;
	m_fainted = false;
	setIV();
	emptyEV();
	setEXP();
	setStats();
	setMoves(pokemon, m_level);

	//Sprites
	m_frontSprite = new Pokemon(0, 0, new Texture("pokemon_front.png", m_frontX, m_frontY, 112, 112));
	m_frontSprite->SetPosX(550);
	m_frontSprite->SetPosY(40);
	m_backSprite = new Pokemon(0, 0, new Texture("battle/pokemon_back.png", m_backX, m_backY, 256, 256));
	m_backSprite->SetPosX(130);
	m_backSprite->SetPosY(175);
}

Pokemon::Pokemon(int x, int y, Texture *tex) {
	mGraphics = Graphics::Instance();
	mAssetManager = AssetManager::Instance();

	mPos.x = x;
	mPos.y = y;
	mTex = tex;
}

void Pokemon::Render() {
	GetmTex()->SetRenderRectX(GetPosX());
	GetmTex()->SetRenderRectY(GetPosY());

	mGraphics->DrawTexture(GetmTex()->GetSDLTex(), (GetmTex()->GetClipped()) ? &GetmTex()->GetmClipRect() : NULL, &GetmTex()->GetmRenderRect());
}

Pokemon::~Pokemon() {}

void Pokemon::retrievePokemon(int pokedex_num) {
	/*Pokedex CSV: https://docs.google.com/spreadsheets/d/1J1R6JvNBhYi7kmQSRrePLh0hvVVZrVLmUItml668wBo/edit?usp=sharing
	std::ifstream src("../Debug/Assets/Pokedex.csv");
	if (!src.is_open()) {
		std::cout << "Could not open file: Pokedex.csv" << std::endl;
	}
	else {
		//Determines which row to fetch data from based on num_pokedex
		for (int k = 0; k < pokedex_num; k++) {
			src.ignore(500, '\n'); //ignore the first 500 characters, or until first \n. skips headers
		}

		src >> m_pokedex;
		src.ignore(1, ',');

		getline(src, m_nickname, ',');
		//base stats
		src >> m_baseHP;
		src.ignore(1, ',');
		src >> m_baseAtk;
		src.ignore(1, ',');
		src >> m_baseDef;
		src.ignore(1, ',');
		src >> m_baseSpd;
		src.ignore(1, ',');
		src >> m_baseSpe;
		src.ignore(1, ',');

		//types
		getline(src, m_type1_str, ',');
		m_type1 = typeConvert(m_type1_str);

		getline(src, m_type2_str, ',');
		if (m_type2_str != "") {
			m_type2 = typeConvert(m_type2_str);
		}

		//other
		src >> m_catchRate;
		src.ignore(1, ',');
		src >> m_expYield;
		src.ignore(1, ',');
		src >> m_expGroup;
		src.ignore(1, ',');
		src >> m_evolve;
		src.ignore(1, ',');
		getline(src, m_kind, ',');
		getline(src, m_height, ',');
		src >> m_weight;
		src.ignore(1, ',');
		getline(src, m_description, '\n');

		src.close();
	}*/

	Pokebase = PokeBase::Instance();

	//set according to array
	pokedex_num--;

	m_pokedex = Pokebase->mP_pokedex[pokedex_num];
	m_nickname = Pokebase->mP_name[pokedex_num];

	m_baseHP = Pokebase->mP_baseHP[pokedex_num];
	m_baseAtk = Pokebase->mP_baseAtk[pokedex_num];
	m_baseDef = Pokebase->mP_baseDef[pokedex_num];
	m_baseSpd = Pokebase->mP_baseSpd[pokedex_num];
	m_baseSpe = Pokebase->mP_baseSpe[pokedex_num];

	m_type1_str = Pokebase->mP_type1_str[pokedex_num];
	m_type1 = Pokebase->mP_type1[pokedex_num];
	m_type2_str = Pokebase->mP_type2_str[pokedex_num];
	m_type2 = Pokebase->mP_type2[pokedex_num];

	m_catchRate = Pokebase->mP_catchRate[pokedex_num];
	m_expYield = Pokebase->mP_expYield[pokedex_num];
	m_expGroup = Pokebase->mP_expGroup[pokedex_num];
	m_evolve = Pokebase->mP_evolve[pokedex_num];
	m_kind = Pokebase->mP_kind[pokedex_num];
	m_height = Pokebase->mP_height[pokedex_num];
	m_weight = Pokebase->mP_weight[pokedex_num];
	m_description = Pokebase->mP_description[pokedex_num];

	m_frontX = 0;
	m_frontY = 0;
	m_backX = 0;
	m_backY = 0;
	int count = 0;
	for (int k = 0; k < pokedex_num; k++) {
		m_frontX += 112;
		m_backX += 256;
		count++;
		//Move back to first column and move down 1 column
		if (count >= 16) {
			count = 0;
			m_frontX = 0;
			m_frontY += 112;
			m_backX = 0;
			m_backY += 256;
		}
	}

}

void Pokemon::retrieveMoves(int index) {
	// CSV: https://docs.google.com/spreadsheets/d/1rtdeZ5ZnPfdBtJH66HlOrYkcqv8HtF1vYtElf6xY40M/edit?usp=sharing
	std::ifstream src("../Debug/Assets/csv/learning_moves.csv");
	if (!src.is_open()) {
		std::cout << "Could not open file: learning_moves.csv" << std::endl;
	}
	else {
		for (int k = 0; k < index; k++) {
			src.ignore(500, '\n'); //ignore the first 500 characters, or until first \n. skips headers
		}

		src.ignore(20, ',');
		src.ignore(20, ',');

		src >> m_numMoves;
		src.ignore(1, ',');
		//Stores levels moves are learnt and moves learnt at level
		for (int k = 0; k < m_numMoves; k++) {
			src >> m_learnLevel[k];
			src.ignore(1, ',');
			src >> m_moveToLearn[k];
			src.ignore(1, ',');
		}

		src.close();
	}
	/*Pokebase = PokeBase::Instance();

	m_numMoves = Pokebase->mP_numMoves[index];
	for (int k = 0; k < m_numMoves; k++) {
		m_learnLevel[k] = Pokebase->mP_learnLevel[index][k];
		m_moveToLearn[k] = Pokebase->mP_moveToLearn[index][k];
	}*/

}

void Pokemon::setIV() {
	m_IV_hp = 0;
	m_IV_atk = randomGen(0, 15);
	m_IV_def = randomGen(0, 15);
	m_IV_spd = randomGen(0, 15);
	m_IV_spe = randomGen(0, 15);

	//HP determined through other IV's
	if (m_IV_atk % 2 != 0) {
		m_IV_hp += 8;
	}
	if (m_IV_def % 2 != 0) {
		m_IV_hp += 4;
	}
	if (m_IV_spd % 2 != 0) {
		m_IV_hp += 2;
	}
	if (m_IV_spe % 2 != 0) {
		m_IV_hp += 1;
	}
}

void Pokemon::emptyEV() {
	m_EV_hp = 0;
	m_EV_atk = 0;
	m_EV_def = 0;
	m_EV_spd = 0;
	m_EV_spe = 0;
}

void Pokemon::setStats() {
	//The HP stat follows: HP = ((((Base + IV) * 2 + (sqrt(EV) / 4)) * Level ) / 100) + Level + 10.
	//All other stats follows : Stat = ((((Base + IV) * 2 + (sqrt(EV) / 4)) * Level ) / 100) + 5

	m_hp = int(((((m_baseHP + m_IV_hp) * 2 + (sqrt(m_EV_hp) / 4)) * m_level) / 100) + m_level + 10);
	m_maxHP = m_hp;
	m_atk = int(((((m_baseAtk + m_IV_atk) * 2 + (sqrt(m_EV_atk) / 4)) * m_level) / 100) + 5);
	m_def = int(((((m_baseDef + m_IV_def) * 2 + (sqrt(m_EV_def) / 4)) * m_level) / 100) + 5);
	m_spd = int(((((m_baseSpd + m_IV_spd) * 2 + (sqrt(m_EV_spd) / 4)) * m_level) / 100) + 5);
	m_spe = int(((((m_baseSpe + m_IV_spe) * 2 + (sqrt(m_EV_spe) / 4)) * m_level) / 100) + 5);
}

void Pokemon::setMoves(int pokemon, int level) {
	int k = 0;
	m_moveCount = 0;
	//Count possible moves to learn
	do {
		m_moveCount++;
	} while (m_learnLevel[m_moveCount] <= level && m_learnLevel[m_moveCount] > 0);
	//Learn up to available moves
	if (m_moveCount <= 4) {
		do {
			move[k].populateMove(m_moveToLearn[k]);
			k++;
		} while (m_learnLevel[k] <= level);
		for (k; k < 4; k++) {
			move[k].populateMove(0);
		}
	}
	else {
		//Learn randomly if more than 4 moves
		for (k = 0; k < 4; k++) {
			move[k].populateMove(m_moveToLearn[randomGen(0, (m_moveCount - 1))]);
			//Make sure move isn't learnt already
			for (int j=0; j < k; j++)
			if (move[k].getMoveID() == move[j].getMoveID()) {
				k--;
			}
		}
	}
}

void Pokemon::setEXP() {
	switch (m_expGroup) {
	case SLOW:
		m_exp = int((5 * (pow(m_level, 3))) / 4);
		break;
	case MED_SLOW:
		m_exp = int((1.2 * (pow(m_level, 3))) - (15 * pow(m_level, 2)) + (100 * m_level) - 140);
		break;
	case MED_FAST:
		m_exp = int(pow(m_level, 3));
		break;
	case FAST:
		m_exp = int(4 * pow(m_level, 3)) / 5;
		break;
	}
}

void Pokemon::gainEXP(Pokemon &object) {
	int exp;
	//EXP = (a * b * L) / (7 * s), where:
	/*a is 1 if the Pokémon is wild, 1.5 if owned by a trainer,
	b is base experience pertaining the their species,
	L is the level of the fainted Pokémon,
	s is the number of Pokémon that were in battle and have not fainted.*/

	exp = (object.getEXPYield() * object.getLevel()) / (7);
	m_exp += exp;
	//if exp equals next level's minimum exp, level up
	int nextLv;
	switch (m_expGroup) {
	case SLOW:
		nextLv = int((5 * (pow(m_level+1, 3))) / 4);
		break;
	case MED_SLOW:
		nextLv = int((1.2 * (pow(m_level+1, 3))) - (15 * pow(m_level, 2)) + (100 * m_level) - 140);
		break;
	case MED_FAST:
		nextLv = int(pow(m_level+1, 3));
		break;
	case FAST:
		nextLv = int(4 * pow(m_level+1, 3)) / 5;
		break;
	}
	if (m_exp >= nextLv) {
		levelUP();
		m_exp = nextLv % m_exp;
	}
}

void Pokemon::levelUP() {
	m_level++;
	setStats();
}

void Pokemon::gainEVs(Pokemon &opposing) {
	m_EV_atk += opposing.m_IV_atk;
	m_EV_def += opposing.m_IV_def;
	m_EV_hp += opposing.m_IV_hp;
	m_EV_spd += opposing.m_IV_spd;
	m_EV_spe += opposing.m_IV_spe;
}

void Pokemon::hurt(int damage) {
	m_hp -= damage;
	//Faints if HP hits 0 or less
	if (m_hp <= 0) {
		fainted();
	}
}

void Pokemon::heal(int amount) {
	m_hp += amount;
	//HP does not go over MAX
	if (m_hp > m_maxHP) {
		m_hp = m_maxHP;
	}
}

void Pokemon::resetStatStages() {
	m_atkStage = 0;
	m_defStage = 0;
	m_spdStage = 0;
	m_speStage = 0;
	m_accStage = 100;
	m_evaStage = 100;
}

void Pokemon::displayMoves() {
	using namespace std;
	cout << "Move 1: " << move[0].getMoveName() << endl;
	cout << "Move 2: " << move[1].getMoveName() << endl;
	cout << "Move 3: " << move[2].getMoveName() << endl;
	cout << "Move 4: " << move[3].getMoveName() << endl << endl;
}

void Pokemon::displayStats() {
	using namespace std;

	cout << "Level: " << m_level << " " << m_nickname << endl;
	cout << "HP: " << m_hp << endl;
	cout << "Attack: " << m_atk << endl;
	cout << "Defence: " << m_def << endl;
	cout << "Speed: " << m_spd << endl;
	cout << "Special: " << m_spe << endl;
	cout << "Type: " << m_type1_str << " | " << m_type2_str << endl;
	cout << "Move 1: " << move[0].getMoveName() << endl;
	cout << "Move 2: " << move[1].getMoveName() << endl;
	cout << "Move 3: " << move[2].getMoveName() << endl;
	cout << "Move 4: " << move[3].getMoveName() << endl << endl;
}

void Pokemon::displayStats2() {
	using namespace std;

	cout << "Level: " << m_level << " " << m_nickname << endl;
	cout << "HP: " << m_hp << endl;
	//cout << "Attack: " << m_atk << endl;
	//cout << "Defence: " << m_def << endl;
	//cout << "Speed: " << m_spd << endl;
	//cout << "Special: " << m_spe << endl;
	cout << "Type: " << m_type1_str << " | " << m_type2_str << endl << endl;
}