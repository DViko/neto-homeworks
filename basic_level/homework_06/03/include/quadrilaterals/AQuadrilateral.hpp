#ifndef AQUADRILATERAL_HPP
#define AQUADRILATERAL_HPP

#include "base/IShape.hpp"
#include <array>
#include <string>

class AQuadrilateral : public IShape
{
    private:

        std::string _name;
        std::array<int,4> _edges;
        std::array<int,4> _angles;

        bool _Check(int a, int b, int c, int d, int A, int B, int C, int D) const;

    protected:

        AQuadrilateral(const std::string& name, int a, int b, int c, int d, int A, int B, int C, int D);

    public:

        void Description() const override;
};

#endif