#pragma once
#include "Attributed.h"


namespace Library
{
	class World;

	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:

#pragma region Construction/Copy/Assignment

		Sector();

		~Sector() = default;

		Sector(const Sector& rhs) = delete;

		Sector* operator=(const Sector& rhs) = delete;

		Sector(Sector&& rhs) = delete;

		Sector* operator=(Sector&& rhs) = delete;

#pragma endregion

		/**
		 * Accessor method for the Name of the sector
		 * @Return: The Name of the sector
		 */
		std::string Name() const;

		/**
		 * Mutator method for the Name of the sector
		 * @Param Name: The new Name of the sector
		 */
		void SetName(const std::string& name);

		/**
		 * Accessor method for the Entities datum in the sector
		 * @Return: A datum reference of the collection of Entities in the sector
		 */
		Datum& Entities();

		/**
		 * Method for adding Entities to the sector
		 * @Param ClassName: The Name of the base class being instantiated
		 * @Param instanceName: The Name that the entity will be instantiated with
		 * @Return: A freshly instantiated entity object
		 */
		class Entity* CreateEntity(const std::string& className, const std::string& instanceName);

		/**
		 * Mutator method which allows the sector to be adopted into another world
		 * @Param world: The new world where this sector will live
		 */
		void SetWorld(World& world);

		/**
		 * Accessor method for the world that this sector lives in
		 * @Return: A reference to the world that this sector lives in
		 */
		World& GetWorld() const;

		/**
		 * Update method for handling change of game state
		 * @Param worldState: The object that contains the world state data
		 */
		void Update(class WorldState& worldState);

	private:

		std::string mName;
	};
}
