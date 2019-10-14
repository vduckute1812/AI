#include <string>
#include <memory>
#include "ResourceManager.h"

const int NUM_FRAME_SWITCH_IMAGE = 10;
const int NUM_IMAGE = 7;



void ResourceManager::Init()
{
	// Background
	images.insert(std::pair<Background, Image*>(Background::MAP, new Image("../Resources/Data/map.png")));
	images.insert(std::pair<Background, Image*>(Background::AIPut, new Image("../Resources/Data/AIPut.png")));
	images.insert(std::pair<Background, Image*>(Background::PlayerPut, new Image("../Resources/Data/PlayerPut.png")));
	images.insert(std::pair<Background, Image*>(Background::Powerup, new Image("../Resources/Data/Powerup.png")));

	const char* prevButton = "../Resources/PlayBttNormal.png";
	const char* pressButton = "../Resources/PlayBttPressing.png";
	button = new UIButton(prevButton, pressButton);

	// Font
	fonts.insert(std::pair<int, Font*>(0, new Font("../Resources/Data/Fonts/font.fnt")));
	fonts.insert(std::pair<int, Font*>(1, new Font("../Resources/Data/Fonts/fontPolygon.fnt")));

	// Animation
	LoadAnimation(PlayerMode::AI, SizeCharacter::BIG);
	LoadAnimation(PlayerMode::AI, SizeCharacter::MEDIUM);
	LoadAnimation(PlayerMode::AI, SizeCharacter::SMALL);
	LoadAnimation(PlayerMode::PLAYER, SizeCharacter::BIG);
	LoadAnimation(PlayerMode::PLAYER, SizeCharacter::MEDIUM);
	LoadAnimation(PlayerMode::PLAYER, SizeCharacter::SMALL);
}

void ResourceManager::Destroy()
{

}

Image* ResourceManager::GetImage(Background id)
{
	return images.find(id)->second;
}

void ResourceManager::LoadAnimation(PlayerMode player, SizeCharacter size)
{
	char* mode = "";
	switch (player)
	{
	case AI:
	{
		mode = "AI";
		break;
	}
	case PLAYER:
	{
		mode = "Player";
		break;
	}
	default:
		break;
	}

	char* sizeCharacter = "";
	switch (size)
	{
	case SMALL:
	{
		sizeCharacter = "SMALL";
		break;
	}
	case MEDIUM:
	{
		sizeCharacter = "MEDIUM";
		break;
	}
	case BIG:
	{
		sizeCharacter = "BIG";
		break;
	}
	default:
		break;
	}

	// Add AI bot animation
	for (int i = 1; i <= NUM_IMAGE; i++)
	{
		char path[256];
		sprintf(path, "../Resources/Data/%s/%s/player_full_%d.png", mode, sizeCharacter, i);
		listImages.push_back(new Image(path));
	}
	BotAnimation bot;
	bot.insert(std::pair<PlayerMode, Animation*>(player, new Animation(listImages, NUM_FRAME_SWITCH_IMAGE)));
	botAnims.insert(std::pair<SizeCharacter, BotAnimation>(size, bot));
	listImages.clear();
}


Font* ResourceManager::GetFontById(int id)
{
	return fonts.find(id)->second;
}

Animation* ResourceManager::GetAnimation(PlayerMode player, SizeCharacter size)
{
	int sizeData = botAnims.size();
	return botAnims.find(size)->second.find(player)->second;
}
