#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "mathHelper.h"

class GameEntity {
public:
	enum SPACE {LOCAL = 0, WORLD = 1};

private:
	Vector2 mPos;
	float  mRotation;
	bool mActive;
	GameEntity* mParent;

public:
	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	void Pos(Vector2 pos);
	Vector2 Pos(SPACE space = WORLD);
	void Rotation(float rotation);
	float Rotation(SPACE space = WORLD);
	void Active(bool active);
	bool Active();
	void Parent(GameEntity*);
	GameEntity* Parent();

	virtual void Update();
	virtual void Render();
};
#endif
