/******************************************
Quest 10 - Programming Quest
Group Members
	- 21/ENG/016 - B.Anchuthan
	- 21/ENG/087 - M.S.S.Rahuman
	- 21/ENG/091 - N.Mathuwanthi
*******************************************/

// 21/ENG/087 - M.S.S.Rahuman
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;

class Game {
private:
    int size_of_grid;
    int no_of_mines;
    vector<vector<char> > field;
    vector<vector<bool> > mines;
    int flags_count;

public:
    Game(int size, int num_mines);
    void display();
    void mines_place();
    void reveal_loc(int rows, int columns);
    void place_flag(int rows, int columns);
    bool is_Win();
    void play();
    int count_neighbor_mines(int rows, int columns);
};

Game::Game(int size, int num_mines) : size_of_grid(size), no_of_mines(num_mines), flags_count(num_mines) {
    field.resize(size_of_grid, vector<char>(size_of_grid, 'c'));
    mines.resize(size_of_grid, vector<bool>(size_of_grid, false));
    srand(static_cast<unsigned>(time(0)));
}


void Game::display() {
    cout << "  ";
    for (int i = 0; i < size_of_grid; ++i) {
        cout << static_cast<char>('A' + i) << " ";
    }
    cout << endl;

    for (int i = 0; i < size_of_grid; ++i) {
        cout << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < size_of_grid; ++j) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

void Game::mines_place() {
    int placed_mines = 0;
    while (placed_mines < no_of_mines) {
        int rows = rand() % size_of_grid;
        int columns = rand() % size_of_grid;
        if (!mines[rows][columns]) {
            mines[rows][columns] = true;
            ++placed_mines;
        }
    }
}