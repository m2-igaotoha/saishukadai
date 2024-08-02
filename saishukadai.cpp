#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;

enum Direction { LEFT, RIGHT };

class Obstacle {
public:
    int x, y;
    Obstacle(int x, int y) : x(x), y(y) {}
};

class Game {
private:
    int width, height;
    int snakeX, snakeY;
    vector<Obstacle> obstacles;
    Direction dir;
    bool gameOver;
    int score;

public:
    Game(int w, int h) : width(w), height(h), gameOver(false), score(0) {
        snakeX = width / 2;
        snakeY = height - 1;
        dir = LEFT;
        generateObstacles();
    }

    void generateObstacles() {
        obstacles.clear();
        for (int i = 0; i < width; i += 3) {
            obstacles.push_back(Obstacle(i, 0));
        }
    }

    void draw() {
        system("cls");
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == snakeY && j == snakeX) {
                    cout << "☆";
                }
                else if (isObstacle(j, i)) {
                    cout << "×";
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << "Score: " << score << endl;
    }

    bool isObstacle(int x, int y) {
        return any_of(obstacles.begin(), obstacles.end(), [x, y](Obstacle& obs) { return obs.x == x && obs.y == y; });
    }

    void input() {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            dir = LEFT;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            dir = RIGHT;
        }
    }

    void logic() {
        // Move snake
        switch (dir) {
        case LEFT: snakeX--; break;
        case RIGHT: snakeX++; break;
        }

        // Boundary check
        if (snakeX < 0) snakeX = 0;
        if (snakeX >= width) snakeX = width - 1;

        // Move obstacles down
        for (auto& obs : obstacles) {
            obs.y++;
            if (obs.y >= height) {
                obs.y = 0;
                obs.x = rand() % width;
                score++;
            }
        }

        // Collision check
        if (isObstacle(snakeX, snakeY)) {
            gameOver = true;
        }
    }

    bool isGameOver() const {
        return gameOver;
    }
};

int main() {
    Game game(20, 20);

    while (!game.isGameOver()) {
        game.draw();
        game.input();
        game.logic();
        Sleep(100);
    }

    cout << "Game Over!" << endl;
    Sleep(2000); // 2秒待つ
 }