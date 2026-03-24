#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include <stdexcept>
#include "List.hpp"

TEST_CASE("PopFront throws on empty list", "[EmptyList]")
{
    List list{};

    REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
}

TEST_CASE("PopBack throws on empty list", "[EmptyList]")
{
    List list{};

    REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
}

TEST_CASE("PushFront, PopFront increments and decrements size.", "[ListSize]")
{
    List list{};

    list.PushFront(10);
    list.PushFront(20);

    REQUIRE(list.Size() == 2);

    list.PopFront();

    REQUIRE(list.Size() == 1);
}

TEST_CASE("PushBack, PopBack increments and decrements size.", "[ListSize]")
{
    List list{};

    list.PushBack(20);
    list.PushBack(30);

    REQUIRE(list.Size() == 2);

    list.PopBack();

    REQUIRE(list.Size() == 1);
}

TEST_CASE("PopFront returns correct value", "[Pop]")
{
    List list{};

    list.PushFront(10);
    list.PushFront(20);

    int value{list.PopFront()};

    REQUIRE(value == 20);
    REQUIRE(list.Size() == 1);
}

TEST_CASE("PopBack returns correct value", "[Pop]")
{
    List list{};

    list.PushBack(10);
    list.PushBack(20);

    int value{list.PopBack()};

    REQUIRE(value == 20);
    REQUIRE(list.Size() == 1);
}

TEST_CASE("PushBack adds elements in correct order", "[Push]")
{
    List list{};

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    REQUIRE(list.PopFront() == 1);
    REQUIRE(list.PopFront() == 2);
    REQUIRE(list.PopFront() == 3);
}

TEST_CASE("PushFront adds elements in correct order", "[Push]")
{
    List list{};

    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);

    REQUIRE(list.PopFront() == 3);
    REQUIRE(list.PopFront() == 2);
    REQUIRE(list.PopFront() == 1);
}

TEST_CASE("Complex usage", "[Complex]")
{
    List list{};

    list.PushBack(1);
    list.PushBack(2);
    list.PushFront(0);
    list.PushBack(3);

    REQUIRE(list.PopFront() == 0);
    REQUIRE(list.PopBack() == 3);

    list.PushFront(10);

    REQUIRE(list.PopFront() == 10);
    REQUIRE(list.PopFront() == 1);
    REQUIRE(list.PopFront() == 2);
}