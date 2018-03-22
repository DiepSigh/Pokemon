#include "Pokemon.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

Pokemon::Pokemon() {
	//m_pokedex = MISSINGNO;
	//m_name = "MISSINGNO";
	//m_baseHP = 33;
	//m_baseAtk = 136;
	//m_baseDef = 0;
	//m_baseSpd = 6;
	//m_baseSpe = 29;

	//m_type1 = FLYING;
	//m_type2 = NORMAL;
	//m_catchRate = 29;
	//m_expYield = 1;
}

Pokemon::Pokemon(int pokemon, int level) {
	getPokemon(pokemon);
	setIV();
	m_EV_hp = 0;
	m_EV_att = 0;
	m_EV_def = 0;
	m_EV_spd = 0;
	m_EV_spe = 0;
	setStats();
}

const void Pokemon::getPokemon(int pokemon){
	std::ifstream src("Pokedex.csv");

	if (!src.is_open()) {
		std::cout << "Could not open file.";
	}
	else {
		for (int k = 0; k < pokemon; k++) {
			src.ignore(500, '\n'); //ignore the first 500 characters, or until first \n. skips headers
		}
		src >> m_pokedex;
		src.ignore(1, ',');

		getline(src, m_name, ',');

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
	}
}

void Pokemon::setIV() {
	m_IV_hp = 0;
	m_IV_att = (rand() % 15);
	m_IV_def = (rand() % 15);
	m_IV_spd = (rand() % 15);
	m_IV_spe = (rand() % 15);
	if (m_IV_att % 2 != 0) {
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

void Pokemon::setStats() {
	//The HP stat follows: HP = ( ( ( (Base + IV) * 2 + ( sqrt(EV) / 4 ) ) * Level ) / 100 ) + Level + 10.
	//All other stats follows : Stat = ((((Base + IV) * 2 + (sqrt(EV) / 4)) * Level) / 100) + 5

	m_hp = ((((m_baseHP + m_IV_hp) * 2 + (sqrt(m_EV_hp) / 4)) * m_level) / 100) + m_level + 10;
}

const void Pokemon::displayStats() {

}