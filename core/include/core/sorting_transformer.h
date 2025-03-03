#pragma once

#include "core/array_transformer.h"

namespace at
{
    template <typename Container>
    class SortingTransformer : public ArrayTransformer<Container>
    {
    public:
        Container transform(const Container& input) override
        {
            Container sorted = input;
            auto end = sorted.end();
            for (auto iter = sorted.begin(); iter != end; ++iter)
            {
                sort(iter->begin(), iter->end());
            }
            return sorted;
        }

    private:
        template <typename Iterator>
        void sort(Iterator begin, Iterator end)
        {
            bool swapped;
            for (auto iterI = begin; iterI != end; ++iterI)
            {
                swapped = false;
                for (auto iterJ = begin; iterJ < end - 1 - (iterI - begin); ++iterJ)
                {
                    if (*iterJ > *(iterJ + 1))
                    {
                        swap(*iterJ, *(iterJ + 1));
                        swapped = true;
                    }
                }
                if (!swapped) break;
            }
        }

        template <typename Iterator>
        void swap(Iterator& first, Iterator& second)
        {
            Iterator tempIterator = first;
            first = second;
            second = tempIterator;
        }
    };
}
