#pragma once

#include "array_transformer.h"

namespace at
{
    template <typename Container>
    class UniqueReverseTransformer : public ArrayTransformer<Container>
    {
    public:
        Container transform(const Container& input) override
        {
            Container uniqueReverseArrays;

            typename Container::value_type mergedReverseArray;
            for (const auto& array : input)
            {
                mergedReverseArray.insert(mergedReverseArray.end(), array.begin(), array.end());
            }

            reverseSort(mergedReverseArray);

            uniqueReverseArrays.insert(uniqueReverseArrays.end(), getUniqueElements(mergedReverseArray));

            return uniqueReverseArrays;
        }

    private:

        typename Container::value_type getUniqueElements(const typename Container::value_type& input)
        {
            typename Container::value_type uniqueElements;

            for (const auto& element : input)
            {
                if (!contains(uniqueElements, element))
                {
                    uniqueElements.insert(uniqueElements.end(), element);
                }
            }

            return uniqueElements;
        }

        void reverseSort(typename Container::value_type& input)
        {
            auto end = input.end();
            for (auto iterI = input.begin(); iterI != end; ++iterI)
            {
                for (auto iterJ = input.begin(); iterJ != iterI; ++iterJ)
                {
                    if (*iterI > *iterJ)
                    {
                        auto tempIterator = *iterI;
                        *iterI = *iterJ;
                        *iterJ = tempIterator;
                    }
                }
            }
        }

        bool contains(const typename Container::value_type& input, const typename Container::value_type::value_type& value)
        {
            for (const auto& item : input)
            {
                if (item == value)
                {
                    return true;
                }
            }
            return false;
        }
    };
}