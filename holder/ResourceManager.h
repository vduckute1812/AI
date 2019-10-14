#pragma once
#include <map>
#include "GameEngine.h"
#include "Singleton.h"


enum Background
{
	MAP,
	AIPut,
	PlayerPut,
	Powerup
};

enum PlayerMode
{
	AI,
	PLAYER
};

enum SizeCharacter
{
	SMALL,
	MEDIUM,
	BIG
};

typedef std::map<PlayerMode, Animation*> BotAnimation;

class ResourceManager: public Singleton<ResourceManager>
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	Image* GetImage(Background id);
	void		LoadAnimation(PlayerMode player, SizeCharacter size);
	Animation*	GetAnimation(PlayerMode player, SizeCharacter size);
	Font*		GetFontById(int id);

private:

	bool		m_isResource;

	UIButton*				button;
	std::list<Image*>		listImages;
	std::map<Background, Image*>		images;
	std::map<int, Font*>		fonts;
	std::map<SizeCharacter, BotAnimation>	botAnims;

};

