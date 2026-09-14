#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <chrono>

struct Edge
{
    int vertex, weight;

    auto operator<=>(const Edge& other) const
    {
        return weight <=> other.weight;
    }
};

std::vector<std::vector<int>> createCinGraph(std::size_t N, std::size_t M)
{
    std::vector<std::vector<int>> adjacencyList(N);
    for (std::size_t i = 0; i < M; ++i)
    {
        std::size_t a, b;
        std::cin >> a >> b;
        adjacencyList[a].push_back(b);
        adjacencyList[b].push_back(a);
    }
    
    return adjacencyList;
}

std::vector<std::vector<Edge>> createCinEdgeGraph(std::size_t N, std::size_t M)
{
    std::vector<std::vector<Edge>> adjacencyList(N);
    for (std::size_t i = 0; i < M; ++i)
    {
        std::size_t a, b, weight;
        std::cin >> a >> b >> weight;
        adjacencyList[a].emplace_back(b, weight);
        adjacencyList[b].emplace_back(a, weight);
    }
    
    return adjacencyList;
}

std::vector<int> BFS(std::vector<std::vector<int>>& adjacencyList, int start)
{
    std::vector<int> nodeDistances(adjacencyList.size(), -1);
    std::queue<int> nodes{};
    nodeDistances[start] = 0;
    nodes.push(start);

    while (!(nodes.empty()))
    {
        int parent = nodes.front();
        nodes.pop();
        for (int neighbor : adjacencyList[parent])
        {
            if (nodeDistances[neighbor] == -1)
            {
                nodes.push(neighbor);
                nodeDistances[neighbor] = nodeDistances[parent] + 1;
            }
        }
    }

    return nodeDistances;
}

std::vector<int> BFS0_1(std::vector<std::vector<Edge>>& adjacencyList, int start)
{
    std::vector<int> nodeDistances(adjacencyList.size(), -1);
    // std::vector<int> path(adjacencyList.size(), -1);
    std::deque<Edge> nodes{};
    nodeDistances[start] = 0;
    nodes.emplace_front(start, 0);

    while (!(nodes.empty()))
    {
        const auto [vertex, w] = nodes.front();
        nodes.pop_front();

        for (const auto& [neighbor, weight] : adjacencyList[vertex])
        {
            if (nodeDistances[neighbor] == -1 || nodeDistances[vertex] + weight < nodeDistances[neighbor])
            {
                nodeDistances[neighbor] = nodeDistances[vertex] + weight;
                if (weight == 0)
                {
                    nodes.emplace_front(neighbor, nodeDistances[neighbor]);
                }
                else
                {
                    nodes.emplace_back(neighbor, nodeDistances[neighbor]);
                }
            }
        }
    }
    
    return nodeDistances;
}

std::vector<int> Dijkstra(std::vector<std::vector<Edge>>& adjacencyList, int start, int target)
{
    std::vector<int> nodeDistances(adjacencyList.size(), -1);
    std::vector<int> parent(adjacencyList.size(), -1);
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> nodes{};
    nodeDistances[start] = 0;
    parent[start] = start;
    nodes.emplace(start, 0);

    while (!(nodes.empty()))
    {
        const auto [vertex, w] = nodes.top();
        nodes.pop();

        if (vertex == target)
        {
            break;
        }
        if (w > nodeDistances[vertex])
        {
            continue;
        }

        for (const auto& [neighbor, weight] : adjacencyList[vertex])
        {
            if (nodeDistances[neighbor] == -1 || nodeDistances[vertex] + weight < nodeDistances[neighbor])
            {
                nodeDistances[neighbor] = nodeDistances[vertex] + weight;
                parent[neighbor] = vertex;
                nodes.emplace(neighbor, nodeDistances[neighbor]);
            }
        }
    }
    
    return parent;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    int startNode, target;
    std::cin >> n >> m;
    std::cin >> startNode >> target;
    std::vector<std::vector<Edge>> graph = createCinEdgeGraph(n, m);

    // for (std::size_t i = 0; i < graph.size(); ++i)
    // {
    //     std::cout << i << "\t";
    //     for (const auto& connection : graph[i])
    //     {
    //         std::cout << connection << " ";
    //     }
    //     std::cout << "\n\n";
    // }

    // for (int elem : BFS0_1(graph, startNode))
    // {
    //     std::cout << elem << "\t";
    // }
    // std::cout << "\n";
    // std::cout << BFS(graph, startNode).at(target) << "\n\n";

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<int> path = Dijkstra(graph, startNode, target);

    auto endTime = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> algoDuration = endTime - startTime;
    std::cerr << algoDuration.count() << "\n";

    int curr = target;
    if (path[target] == -1 && startNode != target)
    {
        std::cout << "No path exists from " << startNode << " to " << target << "\n";
    }
    else
    {
        while (curr != startNode)
        {
            std::cout << curr << " <- ";
            curr = path[curr];
        }
        std::cout << startNode << "\n";
    }

    return 0;
}