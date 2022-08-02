#include <iostream>
#include <fstream>
#include "car.pb.h"



int main() {
    Car car;
    car.set_brand("Peugeot");
    car.set_model("308");
    car.set_year(2010);

    std::cout << " " << car.brand() << " " << car.model() << " " << car.year() << " " << std::endl;

    std::ofstream out("car_info.bin", std::ios::binary);
    //car.SerializeToOstream(&out);

    std::cout << "hello world";


    return 0;
}
