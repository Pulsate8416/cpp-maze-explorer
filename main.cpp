#include <iostream>
#include <cstdlib>
#include <ctime>

// Variables to store the maze dimensions
int WIDTH;
int HEIGHT;

// Pointer to the maze array
char** maze;

// Player's current position
int playerX, playerY;

// Exit's position
int exitX, exitY;

// Function to generate the maze
void generateMaze() {
    // Allocate memory for the maze
    maze = new char*[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        maze[i] = new char[WIDTH];
        for (int j = 0; j < WIDTH; ++j) {
            // Set the borders of the maze as walls
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                maze[i][j] = '#';
            } else {
                maze[i][j] = ' ';
            }
        }
    }
    // Set the player's starting position
    playerX = 1;
    playerY = 1;
    maze[playerY][playerX] = '.';

    // Randomly place the exit within the maze
    exitX = std::rand() % (WIDTH - 2) + 1;
    exitY = std::rand() % (HEIGHT - 2) + 1;
    maze[exitY][exitX] = 'E';
}

// Function to print the maze
void printMaze() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // Print the player character if it's the player's position
            if (x == playerX && y == playerY) {
                std::cout << 'P';
            } else {
                std::cout << maze[y][x];
            }
        }
        std::cout << std::endl;
    }
}

// Function to move the player based on input
bool movePlayer(char direction) {
    int newX = playerX, newY = playerY;
    switch (direction) {
    case 'W': case 'w': newY--; break; // Move up
    case 'S': case 's': newY++; break; // Move down
    case 'A': case 'a': newX--; break; // Move left
    case 'D': case 'd': newX++; break; // Move right
    default: return false; // Invalid input
    }
    // Check if the new position is a valid move
    if (maze[newY][newX] == ' ' || maze[newY][newX] == 'E') {
        playerX = newX;
        playerY = newY;
        return true;
    }
    return false;
}

// Function to check if the player has reached the exit
bool isExitReached() {
    return playerX == exitX && playerY == exitY;
}

int main() {
    std::srand(std::time(0)); // Seed the random number generator

    // Ask the user for the maze dimensions
    std::cout << "What width would you like for the maze? ";
    std::cin >> WIDTH;
    std::cout << "What height would you like for the maze? ";
    std::cin >> HEIGHT;

    // Generate the maze
    generateMaze();

    // Main game loop
    while (true) {
        printMaze(); // Print the current state of the maze
        if (isExitReached()) {
            std::cout << "Congratulations! You've reached the exit!" << std::endl;
            break; // Exit the loop if the player has reached the exit
        }
        char input;
        std::cout << "Where would you like to move? (WASD/wasd): ";
        std::cin >> input;
        if (!movePlayer(input)) {
            std::cout << "Oops! That's an invalid move!" << std::endl;
        }
    }

    // Clean up the dynamically allocated memory
    for (int i = 0; i < HEIGHT; ++i) {
        delete[] maze[i];
    }
    delete[] maze;

    return 0;
}