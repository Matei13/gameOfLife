#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class GameOfLife
{
public:
    // Outputs a game of life with living cells with proba p
    // then runs it.
    GameOfLife(int rows, int columns, double p) :
    rows(rows),
    columns(columns)
    {
        size = columns*rows;
        for (auto i = 0; i < size; ++i)
            game.push_back(random() < p);
        run();
    }

private:
    // outputs a random number in [0, 1)
    double random()
    {
        return double(rand()) / (double(RAND_MAX) + 1.0);
    }

    // count of living neighbours of (i, j)
    auto livingNeighbours(int i, int j)
    {
        return game[i + (j + 1)%columns]
             + game[i + (j - 1 + columns)%columns]
             + game[(i + columns)%size + j]
             + game[(i - columns + size)%size + j]
             + game[(i + columns)%size + (j + 1)%columns]
             + game[(i + columns)%size + (j - 1 + columns)%columns]
             + game[(i - columns + size)%size + (j + 1)%columns]
             + game[(i - columns + size)%size + (j - 1 + columns)%columns];
    }

    void run()
    {
        std::vector<bool> temp(size);
        while (true)
        {
            print();
            for (auto i = 0; i < size; i+=columns)
            {
                for (auto j = 0; j < columns; ++j)
                {
                    auto state = game[i + j];
                    auto living = livingNeighbours(i, j);
                    if (!state)
                        temp[i + j] = living == 3;
                    else
                        temp[i + j] = living == 2 || living == 3;
                }
            }
            std::swap(game, temp);
            std::this_thread::sleep_for(std::chrono::milliseconds(750));
        }
    }

    void print()
    {
        for (auto i = 0; i < size; i+=columns)
        {
            for (auto j = 0; j < columns; ++j)
                std::cout << (game[i + j] ? '0' : ' ');
            std::cout << '\n';
        }
        std::cout << std::endl;
        for (auto i = 0; i <= rows; ++i) {
            std::cout << "\e[A";
        }
    }

    std::vector<bool> game;
    int rows;
    int columns;
    int size;
};

int main(int, char** argv)
{
    GameOfLife game(std::stoi(argv[1]), std::stod(argv[2]), std::stod(argv[3]));
}