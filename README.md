# Toolbox C++

A small, header-only C++17 utility library for reusable helpers across normal C++ and game projects.

The library intentionally stays lightweight and depends only on the C++ standard library.

## Install

Copy the `include/toolbox` directory into your project and add its parent `include` directory to your compiler's include path.

Then include the main header:

```cpp
#include <toolbox/toolbox.hpp>
```

The public API lives in the `toolbox` namespace.

## Random numbers

```cpp
int number = toolbox::random(1, 100);
float value = toolbox::random(0.0f, 1.0f);
```

Integer ranges are inclusive. If `min > max`, the bounds are swapped automatically.

Floating-point bounds must be finite. Invalid non-finite bounds throw `std::invalid_argument`.

## Chance

```cpp
if (toolbox::chance(25.0f)) {
    // Happens roughly 25% of the time.
}
```

Percentages at or below `0` always return `false`. Percentages at or above `100` always return `true`.

## Timer

The timer is independent of Raylib. Pass it delta time once per frame:

```cpp
toolbox::Timer spawnTimer(3.0f);

spawnTimer.update(deltaTime);

if (spawnTimer.done()) {
    spawnEnemy();
    spawnTimer.reset();
}
```

With Raylib, `deltaTime` can simply be `GetFrameTime()`.

`elapsed()` returns elapsed time and `remaining()` never returns less than `0.0f`.

Invalid durations are treated as `0.0f`. Invalid or negative delta times are ignored.

## Logging

Logging writes to `debug.log` by default and flushes every message:

```cpp
toolbox::info("Program started");
toolbox::warning("Enemy count: ", enemyCount);
toolbox::error("Failed to load texture: ", textureName);
```

Messages look like:

```text
[18:52:31] [INFO] Program started
[18:52:34] [WARNING] Enemy count: 14
```

Logging appends by default. To start a new log for each program run:

```cpp
toolbox::startLog();
```

Or choose a different filename:

```cpp
toolbox::startLog("game.log");
```

If the file cannot be opened, the logger writes the failure and message to `std::cerr` instead of crashing.

## Complete example

```cpp
#include <toolbox/toolbox.hpp>

int main() {
    toolbox::startLog();
    toolbox::info("Program started");

    int number = toolbox::random(1, 100);
    float value = toolbox::random(0.0f, 1.0f);

    if (toolbox::chance(25.0f)) {
        toolbox::info("Random event happened");
    }

    toolbox::Timer timer(2.0f);
    timer.update(0.016f);

    if (timer.done()) {
        timer.reset();
    }
}
```

## CMake

If `toolbox-cpp` is inside another CMake project:

```cmake
add_subdirectory(toolbox-cpp)
target_link_libraries(my_game PRIVATE toolbox::toolbox)
```

Build the included example with:

```bash
cmake -S . -B build
cmake --build build
```
