#include <cstddef>
#include <iostream>
#include <stack>
#include <vector>

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

bool DFSIter(std::vector<std::vector<int>>& adjacencyList, int start, int node1, int node2)
{
    std::stack<std::pair<int, std::size_t>> current;
    std::vector<bool> visited(adjacencyList.size());

    visited[start] = true;
    current.push({start, 0});

    while (!current.empty())
    {
        auto& [prev, curr] = current.top();
        if (curr == adjacencyList[prev].size())
        {
            current.pop();
            continue;
        }

        int neighbor = adjacencyList[prev][curr++];
        if ((prev == node1 && neighbor == node2) || (prev == node2 && neighbor == node1))
        {
            return true;
        }

        if (!visited[neighbor])
        {
            visited[neighbor] = true;
            current.push({neighbor, 0});
        }
    }
    
    return false;
}

bool DFS(std::vector<std::vector<int>>& adjacencyList, std::vector<bool>& visited, const int& start, const int& node1, const int& node2)
{
    for (int neighbor : adjacencyList[start])
    {
        if ((start == node1 && neighbor == node2) || (start == node2 && neighbor == node1))
        {
            return true;
        }
        if (!visited[neighbor])
        {
            visited[neighbor] = true;
            if (DFS(adjacencyList, visited, neighbor, node1, node2))
            {
                return true;
            }
        }
    }

    return false;
}

bool DFSRecur(std::vector<std::vector<int>>& adjacencyList, int start, int node1, int node2)
{
    std::vector<bool> visited(adjacencyList.size());
    visited[start] = true;
    if (DFS(adjacencyList, visited, start, node1, node2))
    {
        return true;
    }
    return false;
}

bool ColorDFS(std::vector<std::vector<int>>& adjacencyList, std::vector<int>& color, const int& start) 
{
    for (int neighbor : adjacencyList[start])
    {
        if (color[neighbor] == 0)
        {
            color[neighbor] = -color[start];
            if (!(ColorDFS(adjacencyList, color, neighbor)))
            {
                return false;
            }
        }
        else if (color[neighbor] == color[start])
        {
            return false;
        }
    }

    return true;
}

bool IsBipartite(std::vector<std::vector<int>>& adjacencyList, int start)
{
    std::vector<int> color(adjacencyList.size(), 0);

    color[start] = 1;
    if (!ColorDFS(adjacencyList, color, start))
    {
        return false;
    }

    for (int i = 0; i < adjacencyList.size(); ++i)
    {
        if (color[i] == 0)
        {
            color[i] = 1;
            if (!ColorDFS(adjacencyList, color, i))
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    int startNode, u, v;
    std::cin >> n >> m;
    std::cin >> startNode >> u >> v;
    std::vector<std::vector<int>> graph = createCinGraph(n, m);

    std::cout << "Iterative DFS: " << std::boolalpha << DFSIter(graph, startNode, u, v) << "\n";
    std::cout << "Recursive DFS: " << std::boolalpha << DFSRecur(graph, startNode, u, v) << "\n\n";
    std::cout << "Is Bipartite: " << std::boolalpha << IsBipartite(graph, startNode) << "\n\n";

    return 0;
}