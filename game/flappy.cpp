

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PIPE_WIDTH = 80;
const int PIPE_HEIGHT = 500;
const int PIPE_GAP = 200;
const float GRAVITY = 0.3f;
const float JUMP_FORCE = -7.0f;

class Bird {
private:
    sf::CircleShape shape;
    float velocity;

public:
    Bird(float x, float y) : velocity(0) {
        shape.setRadius(20);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x, y);
    }

    void jump() {
        velocity = JUMP_FORCE;
    }

    void update() {
        velocity += GRAVITY;
        shape.move(0, velocity);
    }

    sf::CircleShape& getShape() {
        return shape;
    }

    float getY() {
        return shape.getPosition().y;
    }
};

class Pipe {
private:
    sf::RectangleShape topPipe;
    sf::RectangleShape bottomPipe;

public:
    Pipe(float x) {
        topPipe.setSize(sf::Vector2f(PIPE_WIDTH, PIPE_HEIGHT));
        bottomPipe.setSize(sf::Vector2f(PIPE_WIDTH, PIPE_HEIGHT));
        topPipe.setFillColor(sf::Color::Green);
        bottomPipe.setFillColor(sf::Color::Green);
        topPipe.setPosition(x, -PIPE_HEIGHT - PIPE_GAP);
        bottomPipe.setPosition(x, WINDOW_HEIGHT);
    }

    void move(float dx) {
        topPipe.move(dx, 0);
        bottomPipe.move(dx, 0);
    }

    sf::RectangleShape& getTopPipe() {
        return topPipe;
    }

    sf::RectangleShape& getBottomPipe() {
        return bottomPipe;
    }

    float getX() {
        return topPipe.getPosition().x;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird");
    Bird bird(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
    sf::Clock clock;
    std::vector<Pipe> pipes;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setPosition(20, 20);
    int score = 0;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("flap.wav")) {
        std::cerr << "Failed to load sound\n";
        return 1;
    }
    sf::Sound flapSound;
    flapSound.setBuffer(buffer);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    bird.jump();
                    flapSound.play();
                }
            }
        }

        if (clock.getElapsedTime().asSeconds() > 1.5f) {
            pipes.emplace_back(WINDOW_WIDTH);
            clock.restart();
        }

        for (size_t i = 0; i < pipes.size(); ++i) {
            pipes[i].move(-1.0f);
            if (pipes[i].getX() + PIPE_WIDTH < 0) {
                pipes.erase(pipes.begin() + i);
                ++score;
                break;
            }
        }

        bird.update();

        for (const auto& pipe : pipes) {
            if (bird.getShape().getGlobalBounds().intersects(pipe.getTopPipe().getGlobalBounds()) ||
                bird.getShape().getGlobalBounds().intersects(pipe.getBottomPipe().getGlobalBounds()) ||
                bird.getY() + 2 * bird.getShape().getRadius() > WINDOW_HEIGHT ||
                bird.getY() < 0) {
                std::cout << "Game Over! Score: " << score << std::endl;
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (const auto& pipe : pipes) {
            window.draw(pipe.getTopPipe());
            window.draw(pipe.getBottomPipe());
        }
        window.draw(bird.getShape());
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        window.display();
    }

    return 0;
}

