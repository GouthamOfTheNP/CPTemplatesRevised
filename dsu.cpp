#include <iostream>
#include <vector>
#include <numeric>
#include <utility>

struct DSU
{
    std::vector<int> parent, rank;

    DSU(std::size_t n) : parent(n), rank(n, 0)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int node)
    {
        if (parent[node] == node)
        {
            return node;
        }
        return parent[node] = find(parent[node]);
    }

    bool unite(int connector, int connectee)
    {
        int orRoot = find(connector);
        int eeRoot = find(connectee);

        if (orRoot == eeRoot)
        {
            return false;
        }

        if (rank[orRoot] < rank[eeRoot])
        {
            std::swap(orRoot, eeRoot);
        }

        parent[eeRoot] = orRoot;
        if (rank[orRoot] == rank[eeRoot])
        {
            ++rank[orRoot];
        }

        return true;

    }

    bool connected(int u, int v)
    {
        return find(u) == find(v);
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t size;
    std::cin >> size;
    DSU dsu(size);

    int connector, connectee;
    while (std::cin >> connector >> connectee)
    {
        dsu.unite(connector, connectee);
        for (std::size_t i = 0; i < size; ++i)
        {
            std::cout << "Node " << i << " -> Root " << dsu.find(static_cast<int>(i)) << "\t";
        }
        std::cout << "\n\n";
    }

    std::cout << "\n";
    
    return 0;
}