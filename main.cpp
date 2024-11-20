#include "colors.h"
#include <iomanip>
#include <iostream>
#include <cmath>
#include <sstream>
struct Звено {
    int a;
    float k;
    Звено* next;
    Звено(int ac, float kc, Звено* nextc=nullptr): a(ac), k(kc), next(nextc) {};
};
struct Chain {
private:
    Звено* create(int n) {
        float k;
        std::cout<<Colors::blue<<"Вводи коэф на степень "<<n<<": "<<Colors::reset;
        std::cin>>k;
        std::cout<<Colors::clear;
        if (n==0) {
            if (k==0) {return nullptr;}
            else {return new Звено(n, k);};
        }
        else {
            if (k==0) {
                return create(n-1);
            }
            else {
                return new Звено(n, k, create(n-1));
            }
        }
    }
public:
    Звено* first;
    Chain() {
        int n;
        std::cout<<Colors::blue<<"Вводи n: "<<Colors::reset;
        std::cin >> n;
        std::cout<<std::endl;
        first = create(n);
    }
    ~Chain() {
        while (first != nullptr) {
           Звено* temp = first;
           first = first->next;
           delete temp;
       }
    }
    std::string formula() {
        std::stringstream ss;
        Звено* temp = first;
        while (temp != nullptr) {
            ss << Colors::скучный << (temp!=first?((temp->k < 0) ? " - " : " + "): ((temp->k < 0) ? "-" : ""));
            ss << Colors::green << std::fixed << std::setprecision(2)<< fabs(temp->k);
            ss << Colors::скучный << (temp->a==0?"": "*X^") << Colors::green << temp->a << Colors::reset;
            temp = temp->next;
            
        }
        return ss.str();
    }
    float calc(float x, bool show=false) {
        float result;
        Звено* temp = first;
        while (temp != nullptr) {
            if (show) {
                std::cout<<Colors::green<<temp->k<<Colors::скучный<<" * "<<Colors::green<<x<<Colors::скучный<<"^"<<Colors::green<<temp->a<<Colors::скучный<<" = "<<Colors::red<<temp->k*std::pow(x, temp->a)<<Colors::reset<<std::endl;
            }
            result+=temp->k*std::pow(x, temp->a);
            temp = temp->next;
        }
        return result;
    }
};
int main() {
    std::cout<<Colors::clear;
    Chain* цепь = new Chain;
    std::cout<<std::endl<<цепь->formula()<<std::endl;
    int x;
    std::cout<<Colors::blue<<"Вводи X: "<<Colors::reset;
    std::cin>>x;
    std::cout<<Colors::green<<"Итого: \n" <<Colors::reset<<цепь->calc(x, true)<<std::endl;
    delete цепь;
    return 0;
}