#include <iostream>
#include <fstream>

void dfs(size_t vertex, size_t component_id, bool **graph, size_t vertex_count, size_t *components)
{
    components[vertex] = component_id;

    for (size_t adjacent{}; adjacent < vertex_count; ++adjacent)
    {
        if (graph[vertex][adjacent] && components[adjacent] == 0)
        {
            dfs(adjacent, component_id, graph, vertex_count, components);
        }
    }
}

int main()
{
    std::ifstream file("input.txt");

    size_t vertex_count{};
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

    size_t *components{new size_t[vertex_count]{0}};

    size_t component_id = 0;

    for (size_t i{}; i < vertex_count; ++i)
    {
        if (components[i] == 0)
        {
            ++component_id;
            dfs(i, component_id, graph, vertex_count, components);
        }
    }

    std::cout << "Belonging of vertices to connectivity components:\n";

    for (size_t i{}; i < vertex_count; ++i)
    {
        std::cout << i + 1 << " - " << components[i] << "\n";
    }

    std::cout << "Number of connectivity components in the graph: " << component_id << "\n";

    for (size_t i{}; i < vertex_count; ++i)
    {
        delete[] graph[i];
    }

    delete[] graph;
    delete[] components;
}