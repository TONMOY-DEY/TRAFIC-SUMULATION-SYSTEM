#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;


class TrafficLight {
private:
    string color;
    int duration;

public:
    TrafficLight(string col, int dur) : color(col), duration(dur) {}


    string getColor() {
        return color;
    }


    int getDuration() {
        return duration;
    }


    void changeColor(string newColor) {
        color = newColor;
    }
};


class Vehicle {
private:
    int id;

public:
    Vehicle(int vehicleId) : id(vehicleId) {}


    int getId() {
        return id;
    }
};


class Intersection {
private:
    queue<Vehicle> vehicleQueue;
    TrafficLight trafficLight;

public:
    Intersection(TrafficLight light) : trafficLight(light) {}


    void addVehicle(Vehicle vehicle) {
        vehicleQueue.push(vehicle);
        cout << "Vehicle " << vehicle.getId() << " added to the queue." << endl;
    }


    void simulateTraffic() {
        while (true) {

            if (trafficLight.getColor() == "Green") {
                cout << "Traffic light is Green. Vehicles are moving..." << endl;
                while (!vehicleQueue.empty()) {
                    Vehicle currentVehicle = vehicleQueue.front();
                    vehicleQueue.pop();
                    cout << "Vehicle " << currentVehicle.getId() << " is passing through the intersection." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "All vehicles have passed." << endl;
                trafficLight.changeColor("Red");
            }

            else {
                cout << "Traffic light is Red. Vehicles are waiting..." << endl;
                this_thread::sleep_for(chrono::seconds(trafficLight.getDuration()));
                trafficLight.changeColor("Green");
            }
        }
    }
};

int main() {
    TrafficLight light("Green", 5);

    Intersection intersection(light);

    intersection.addVehicle(Vehicle(1));
    intersection.addVehicle(Vehicle(2));
    intersection.addVehicle(Vehicle(3));

    intersection.simulateTraffic();

    return 0;
}
