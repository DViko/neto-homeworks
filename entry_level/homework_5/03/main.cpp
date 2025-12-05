#include <iostream>
#include <format>

int main() {

    int matrix[3][6]{
                    {9, 2, 3, 4, 12, 90},
                    {7, 50, 13, 10, 1, 12},
                    {13, -14, 40, 16, 17, 18}
    };

    const int RSIZE{sizeof(matrix) / sizeof(matrix[0])};
    const int CSIZE{sizeof(matrix[0]) / sizeof(matrix[0][0])};

    int min_point[2]{0, 0}, max_point[2]{0, 0};
    int min_value{matrix[0][0]}, max_value{matrix[0][0]};


    for (int row = 0; row < RSIZE; row ++) {

        for (int col = 0; col < CSIZE; col ++) {

            std::cout << matrix[row][col] << "\t";

            if (matrix[row][col] < min_value) {

                min_value = matrix[row][col];

                min_point[0] = row;
                min_point[1] = col;
            }

            if (matrix[row][col] > max_value) {

                max_value = matrix[row][col];

                max_point[0] = row;
                max_point[1] = col;
            }
        }

        std::cout << '\n';
    }

    std::cout << std::format("Min: row: {} col: {} value: {} \n", min_point[0], min_point[1], min_value);
    std::cout << std::format("Max: row: {} col: {} value: {} \n", max_point[0], max_point[1], max_value);

    return EXIT_SUCCESS;
}