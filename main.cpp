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


// 21/ENG/016 - B.Anchuthan
void Game::reveal_loc(int rows, int columns) {
    if (mines[rows][columns]) {
        cout << "Mission Failed! You triggered a mine." << endl;
        display();
        exit(0);
    }

    if (field[rows][columns] == 'c') {
        int neighbor_mines = count_neighbor_mines(rows, columns);
        if (neighbor_mines == 0) {
            field[rows][columns] = '.';
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int new_row = rows + i;
                    int new_column = columns + j;
                    if (new_row >= 0 && new_row < size_of_grid && new_column >= 0 && new_column < size_of_grid) {
                        reveal_loc(new_row, new_column);
                    }
                }
            }
        } else {
            field[rows][columns] = '0' + neighbor_mines;
        }
    }
}

void Game::place_flag(int rows, int columns) {
    if (field[rows][columns] == 'c') {
        field[rows][columns] = 'F';
        --flags_count;
    } else {
        cout << "Invalid move! Flags can only be placed on covered tiles." << endl<<endl;
    }
}

bool Game::is_Win() {
    for (int i = 0; i < size_of_grid; ++i) {
        for (int j = 0; j < size_of_grid; ++j) {
            if (mines[i][j] && field[i][j] != 'F') {
                return false;
            }
        }
    }
    return true;
}

int Game::count_neighbor_mines(int rows, int columns) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int new_row = rows + i;
            int new_column = columns + j;
            if (new_row >= 0 && new_row < size_of_grid && new_column >= 0 && new_column < size_of_grid) {
                if (mines[new_row][new_column]) {
                    ++count;
                }
            }
        }
    }
    return count;
}

// 21/ENG/091 - N.Mathuwanthi
void Game::play() {
    mines_place();

    while (true) {
        display();
        cout << "\nFlags remaining : " << flags_count << endl;
        cout << "\nEnter your move in the format - <Row><Column><Operation>\nF for flag and R for reveal (Example - ABF)" << endl;
        cout << "\nEnter your move : ";
        string move_inp;
        cin >> move_inp;
        transform(move_inp.begin(), move_inp.end(), move_inp.begin(), ::toupper);

        cout<<endl;

        if (move_inp.size() != 3) {
            cout << "Error : Enter a valid move!" << endl<<endl;
            continue;
        }

        int rows = move_inp[0] - 'A';
        int columns = move_inp[1] - 'A';

        if (rows < 0 || rows >= size_of_grid || columns < 0 || columns >= size_of_grid) {
            cout << "Error : Enter a valid move!" << endl<<endl;
            continue;
        }

        char operation = move_inp[2];

        if (operation == 'F') {
            place_flag(rows, columns);
        } else if (operation == 'R') {
            reveal_loc(rows, columns);
        } else {
            cout << "Error : Enter a valid move!" << endl<<endl;
            continue;
        }
        if (is_Win()) {
            cout << "Victory! You have successfully conquered the game." << endl;
            break;
        }
    }
}

int main() {
    int option;
	do{
        cout << "---------------------------------------------------------------" << endl;
        cout<<"\t\t\tMineSweeper"<<endl;
        cout << "---------------------------------------------------------------" << endl;
        cout<<"\nSelect The Field Option:\n1. 10-by-10 - 12 Mines\n2. 15-by-15 - 18 Mines\n3. 20-by-20 - 24 Mines"<<endl<<endl;
        cout<<"Enter Your Choice : ";
        cin>>option;
        cout<<endl;
        if (option == 1) {
            Game game(10, 12);
            game.play();
        } else if (option == 2) {
            Game game(15, 18);
            game.play();
        } else if (option == 3) {
            Game game(20, 24);
            game.play();
        } else {
            cout << "Error : Select a valid field option!\n" << endl;
        }
	}while(option!=4);
    return 0;
}
