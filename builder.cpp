#include <iostream>


class Engine {
    public:
        virtual ~Engine() {}
        virtual std::string GetName() const = 0;
};

class SportEngine : public Engine {
    public:
        std::string GetName() const override {
            return "Sport";
        }
};

class SUVEngine : public Engine {
    public:
        std::string GetName() const override {
            return "SUV";
        }
};

class Car {
    public:
        virtual ~Car() {}
        virtual void ListInfo() = 0;
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

        void ListInfo() override {
            std::cout << "[MANUAL]"
                      << " Seats:" << this->seats 
                      << " Engine:" << this->engine->GetName() 
                      << " Trip computer:" << this->tripComputer 
                      << " GPS:" << this->gps 
                      << std::endl;
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

        void ListInfo() override {
            std::cout << "[AUTOMATIC] " 
                      << " Seats:" << this->seats 
                      << " Engine:" << this->engine->GetName() 
                      << " Trip computer:" << this->tripComputer 
                      << " GPS:" << this->gps 
                      << std::endl;
        }
};

class Builder {
    public:
        virtual ~Builder() {}
        virtual void Reset() = 0;
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

        void Reset() override {
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

        void Reset() override {
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
        ~Director() {
            delete this->mBuilder;
        }

        void SetBuilder(Builder *builder) {
            this->mBuilder = builder;
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

void ClientCode(Director *director) {
    ManualBuilder *manualBuilder = new ManualBuilder();
    director->SetBuilder(manualBuilder);

    director->BuildSportCar();
    Manual *manualSportCar = manualBuilder->GetCar();
    manualSportCar->ListInfo();
    delete manualSportCar;

    director->BuildSUVCar();
    Manual *manualSUVCar = manualBuilder->GetCar();
    manualSUVCar->ListInfo();
    delete manualSUVCar;

    AutomaticBuilder *automaticBuilder = new AutomaticBuilder();
    director->SetBuilder(automaticBuilder);

    director->BuildSportCar();
    Automatic *automaticSportCar = automaticBuilder->GetCar();
    automaticSportCar->ListInfo();
    delete automaticSportCar;

    director->BuildSUVCar();
    Automatic *automaticSUVCar = automaticBuilder->GetCar();
    automaticSUVCar->ListInfo();
    delete automaticSUVCar;
}

int main() {
    Director *director = new Director();
    ClientCode(director);
    delete director;
    return 0;
}
