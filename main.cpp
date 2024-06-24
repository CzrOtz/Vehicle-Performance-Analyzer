
#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Calculations {
private:
    double power;       // in horsepower
    double weight;      // in lbs
    double displacement;// in cc
    int cylinders;      // number of cylinders

public:
    // Parameterized constructor
    Calculations(double p, double w, double d, int c) : power(p), weight(w), displacement(d), cylinders(c) {}

    // Getter methods
    double getPower() const { return power; }
    double getWeight() const { return weight; }
    double getDisplacement() const { return displacement; }
    int getCylinders() const { return cylinders; }

    // Calculation methods
    double powerToWeightRatio() const {
        return weight / power;
    }

    double displacementToPowerRatio() const {
        return power / displacement;
    }

    double cylindersToPowerRatio() const {
        return power / cylinders;
    }

    double scaleUpCylinder(double value) const {
        double powerPerCylinder = getPower() / getCylinders();
        return powerPerCylinder * value;
    }

    double scaleUpDisplacement(double value) const {
        double powerPerLitter = getPower() / getDisplacement();
        return powerPerLitter * value;
    }
};

class Display {
private:
    Calculations calc; // Calculations object

public:
    Display() : calc(0, 0, 0, 0) {}

    void welcome() {
        int choice;
        cout << "\nChoose an option:\n";
        cout << "1. Enter values for your vehicle\n";
        cout << "2. Display all values\n";
        cout << "3. Display power-to-weight ratio\n";
        cout << "4. Display displacement-to-power ratio\n";
        cout << "5. Display cylinders-to-power ratio\n";
        cout << "6. Scale up (or down) my engine based on cylinders\n";
        cout << "7. Scale up (or down) my engine based on displacement\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "\nInvalid input. Please enter a number between 1 and 8.\n";
            return;
        }

        try {
            switch (choice) {
                case 1:
                    cout << "\n1: Enter values for your vehicle.\n";
                    getValues();
                    break;
                case 2:
                    cout << "\n2: Display all values.\n";
                    generalDisplay();
                    break;
                case 3:
                    cout << "\n3: Calculate power-to-weight ratio.\n";
                    displayPowerToWeightRatio();
                    break;
                case 4:
                    cout << "\n4: Calculate displacement-to-power ratio.\n";
                    displayDisplacementToPowerRatio();
                    break;
                case 5:
                    cout << "\n5: Calculate cylinders-to-power ratio.\n";
                    displayCylindersToPowerRatio();
                    break;
                case 6:
                    cout << "\n6: Scale up (or down) my engine based on cylinders.\n";
                    scaleUpDisplayCylinders();
                    break;
                case 7:
                    cout << "\n7: Scale up (or down) my engine based on displacement.\n";
                    scaleUpDisplayDisplacement();
                    break;
                case 8:
                    cout << "\n8: Exit\n";
                    cout << "Exiting the program.\n";
                    exit(0);
                default:
                    cout << "\nInvalid choice. Please choose a valid option.\n";
            }
        } catch (const invalid_argument& e) {
            cout << "\nError: " << e.what() << "\n";
        } catch (const out_of_range& e) {
            cout << "\nError: " << e.what() << "\n";
        } catch (...) {
            cout << "\nAn unknown error occurred.\n";
        }
    }

    void getValues() {
        double power, weight, displacement;
        int cylinders;

        cout << "\nEnter power (hp): ";
        if (!(cin >> power)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input for power.");
        }

        cout << "Enter weight (lbs): ";
        if (!(cin >> weight)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input for weight.");
        }

        cout << "Enter displacement (liters): ";
        if (!(cin >> displacement)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input for displacement.");
        }

        cout << "Enter cylinders: ";
        if (!(cin >> cylinders)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input for cylinders.");
        }

        calc = Calculations(power, weight, displacement, cylinders);
    }

    void generalDisplay() const {
        cout << "\n--- Vehicle Values ---\n";
        cout << "Power to weight ratio: " << calc.powerToWeightRatio() << " lbs per horsepower\n";
        cout << "Displacement to power ratio: " << calc.displacementToPowerRatio() << " hp per liter\n";
        cout << "Cylinders to power ratio: " << calc.cylindersToPowerRatio() << " hp per cylinder\n";
        cout << "-----------------------\n";
    }

    void displayPowerToWeightRatio() const {
        cout << "\nPower to weight ratio: " << calc.powerToWeightRatio() << " lbs per horsepower\n";
    }

    void displayDisplacementToPowerRatio() const {
        cout << "\nDisplacement to power ratio: " << calc.displacementToPowerRatio() << " hp per liter\n";
    }

    void displayCylindersToPowerRatio() const {
        cout << "\nCylinders to power ratio: " << calc.cylindersToPowerRatio() << " hp per cylinder\n";
    }

    void scaleUpDisplayCylinders() const {
        double value;
        cout << "\nEnter the number of cylinders: ";
        if (!(cin >> value)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input for number of cylinders.");
        }
        cout << "If your engine had " << value << " cylinders, it would produce " << calc.scaleUpCylinder(value) << " horsepower\n";
    }

    void scaleUpDisplayDisplacement() const {
        double value;
        cout << "\nEnter the displacement value (liters): ";
        if (!(cin >> value)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input for displacement value.");
        }
        cout << "If your engine had " << value << " liters, it would produce " << calc.scaleUpDisplacement(value) << " horsepower\n";
    }

    void display() {
        while (true) {
            welcome();
        }
    }
};

int main() {
    Display display;
    display.display();
    return 0;
}