
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Table
{
public:
   int tableNumber;
   int minCapacity;
   int maxCapacity;
   bool isAvailable;

   Table(int number, int minCap, int maxCap) : tableNumber(number), minCapacity(minCap), maxCapacity(maxCap), isAvailable(true) {}
};

class Reservation
{
public:
   int guests;
   string date;
   string userName;
   string contactInfo;
   string cardNumber;
   string cardExpDate;

   Reservation(int guests, const string &date, const string &name, const string &contact,
               const string &cardNum, const string &expDate)
       : guests(guests), date(date), userName(name), contactInfo(contact), cardNumber(cardNum), cardExpDate(expDate) {}
};

class Restaurant
{
private:
   vector<Table> tables;
   vector<Reservation> reservations;

public:
   Restaurant()
   {
      // Initialize tables for 1st floor
      for (int i = 1; i <= 20; ++i)
      {
         tables.push_back(Table(i, 8, 10));
      }
      for (int i = 21; i <= 30; ++i)
      {
         tables.push_back(Table(i, 5, 7));
      }

      // Initialize tables for 2nd floor
      for (int i = 31; i <= 45; ++i)
      {
         tables.push_back(Table(i, 1, 3));
      }
      for (int i = 46; i <= 50; ++i)
      {
         tables.push_back(Table(i, 4, 4));
      }
   }

   void displayWelcomeMessage()
   {
      cout << "Welcome to our reservation table program" << endl;
   }

   void saveReservationToFile(const Reservation &reservation)
   {
      ofstream outFile("D:\\reservations.txt", ios::app);

      if (!outFile.is_open())
      {
         cerr << "Error opening file!" << endl;
         return;
      }

      outFile << "Date: " << reservation.date << endl;
      outFile << "Guests: " << reservation.guests << endl;
      outFile << "Name: " << reservation.userName << endl;
      outFile << "Contact Info: " << reservation.contactInfo << endl;
      outFile << "Card Number: " << reservation.cardNumber << endl;
      outFile << "Card Expiry Date: " << reservation.cardExpDate << endl;
      outFile << "---------------------" << endl;

      outFile.close();
   }

   void reserveTable()
   {
      string date;
      cout << "Enter the reservation date (dd/mm/yyyy): ";
      cin >> date;

      int guests;
      cout << "Enter the number of guests: ";
      cin >> guests;

      vector<Table *> availableTables;
      for (Table &table : tables)
      {
         if (guests >= table.minCapacity && guests <= table.maxCapacity && table.isAvailable)
         {
            availableTables.push_back(&table);
         }
      }

      if (availableTables.empty())
      {
         cout << "No available tables for " << guests << " guests." << endl;
         return;
      }

      cout << "Available tables for " << guests << " guests:" << endl;
      for (Table *table : availableTables)
      {
         cout << "Table " << table->tableNumber << " - Capacity: " << table->minCapacity << "-" << table->maxCapacity << endl;
      }

      int tableChoice;
      cout << "Enter the table number you'd like to reserve: ";
      cin >> tableChoice;

      Table *selectedTable = nullptr;
      for (Table *table : availableTables)
      {
         if (table->tableNumber == tableChoice)
         {
            selectedTable = table;
            break;
         }
      }

      if (selectedTable == nullptr)
      {
         cout << "Invalid table choice. Reservation canceled." << endl;
         return;
      }

      int choice = 0;
      do
      {
         cout << "Menu:\n";
         cout << "1. Steak\n2. Soup\n3. Salad\n4. Cake\n5. Cancel the order\n";
         cout << "Enter your choice (1-5): ";
         cin >> choice;

         switch (choice)
         {
         case 1:
         case 2:
         case 3:
         case 4:
         {
            vector<string> menu = {"Steak", "Soup", "Salad", "Cake"};
            int servings;
            cout << "Enter the number of servings for " << menu[choice - 1] << ": ";
            cin >> servings;
            cout << "Processing your order for " << servings << " servings of " << menu[choice - 1] << "..." << endl;
            // Additional logic based on the selected item and servings
            break;
         }
         case 5:
            cout << "Order canceled. Exiting program." << endl;
            return; // Stop running the program
         default:
            cout << "Invalid choice. Please select again." << endl;
            break;
         }

         if (choice != 5)
         {
            // Proceed to the confirmation stage only if choice is not to cancel
            char confirm;
            cout << "Confirm reservation? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {
               string name, contact, cardNum, expDate;
               cout << "The reservation cost is $30. Refund will be provided after dining." << endl;

               cout << "Enter your 16-digit debit card number: ";
               cin >> cardNum;

               cout << "Enter your debit card expiration date (mm/yyyy): ";
               cin >> expDate;

               cout << "Enter your name: ";
               cin.ignore();
               getline(cin, name);

               cout << "Enter your contact information (phone number): ";
               getline(cin, contact);

               reservations.push_back(Reservation(guests, date, name, contact, cardNum, expDate));
               cout << "Thank you for your reservation. We appreciate it :)" << endl;

               saveReservationToFile(reservations.back());
            }
            else
            {
               cout << "Reservation canceled. Thank you for considering us." << endl;
            }
            return; // Stop running the program after confirmation or cancellation
         }
      } while (choice != 5);
   }
};

int main()
{
   Restaurant restaurant;
   restaurant.displayWelcomeMessage();
   restaurant.reserveTable();

   return 0;
}