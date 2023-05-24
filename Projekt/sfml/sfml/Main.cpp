// Include the SFML library
#include <SFML/Graphics.hpp>

// Define some constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GRAVITY = 9.8f;
const float BLOCK_SIZE = 50.0f;
const float ACCELERATION = 2.0f;
const float ROTATION_SPEED = 180.0f;

// Create a block class
class Block {
public:
    // Constructor
    Block(float x, float y, sf::Color color) {
        // Set the position and color of the block
        shape.setPosition(x, y);
        shape.setFillColor(color);

        // Set the size and origin of the block
        shape.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        shape.setOrigin(BLOCK_SIZE / 2, BLOCK_SIZE / 2);

        // Set the initial velocity and angle to zero
        velocity = 0.0f;
        angle = 0.0f;
    }

    // Update the block
    void update(float dt) {
        // Apply gravity to the velocity
        velocity += GRAVITY * dt;

        // Move the block according to the velocity
        shape.move(0.0f, velocity * dt);

        // Rotate the block according to the angle
        shape.rotate(angle * dt);

        // Check if the block is out of bounds and bounce it back
        if (shape.getPosition().y + BLOCK_SIZE / 2 > WINDOW_HEIGHT) {
            shape.setPosition(shape.getPosition().x, WINDOW_HEIGHT - BLOCK_SIZE / 2);
            velocity = -velocity;
        }
        if (shape.getPosition().x - BLOCK_SIZE / 2 < 0) {
            shape.setPosition(BLOCK_SIZE / 2, shape.getPosition().y);
            angle = -angle;
        }
        if (shape.getPosition().x + BLOCK_SIZE / 2 > WINDOW_WIDTH) {
            shape.setPosition(WINDOW_WIDTH - BLOCK_SIZE / 2, shape.getPosition().y);
            angle = -angle;
        }
    }

    // Draw the block
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    // Accelerate the block upwards
    void accelerate() {
        velocity -= ACCELERATION;
    }

    // Rotate the block clockwise or counterclockwise
    void rotate(bool clockwise) {
        if (clockwise) {
            angle += ROTATION_SPEED;
        }
        else {
            angle -= ROTATION_SPEED;
        }
    }

private:
    // The shape of the block
    sf::RectangleShape shape;

    // The velocity and angle of the block
    float velocity;
    float angle;
};

// Main function
int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Falling Block");

    // Create a clock to measure time
    sf::Clock clock;

    // Create a block with a random position and color
    Block block(rand() % (WINDOW_WIDTH - (int)BLOCK_SIZE), 0.0f,
        sf::Color(rand() % 256, rand() % 256, rand() % 256));

    // Main loop
    while (window.isOpen()) {
        // Get the elapsed time since last frame
        float dt = clock.restart().asSeconds();

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if requested
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle keyboard input
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Space: // Accelerate upwards with space key
                    block.accelerate();
                    break;
                case sf::Keyboard::Left: // Rotate counterclockwise with left arrow key
                    block.rotate(false);
                    break;
                case sf::Keyboard::Right: // Rotate clockwise with right arrow key
                    block.rotate(true);
                    break;
                default:
                    break;
                }
            }
        }

        // Update the block
        block.update(dt);

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw the block
        block.draw(window);

        // Display the window
        window.display();
    }

    return 0;
}
