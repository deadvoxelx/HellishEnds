#include "stdafx.h"
#include "NetherWoodTile.h"
#include "net.minecraft.world.h"
#include "Facing.h"

NetherWoodTile::NetherWoodTile(int id) : Tile(id, Material::wood)
{
	iconTop = NULL;
}

Icon *NetherWoodTile::getTexture(int face, int data)
{
	if (face == Facing::UP || face == Facing::DOWN) return iconTop;
	return icon;
}

void NetherWoodTile::registerIcons(IconRegister *iconRegister)
{
	icon = iconRegister->registerIcon(getIconName() + L"_side");
	iconTop = iconRegister->registerIcon(getIconName() + L"_top");
}