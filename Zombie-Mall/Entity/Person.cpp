
#include "Person.h"

#include "../Capsule.h"
#include "../Circle.h"
#include "../MathUtils.h"

Person::Person(Game& game) :
    Entity(game),
    rng(0, 360)
{
    SetType(Entity::Type::Person);
    SetRotation(static_cast<float>(rng.GetRandomValue()));
}

Person::~Person() {}

void Person::Update()
{
    Entity::Update();
}

void Person::ConvertToZombie()
{
    SetType(Entity::Type::Zombie);
    Load("Resources/Data/Zombie.json");
}

void Person::HandleCollision(const Capsule& capsule)
{
    const sf::Vector2f closestPoint = ClosestPointOnALine(capsule.GetStart(), capsule.GetEnd(), GetPosition());
    const Circle testCircle(closestPoint, capsule.GetRadius());
    const Circle entityCircle(GetPosition(), 32.0f);

    if (CircleCollision(testCircle, entityCircle))
    {
        const sf::Vector2f vecDistance = entityCircle.GetPosition() - testCircle.GetPosition();
        const sf::Vector2f testToEntity = Normalize(vecDistance);
        const float pushBackDist = (entityCircle.GetRadius() + testCircle.GetRadius()) - VectorLength(vecDistance);

        Move(testToEntity * pushBackDist);

        SetRotation(static_cast<float>(rng.GetRandomValue()));
    }
}