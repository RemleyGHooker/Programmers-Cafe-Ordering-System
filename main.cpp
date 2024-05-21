/*
  A program to display a menu, alow a customer to order what they want 
  off of them menu and the quantity that they desire, and display the 
  total cost of the item(s) including tax. This program uses parrallel
  arrays and structs.

  By Remley

*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//The number of items in the text file "menu.txt"
const int MAX_MENU = 10;

// struct for items in the menu and their corresponding prices. 
struct MenuItem{
  string name;
  double price;
};

// declare functions 

//read in all of the data from the menu.txt file
void getData(MenuItem menu[], int length);

//output the menu onto the screen
void showMenu(const MenuItem menu[]);

// let customer pick their order, and save their data.
void makeSelection(int selections[]);

// get cost of everything and tax, and print as a reciept.
void printReciept( MenuItem menu[], int selections[], int arraySize);

int main() 
{
  MenuItem menu[MAX_MENU];
  int selections[MAX_MENU]{0};
  
  // call functions
  getData(menu, MAX_MENU);
  showMenu(menu);
  makeSelection(selections);
  printReciept(menu, selections , MAX_MENU);
}

void getData(MenuItem menu[], int length)
{
  // open file
  ifstream file;
  file.open("menu.txt");
  string stringPrice;

  // get lines of data from file, ignore every other line, 
  // because its the price and I'm getting it differently.
  for (int index = 0; index < length; index++)
  {
    file >> menu[index].price;
    getline(file, menu[index].name);
    menu[index].name.erase(0, 1);
  }
  file.close();

}

void showMenu(const MenuItem menu[])
{
  // print menu
  cout << "Welcome to the Programmers' Cafe" << endl;
  cout << "-----------Today's Menu-----------" << endl;
  for (int index = 0; index < MAX_MENU; index++){
    cout << fixed << setprecision(2);
    cout << right << setw(2) << index + 1 << ":"; 
    cout << " " << setw(25) << left << menu[index].name;
    cout << setw(1) << right << "$";
    cout << right << menu[index].price << endl;
  }
}

void makeSelection(int selections[])
{
  int item;
  int quantity;
  cout << "\n";
  cout << "Do you want to place an order? (y/n):";
  char input;
  cin >> input;
  cout << "\n";
  
  // while they want to order do this:
  while(input == 'y' || input == 'Y')
  {
    cout << "Enter item number: ";
    cin >> item;
    cout << "\n";
    
    // if item is not on menu
    while (item < 1 || item > 10)
    {
      cout << "Enter item number between 1 and 10: ";
      cin >> item;
      cout << "\n";
    }
      
    // get item quantity
    cout << "Enter item quantity: ";
    cin >> quantity;
    cout << "\n";
    selections[item - 1] += quantity;
    cout << "Select another item? (y/n):";
    cin >> input;
    cout << "\n";
  }
  
}

void printReciept( MenuItem menu[], int selections[], int arraySize)
{
  const double TAX = 0.07;
  double total = 0;
  
  // print reciept
  cout << "  Thank you for eating at" << endl;
  cout << "   The Programmers\' Cafe " << endl;
  cout << "------------------------------------" << endl;
  cout << "Receipt                 Qty   Amount" << endl;
  cout << "------------------------------------" << endl;
  
  for (int index = 0; index < arraySize; index++)
  {
    if (selections[index] != 0){
      cout << setw(26) << left << menu[index].name;
      cout << setw(3) << left << selections[index];
      cout << setw(2) << left << "$";
      cout << setw(5) << right << selections[index] * menu[index].price;
      cout << endl;
      total += selections[index] * menu[index].price;
    }
  }

  // formatting for reciept
  double taxOutput = total * TAX;
  cout << fixed << setprecision(2);
  cout << setw(2) << left << "    Tax                      $";
  cout << setw(6) << right << setprecision(2) << taxOutput << endl;
  
  cout << setw(28) << left << "    Amount Due               $";
  cout << setw(6) << right << setprecision(2) << total + taxOutput;
}
