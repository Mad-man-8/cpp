#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For non-buffered input

const int PIPE_HEIGHT = 10;
const int PIPE_GAP = 5;
const int PIPE_WIDTH = 2;
const int PIPE_DISTANCE = 20;
const int SCREEN_HEIGHT = 20;
const int SCREEN_WIDTH = 50;
const char BIRD_CHAR = '*';
const char PIPE_CHAR = '#';
const char AIR_CHAR = ' ';

class FlappyBird {
private:
    int birdPosition;
    int pipePosition;
    int score;

public:
    FlappyBird() : birdPosition(SCREEN_HEIGHT / 2), pipePosition(SCREEN_WIDTH), score(0) {}

    void jump() {
        birdPosition -= 2;
    }

    void movePipe() {
        --pipePosition;
        if (pipePosition == 0) {
            pipePosition = SCREEN_WIDTH;
            score++;
        }
    }

    bool checkCollision() {
        if (birdPosition <= 0 || birdPosition >= SCREEN_HEIGHT)
            return true;
        if (pipePosition == SCREEN_WIDTH / 2) {
            if (birdPosition - PIPE_GAP / 2 <= PIPE_HEIGHT || birdPosition + PIPE_GAP / 2 >= SCREEN_HEIGHT - PIPE_HEIGHT)
                return true;
        }
        return false;
    }

    void draw() {
        system("cls"); // Clear the screen (for Windows)
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            for (int j = 0; j < SCREEN_WIDTH; ++j) {
                if ((j == SCREEN_WIDTH / 2 - PIPE_WIDTH / 2 || j == SCREEN_WIDTH / 2 + PIPE_WIDTH / 2) && (i <= PIPE_HEIGHT || i >= SCREEN_HEIGHT - PIPE_HEIGHT))
                    std::cout << PIPE_CHAR;
                else if (j == SCREEN_WIDTH / 2 && (i > PIPE_HEIGHT && i < SCREEN_HEIGHT - PIPE_HEIGHT))
                    std::cout << AIR_CHAR;
                else if (i == birdPosition && j == SCREEN_WIDTH / 4)
                    std::cout << BIRD_CHAR;
                else
                    std::cout << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << "Score: " << score << std::endl;
    }

    int getScore() {
        return score;
    }
};

int main() {
    FlappyBird game;
    char input;
    std::srand(std::time(nullptr));

    while (true) {
        game.draw();
        std::cout << "Press 'j' to jump: ";
        input = _getch(); // Read a single character without waiting for Enter

        if (input == 'j')
            game.jump();

        game.movePipe();
    }

    return 0;
}
