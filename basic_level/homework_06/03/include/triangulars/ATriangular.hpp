#ifndef ATRIANGULAR_HPP
#define ATRIANGULAR_HPP

#include "base/IShape.hpp"
#include <array>
#include <string>

class ATriangular : public IShape
{
    private:

        std::string _name;
        std::array<int,3> _edges;
        std::array<int,3> _angles;

        bool _Check(int a, int b, int c, int A, int B, int C) const;

    protected:

        ATriangular(const std::string& name, int a, int b, int c, int A, int B, int C);

    public:

        void Description() const override;
};

#endif