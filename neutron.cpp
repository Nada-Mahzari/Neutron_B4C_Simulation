
#include <iostream>
using namespace std;

int main() {

    // Neutron properties
    double initial_energy = 1.0; // MeV

    // Boron Carbide (B4C) sample dimensions
    double length = 5.0;  // cm
    double width  = 5.0;  // cm
    double height = 5.0;  // cm

    // Calculate sample volume
    double volume = length * width * height;

    cout << "Neutron Energy Loss in B4C" << endl;
    cout << "--------------------------" << endl;

    cout << "Initial neutron energy: "
         << initial_energy << " MeV" << endl;

    cout << "Material: B4C" << endl;

    cout << "Sample dimensions: "
         << length << " x "
         << width << " x "
         << height << " cm^3" << endl;

    cout << "Sample volume: "
         << volume << " cm^3" << endl;

    return 0;
}
