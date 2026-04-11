#include "stdafx.h"
#include "PumpkinFacelessTile.h"
#include "net.minecraft.world.h"
#include "Facing.h"

PumpkinFacelessTile::PumpkinFacelessTile(int id) : Tile(id, Material::vegetable)
{
	iconTop = nullptr;
}

Icon *PumpkinFacelessTile::getTexture(int face, int data)
{
	if (face == Facing::UP || face == Facing::DOWN) return iconTop;
	return icon;
}

void PumpkinFacelessTile::registerIcons(IconRegister *iconRegister)
{
	icon = iconRegister->registerIcon(getIconName() + L"_side");
	iconTop = iconRegister->registerIcon(getIconName() + L"_top");
}