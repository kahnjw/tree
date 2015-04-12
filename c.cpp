#include "tree.hpp"

int main()
{
    Tree<double> stellarMass = Tree<double>();
    double delta;

    stellarMass.set("Sun", 1.0);
    stellarMass.set("Sirius", 2.02);
    stellarMass.set("R136a1", 256.0);

    delta = stellarMass.get("R136a1") - stellarMass.get("Sun");

    // ...

    return 0;
}
