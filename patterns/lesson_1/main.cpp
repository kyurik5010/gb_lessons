#include <iostream>
#include <map>
#include <thread>
#include <chrono>

//TASK_1________________________________________________________________________________________________________________

std::mutex ChocoGuard;
class ChocolateBoiler{
private:
    //static
    int _check;
    bool _empty;
    bool _boiled;
    static ChocolateBoiler* boiler;

    ChocolateBoiler (){
        boiler = this;
        _empty = true;
        _boiled = false;
    }
public:
    ChocolateBoiler(const ChocolateBoiler& instance) = delete;
    ChocolateBoiler& operator=(const ChocolateBoiler&) = delete;

    static ChocolateBoiler* create();

    bool isEmpty() const{ return _empty; }
    bool isBoiled() const{ return _boiled; }

    int get_check() const { return _check; }
    void set_check(int x) { _check = x; }

    void fill(){
        if (isEmpty()){
            _empty = false;
            _boiled = false;
        }
    }

    void drain(){
        if (!isEmpty() && isBoiled()){
            _empty = true;
        }
    }

    void boil(){
        if (!isEmpty() && !isBoiled()){
            _boiled = true;
        }
    }
};

ChocolateBoiler* ChocolateBoiler::boiler = nullptr;
ChocolateBoiler* ChocolateBoiler::create() {
    std::lock_guard<std::mutex> lock (ChocoGuard);
    if(boiler == nullptr)
        return new ChocolateBoiler();
    else
        return boiler;
}

//TASK_2________________________________________________________________________________________________________________

/**Автоматы в наше время все чаще заменяют людей. Появились автоматы, наливающие напитки, продающие сухарики, контактные линзы, автоматы выдающие ваши интернет заказы. Обычно все эти автоматы связаны между собой в сеть и управляются с клиента. Раз в месяц необходимо составлять отчет о состоянии автоматов. Но проблема в том, что ресурсов на клиенте недостаточно, чтобы постоянно опрашивать сраазу все автоматы в режиме реального времени.*/

 /**Реализуйте паттерн Proxy для данного кода. Заместитель должен хранить в себе еще одно дополнительное поле с датой получения данных. При вызове любого из отчетов, должна происходить проверка времени последнего запроса данных. Если прошло более одного часа, то тогда вызываем метод с отчетом в реальном объекте. Если меньше, то выводим на экран сохраненные данные с прошлого отчета. Для времени удобно использовать #include <ctime>*/

class ISellSystem{
public:
    virtual void changePrice(std::string, float) = 0;
    virtual void sellProduct(std::string) = 0;
    virtual void addProduct(std::string, size_t) = 0;
};


class Automaton: ISellSystem {
private:
    std::string location;
    double recieved_money;
    double spent_money;
    std::map<std::string, float> goods_price;
    std::map<std::string, size_t> goods_count;

public:
    Automaton(const std::string &location, double recievedMoney) : location(location), recieved_money(recievedMoney) {
        spent_money = 0.0;
    }

    void changePrice(std::string name, float newPrice) override {
        goods_price[name] = newPrice;
    }

    void sellProduct(std::string name) {
        if (goods_count[name] > 0) {
            recieved_money += goods_price[name];
        } else {
            std::cerr << "Not enough goods" << std::endl;
        }
    }

    void addProduct(std::string name, size_t count) {
        goods_count[name] += count;
    }

    double allMoneyReport() const { return recieved_money - spent_money; }
    const std::string &getLocationReport() const { return location; }
    std::map<std::string, size_t> goodsCountReport() { return goods_count; };
    std::map<std::string, float> goodsPriceReport() { return goods_price; };
};


class Proxy : public ISellSystem{
    Automaton* machine;
    std::chrono::time_point<std::chrono::steady_clock> LogDate;
    bool IsLive() { return machine != nullptr; }
    bool IsOldLog(){ return std::chrono::steady_clock::now() - LogDate > std::chrono::seconds (1); } //секунды для проверки

    std::string OldLocationReport;
    double OldMoneyReport;
    std::map<std::string, float> OldPriceReport;
    std::map<std::string, size_t> OldCountReport;
public:
    Proxy(std::string location, double receivedMoney): machine(new Automaton(location, receivedMoney)) {
        LogDate = std::chrono::steady_clock::now();
    };
    void changePrice  (std::string name, float newPrice) override{
        if(IsLive())
            machine->changePrice(name, newPrice);
        else
            std::cout << "Access denied, machine is unreachable" << std::endl;
    }
    void sellProduct(std::string name) override{
        if(IsLive())
                machine->sellProduct(name);
        else
            std::cout << "Access denied, machine is unreachable" << std::endl;
    }
    void addProduct(std::string name, size_t amount) override{
        if(IsLive())
            machine->addProduct(name, amount);
        else
            std::cout << "Access denied, machine is unreachable" << std::endl;
    }

    double allMoneyReport() {
        if(IsOldLog()) {
            OldMoneyReport = machine->allMoneyReport();
            LogDate = std::chrono::steady_clock::now();
            std::cout << "New Report" << std::endl; //для проверки
            return OldMoneyReport;
        }
        else {
            std::cout << "Old Report" << std::endl; //для проверки
            return OldMoneyReport;
        }
    }

    const std::string &getLocationReport() {
        if (IsOldLog()) {
            OldLocationReport = machine->getLocationReport();
            LogDate = std::chrono::steady_clock::now();
            return OldLocationReport;
        }
        else
            return OldLocationReport;
    }

    std::map<std::string, size_t> goodsCountReport() {
        if (IsOldLog()) {
            OldCountReport = machine->goodsCountReport();
            LogDate = std::chrono::steady_clock::now();
            return OldCountReport;
        }
        else
            return OldCountReport;
    }

    std::map<std::string, float> goodsPriceReport() {
        if (IsOldLog()) {
            OldPriceReport = machine->goodsPriceReport();
            LogDate = std::chrono::steady_clock::now();
            return OldPriceReport;
        }
        else
            return OldPriceReport;
    }

};
//MAIN__________________________________________________________________________________________________________________

int main() {
    ChocolateBoiler* boiler = ChocolateBoiler::create();
    ChocolateBoiler* Cboiler = ChocolateBoiler::create();
    Cboiler->set_check(5);
    std::cout << "boiler check " << boiler->get_check() << " " << Cboiler->get_check() << std::endl;

    Proxy pr("mk", 12.5);
    pr.addProduct("snickers", 2);
    pr.changePrice("snickers", 5);
    pr.sellProduct("snickers");
    pr.sellProduct("snickers");
    pr.allMoneyReport();
    std::this_thread::sleep_for(std::chrono::seconds(2)); //чтобы не ждать
    pr.allMoneyReport();

    return 0;
}
