#include <iostream>


class Engine {
    public:
        virtual ~Engine() {}
};

class SportEngine : public Engine {};
class SUVEngine : public Engine {};

class Car {
    public:
        virtual ~Car() {}
};

class Manual : public Car {
    public:
        int seats;
        Engine *engine;
        bool tripComputer;
        bool gps;

        ~Manual() {
            delete engine;
        }
};

class Automatic : public Car {
    public:
        int seats;
        Engine *engine;
        bool tripComputer;
        bool gps;

        ~Automatic() {
            delete engine;
        }    
};

class Builder {
    public:
        virtual ~Builder() {}
        virtual void Reset();
        virtual void SetSeats(int number) = 0;
        virtual void SetEngine(Engine *engine) = 0;
        virtual void SetTripComputer(bool hasTripComputer) = 0;
        virtual void SetGPS(bool hasGps) = 0;
};

class ManualBuilder : public Builder {
    private:
        Manual *mCar;
    
    public:
        ManualBuilder() {
            this->Reset();
        }

        ~ManualBuilder() {
            delete mCar;
        }

        void Reset() {
            this->mCar = new Manual();
        }

        void SetSeats(int number) override {
            this->mCar->seats = number;
        }

        void SetEngine(Engine *engine) override {
            this->mCar->engine = engine;
        }

        void SetTripComputer(bool hasTripComputer) override {
            this->mCar->tripComputer = hasTripComputer;
        }

        void SetGPS(bool hasGps) override {
            this->mCar->gps = hasGps;
        }

        Manual *GetCar() {
            Manual *result = this->mCar;
            
            this->Reset();
            
            return result;
        }
};

class AutomaticBuilder : public Builder {
    private:
        Automatic *mCar;
    
    public:
        AutomaticBuilder() {
            this->Reset();
        }

        ~AutomaticBuilder() {
            delete mCar;
        }

        void Reset() {
            this->mCar = new Automatic();
        }

        void SetSeats(int number) override {
            this->mCar->seats = number;
        }

        void SetEngine(Engine *engine) override {
            this->mCar->engine = engine;
        }

        void SetTripComputer(bool hasTripComputer) override {
            this->mCar->tripComputer = hasTripComputer;
        }

        void SetGPS(bool hasGps) override {
            this->mCar->gps = hasGps;
        }

        Automatic *GetCar() {
            Automatic *result = this->mCar;
            
            this->Reset();
            
            return result;
        }
};

class Director {
    private:
        Builder *mBuilder;
    
    public:
        void SetBuilder(Builder *builder) {
            this->mBuilder = builder;
        }

        ~Director() {
            delete mBuilder;
        }

        void BuildSUVCar() {
            this->mBuilder->SetEngine(new SUVEngine());
            this->mBuilder->SetSeats(4);
            this->mBuilder->SetTripComputer(true);
            this->mBuilder->SetGPS(true);
        }

        void BuildSportCar() {
            this->mBuilder->SetEngine(new SportEngine());
            this->mBuilder->SetSeats(2);
            this->mBuilder->SetTripComputer(false);
            this->mBuilder->SetGPS(false);
        }
};

void ClientCode(Director &director) {
    ManualBuilder builder;
    director.SetBuilder(&builder);


}

