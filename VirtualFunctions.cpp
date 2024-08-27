#include <iostream>
#include "OtherClasses.h"
#include <vector>

class Vehicle
{
public:
    virtual std::ostream& print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Vehicle& vehicle)
    {
        return vehicle.print(out);
    }
    virtual ~Vehicle() = default;
};

class WaterVehicle : public Vehicle
{
protected:
    float m_draft;
public:
    WaterVehicle(float draft) : m_draft{ draft }
    {

    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "WaterVehicle " << "Draft: " << m_draft;
        return out;
    }
};

class RoadVehicle : public Vehicle
{
protected:
    float m_rideHeight;
public:
    RoadVehicle(float rideHeight) : m_rideHeight{ rideHeight }
    {

    }
};

class Bicycle : public RoadVehicle
{
private: 
    Wheel m_wheel1;
    Wheel m_wheel2;
public:
    Bicycle(Wheel whell1, Wheel wheel2, float rideHeight)
        : m_wheel1{ whell1 }, m_wheel2{ wheel2 }, RoadVehicle(rideHeight)
    {

    }

    std::ostream& print(std::ostream& out) const override 
    {
        out << "Bicycle Wheels: " << m_wheel1.m_diameter << ' ' << m_wheel2.m_diameter <<
            " Ride height: " << m_rideHeight;
        return out;
    }
};

class Car : public RoadVehicle
{
private:
    Wheel m_wheel1;
    Wheel m_wheel2;
    Wheel m_wheel3;
    Wheel m_wheel4;
    Engine m_engine;
public:
    Car(Engine engine, Wheel whell1, Wheel wheel2, Wheel whell3, Wheel wheel4, float rideHeight)
        : m_engine{ engine },
        m_wheel1{ whell1 },
        m_wheel2{ wheel2 },
        m_wheel3{ whell1 },
        m_wheel4{ wheel2 },
        RoadVehicle(rideHeight)
    {

    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Car Engine: " << m_engine.m_power << " Wheels: " << 
            m_wheel1.m_diameter << ' ' << m_wheel2.m_diameter << ' ' <<
            m_wheel3.m_diameter << ' ' << m_wheel4.m_diameter <<
            " Ride height: " << m_rideHeight;
        return out;
    }

    float getPower() { return m_engine.m_power; }
};

/*
int main()
{
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
    std::cout << c << '\n';

    Bicycle t(Wheel(20), Wheel(20), 300);
    std::cout << t << '\n';

    return 0;
}
*/

float getHighestPower(const std::vector<Vehicle*>& v)
{
    float result = -FLT_MAX;
    for (Vehicle* vehicle : v)
    {
        if (Car* car = dynamic_cast<Car*>(vehicle))
        {
            result = std::max(result, car->getPower());
        }
    }
    return result;
}

int main()
{
    std::vector<Vehicle*> v;
    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    v.push_back(new WaterVehicle(5000));

    for (Vehicle* vehicle : v)
    {
        std::cout << *vehicle << std::endl;
    }

    std::cout << "The highest power is " << getHighestPower(v) << '\n';

    for (Vehicle* vehicle : v)
    {
        delete vehicle;
    }
}