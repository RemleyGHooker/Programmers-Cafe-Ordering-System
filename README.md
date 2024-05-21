# Programmers' Cafe Ordering System

This program allows a customer to view a menu, place an order by selecting items and their quantities, and receive a receipt displaying the total cost including tax. The program uses parallel arrays and structs to manage the menu items and their prices.

## Features
- Reads menu items from a `menu.txt` file.
- Displays the menu with item names and prices.
- Allows customers to select items and specify quantities.
- Generates a receipt including tax.

## Requirements
- C++ compiler
- `menu.txt` file containing the menu items and their prices.

## How to Use
1. Ensure you have a `menu.txt` file with the menu items in the following format:
    ```
    5.99
    Coffee
    7.49
    Latte
    2.99
    Cookie
    ...
    ```

2. Compile the program:
    ```sh
    g++ -o cafe_ordering cafe_ordering.cpp
    ```

3. Run the compiled program:
    ```sh
    ./cafe_ordering
    ```

4. Follow the on-screen instructions to place your order.

## File Structure
- `cafe_ordering.cpp`: Main program file.
- `menu.txt`: File containing the menu items and their prices.

## Code Explanation

### Libraries Used
```cpp
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
```

- iostream: For standard input/output.
- fstream: For file input/output.
- iomanip: For input/output manipulation.

## Constants and Structs
```cpp
const int MAX_MENU = 10;

struct MenuItem {
  string name;
  double price;
};
```
- MAX_MENU: The number of items in the menu.
- MenuItem: Structure to store a menu item's name and price.

## Function Declarations

### Main Function
```cpp
int main() 
{
  MenuItem menu[MAX_MENU];
  int selections[MAX_MENU]{0};

  getData(menu, MAX_MENU);
  showMenu(menu);
  makeSelection(selections);
  printReciept(menu, selections, MAX_MENU);
}
```
- Initializes the menu and selections arrays.
- Calls functions to read menu data, display the menu, handle customer selections, and print the receipt.
- 
## Function Definitions

#### getData
- Reads menu data from menu.txt file.

```cpp
void getData(MenuItem menu[], int length)
{
  ifstream file;
  file.open("menu.txt");
  
  for (int index = 0; index < length; index++)
  {
    file >> menu[index].price;
    getline(file, menu[index].name);
    menu[index].name.erase(0, 1);
  }
  file.close();
}
```

#### showMenu
- Displays the menu items and their prices.

```cpp
void showMenu(const MenuItem menu[])
{
  cout << "Welcome to the Programmers' Cafe" << endl;
  cout << "-----------Today's Menu-----------" << endl;
  
  for (int index = 0; index < MAX_MENU; index++) {
    cout << fixed << setprecision(2);
    cout << right << setw(2) << index + 1 << ": ";
    cout << setw(25) << left << menu[index].name;
    cout << setw(1) << right << "$";
    cout << right << menu[index].price << endl;
  }
}
```

#### makeSelection
- Handles customer selections and quantities.
```cpp
void makeSelection(int selections[])
{
  int item;
  int quantity;
  cout << "\nDo you want to place an order? (y/n):";
  char input;
  cin >> input;
  cout << "\n";

  while(input == 'y' || input == 'Y')
  {
    cout << "Enter item number: ";
    cin >> item;
    cout << "\n";
    
    while (item < 1 || item > 10)
    {
      cout << "Enter item number between 1 and 10: ";
      cin >> item;
      cout << "\n";
    }

    cout << "Enter item quantity: ";
    cin >> quantity;
    cout << "\n";
    selections[item - 1] += quantity;
    cout << "Select another item? (y/n):";
    cin >> input;
    cout << "\n";
  }
}
```

#### printReciept
- Prints the receipt with itemized costs and tax.

```cpp
void printReciept(MenuItem menu[], int selections[], int arraySize)
{
  const double TAX = 0.07;
  double total = 0;
  
  cout << "  Thank you for eating at" << endl;
  cout << "   The Programmers\' Cafe " << endl;
  cout << "------------------------------------" << endl;
  cout << "Receipt                 Qty   Amount" << endl;
  cout << "------------------------------------" << endl;
  
  for (int index = 0; index < arraySize; index++)
  {
    if (selections[index] != 0) {
      cout << setw(26) << left << menu[index].name;
      cout << setw(3) << left << selections[index];
      cout << setw(2) << left << "$";
      cout << setw(5) << right << selections[index] * menu[index].price;
      cout << endl;
      total += selections[index] * menu[index].price;
    }
  }

  double taxOutput = total * TAX;
  cout << fixed << setprecision(2);
  cout << setw(2) << left << "    Tax                      $";
  cout << setw(6) << right << taxOutput << endl;
  cout << setw(28) << left << "    Amount Due               $";
  cout << setw(6) << right << total + taxOutput;
}
```

## Contributing
Feel free to submit issues or pull requests if you have suggestions for improving this project.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.
