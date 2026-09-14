#include <iostream>
#include <vector>
#include <random>

std::vector<int> subarraySum(const std::vector<int>& vect, int sum)
{
    int total = 0;

    for (std::size_t first = 0, second = 0; second < vect.size(); ++second)
    {
        total += vect[second];
        while (total > sum && first < second)
        {
            total -= vect[first++];
        }

        if (total == sum)
        {
            return std::vector<int>(vect.begin() + first, vect.begin() + second + 1);
        }
    }
     
    return std::vector<int>{};
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 100);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> array; 
    
    for (int j = 1; j <= 100; ++j)
    {
        for (int i = 0; i < distrib(gen); ++i)
        {
            array.push_back(distrib(gen));
        }
        
        std::vector<int> subarray = subarraySum(array, distrib(gen));
        if (subarray.size() > 0)
        {
            for (int i : subarray)
            {
                std::cout << i << "\t";
            }
        }
        else
        {
            std::cout << "Attempt: " << j;
        }
        
        std::cout << "\n";

        array.clear();
    }

    return 0;
}