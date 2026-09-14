#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <queue>

std::vector<std::vector<int>> createCinGrid(std::size_t N, std::size_t M)
{
    std::vector<std::vector<int>> grid(N, std::vector<int>(M));
    for (std::size_t i = 0; i < N; ++i)
    {
        for (std::size_t j = 0; j < M; ++j)
        {
            int n;
            std::cin >> n;
            grid[i][j] = n;
        }
    }
    
    return grid;
}

void DFS(std::vector<std::vector<int>>& grid, int newColor, const std::pair<int, int>& start)
{
    const auto& [x, y] = start;
    int color = grid[x][y];
    grid[x][y] = newColor;
    std::array<std::pair<int, int>, 4> neighbors{{{x, y + 1}, {x + 1, y}, {x, y - 1}, {x - 1, y}}};
    for (const auto& neighbor : neighbors)
    {
        const auto& [i, j] = neighbor;
        if (i >= 0 && i < grid.size() && j >= 0 && j < grid.at(0).size())
        {
            if (grid[i][j] == color && grid[i][j] != newColor)
            {
                DFS(grid, newColor, neighbor);
            }
        }
    }
}

void BFS(std::vector<std::vector<int>>& grid, int newColor, const std::pair<int, int>& start)
{
    std::queue<std::pair<int, int>> nodes{};
    nodes.push(start);

    while (!nodes.empty())
    {
        const auto& [x, y] = nodes.front();
        int color = grid[x][y];
        grid[x][y] = newColor;
        std::array<std::pair<int, int>, 4> neighbors{{{x, y + 1}, {x + 1, y}, {x, y - 1}, {x - 1, y}}};

        for (const auto& neighbor : neighbors)
        {
            const auto& [i, j] = neighbor;
            if (i >= 0 && i < grid.size() && j >= 0 && j < grid.at(0).size())
            {
                if (grid[i][j] == color && grid[i][j] != newColor)
                {
                    nodes.push(neighbor);
                }
            }
        }

        nodes.pop();
    }
}

void floodFillDFS(std::vector<std::vector<int>>& grid, int newColor, const std::pair<int, int>& start)
{
    if (grid[start.first][start.second] == newColor)
    {
        return;
    }
    DFS(grid, newColor, start);
}

void floodFillBFS(std::vector<std::vector<int>>& grid, int newColor, const std::pair<int, int>& start)
{
    if (grid[start.first][start.second] == newColor)
    {
        return;
    }
    BFS(grid, newColor, start);
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    int newColor;
    std::pair<int, int> startNode;

    std::cin >> n >> m;
    std::cin >> newColor >> startNode.first >> startNode.second;

    std::vector<std::vector<int>> grid = createCinGrid(n, m);
    auto grid2 = grid;

    floodFillDFS(grid, newColor, startNode);
    floodFillBFS(grid2, newColor, startNode);

    std::cout << "\n";
    for (const auto& row : grid)
    {
        for (const auto& elem : row)
        {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    for (const auto& row : grid2)
    {
        for (const auto& elem : row)
        {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }

    return 0;
}