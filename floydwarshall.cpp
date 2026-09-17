#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

struct Edge
{
    int vertex, weight;

    auto operator<=>(const Edge& other) const
    {
        return weight <=> other.weight;
    }
};

std::vector<std::vector<Edge>> createCinEdgeGraph(std::size_t N, std::size_t M)
{
    std::vector<std::vector<Edge>> adjacencyList(N);
    for (std::size_t i = 0; i < M; ++i)
    {
        std::size_t a, b;
        int weight;
        std::cin >> a >> b >> weight;
        adjacencyList[a].emplace_back(b, weight);
        adjacencyList[b].emplace_back(a, weight);
    }

    return adjacencyList;
}

std::vector<std::vector<long long>> floydWarshall(const std::vector<std::vector<Edge>>& adjacencyList)
{
    constexpr long long INF = 1e17;
    const std::size_t N = adjacencyList.size();
    std::vector<std::vector<long long>> nodeDistances(N, std::vector<long long>(N, INF));

    for (std::size_t i = 0; i < N; ++i)
    {
        nodeDistances[i][i] = 0;
        for (const auto& [neighbor, weight] : adjacencyList[i])
        {
            nodeDistances[i][neighbor] = std::min(nodeDistances[i][neighbor], static_cast<long long>(weight));
        }
    }

    for (std::size_t k = 0; k < N; ++k)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            for (std::size_t j = 0; j < N; ++j)
            {
                if (nodeDistances[i][k] < INF && nodeDistances[k][j] < INF)
                {
                    nodeDistances[i][j] = std::min(nodeDistances[i][j], nodeDistances[i][k] + nodeDistances[k][j]);
                }
            }
        }
    }

    for (std::size_t i = 0; i < N; ++i)
    {
        if (nodeDistances[i][i] < 0)
        {
            return std::vector<std::vector<long long>>();
        }
    }

    return nodeDistances;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr long long INF = 1e17;

    std::size_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> graph = createCinEdgeGraph(n, m);

    std::vector<std::vector<long long>> distances = floydWarshall(graph);

    if (distances.size() > 0)
    {
        std::cout << "\t";
        for (std::size_t i = 0; i < distances.size(); ++i)
        {
            std::cout << i << "\t";
        }
        std::cout << "\n";

        for (std::size_t i = 0; i < distances.size(); ++i)
        {
            std::cout << i << "\t";
            for (long long distance : distances[i])
            {
                std::cout << (distance == INF ? "INF" : std::to_string(distance)) << "\t";
            }
            std::cout <<"\n";
        }
    }
    else
    {
        std::cout << "Negative Cycle Detected!" << "\n";
    }

    return 0;
}