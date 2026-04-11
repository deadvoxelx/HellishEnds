#include "stdafx.h"
#include "ShearsItem.h"
#include "net.minecraft.world.entity.player.h"
#include "Tile.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"

ShearsItem::ShearsItem(int itemId) : Item(itemId)
{
	setMaxStackSize(1);
	setMaxDamage(385);
}

bool ShearsItem::mineBlock(shared_ptr<ItemInstance> itemInstance, Level *level, int tile, int x, int y, int z, shared_ptr<LivingEntity> owner)
{
	if (tile == Tile::leaves_Id || tile == Tile::web_Id || tile == Tile::tallgrass_Id || tile == Tile::vine_Id || tile == Tile::tripWire_Id)
	{
		itemInstance->hurtAndBreak(1, owner);
		return true;
	}
	return Item::mineBlock(itemInstance, level, tile, x, y, z, owner);
}

bool ShearsItem::canDestroySpecial(Tile *tile)
{
	return tile->id == Tile::web_Id || tile->id == Tile::redStoneDust_Id || tile->id == Tile::tripWire_Id;
}

float ShearsItem::getDestroySpeed(shared_ptr<ItemInstance> itemInstance, Tile *tile)
{
	if (tile->id == Tile::web_Id || tile->id == Tile::leaves_Id)
	{
		return 15;
	}
	if (tile->id == Tile::wool_Id)
	{
		return 5;
	}
	return Item::getDestroySpeed(itemInstance, tile);
}

bool ShearsItem::useOn(shared_ptr<ItemInstance> instance, shared_ptr<Player> player, Level *level, int x, int y, int z, int face, float clickX, float clickY, float clickZ, bool bTestUseOnOnly)
{
	if (!player->mayUseItemAt(x, y, z, face, instance)) return false;

	int targetType = level->getTile(x, y, z);

	if ((targetType == Tile::pumpkinFaceless_Id)) 
	{
		if(!bTestUseOnOnly)
		{
			Tile *tile = Tile::pumpkin;
			level->playSound(x + 0.5f, y + 0.5f, z + 0.5f, tile->soundType->getStepSound(), (tile->soundType->getVolume() + 1) / 2, tile->soundType->getPitch() * 0.8f);

			if (level->isClientSide) return true;
			level->setTileAndUpdate(x, y, z, tile->id);
			instance->hurtAndBreak(1, player);
		}
		return true;
	}

	return false;
}
