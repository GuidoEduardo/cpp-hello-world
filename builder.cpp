#include <iostream>


class Engine {
    public:
        int horsepower;
};

class Seats {
    public:
        int number;
};

class Navegation {
    public:
        bool gps;
        bool tripSystem;
};

class Car {
    public:
        Engine* engine;
        Seats* seats;
        Navegation* navegation;

        virtual void ListInfo() {
            std::cout << "Engine (horsepower): " << engine->horsepower << std::endl;
            std::cout << "Seats: " << seats->number << std::endl;
            std::cout << "Navegation (gps): " << navegation->gps << std::endl;
            std::cout << "Navegation (trip system): " << navegation->tripSystem << std::endl;
        }
};

class CarBuilder {
    public:
        virtual Engine* GetEngine() const = 0;
        virtual Seats* GetSeats() const = 0;
        virtual Navegation* GetNavegation() const = 0;
};

class Director {
    private:
        CarBuilder* mBuilder;
    
    public:
        void SetBuilder(CarBuilder* mBuilder) {
            this->mBuilder = mBuilder;
        }

        Car* Build() {
            Car* car = new Car();

            car->engine = mBuilder->GetEngine();
            car->seats = mBuilder->GetSeats();
            car->navegation = mBuilder->GetNavegation();

            return car;
        }
};

class SportBuilder : public CarBuilder {
    public:
        Engine* GetEngine() const override {
            Engine* engine = new Engine();
            engine->horsepower = 2000;
            return engine;
        }

        Seats* GetSeats() const override {
            Seats* seats = new Seats();
            seats->number = 2;
            return seats;
        }

        Navegation* GetNavegation() const override {
            Navegation* navegation = new Navegation();
            navegation->gps = true;
            navegation->tripSystem = false;
            return navegation;
        }
};

class SUVBuilder : public CarBuilder {
    public:
        Engine* GetEngine() const override {
            Engine* engine = new Engine();
            engine->horsepower = 400;
            return engine;
        }

        Seats* GetSeats() const override {
            Seats* seats = new Seats();
            seats->number = 4;
            return seats;
        }

        Navegation* GetNavegation() const override {
            Navegation* navegation = new Navegation();
            navegation->gps = true;
            navegation->tripSystem = true;
            return navegation;
        }
};

int main() {
    Car* car;
    
    SportBuilder sportBuilder;
    SUVBuilder suvBuilder;

    Director director;

    std::cout << "Building Sport Car" << std::endl;
    director.SetBuilder(&sportBuilder);
    car = director.Build();
    car->ListInfo();

    std::cout << std::endl;

    std::cout << "Building SUV Car" << std::endl;
    director.SetBuilder(&suvBuilder);
    car = director.Build();
    car->ListInfo();

    return 0;
}
