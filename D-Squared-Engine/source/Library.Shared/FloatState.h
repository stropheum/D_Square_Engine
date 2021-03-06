#pragma once
#include "TypeState.h"


namespace Library
{
    class FloatState : public TypeState
    {

    public:

#pragma region Construction/Copy/Assignment

        explicit FloatState(Datum& context);

        FloatState(const FloatState& rhs) = delete;

        FloatState& operator=(const FloatState& rhs) = delete;

        FloatState(FloatState&& rhs) = delete;

        FloatState& operator=(FloatState&& rhs) = delete;

#pragma endregion

        /**
         * Comparison operator for Datum objects
         * @Param rhs: The Datum object being compared against
         * @Return: True if Type, Size, and each element of the Datum objects are equivalent. False otherwise
         */
        bool operator==(const Datum& rhs) override;

        /**
         * Scalar assignment operator
         * @Param rhs: The float being Set to the only element in the Datum
         * @Return: The modified Datum object
         */
        Datum& operator=(const float& rhs) override;

        /**
         * Reserves the number of floats in the local buffer
         * @Param Capacity: The current maximum Size of the array
         */
        void SetSize(const std::uint32_t& size) override;

        /**
         * Modifies the Capacity of the array to any value greater than or equal to current Size
         * @Param Capacity: The new Capacity of the array
         */
        void Reserve(const std::uint32_t& capacity) override;

        /**
         * Clears the value of all elements in the array without changing Capacity
         */
        void Clear() override;

        /**
         * Parses a string value and assigns the specified index of the array to its value
         * @Param value: The string value being parsed
         * @Param index: The index of the array being assigned to
         */
        void SetFromString(const std::string& value, const std::uint32_t& index) override;

        /**
         * Sets external storage on copy
         * @Param rhs: The Datum object that the storage reference is being taken from
         */
        void SetStorage(const Datum& rhs) override;

        /**
         * Sets the external storage to the specified pointer
         * @Param data: The external storage being utilized
         * @Pram Size: The number of elements in the external storage
         * @Exception: Thrown if attempting to reassign datum Type, or if local memory is already used
         */
        void SetStorage(float* data, const std::uint32_t& size) override;

        /**
         * A string representation of a piece of data stored in the Datum object
         * @Param index: Optional index of the value being retrieved. Defaulted to first element
         */
        std::string ToString(const std::uint32_t& index = 0) override;

    };
}