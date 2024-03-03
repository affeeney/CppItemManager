//Include necessary libraries
#include <iostream>      //Input-output stream.
#include <fstream>       //File stream.
#include <map>           //Map container.
#include <string>        //String operations.

//Declare the class for GroceryManager.
class GroceryManager {
private:
    std::map<std::string, int> itemQuantity; //Map to store item quantity.

public:
    //Constructor to initialize data from file or create a new grocery_data.dat file.
    GroceryManager() {
        loadDataFromFile(); //Call the function to load data from file.
    }

    //Function to load data from the grocery_data.dat file.
    void loadDataFromFile() {
        std::ifstream file("grocery_data.dat"); //Open the grocery_data.dat file for reading.
        if (file.is_open()) {
            std::string itemName;
            int quantity;
            //Read data from the file and populate the map.
            while (file >> itemName >> quantity) {
                itemQuantity[itemName] = quantity;
            }
            file.close(); // Close the file.
            std::cout << "Grocery data loaded successfully.\n"; //Display success message.
        }
        else {
            std::cout << "Creating a new grocery_data.dat file.\n"; //Display message for creating a new file.
        }
    }
    
    //Function to save data to the grocery_data.dat file.
    void saveDataToFile() {
        std::ofstream file("grocery_data.dat"); //Open the grocery_data.dat file for writing.
        // Write item quantity data to the file
        for (const auto& pair : itemQuantity) {
            file << pair.first << " " << pair.second << "\n";
        }
        file.close(); //Close the file
        std::cout << "Grocery data saved successfully.\n"; //Display success message
    }

    //Function to prompt user for input and return quantity of a specific item.
    int getItemQuantity(const std::string& itemName) {
        // Check if the item is in the map and return its quantity.
        if (itemQuantity.find(itemName) != itemQuantity.end()) {
            return itemQuantity[itemName];
        }
        else {
            std::cout << "Item not found in records.\n"; //Display message if item is not found.
            return 0;
        }
    }

    //Function to print list with quantities of all items.
    void printItemQuantities() {
        std::cout << "Item Quantities:\n";
        //Display item quantities.
        for (const auto& pair : itemQuantity) {
            std::cout << pair.first << " " << pair.second << "\n";
        }
    }

    //Function to print histogram of item quantities.
    void printItemHistogram() {
        std::cout << "Item Histogram:\n";
        //Display histogram using asterisks.
        for (const auto& pair : itemQuantity) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }

    //Function to handle user input validation.
    int getUserChoice() {
        int choice;
        while (true) {
            // Display menu options.
            std::cout << "Menu:\n";
            std::cout << "1. Search for an item\n";
            std::cout << "2. Print item quantities\n";
            std::cout << "3. Print item histogram\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter your choice: ";

            //Validate user input
            if (!(std::cin >> choice) || choice < 1 || choice > 4) {
                std::cin.clear(); //clear input buffer to restore cin to a usable state.
                std::cin.ignore(INT_MAX, '\n'); //ignore last input.
                std::cout << "Invalid input. Please enter a number between 1 and 4.\n";
            }
            else {
                break; //Break out of the loop if input is valid.
            }
        }
        return choice; //Return the user's choice.
    }
};

//Main function.
int main() {
    GroceryManager manager; //Create an instance of the GroceryManager class.

    while (true) {
        int choice = manager.getUserChoice(); //Get user's menu choice.

        //Switch statement to handle user's choice.
        switch (choice) {
        case 1: {
            std::string itemName;
            std::cout << "Enter the item name: ";
            std::cin >> itemName;
            int quantity = manager.getItemQuantity(itemName);
            std::cout << "Quantity of " << itemName << ": " << quantity << "\n";
            break;
        }
        case 2:
            manager.printItemQuantities();
            break;
        case 3:
            manager.printItemHistogram();
            break;
        case 4:
            manager.saveDataToFile();
            std::cout << "Exiting program.\n";
            return 0;
        }
    }

    return 0;
}
