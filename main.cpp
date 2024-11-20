#include "colors.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
const bool debug = false;
struct Звено {
    int a;
    float k;
    Звено* next;
    Звено(int ac, float kc, Звено* nextc=nullptr): a(ac), k(kc), next(nextc) {if (debug) {std::cout<<Colors::green<<"Creating "<<Colors::reset<<this<<std::endl;}};
    ~Звено() {if (debug) {std::cout<<Colors::red<<"Deleting "<<Colors::reset<<this<<std::endl;}}
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
    int size() {
        Звено* temp = first;
        int counter = 0;
        while (temp!=nullptr) {
            counter++;
            temp=temp->next;
        }
        return counter;
    }
    std::string formula() {
        std::stringstream ss;
        Звено* temp = first;
        while (temp != nullptr) {
            ss << Colors::скучный << (temp!=first?((temp->k < 0) ? " - " : " + "): ((temp->k < 0) ? "-" : ""));
            //ss.precision(2);
            ss << Colors::green << fabs(temp->k)*1.;
            ss << Colors::скучный << (temp->a==0?"": (temp->a==1?"*X": "*X^")) << Colors::green << (temp->a<=1?"": std::to_string(temp->a)) << Colors::reset;
            temp = temp->next;
            
        }
        return ss.str();
    }
    float calc(float x, bool show=false) {
        if (size()==0) {return 0;}
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
    std::cout<<Colors::blue<<"Размер цепи: "<<Colors::reset<<цепь->size()<<std::endl;
    int x;
    std::cout<<Colors::blue<<"Вводи X: "<<Colors::reset;
    std::cin>>x;
    std::cout<<Colors::green<<"Итого: \n" <<Colors::reset<<цепь->calc(x, true)<<std::endl;
    
    delete цепь;
    return 0;
}