#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>

struct Edge
{
    int vertex, weight;
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
    }
    
    return adjacencyList;
}

std::vector<long long> bellmanFord(std::vector<std::vector<Edge>>& adjacencyList, int start)
{
    constexpr long long INF = 1e18;
    std::vector<long long> nodeDistances(adjacencyList.size(), INF);
    nodeDistances[start] = 0;
    int N = adjacencyList.size();

    for (int i = 0; i <= N; ++i)
    {
        if (i == N)
        {
            return std::vector<long long>{};
        }

        bool notUpdated = true;
        for (int v = 0; v < N; ++v)
        {
            if (nodeDistances[v] == INF)
            {
                continue;
            }
            for (const auto& [neighbor, weight] : adjacencyList[v])
            {
                if (nodeDistances[v] + weight < nodeDistances[neighbor])
                {
                    nodeDistances[neighbor] = nodeDistances[v] + weight;
                    notUpdated = false;
                }
            }
        }

        if (notUpdated)
        {
            break;
        }
    }

    return nodeDistances;
}

std::vector<long long> SPFA(std::vector<std::vector<Edge>>& adjacencyList, int start)
{
    constexpr long long INF = 1e18;
    std::vector<long long> nodeDistances(adjacencyList.size(), INF);
    std::vector<std::size_t> iters(adjacencyList.size(), 0);
    std::queue<int> nodes{};
    std::vector<bool> inQueue(adjacencyList.size(), false);

    nodeDistances[start] = 0;
    nodes.push(start);
    inQueue[start] = true;

    while (!nodes.empty())
    {
        const auto vertex = nodes.front();
        nodes.pop();
        inQueue[vertex] = false;

        for (const auto& [neighbor, weight] : adjacencyList[vertex])
        {
            if (nodeDistances[vertex] + weight < nodeDistances[neighbor])
            {
                nodeDistances[neighbor] = nodeDistances[vertex] + weight;

                if (!inQueue[neighbor])
                {
                    nodes.push(neighbor);
                    inQueue[neighbor] = true;

                    ++iters[neighbor];
                    if (iters[neighbor] >= adjacencyList.size())
                    {
                        return std::vector<long long>{};
                    }
                }
            }
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
    
    std::vector<long long> distances = bellmanFord(graph, 0);

    if (distances.size() > 0)
    {
        for (std::size_t i = 0; i < distances.size(); ++i)
        {
            std::cout << i << "\t" << distances[i] << "\n";
        }
    }
    else
    {
        std::cout << "Negative Cycle Detected!\n";
    }

    distances = SPFA(graph, 0);

    if (distances.size() > 0)
    {
        for (std::size_t i = 0; i < distances.size(); ++i)
        {
            std::cout << i << "\t" << (distances[i] == INF ? "INF" : std::to_string(distances[i])) << "\n";
        }
    }
    else
    {
        std::cout << "Negative Cycle Detected!\n";
    }

    return 0;
}