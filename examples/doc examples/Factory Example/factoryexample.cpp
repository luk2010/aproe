/*
    Factory Example

    Shows how to implement a factory using the templated
    class of the Engine.
*/

#include <Main.h>
#include <Factory.h>

/*
    The prototype we want to store.
*/
class Voiture : public Prototype
{
public:
    virtual ~Voiture() {}

    virtual const String& getManufacturer() const = 0;
    virtual const String& getModele() const = 0;

    void print()
    {
        Console::get() << "\nVoiture is : \nManufacturer : " << getManufacturer() << "\nModele : " << getModele();
    }
};

/*
    The factory is automatycly created by template.
*/
typedef Factory<Voiture> VoitureFactory;

/* Some manufacturer and cars. */

/////////////////////////////////
//Toyota
/////////////////////////////////
class Toyota : public Voiture
{
public:
    virtual ~Toyota() {}

    const String& getManufacturer() const { return String("Toyota"); }
};

class Aygo : public Toyota
{
public:
    virtual ~Aygo() {}

    Prototype* clone() const { return AProNew3(Aygo); }
    const String& getModele() const { return }
};

/////////////////////////////////
//Audi
/////////////////////////////////
class Audi : public Voiture
{
public:
    virtual ~Audi() {}

    const String& getManufacturer() const { return String("Audi"); }
}

/////////////////////////////////
//Bmw
/////////////////////////////////
class Bmw : public Voiture
{
public:
    virtual ~Bmw() {}

    const String& getManufacturer() const { return String("Bmw"); }
}

/////////////////////////////////
//Renault
/////////////////////////////////
class Renault : public Voiture
{
public:
    virtual ~Renault() {}

    const String& getManufacturer() const { return String("Renault"); }
}

int main()
{
    VoitureFactory myFactory;
    myFactory.register_prototype(String("Bmw"), new Bmw);
    myFactory.register_prototype(String("Audi"), new Audi);
    myFactory.register_prototype(String("Toyota"), new Toyota);

    Voiture* myCar = myFactory.create(String("Toyota"));

    return 0;
}
