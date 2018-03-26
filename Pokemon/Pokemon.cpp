#include "Pokemon.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

Pokemon::Pokemon() {
	//m_pokedex = MISSINGNO;
	//m_name = "RICHARD";
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
	m_level = level;
	m_status = CLEAN;
	setIV();
	m_EV_hp = 0;
	m_EV_atk = 0;
	m_EV_def = 0;
	m_EV_spd = 0;
	m_EV_spe = 0;
	setStats();
}

const void Pokemon::getPokemon(int num_pokedex){
	//CSV: https://docs.google.com/spreadsheets/d/1J1R6JvNBhYi7kmQSRrePLh0hvVVZrVLmUItml668wBo/edit?usp=sharing
	std::ifstream src("Pokedex.csv");

	if (!src.is_open()) {
		std::cout << "Could not open file.";
	}
	else {
		//Determines which row to fetch data from based on num_pokedex
		for (int k = 0; k < num_pokedex; k++) {
			src.ignore(500, '\n'); //ignore the first 500 characters, or until first \n. skips headers
		}

		src >> m_pokedex;
		src.ignore(1, ',');

		getline(src, m_name, ',');
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

		src >> m_catchRate;
		src.ignore(1, ',');
		src >> m_expYield;

		src.close();
	}
}

int Pokemon::typeConvert(string t) {
	//enum pokemon_type { NORMAL=0, FIGHTING=1, FLYING=2, POISON=3, GROUND=4, ROCK=5, BUG=7, GHOST=8,
	//BLANK=9, FIRE=14, WATER=15, GRASS=16, ELECTRIC=17, PSYCHIC=18, ICE=19, DRAGON=20 };
	if (t == "NORMAL") {
		return NORMAL;
	}else if (t == "FIGHTING") {
		return FIGHTING;
	}else if (t == "FLYING") {
		return FLYING;
	}else if (t == "POISON") {
		return POISON;
	}else if (t == "GROUND") {
		return GROUND;
	}else if (t == "ROCK") {
		return ROCK;
	}else if (t == "BUG") {
		return BUG;
	}else if (t == "GHOST") {
		return GHOST;
	}else if (t == "FIRE") {
		return FIRE;
	}else if (t == "WATER") {
		return WATER;
	}else if (t == "GRASS") {
		return GRASS;
	}else if (t == "ELECTRIC") {
		return ELECTRIC;
	}else if (t == "PSYCHIC") {
		return PSYCHIC;
	}else if (t == "ICE") {
		return ICE;
	}else if (t == "DRAGON") {
		return DRAGON;
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

void Pokemon::setStats() {
	//The HP stat follows: HP = ((((Base + IV) * 2 + (sqrt(EV) / 4)) * Level ) / 100) + Level + 10.
	//All other stats follows : Stat = ((((Base + IV) * 2 + (sqrt(EV) / 4)) * Level ) / 100) + 5

	m_hp = int(((((m_baseHP + m_IV_hp) * 2 + (sqrt(m_EV_hp) / 4)) * m_level) / 100) + m_level + 10);
	m_atk = int(((((m_baseAtk + m_IV_atk) * 2 + (sqrt(m_EV_atk) / 4)) * m_level) / 100) + 5);
	m_def = int(((((m_baseDef + m_IV_def) * 2 + (sqrt(m_EV_def) / 4)) * m_level) / 100) + 5);
	m_spd = int(((((m_baseSpd + m_IV_spd) * 2 + (sqrt(m_EV_spd) / 4)) * m_level) / 100) + 5);
	m_spe = int(((((m_baseSpe + m_IV_spe) * 2 + (sqrt(m_EV_spe) / 4)) * m_level) / 100) + 5);
}

const void Pokemon::displayStats() {
	cout << "Level: " << m_level << " " << m_name << endl;
	cout << "HP: " << m_hp << endl;
	cout << "Attack: " << m_atk << endl;
	cout << "Defence: " << m_def << endl;
	cout << "Speed: " << m_spd << endl;
	cout << "Special: " << m_spe << endl;
	cout << "Type: " << m_type1_str << ", " << m_type2_str << endl;
	cout << "Catch Rate: " << m_catchRate << endl;
	cout << "EXP Yield: " << m_expYield << endl;
}