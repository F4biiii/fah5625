#include <iostream>
#include <string>
#include <vector>

class Tier
{
    public:
        Tier(const std::string pName)
        {
            name = pName;
        }
        Tier() {}
        ~Tier() {}
        std::string name;
        virtual void makeSound() 
        {
            std::cout << "Tier" << std::endl;
        }
};

class Hund : public Tier
{
    public:
        Hund(const std::string pName) : Tier(pName) {}
        Hund() {}
        ~Hund() {}
        virtual void makeSound() override
        {
            std::cout << "Hund" << std::endl;
        } 
};

class Katze : public Tier
{
    public:
        Katze(const std::string pName) : Tier(pName) {}
        Katze() {}
        ~Katze() {}
        virtual void makeSound() override
        {
            std::cout << "Katze" << std::endl;
        }  
};

class Vogel : public Tier
{
    public:
        Vogel(const std::string pName) : Tier(pName) {}
        Vogel() {}
        ~Vogel() {}
        virtual void makeSound() override
        {
            std::cout << "Vogel" << std::endl;
        }  
};

int main() {

    Vogel v1("Tweety");
    Tier t1("Tierchen");

    Tier* tierP = new Tier("Tierchen2");
    tierP->makeSound();
    tierP = &v1;
    tierP->makeSound();

    return 0;
}



