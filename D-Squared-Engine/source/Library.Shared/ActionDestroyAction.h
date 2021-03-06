#pragma once
#include "Action.h"


namespace Library
{
    class ActionDestroyAction : public Action
    {

    public:

#pragma region Construction/Copy/Assignment

        ActionDestroyAction();

        ~ActionDestroyAction() = default;

        ActionDestroyAction(const ActionDestroyAction& rhs) = delete;

        ActionDestroyAction& operator=(const ActionDestroyAction& rhs) = delete;

        ActionDestroyAction(ActionDestroyAction&& rhs) = delete;

        ActionDestroyAction& operator=(ActionDestroyAction&& rhs) = delete;

#pragma endregion

        /**
         * Destroys the action with the specified Name, if it exists in the hierarchy
         * @Param worldState: The world state object that stores the current mWorld state
         */
        void Update(WorldState& worldState) override;

        /**
         * Mutator method for the Name of the action being destroyed
         * @Param Name: The Name of the action being destroyed
         */
        void SetActionInstanceName(const std::string& name);

        /**
         * Accessor for the Name of the action being destroyed
         * @Return: The Name of the action being destroyed
         */
        std::string GetActionInstanceName() const;

    private:

        std::string m_actionInstanceName; // The Name of the action being destroyed

    };

    ActionFactory(ActionDestroyAction)
}