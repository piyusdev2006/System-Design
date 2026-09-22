#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <utility>
using namespace std;

// Builder - Creates the intrinsic configuration for a flyweight.
struct AsteroidProperties
{
    int length;
    int width;
    int weight;
    string color;
    string texture;
    string material;
};

class AsteroidBuilder
{
private:
    AsteroidProperties properties{0, 0, 0, "", "", ""};

public:
    AsteroidBuilder &setSize(int length, int width)
    {
        properties.length = length;
        properties.width = width;
        return *this;
    }

    AsteroidBuilder &setWeight(int weight)
    {
        properties.weight = weight;
        return *this;
    }

    AsteroidBuilder &setAppearance(string color, string texture, string material)
    {
        properties.color = move(color);
        properties.texture = move(texture);
        properties.material = move(material);
        return *this;
    }

    AsteroidProperties build() const
    {
        if (properties.length <= 0 || properties.width <= 0 || properties.weight <= 0 ||
            properties.color.empty() || properties.texture.empty() ||
            properties.material.empty())
        {
            throw invalid_argument("Asteroid properties are incomplete or invalid");
        }

        return properties;
    }
};

// Flyweight - Stores INTRINSIC state only
class AsteroidFlyweight
{
private:
    // Intrinsic properties (shared among asteroids of same type)
    int length;
    int width;
    int weight;
    string color;
    string texture;
    string material;

public:
    explicit AsteroidFlyweight(const AsteroidProperties &properties)
        : length(properties.length), width(properties.width), weight(properties.weight),
          color(properties.color), texture(properties.texture), material(properties.material) {}

    void render(int posX, int posY, int velocityX, int velocityY)
    {
        cout << "Rendering " << color << ", " << texture << ", " << material
             << " asteroid at (" << posX << "," << posY
             << ") Size: " << length << "x" << width
             << " Velocity: (" << velocityX << ", "
             << velocityY << ")" << endl;
    }

    static size_t getMemoryUsage()
    {
        return sizeof(int) * 3 +    // length, width, weight
               sizeof(string) * 3 + // color, texture, material string objects
               32 * 3;              // Approximate string data
    }
};

// Flyweight Factory
class AsteroidFactory
{
private:
    static unordered_map<string, unique_ptr<AsteroidFlyweight>> flyweights;

public:
    static AsteroidFlyweight *getAsteroid(const AsteroidProperties &properties)
    {
        string key = to_string(properties.length) + "_" + to_string(properties.width) +
                     "_" + to_string(properties.weight) + "_" + properties.color + "_" +
                     properties.texture + "_" + properties.material;

        if (flyweights.find(key) == flyweights.end())
        {
            flyweights[key] = make_unique<AsteroidFlyweight>(properties);
        }

        return flyweights.at(key).get();
    }

    static int getFlyweightCount()
    {
        return flyweights.size();
    }

    static size_t getTotalFlyweightMemory()
    {
        return flyweights.size() * AsteroidFlyweight::getMemoryUsage();
    }

    static void cleanup()
    {
        flyweights.clear();
    }
};

// Static member definition
unordered_map<string, unique_ptr<AsteroidFlyweight>> AsteroidFactory::flyweights;

// Context - Stores EXTRINSIC state only
class AsteroidContext
{
private:
    AsteroidFlyweight *flyweight;
    int posX, posY;           // 8 bytes (position)
    int velocityX, velocityY; // 8 bytes (velocity)

public:
    AsteroidContext(AsteroidFlyweight *fw, int posX, int posY, int velX, int velY)
    {
        this->flyweight = fw;
        this->posX = posX;
        this->posY = posY;
        this->velocityX = velX;
        this->velocityY = velY;
    }

    void render()
    {
        flyweight->render(posX, posY, velocityX, velocityY);
    }

    static size_t getMemoryUsage()
    {
        return sizeof(AsteroidFlyweight *) +
               sizeof(int) * 4;
    }
};

class SpaceGameWithFlyweight
{
private:
    vector<AsteroidContext> asteroids;

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

            AsteroidProperties properties = AsteroidBuilder()
                                                .setSize(sizes[type], sizes[type])
                                                .setWeight(sizes[type] * 10)
                                                .setAppearance(colors[type], textures[type], materials[type])
                                                .build();

            asteroids.emplace_back(
                AsteroidFactory::getAsteroid(properties),
                100 + i * 50,
                200 + i * 30,
                1,
                2);
        }

        cout << "Created " << asteroids.size() << " asteroid contexts" << endl;
        cout << "Total flyweight objects: " << AsteroidFactory::getFlyweightCount() << endl;
    }

    void renderAll()
    {
        cout << "\n--- Rendering first 5 asteroids ---" << endl;
        for (int i = 0; i < min(5, (int)asteroids.size()); i++)
        {
            asteroids[i].render();
        }
    }

    size_t calculateMemoryUsage()
    {
        size_t contextMemory = asteroids.size() * AsteroidContext::getMemoryUsage();
        size_t flyweightMemory = AsteroidFactory::getTotalFlyweightMemory();
        return contextMemory + flyweightMemory;
    }

};

int main()
{
    const int ASTEROID_COUNT = 1000000;

    cout << "\nTESTING WITH FLYWEIGHT PATTERN" << endl;
    SpaceGameWithFlyweight game;
    game.spawnAsteroids(ASTEROID_COUNT);

    // Show first 5 asteroids to see the pattern
    game.renderAll();

    // Calculate and display memory usage
    size_t totalMemory = game.calculateMemoryUsage();

    cout << "\n=== MEMORY USAGE ===" << endl;
    cout << "Total asteroids: " << ASTEROID_COUNT << endl;
    cout << "Memory per asteroid: " << AsteroidContext::getMemoryUsage() << " bytes" << endl;
    cout << "Total memory used: " << totalMemory << " bytes" << endl;
    cout << "Memory in MB: " << totalMemory / (1024.0 * 1024.0) << " MB" << endl;

    AsteroidFactory::cleanup();
    return 0;
}