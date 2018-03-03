#include "Consumable_Entity.h"

Consumable_Entity::Consumable_Entity(iPoint coor, ENTITY_TYPE type, SDL_Texture* texture, CONSUMABLE_TYPE consumableType) : StaticEntity(coor, type, texture)
{
	this->consumableType = consumableType;
}

void Consumable_Entity::Start() {}
void Consumable_Entity::Finish() {}

void Consumable_Entity::Interaction() {}