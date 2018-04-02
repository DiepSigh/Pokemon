//Stephen
#include "Pokemon.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

//default constructor / empty
Pokemon::Pokemon() {
	m_pokedex = MISSINGNO;
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
	m_catchRate = 29;
	m_expYield = 1;
	setStats();
}

Pokemon::Pokemon(int pokemon, int level) {
	getPokemon(pokemon);
	m_level = level;
	m_status = OK;
	setIV();
	emptyEV();
	expCalculator(m_expGroup);
	setStats();
	setMoves(pokemon, m_level);
}

Pokemon::~Pokemon() {}

const void Pokemon::getPokemon(int pokedex_num){
	//CSV: https://docs.google.com/spreadsheets/d/1J1R6JvNBhYi7kmQSRrePLh0hvVVZrVLmUItml668wBo/edit?usp=sharing
	std::ifstream src("Pokedex.csv");

	if (!src.is_open()) {
		std::cout << "Could not open file.";
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

		//moves
		src >> m_numMoves;
		src.ignore(1, ',');
		for (int k = 0; k < m_numMoves; k++) {
			src >> m_learnLevel[k];
			src.ignore(1, ',');
			std::cout << m_learnLevel[k];
		}


		src.close();
	}
}

void Pokemon::setIV() {
	m_IV_hp = 0;
	m_IV_atk = (rand() % 15);
	m_IV_def = (rand() % 15);
	m_IV_spd = (rand() % 15);
	m_IV_spe = (rand() % 15);

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
	m_atk = int(((((m_baseAtk + m_IV_atk) * 2 + (sqrt(m_EV_atk) / 4)) * m_level) / 100) + 5);
	m_def = int(((((m_baseDef + m_IV_def) * 2 + (sqrt(m_EV_def) / 4)) * m_level) / 100) + 5);
	m_spd = int(((((m_baseSpd + m_IV_spd) * 2 + (sqrt(m_EV_spd) / 4)) * m_level) / 100) + 5);
	m_spe = int(((((m_baseSpe + m_IV_spe) * 2 + (sqrt(m_EV_spe) / 4)) * m_level) / 100) + 5);
}

void Pokemon::setMoves(int pokemon, int level) {

	move[0].getMove(ABSORB);
	move[1].getMove(0);
	move[2].getMove(0);
	move[3].getMove(0);
}

void Pokemon::expCalculator(int group) {
	switch (group) {
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

const void Pokemon::displayStats() {
	using namespace std;

	cout << "Level: " << m_level << " " << m_nickname << endl;
	cout << "HP: " << m_hp << endl;
	cout << "Attack: " << m_atk << endl;
	cout << "Defence: " << m_def << endl;
	cout << "Speed: " << m_spd << endl;
	cout << "Special: " << m_spe << endl;
	cout << "Type: " << m_type1_str << ", " << m_type2_str << endl;
	cout << "Catch Rate: " << m_catchRate << endl;
	cout << "EXP Yield: " << m_expYield << endl;
	cout << "EXP: " << m_exp << endl;
	cout << "Status: " << m_status << endl;
	cout << "Move 1: " << move[0].returnMove() << endl;
	cout << "Move 2: " << move[1].returnMove() << endl;
	cout << "Move 3: " << move[2].returnMove() << endl;
	cout << "Move 4: " << move[3].returnMove() << endl;
}