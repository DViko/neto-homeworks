#include <iostream>
#include <fstream>

void dfs(size_t vertex, bool **graph, size_t vertex_count, bool *is_visited)
{
    is_visited[vertex] = true;
    std::cout << vertex + 1 << " ";

    for (size_t adjacent{}; adjacent < vertex_count; ++adjacent)
    {
        if (graph[vertex][adjacent] && !is_visited[adjacent])
        {
            dfs(adjacent, graph, vertex_count, is_visited);
        }
    }
}

int main()
{
    std::ifstream file("input.txt");

    size_t vertex_count;
    file >> vertex_count;

    bool **graph{new bool *[vertex_count]{}};

    for (size_t i{}; i < vertex_count; ++i)
    {
        graph[i] = new bool[vertex_count]{};
    }

    for (size_t i{}; i < vertex_count; ++i)
    {
        for (size_t j{}; j < vertex_count; ++j)
        {
            int temp{};

            file >> temp;
            graph[i][j] = (temp != 0);
        }
    }

    bool *visited{new bool[vertex_count]{false}};

    std::cout << "Order of traversing: ";

    dfs(0, graph, vertex_count, visited);

    std::cout << "\n";

    for (size_t i{}; i < vertex_count; ++i)
    {
        delete[] graph[i];
    }

    delete[] graph;
    delete[] visited;
}