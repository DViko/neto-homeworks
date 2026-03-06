#include <iostream>
#include <fstream>

void bfs(size_t start, bool **graph, size_t vertex_count, bool *is_visited)
{
    size_t *queue{new size_t[vertex_count]{}};
    size_t head{}, tail{};

    is_visited[start] = true;
    queue[tail++] = start;

    while (head != tail)
    {
        size_t vertex{queue[head++]};

        std::cout << vertex + 1 << " ";

        for (size_t adjacent{}; adjacent < vertex_count; ++adjacent)
        {
            if (graph[vertex][adjacent] && !is_visited[adjacent])
            {
                is_visited[adjacent] = true;
                queue[tail++] = adjacent;
            }
        }
    }

    delete[] queue;
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

    std::cout << "There are " << vertex_count << " vertices in the graph. Enter the starting vertex: ";

    size_t start_vertex;
    std::cin >> start_vertex;

    if (start_vertex < 1 || start_vertex > vertex_count)
    {
        std::cerr << "Invalid starting vertex.\n";
        return EXIT_FAILURE;
    }

    bool *is_visited{new bool[vertex_count]{}};

    std::cout << "Vertex order: ";

    bfs(start_vertex - 1, graph, vertex_count, is_visited);

    std::cout << "\n";

    for (size_t i{}; i < vertex_count; ++i)
    {
        delete[] graph[i];
    }

    delete[] graph;
    delete[] is_visited;
}