#pragma once

#include "core/array_transformer.h"
#include "core/sorting_transformer.h"

namespace at
{
    template <typename Container>
    class IntersectionTransformer : public ArrayTransformer<Container>
    {
    public:
        Container transform(const Container& input) override
        {
            SortingTransformer<Container> sortingTransformer;
            Container sortedArrays = sortingTransformer.transform(input);

            manualSortArrays(sortedArrays);

            typename Container::value_type intersectionTwoBig = findIntersection(
                sortedArrays.begin()->begin(), sortedArrays.begin()->end(),
                (sortedArrays.begin() + 1)->begin(), (sortedArrays.begin() + 1)->end()
            );

            typename Container::value_type intersectionAll = *sortedArrays.begin();
            auto end = sortedArrays.end();
            for (auto iter = sortedArrays.begin(); iter != end; ++iter)
            {
                intersectionAll = findIntersection(
                    intersectionAll.begin(), intersectionAll.end(),
                    iter->begin(), iter->end()
                );
            }

            Container intersection;
            intersection.insert(intersection.end(), intersectionTwoBig);
            intersection.insert(intersection.end(), intersectionAll);

            return intersection;
        }
    private:

        void manualSortArrays(Container& input)
        {
            auto end = input.end();
            for (auto iterI = input.begin(); iterI != end; ++iterI)
            {
                for (auto iterJ = input.begin(); iterJ != iterI; ++iterJ)
                {
                    if (iterI->size() > iterJ->size())
                    {
                        auto tempIterator = *iterI;
                        *iterI = *iterJ;
                        *iterJ = tempIterator;
                    }
                }
            }
        }

        typename Container::value_type findIntersection(
            typename Container::value_type::const_iterator beginFirst,
            typename Container::value_type::const_iterator endFirst,
            typename Container::value_type::const_iterator beginSecond,
            typename Container::value_type::const_iterator endSecond)
        {
            typename Container::value_type intersectionBetweenTwo;

            while (beginFirst != endFirst && beginSecond != endSecond)
            {
                if (*beginFirst < *beginSecond)
                {
                    ++beginFirst;
                }
                else if (*beginSecond < *beginFirst)
                {
                    ++beginSecond;
                }
                else
                {
                    intersectionBetweenTwo.insert(intersectionBetweenTwo.end(), *beginFirst);
                    ++beginFirst;
                    ++beginSecond;
                }
            }

            return intersectionBetweenTwo;
        }
    };
};
