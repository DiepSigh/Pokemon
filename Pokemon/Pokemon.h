//Stephen

//Resources:
//Data Structure: https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_data_structure_in_Generation_I
//Base Stats: https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_stats_(Generation_I)
//EXP Yield: https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_effort_value_yield_(Generation_III-IV)
//Catch Rate: https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_catch_rate
#ifndef POKEMON_H
#define POKEMON_H

#include "PokeBase.h"
//#include "moves.h"
#include <math.h>
//#include <iostream>
//#include <fstream>

//enum pokemon {MISSINGNO, BULBASAUR, IVYSAUR, VENUSAUR, CHARMANDER, CHARMELEON, CHARIZARD, SQUIRTLE, WARTORTLE, BLASTOISE, CATERPIE, METAPOD, BUTTERFREE,
//	  WEEDLE, KAKUNA, BEEDRILL, PIDGEY, PIDGEOTTO, PIDGEOT, RATTATA, RATICATE, SPEAROW, FEAROW, EKANS, ARBOK, PIKACHU, RAICHU, SANDSHREW, SANDSLASH,  
//	  NIDORAN_F, NIDORINA, NIDOQUEEN, NIDORAN_M, NIDORINO, NIDOKING, CLEFAIRY, CLEFABLE, VULPIX, NINETALES, JIGGLYPUFF, WIGGLYTUFF, ZUBAT, GOLBAT,  
//	  ODDISH, GLOOM, VILEPLUME, PARAS, PARASECT, VENONAT, VENOMOTH, DIGLETT, DUGTRIO, MEOWTH, PERSIAN, PSYDUCK, GOLDUCK, MANKEY, PRIMEAPE, GROWLITHE,  
//	  ARCANINE, POLIWAG, POLIWHIRL, POLIWRATH, ABRA, KADABRA, ALAKAZAM, MACHOP, MACHOKE, MACHAMP, BELLSPROUT, WEEPINBELL, VICTREEBEL, TENTACOOL,  
//	  TENTACRUEL, GEODUDE, GRAVELER, GOLEM, PONYTA, RAPIDASH, SLOWPOKE, SLOWBRO, MAGNEMITE, MAGNETON, FARFETCHD, DODUO, DODRIO, SEEL, DEWGONG,  
//	  GRIMER, MUK, SHELLDER, CLOYSTER, GASTLY, HAUNTER, GENGAR, ONIX, DROWZEE, HYPNO, KRABBY, KINGLER, VOLTORB, ELECTRODE, EXEGGCUTE, EXEGGUTOR,  
//	  CUBONE, MAROWAK, HITMONLEE, HITMONCHAN, LICKITUNG, KOFFING, WEEZING, RHYHORN, RHYDON, CHANSEY, TANGELA, KANGASKHAN, HORSEA, SEADRA, GOLDEEN,  
//	  SEAKING, STARYU, STARMIE, MR_MIME, SCYTHER, JYNX, ELECTABUZZ, MAGMAR, PINSIR, TAUROS, MAGIKARP, GYARADOS, LAPRAS, DITTO, EEVEE, VAPOREON,  
//	  JOLTEON, FLAREON, PORYGON, OMANYTE, OMASTAR, KABUTO, KABUTOPS, AERODACTYL, SNORLAX, ARTICUNO, ZAPDOS, MOLTRES, DRATINI, DRAGONAIR, DRAGONITE,  
//	  MEWTWO, MEW};
//
//enum experience_group { SLOW = 1, MED_SLOW = 2, MED_FAST = 3, FAST = 4 };

enum pokemon_status { OK=0, BURNED=1, FROZEN=2, PARALYZED=3, POISONED=4, BADLY_POISONED=5, ASLEEP=6 };

const int MAX_EV = 65535;

//TO DO:
//Pokemon into array

class Pokemon : public GameEntity {
public:
	Pokemon();
	Pokemon(int pokemon, int level);
	~Pokemon();
	//void setPokemonStats(int pokemon); 
	void retrievePokemon(int pokemon); //Grabs data from PokeBase class to Pokemon variables
	void openMoves(int pokemon); //Stores learnable moves at levels in m_learnLevel[] and m_moveToLearn[]
	void setIV(); //Sets IV's randomly
	void emptyEV(); //Sets all EV's to 0
	void setStats(); //Sets stats of Pokemon based on IV's, current EV's, and level
	void setEXP(); //Sets EXP of Pokemon based on level; should only be called when new Pokemon is created
	void setMoves(int pokemon, int level); //Sets 4 learnables moves based on level or less
	void resetStatStages(); //Resets stages of stats for battles
	void displayMoves();
	void displayStats();
	void displayStats2();

	//Battle
	void hurt(int damage);
	void heal(int amount);
	inline void awake() { m_status = OK; m_sleepCount = 0; }
	inline void asleep() { m_sleepCount++; }
	inline void cured() { m_status = OK; m_poisonCount = 0; }
	inline void poison() { m_poisonCount++; }
	inline void resetConfused() { setConfused(false); m_confusedCount = 0; }
	inline void confused() { m_confusedCount++; }
	inline void fainted() { m_fainted = true; m_hp = 0; m_status = OK; }
	inline void restored() { m_fainted = false; m_hp = m_maxHP; }

	//Getters
	inline std::string getName() { return m_nickname; }
	inline Move getMove(int k) { return move[k]; }
	inline int getLevel() { return m_level; }
	inline int getStatus() { return m_status; }
	inline bool getFainted() { return m_fainted; }
	inline int getHP() { return m_hp; }
	inline int getMaxHP() { return m_maxHP; }
	inline int getAtk() { return m_atk; }
	inline int getDef() { return m_def; }
	inline int getSpd() { return m_spd; }
	inline int getSpe() { return m_spe; }
	inline int getType1() { return m_type1; }
	inline int getType2() { return m_type2; }

	inline int getBaseSpd() { return m_baseSpd; }

	inline int getAtkStage() { return m_atkStage; }
	inline int getDefStage() { return m_defStage; }
	inline int getSpdStage() { return m_spdStage; }
	inline int getSpeStage() { return m_speStage; }
	inline int getAccStage() { return m_accStage; }
	inline int getEvaStage() { return m_evaStage; }

	inline bool getBounded() { return m_bounded; }
	inline bool getConfused() { return m_confused; }
	inline int getConfusedCount() { return m_confusedCount; }
	inline bool getFlinched() { return m_flinched; }
	inline bool getSeeded() { return m_seeded; }

	inline int getSleepCount() { return m_sleepCount; }
	inline int getPoisonCount() { return m_poisonCount; }

	//Setters
	inline void setStatus(int status) { m_status = status; }

	inline void setAtkStage(int stage) { m_atkStage += stage; }
	inline void setDefStage(int stage) { m_defStage += stage; }
	inline void setSpdStage(int stage) { m_spdStage += stage; }
	inline void setSpeStage(int stage) { m_speStage += stage; }
	inline void setAccStage(int stage) { m_accStage += stage; }
	inline void setEvaStage(int stage) { m_evaStage += stage; }

	inline void setBounded(bool state) { m_bounded = state; }
	inline void setConfused(bool state) { m_confused = state; }
	inline void setFlinched(bool state) { m_flinched = state; }
	inline void setSeeded(bool state) { m_seeded = state; }

protected:
	PokeBase *Pokebase;
	int m_pokedex; //stores # in pokedex
	std::string m_nickname; //stores nickname if any
	int m_level;
	int m_status;
	bool m_fainted;
	int m_exp;
	Move move[4];
	
	//Other
	int m_type1;
	int m_type2;
	std::string m_type1_str;
	std::string m_type2_str;
	int m_catchRate;
	int m_expYield;
	int m_expGroup; //part of one of four exp groups
	int m_evolve; //level Pokemon evolves at

	//description
	std::string m_kind;
	std::string m_height;
	float m_weight;
	std::string m_description;

	//moves
	int m_numMoves; //number of moves they can learn from leveing
	int m_learnLevel[10]; //levels moves will be learned
	int m_moveToLearn[10]; //moves to be learnt

	int m_maxHP;
	//dynamic stats
	int m_hp;
	int m_atk;
	int m_def;
	int m_spd;
	int m_spe;

	//IV
	int m_IV_hp;
	int m_IV_atk;
	int m_IV_def;
	int m_IV_spd;
	int m_IV_spe;

	//EV
	int m_EV_hp;
	int m_EV_atk;
	int m_EV_def;
	int m_EV_spd;
	int m_EV_spe;

	//static stats
	int m_baseHP;
	int m_baseAtk;
	int m_baseDef;
	int m_baseSpd;
	int m_baseSpe;

	//stat stages for battle
	int m_atkStage;
	int m_defStage;
	int m_spdStage;
	int m_speStage;
	int m_accStage;
	int m_evaStage;

	//more battle stuff
	bool m_bounded;
	bool m_confused;
	int m_confusedCount;
	bool m_flinched;
	bool m_seeded;

	int m_sleepCount;
	int m_poisonCount;
};

#endif // !POKEMON_H