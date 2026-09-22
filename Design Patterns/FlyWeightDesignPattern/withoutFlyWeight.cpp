#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Asteroid
{
private:
    // Intrinsic properties (same for many asteroids) - DUPLICATED FOR EACH OBJECT
    int length;
    int width;
    int weight;
    string color;
    string texture;
    string material;

    // Extrinsic properties (unique for each asteroid)
    int posX, posY;
    int velocityX, velocityY;

public:
    Asteroid(int length, int width, int /*weight*/, string color, string texture,
             string material, int posX, int posY, int velocityX, int velocityY)
    {
        this->length = length;
        this->width = width;
        this->weight = width;
        this->color = color;
        this->texture = texture;
        this->material = material;
        this->posX = posX;
        this->posY = posY;
        this->velocityX = velocityX;
        this->velocityY = velocityY;
    }

    void render()
    {
        cout << "Rendering " << color << ", " << texture << ", " << material
             << " asteroid at (" << posX << "," << posY
             << ") Size: " << length << "x" << width
             << " Velocity: (" << velocityX << ", "
             << velocityY << ")" << endl;
    }

    // Calculate approximate memory usage per object
    static size_t getMemoryUsage()
    {
        return sizeof(int) * 7 +    // length, width, weight, x, y, velocityX, velocityY
               sizeof(string) * 3 + // color, texture, material string objects
               32 * 3;              // Approximate string data (assuming average 10 chars each)
    }
};

class AsteroidBuilder
{
private:
    int length = 0;
    int width = 0;
    int weight = 0;
    string color;
    string texture;
    string material;
    int posX = 0;
    int posY = 0;
    int velocityX = 0;
    int velocityY = 0;

public:
    AsteroidBuilder &withSize(int size)
    {
        length = size;
        width = size;
        weight = size * 10;
        return *this;
    }

    AsteroidBuilder &withAppearance(string asteroidColor, string asteroidTexture,
                                    string asteroidMaterial)
    {
        color = asteroidColor;
        texture = asteroidTexture;
        material = asteroidMaterial;
        return *this;
    }

    AsteroidBuilder &atPosition(int x, int y)
    {
        posX = x;
        posY = y;
        return *this;
    }

    AsteroidBuilder &withVelocity(int x, int y)
    {
        velocityX = x;
        velocityY = y;
        return *this;
    }

    Asteroid *build() const
    {
        return new Asteroid(length, width, weight, color, texture, material,
                            posX, posY, velocityX, velocityY);
    }
};

class SpaceGame
{
private:
    vector<Asteroid *> asteroids;

public:
    void spawnAsteroids(int count)
    {
        cout << "\n=== Spawning " << count << " asteroids ===" << endl;

        vector<string> colors = {"Red", "Blue", "Gray"};
        vector<string> textures = {"Rocky", "Metallic", "Icy"};
        vector<string> materials = {"Iron", "Stone", "Ice"};
        int sizes[] = {25, 35, 45};

        for (int i = 0; i < count; i++)
        {
            int type = i % 3;

            asteroids.push_back(
                AsteroidBuilder()
                    .withSize(sizes[type])
                    .withAppearance(colors[type], textures[type], materials[type])
                    .atPosition(
                        100 + i * 50, // Simple x: 100, 150, 200, 250...
                        200 + i * 30) // Simple y: 200, 230, 260, 290...
                    .withVelocity(
                        1, // All move right with velocity 1
                        2) // All move down with velocity 2
                    .build());
        }

        cout << "Created " << asteroids.size() << " asteroid objects" << endl;
    }

    void renderAll()
    {
        cout << "\n--- Rendering first 5 asteroids ---" << endl;
        for (int i = 0; i < min(5, (int)asteroids.size()); i++)
        {
            asteroids[i]->render();
        }
    }

    size_t calculateMemoryUsage()
    {
        return asteroids.size() * Asteroid::getMemoryUsage();
    }

    int getAsteroidCount()
    {
        return asteroids.size();
    }
};

int main()
{
    const int ASTEROID_COUNT = 1000000;

    cout << "\n TESTING WITHOUT FLYWEIGHT PATTERN" << endl;
    SpaceGame *game = new SpaceGame();

    game->spawnAsteroids(ASTEROID_COUNT);

    // Show first 5 asteroids to see the pattern
    game->renderAll();

    // Calculate and display memory usage
    size_t totalMemory = game->calculateMemoryUsage();

    cout << "\n=== MEMORY USAGE ===" << endl;
    cout << "Total asteroids: " << ASTEROID_COUNT << endl;
    cout << "Memory per asteroid: " << Asteroid::getMemoryUsage() << " bytes" << endl;
    cout << "Total memory used: " << totalMemory << " bytes" << endl;
    cout << "Memory in MB: " << totalMemory / (1024.0 * 1024.0) << " MB" << endl;

    return 0;
}