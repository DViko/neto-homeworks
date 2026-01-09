#pragma once

#include <cstddef>

#define LEAVER_API __attribute__((visibility("default")))


extern "C" LEAVER_API void SayGoodbye(const char* string, size_t length);

class Leaver
{
    public:

        void SayGoodbye(const char* string, size_t length) const;
};