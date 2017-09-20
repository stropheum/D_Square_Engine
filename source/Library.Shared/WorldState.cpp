#include "pch.h"
#include "WorldState.h"


using namespace std;

namespace Library
{
	WorldState::WorldState() :
		world(nullptr), sector(nullptr), entity(nullptr), action(nullptr), gameTime(nullptr)
	{}

	WorldState::~WorldState()
	{}

	GameTime& WorldState::GetGameTime() const
	{
		if (gameTime == nullptr)
		{
			throw exception("Attempting to get gametime before setting");
		}
		return *gameTime;
	}

	void WorldState::SetGameTime(GameTime& newGameTime)
	{
		gameTime = &newGameTime;
	}
}