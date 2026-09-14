#include <iostream>
#include <map>
#include <utility>

std::map<int, int> initialize(int size)
{
    std::map<int, int> parent;
    for (int i = 0; i < size; ++i)
    {
        parent[i] = i;
    }

    return parent;
}

int find(std::map<int, int>& parent, int node)
{
    if (parent[node] == node)
    {
        return node;
    }
    parent[node] = find(parent, parent[node]);
    return parent[node];
}

void DSU(std::map<int, int>& parent, int connector, int connectee)
{
    int orRoot = find(parent, connector);
    if (!parent.contains(connectee))
    {
        parent[connectee] = orRoot;
    }
    else
    {
        int eeRoot = find(parent, connectee);
        if (orRoot != eeRoot)
        {
            parent[eeRoot] = orRoot;
        }
    }

}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;
    std::map<int, int> set = initialize(size);

    int connector, connectee;
    while (std::cin >> connector >> connectee)
    {
        DSU(set, connector, connectee);
        for (const auto& [node, parent] : set)
        {
            if (node != parent)
            {
                std::cout << parent << " -> " << node << "\t";
            }
        }
        std::cout << "\n\n";
    }

    std::cout << "\n";
    
    return 0;
}