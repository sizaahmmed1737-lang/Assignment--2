#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Observer Interface
class Observer {
public:
    virtual void update(string status) = 0;
    virtual ~Observer() {}
};

// SMS Notification
class SMSNotification : public Observer {
private:
    string customerName;

public:
    SMSNotification(string name) {
        customerName = name;
    }

    void update(string status) override {
        cout << "  SMS to " << customerName
             << ": your order is now " << status << endl;
    }
};

// Kitchen Screen
class KitchenScreen : public Observer {
public:
    void update(string status) override {
        cout << "  Kitchen screen: " << status << endl;
    }
};

// Order Class (Subject)
class Order {
private:
    string status;
    vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        for (int i = 0; i < observers.size(); i++) {
            if (observers[i] == observer) {
                observers.erase(observers.begin() + i);
                break;
            }
        }
    }

    void setStatus(string newStatus) {
        status = newStatus;

        cout << "Order is now: " << status << endl;

        for (Observer* observer : observers) {
            observer->update(status);
        }
    }
};

int main() {
    Order order;

    SMSNotification sms("Siza Ahmmed");
    KitchenScreen kitchen;

    // Add observers
    order.addObserver(&sms);
    order.addObserver(&kitchen);

    // Change order status
    order.setStatus("Cooking");

    cout << endl;

    order.setStatus("Out for delivery");

    cout << endl;

    // Remove kitchen before delivery
    order.removeObserver(&kitchen);

    order.setStatus("Delivered");

    return 0;
}
