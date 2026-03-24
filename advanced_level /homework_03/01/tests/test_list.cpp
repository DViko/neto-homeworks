#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include <stdexcept>
#include "List.hpp"

TEST_CASE("List is empty after construction", "[EmptyList]")
{
    List list{};

    REQUIRE(list.Empty() == true);
}

TEST_CASE("Clear removes all elements", "[Clear]")
{
    List list{};

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    list.Clear();

    REQUIRE(list.Empty() == true);
    REQUIRE(list.Size() == 0);
}

TEST_CASE("Reuse after Clear", "[Clear]")
{
    List list{};

    for (int i{}; i < 5; ++i)
    {
        list.PushBack(i);
    }

    list.Clear();

    list.PushBack(42);
    list.PushFront(10);

    REQUIRE(list.PopFront() == 10);
    REQUIRE(list.PopBack() == 42);
}

TEST_CASE("Clear on empty list is safe", "[Clear]")
{
    List list{};

    list.Clear();

    REQUIRE(list.Empty() == true);
    REQUIRE(list.Size() == 0);
}