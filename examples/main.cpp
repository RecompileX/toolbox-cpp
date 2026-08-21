#include <iostream>
#include <string>

#include <toolbox/toolbox.hpp>

int main() {
    toolbox::startLog();
    toolbox::info("Program started");

    const int number = toolbox::random(1, 100);
    const float value = toolbox::random(0.0f, 1.0f);

    std::cout << "Random integer: " << number << '\n';
    std::cout << "Random float: " << value << '\n';

    if (toolbox::chance(25.0f)) {
        toolbox::info("The 25% chance happened");
    }

    toolbox::Timer timer(2.0f);
    timer.update(0.016f);

    std::cout << "Timer elapsed: " << timer.elapsed() << '\n';
    std::cout << "Timer remaining: " << timer.remaining() << '\n';

    if (timer.done()) {
        timer.reset();
    }

    const int health = 72;
    const int enemyCount = 14;
    const std::string textureName = "player.png";

    toolbox::info("Player health: ", health);
    toolbox::warning("Enemy count: ", enemyCount);
    toolbox::error("Failed to load texture: ", textureName);

    return 0;
}
