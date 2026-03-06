#include <iostream>
#include <fstream>
#include <vector>

bool dfs(size_t vertex, size_t parent, const std::vector<std::vector<size_t>> &graph, std::vector<bool> &visited)
{
    visited[vertex] = true;

    for (size_t adjacent : graph[vertex])
    {
        if (!visited[adjacent])
        {
            if (dfs(adjacent, vertex, graph, visited))
            {
                return true;
            }
        }
        else if (adjacent != parent)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::ifstream file("input.txt");

    size_t vertex_count{};
    file >> vertex_count;

    std::vector<std::vector<size_t>> graph(vertex_count);

    for (size_t i{}; i < vertex_count; ++i)
    {
        for (size_t j{}; j < vertex_count; ++j)
        {
            int temp{};
            file >> temp;

            if (temp != 0)
            {
                graph[i].push_back(j);
            }
        }
    }

    std::vector<bool> visited(vertex_count, false);

    bool has_cycle{false};

    for (size_t i{}; i < vertex_count; ++i)
    {
        if (!visited[i])
        {
            if (dfs(i, size_t(-1), graph, visited))
            {
                has_cycle = true;
                break;
            }
        }
    }

    if (has_cycle)
    {
        std::cout << "There is a cycle in the graph!\n";
    }
    else
    {
        std::cout << "There is no cycle in the graph.\n";
    }

    return EXIT_SUCCESS;
}