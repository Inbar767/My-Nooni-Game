#include "Accessorizes.h"
#include "Definitions.h"

//Constructor gets a data
Accessorizes::Accessorizes(gameDataRef data) : visibleTable(false), typeUsed(AccessoryType::NO_ACCESSORY), data(data)
{
	data->assets.loadTexture("Accessorize 0", REFRIGERATOR_FILE);
	data->assets.loadTexture("Accessorize 1", BED_FILE);
	data->assets.loadTexture("Accessorize 2", BATH_FILE);
	data->assets.loadTexture("Accessorize 3", TABLE_FILE);
	data->assets.loadTexture("Accessorize Used 0", OPENED_REFRIGERATOR_FILE);
	data->assets.loadTexture("Accessorize Used 1", USED_BED_FILE);


	for (int i = 0; i < ACCESSORIES_NUBER; i++)
	{
		accessorizes.push_back(sf::Sprite(data->assets.getTexture("Accessorize " + std::to_string(i))));
	}

	accessorizes.at(0).setPosition(sf::Vector2f(67, 240));
	accessorizes.at(1).setPosition(sf::Vector2f(290, 260));
	accessorizes.at(2).setPosition(sf::Vector2f(650, 295));
	accessorizes.at(3).setPosition(sf::Vector2f(400, 540));
}

//Set visibility of table
void Accessorizes::setVisibleTable()
{
	visibleTable = !visibleTable;
}

//Handles input if one accessory is being touched by the mouse
AccessoryType Accessorizes::handleInput(sf::Event event)
{
	for (int accessoryIndex = 0; accessoryIndex < ACCESSORIES_NUBER - 1; accessoryIndex++)
	{
		if (data->input.isSpriteClicked(accessorizes.at(accessoryIndex), sf::Mouse::Left, data->window))
		{
			
			if (accessoryIndex <= static_cast<int>(AccessoryType::BED)) //If accessory's image is changing to being used
			{
				typeUsed = static_cast<AccessoryType>(accessoryIndex);
				accessorizes.at(accessoryIndex).setTexture(data->assets.getTexture("Accessorize Used " + std::to_string(accessoryIndex)));
			}
			return typeUsed;
		}
	}
	return AccessoryType::NO_ACCESSORY;
}

//Draws accessorizes
void Accessorizes::draw()
{
	for (int accessoryIndex = 0; accessoryIndex < ACCESSORIES_NUBER - 1; accessoryIndex++)
	{
		data->window.draw(accessorizes.at(accessoryIndex));
	}
}

//Stops the use of accessory
void Accessorizes::stopUse()
{
	if (typeUsed == AccessoryType::REFRIGERATOR || typeUsed == AccessoryType::BED)
	{
		int typeIndex = static_cast<int>(typeUsed);
		accessorizes.at(typeIndex).setTexture(data->assets.getTexture("Accessorize " + std::to_string(typeIndex)));
		typeUsed = AccessoryType::NO_ACCESSORY;
	}
}

//Draws table
void Accessorizes::drawTable()
{
	if (visibleTable)
	{
		int tableIndex = static_cast<int>(TABLE);
		data->window.draw(accessorizes.at(tableIndex));
	}
}