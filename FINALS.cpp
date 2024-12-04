#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class UserAccount;
class Venue;
class Reservation;
class PaymentMethod;
class PaymentRecord;
class Report;
class UserMenu;
class RoleMenu;

class BaseAccount {
public:
	virtual void create() = 0;
	virtual void view() = 0;
	virtual void update() = 0;
	virtual void remove() = 0;
	
	void reset() {
		cout << endl;
		system("pause");
		system("cls");
	}
};

class BaseMenu {
public:
	virtual void menu() = 0;
	
	void reset() {
		cout << endl;
		system("pause");
		system("cls");
	}
};

class AdminAccount {
private:
	string username;
	string password;
	const string adminPassword;
	// AllUsers& allUsers
	// AllVenues& allVenues
	// AllReservations& allReservations
	// AllPaymentMethods& allPaymentMethods
	// AllPaymentRecords& allPaymentRecords

	AdminAccount() : username("admin"), password("admin1"), adminPassword("yuripogi") {}

public:
	// Singleton instance getter
	static AdminAccount& getInstance() {
		static AdminAccount instance;
		return instance;
	}

	// Delete copy constructor and assignment operator
	AdminAccount(const AdminAccount&) = delete;
	void operator=(const AdminAccount&) = delete;

	// Setters
	string getUsername() const { return username; }
	string getPassword() const { return password; }
	// Getters
    void setUsername(string& user) { username = user; }
    void setPassword(string& pass) { password = pass; }
};

class UserAccount : public BaseAccount{
public: 
	void create() override {
		cout << "- User Create Account -\n\n";
		
		reset();
	}
	
	void view() override {
		cout << "- User View Account -\n\n";
		
		reset();
	}
	
	void update() override {
		cout << "- User Update Account -\n\n";
		
		reset();
	}
	
	void remove() override {
		cout << "- User Remove Account -\n\n";
		
		reset();
	}
};

class Venue {
private:
    char venueType;
    string venueName;
    string venueSize;
    int venueCapacity;
    double venueRate;
    string venueDescription;

    // Reservation structure
    struct Reservation {
        string customerName;
        string date;
        string time;
    };

    vector<Reservation> reservations;  // Holds reservations

public:
    // Constructor
    Venue(char type, const string& name, const string& size, int capacity, double rate, const string& description)
        : venueType(type), venueName(name), venueSize(size), venueCapacity(capacity), venueRate(rate), venueDescription(description) {}

    // Setters and Getters
    void setVenueType(char type) { venueType = type; }
    void setVenueName(const string& name) { venueName = name; }
    void setVenueSize(const string& size) { venueSize = size; }
    void setVenueCapacity(int capacity) { venueCapacity = capacity; }
    void setVenueRate(double rate) { venueRate = rate; }
    void setVenueDescription(const string& description) { venueDescription = description; }

    char getVenueType() const { return venueType; }
    string getVenueName() const { return venueName; }
    string getVenueSize() const { return venueSize; }
    int getVenueCapacity() const { return venueCapacity; }
    double getVenueRate() const { return venueRate; }
    string getVenueDescription() const { return venueDescription; }

    // Function to make a reservation
    void reserveVenue(const string& customerName, const string& date, const string& time) {
        Reservation newReservation = { customerName, date, time };
        reservations.push_back(newReservation);
        cout << "Reservation made successfully for " << customerName << " on " << date << " at " << time << "." << endl;
    }

    // Display all reservations for the venue
    void showReservations() const {
        if (reservations.empty()) {
            cout << "No reservations for this venue." << endl;
        } else {
            cout << "Reservations for " << venueName << ":\n";
            for (const auto& res : reservations) {
                cout << "Customer: " << res.customerName << ", Date: " << res.date << ", Time: " << res.time << endl;
            }
        }
    }

    bool viewReservations() {
        if (reservations.empty()) {
            return false;  // No reservations
        }

        cout << "\nReservations for " << getVenueName() << ":\n";
        for (size_t i = 0; i < reservations.size(); ++i) {
            const Reservation& res = reservations[i];
            cout << "Reservation #" << i + 1 << "\n";
            cout << "Customer: " << res.customerName << "\n";
            cout << "Date: " << res.date << "\n";
            cout << "Time: " << res.time << "\n";
            cout << "------------------------\n";
        }
        return true;  // Reservations found
    }
	
	    
	    // Search for a venue by name
	    static Venue* searchVenue(vector<Venue*> venues, const string& name) {
	    for (auto& venue : venues) {
	        if (venue->getVenueName() == name) {
	            return venue;  // Return the pointer itself, not dereferenced
	        }
	    }
	    return nullptr;  // Return null if not found
	}

    // Update a reservation (update by customer name)
    bool updateReservation(const string& customerName, const string& newDate, const string& newTime) {
        for (auto& res : reservations) {
            if (res.customerName == customerName) {
                res.date = newDate;
                res.time = newTime;
                cout << "Reservation for " << customerName << " has been updated to " << newDate << " at " << newTime << "." << endl;
                return true;
            }
        }
        cout << "Reservation not found for " << customerName << "." << endl;
        return false;
    }
    
	};

class AllVenues : public BaseAccount {
	private:
		vector<Venue*> allVenues;

	public:		
	AllVenues() {
		allVenues.push_back(new Venue('I', "GRAND CANVAS", "BIG", 100, 25000, "An expansive open space is perfect for all types of events."));
		allVenues.push_back(new Venue('I', "MIDSCALE CANVAS", "MEDIUM", 50, 14000, "A cozy space for smaller gatherings."));
		allVenues.push_back(new Venue('I', "SNUG CANVAS", "SMALL", 25, 6000, "An intimate venue is perfect for private events."));
		allVenues.push_back(new Venue('I', "KTV LOUNGE", "SMALL", 20, 10000, "A karaoke space is ideal for music lovers."));
		allVenues.push_back(new Venue('I', "THE FORUM", "SMALL", 15, 10000, "A professional meeting place is perfect for business events."));
		allVenues.push_back(new Venue('O', "OPEN AREA", "BIG", 100, 22000, "A spacious outdoor venue is great for large gatherings."));
		allVenues.push_back(new Venue('O', "BACKYARD HAVEN", "SMALL", 20, 12000, "An inviting backyard is perfect for casual events."));
		allVenues.push_back(new Venue('O', "ROOFTOP TERRACE", "MEDIUM", 40, 35000, "An expansive rooftop for unforgettable views."));
		allVenues.push_back(new Venue('O', "TINY CABIN", "SMALL", 6, 20000, "An escape to this charming tiny cabin in nature."));
		allVenues.push_back(new Venue('O', "MULTISPORTS COURT", "MEDIUM", 10, 4000, "A versatile sports court is ideal for active events."));
	}
	
	vector<Venue*> getAllVenues(){
		return allVenues;
	}
	
	void displayAllVenues() {
    cout << "\n- All Venues -\n\n";
    
    // Set the column widths for neat table formatting
    cout << left << setw(5) << "ID" << setw(20) << "Venue Name" << setw(10) << "Type" 
         << setw(10) << "Size" << setw(12) << "Capacity" << setw(10) << "Rate" << setw(30) << "Description\n";
    cout << "---------------------------------------------------------------\n";
    
    for (size_t i = 0; i < allVenues.size(); ++i) {
        Venue* v = allVenues[i];
        
        // Display the venue details in a table format
        cout << left << setw(5) << i + 1
             << setw(20) << v->getVenueName() 
             << setw(10) << v->getVenueType()
             << setw(10) << v->getVenueSize()
             << setw(12) << v->getVenueCapacity()
             << setw(10) << v->getVenueRate()
             << setw(30) << v->getVenueDescription() << "\n";
    }
    cout << "---------------------------------------------------------------\n";
    reset();  // Assuming you still want to reset after viewing.
}

	
	void create() override {
		char type;
        string name, size, description;
        int capacity;
        double rate;

		cout << "- Create Venue -\n\n";
        validateVenueType(type);
        cout << "Enter Venue Name: ";
        cin.ignore();
        getline(cin, name);
        validateVenueSize(size);
        validateVenueCapacity(capacity);
        validateVenueRate(rate);
        cin.ignore();
        cout << "Enter Venue Description: ";
        getline(cin, description);

        allVenues.push_back(new Venue(type, name, size, capacity, rate, description));
        cout << "Venue created successfully.\n";
		
		reset();
	}
	
	void view() override {
		cout << "\n- List of Venues -\n\n";
        for (size_t i = 0; i < allVenues.size(); ++i) {
            Venue* v = allVenues[i];
            cout << "Venue #" << i + 1 << "\n";
            cout << "Type: " << v->getVenueType() << "\n";
            cout << "Name: " << v->getVenueName() << "\n";
            cout << "Size: " << v->getVenueSize() << "\n";
            cout << "Capacity: " << v->getVenueCapacity() << "\n";
            cout << "Rate: " << v->getVenueRate() << "\n";
            cout << "Description: " << v->getVenueDescription() << "\n";
            cout << "--------------------\n";
        }
		reset();
	}
	
	void remove() override {
		cout << "\n- List of Venues -\n\n";
        for (size_t i = 0; i < allVenues.size(); ++i) {
            Venue* v = allVenues[i];
            cout << "Venue #" << i + 1 << "\n";
            cout << "Name: " << v->getVenueName() << "\n";
            cout << "--------------------\n\n";
        }
        
		cout << "- Remove Venue -\n\n";
		int index;
        cout << "Enter Venue Number to Remove: ";
        cin >> index;
        if (index < 1 || index > allVenues.size()) {
            cout << "Invalid venue number.\n";
            return;
        }

        delete allVenues[index - 1];
        allVenues.erase(allVenues.begin() + index - 1);
        cout << "Venue removed successfully.\n";
		reset();
	}
	
	void viewReservation() {
	    bool anyReservations = false;
	
	    for (size_t i = 0; i < allVenues.size(); ++i) {
	        Venue* venue = allVenues[i];
	        if (venue->viewReservations()) {
	            anyReservations = true;  // At least one venue has reservations
	        }
	    }
	
	    if (!anyReservations) {
	        cout << "No reservations found.\n";  // Print this message only once
	    }
	}
	
	void updateReservation() {
    // Display all venues with their names
    cout << "\n- List of Venues -\n\n";
    for (size_t i = 0; i < allVenues.size(); ++i) {
        cout << "Venue #" << i + 1 << ": " << allVenues[i]->getVenueName() << "\n";
    }

    // Prompt the user to select a venue
    int venueIndex;
	    cout << "\nEnter Venue Number to Update Reservation: ";
	    cin >> venueIndex;
	
	    // Validate venue selection
	    if (cin.fail() || venueIndex < 1 || venueIndex > allVenues.size()) {
	        cin.clear(); // Clear error state
	        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
	        cout << "Invalid venue number. Please enter a number between 1 and " << allVenues.size() << ".\n";
	        return;
	    }
	
	    Venue* selectedVenue = allVenues[venueIndex - 1];
	
	    // Check if the selected venue has reservations
	    if (!selectedVenue->viewReservations()) {
	        cout << "No reservations found for the selected venue.\n";
	        return;
	    }
	
	    // Prompt user to enter the customer name for the reservation they want to update
	    string customerName, newDate, newTime;
	    cin.ignore(); // Clear input buffer
	    cout << "Enter Customer Name for the Reservation to Update: ";
	    getline(cin, customerName);
	
	    // Prompt for new reservation details
	    cout << "Enter New Date (YYYY-MM-DD): ";
	    getline(cin, newDate);
	    cout << "Enter New Time (HH:MM): ";
	    getline(cin, newTime);
	
	    // Attempt to update the reservation
	    if (!selectedVenue->updateReservation(customerName, newDate, newTime)) {
	        cout << "Failed to update the reservation. No matching reservation found for " << customerName << ".\n";
	    } else {
	        cout << "Reservation updated successfully for " << customerName << "!\n";
	    }
	}

		void update() override {
		cout << "\n- List of Venues -\n\n";
        for (size_t i = 0; i < allVenues.size(); ++i) {
            Venue* v = allVenues[i];
            cout << "Venue #" << i + 1 << "\n";
            cout << "Name: " << v->getVenueName() << "\n";
            cout << "--------------------\n\n";
        }
        
		cout << "- Update Venue -\n\n";
		int index;
        cout << "Enter Venue Number to Update: ";
        cin >> index;
        if (index < 1 || index > allVenues.size()) {
            cout << "Invalid venue number.\n";
            return;
        }

        Venue* v = allVenues[index - 1];
        cout << "Updating Venue #" << index << "\n";
        char type;
        string name, size, description;
        int capacity;
        double rate;

        validateVenueType(type);
        cout << "Enter New Venue Name: ";
        cin.ignore();
        getline(cin, name);
        validateVenueSize(size);
        validateVenueCapacity(capacity);
        validateVenueRate(rate);
        cin.ignore();
        cout << "Enter New Venue Description: ";
        getline(cin, description);

        v->setVenueType(type);
        v->setVenueName(name);
        v->setVenueSize(size);
        v->setVenueCapacity(capacity);
        v->setVenueRate(rate);
        v->setVenueDescription(description);

        cout << "Venue updated successfully.\n";
		reset();
	}
	
	
	~AllVenues() {
        for (Venue* v : allVenues) {
            delete v;
        }
    }
    
    void validateVenueType(char& type) {
	    string input;
	    bool condition = true;
	    while (condition) {
	        cout << "Enter Venue Type (I/O): ";
	        cin >> input;
	
	        // Check if the input is a single character
	        if (input.length() == 1) {
	            type = toupper(input[0]); // Convert to uppercase
	
	            // Check if input is valid
	            if (type == 'I' || type == 'O') {
	                break; // Exit loop if input is valid
	            }
	        }
	        cout << "Invalid input. Please enter 'I' or 'O' only.\n";
	    }
	}
	void validateVenueSize(string& size) {
	    string input;
	    bool condition = true;
	    while (condition) {
	        cout << "Enter Venue Size (SMALL/MEDIUM/BIG): ";
	        getline(cin, input);
	
	        // Convert input to uppercase
	        for (char& c : input) {
	            c = toupper(c);
	        }
	
	        // Check if input matches valid options
	        if (input == "SMALL" || input == "MEDIUM" || input == "BIG") {
	            size = input; // Assign valid input to size
	            break;
	        }
	
	        cout << "Invalid input. Please enter 'SMALL', 'MEDIUM', or 'BIG' only.\n";
	    }
	}
	void validateVenueCapacity(int& capacity) {
	    string input;
	    bool condition = true;
	    while (condition) {
	        cout << "Enter Venue Capacity: ";
	        cin >> input;
	
	        // Check if the input contains only digits (no letters)
	        bool isValid = true;
	        for (char c : input) {
	            if (!isdigit(c)) {
	                isValid = false;
	                break;
	            }
	        }
	
	        // If valid and not starting with '0' (for non-zero positive integers)
	        if (isValid && input[0] != '0' && !input.empty()) {
	            capacity = stoi(input);  // Convert string to integer
	            break;
	        }
	
	        // Invalid input messages
	        cout << "Invalid input. Please enter a positive integer without leading zeros.\n";
	    }
	}
	void validateVenueRate(double& rate) {
		    string input;
		    bool condition = true;
		    while (condition) {
		        cout << "Enter Venue Rate: ";
		        cin >> input;
		
		        // Check if the input contains only digits (no letters)
		        bool isValid = true;
		        for (char c : input) {
		            if (!isdigit(c)) {
		                isValid = false;
		                break;
		            }
		        }
		
		        // If valid and not starting with '0' (for non-zero positive integers)
		        if (isValid && input[0] != '0' && !input.empty()) {
		            rate = stoi(input);  // Convert string to integer
		            break;
		        }
		
		        // Invalid input messages
		        cout << "Invalid input. Please enter a positive integer without leading zeros.\n";
		    }
		}
	
};

/*class Reservation : public BaseAccount {
private:
	string venueNames;
	
public:
	Reservation(string name) : venueNames(name) {}
	
	void setVenueNames(string name) { venueNames = name; }
	
	string getVenueNames() const { return venueNames; }
};

class AllReservation : public BaseAccount {
	private:
		vector<Reservation*> a; 
		
	public:
	void create() override {
		cout << "- Create Reservation -\n\n";
		
		reset();
	}
	
	void view() override {
		cout << "- View Reservation -\n\n";
		
		reset();
	}
	
	void update() override {
		cout << "- Update Reservation -\n\n";
		
		reset();
	}
	
	void remove() override {
		cout << "- Remove Reservation -\n\n";
		
		reset();
	}
}; */

class PaymentMethod : public BaseAccount {
public:
	void create() override {
		cout << "- Create Payment Method -\n\n";
		
		reset();
	}
	
	void view() override {
		cout << "- View Payment Method -\n\n";
		
		reset();
	}
	
	void update() override {
		cout << "- Update Payment Method -\n\n";
		
		reset();
	}
	
	void remove() override {
		cout << "- Remove Payment Method -\n\n";
		
		reset();
	}
};

class PaymentRecord {
public:
	void reset() {
		cout << endl;
		system("pause");
		system("cls");
	}
	
	void pendingPayment() {
		cout << "- Pending Payment Record -\n\n";
		
		reset();
	}
	
	void overduePayment() {
		cout << "- Overdue Payment Record -\n\n";
		
		reset();
	}
	
	void completedPayment() {
		cout << "- Completed Payment Record -\n\n";
		
		reset();
	}
	
	void deletePayment() {
		cout << "- Delete Payment Record -\n\n";
		
		reset();
	}
};

class Report : public BaseAccount {
public:
	void create() override {
		cout << "- Create Report -\n\n";
		
		reset();
	}
	
	void view() override {
		cout << "- View Report -\n\n";
		
		reset();
	}
	
	void update() override {
		cout << "- Update Report -\n\n";
		
		reset();
	}
	
	void remove() override {
		cout << "- Remove Report -\n\n";
		
		reset();
	}
};

int AdminMenu() {
	//reset();
	bool condition = true;
	int choice;

	while(condition) {
		cout << "Welcome to the back end of this system!\n\n";
		cout << "- Choose a menu: -\n";
		cout << "1 - Manage User Section\n";
		cout << "2 - Manage Venue Section\n";
		cout << "3 - Manage Reservation Section\n";
		cout << "4 - Manage Payment Section\n";
		cout << "5 - Manage Payment Record Section\n";
		cout << "6 - Generate Report Section\n";
		cout << "7 - Return\n";
		cout << ": ";
		cin >> choice;

		switch(choice) {
			case 1: {
				// reset();
				bool MUAcondition = true;
				int MUAchoice;

				while(MUAcondition) {
					cout << "Manage User Account\n\n";
					cout << "- Choose a menu: -\n";
					cout << "1 - Create User Account\n";
					cout << "2 - View User Account\n";
					cout << "3 - Update User Account\n";
					cout << "4 - Remove User Account\n";
					cout << "5 - Return\n";
					cout << ": ";
					cin >> MUAchoice;

					switch(MUAchoice) {
						case 1: {
							// reset();
							UserAccount ua;
							ua.create();
							break;
						}
						case 2: {
							// reset();
							UserAccount ua;
							ua.view();
							break;
						}
						case 3: {
							// reset();
							UserAccount ua;
							ua.update();
							break;
						}
						case 4: {
							// reset();
							UserAccount ua;
							ua.remove();
							break;
						}
						case 5: {
							MUAcondition = false;
							break;
						}
						default:
							cout << "Invalid choice. Please try again.\n";
					}
				}
				// reset();
				break;
			}
			case 2: {
					cout << endl;
					system("pause");
					system("cls");
					bool MVScondition = true;
					int MVSchoice;
					AllVenues allvenues;
					Venue v (' ', "", "", 0, 0.0, "");
					
					while(MVScondition) {
						cout << "Manage Venue Section\n\n";
						cout << "- Choose a menu: -\n";
						cout << "1 - Create Venue\n";
						cout << "2 - View Venue\n";
						cout << "3 - Update Venue\n";
						cout << "4 - Remove Venue\n";
						cout << "5 - Return\n";
						cout << ": ";
						cin >> MVSchoice;
						
						switch(MVSchoice) {
							case 1: {
								cout << endl;
								system("pause");
								system("cls");
								allvenues.create();
								break;
							}
							case 2: {
								cout << endl;
								system("pause");
								system("cls");
								allvenues.view();
								break;
							}
							case 3: {
								cout << endl;
								system("pause");
								system("cls");
								allvenues.update();
								break;
							}
							case 4: {
								cout << endl;
								system("pause");
								system("cls");
								allvenues.remove();
								break;
							}
							case 5: {
								MVScondition = false;
								break;
							}
							default: 
								cout << "Invalid choice. Please try again.\n";
							}
						}
						cout << endl;
						system("pause");
						system("cls");
						break;
					}
				case 3: {
				    cout << endl;
					system("pause");
					system("cls");
				    bool MRScondition = true;
				    int MRSchoice;
				    
				    // Create an instance of AllVenues
				    AllVenues v; 
				
				    while(MRScondition) {
				        cout << "Manage Reservation Section\n\n";
				        cout << "- Choose a menu: -\n";
				        cout << "1 - Create Reservation\n";
				        cout << "2 - View Reservation\n";
				        cout << "3 - Update Reservation\n";
				        cout << "4 - Remove Reservation\n";
				        cout << "5 - Return\n";
				        cout << ": ";
				        cin >> MRSchoice;
				
				        switch (MRSchoice) {
				            case 1: {
				                cout << endl;
								system("pause");
								system("cls");
				                string venueName, customerName, date, time;
				                v.displayAllVenues();
				                cout << "\nEnter venue name: ";
								cin.ignore(); 
								getline(cin, venueName);
				                
								 // Clear the input buffer
								
				                // Find venue by name
				                Venue* venue = Venue::searchVenue(v.getAllVenues(), venueName);
				                if (venue) {
				                    cout << "Enter customer name: ";
				                    getline(cin, customerName);
				                    cout << "Enter reservation date (YYYY-MM-DD): ";
				                    getline(cin, date);
				                    cout << "Enter reservation time (HH:MM): ";
				                    getline(cin, time);
				
				                    venue->reserveVenue(customerName, date, time);
				                } else {
				                    cout << "Venue not found.\n";
				                }
				                break;
				            }
				            case 2: {
				            	cout << "\n- View All Reservations -\n\n";
                				v.viewReservation();
                				cout << endl;
								system("pause");
								system("cls");	
								break;
							}
				            case 3: {
				            	v.updateReservation();
				            	cout << endl;
								system("pause");
								system("cls");
								break;
							}
				            case 4: {
				            	
								break;
							}
				            case 5:
				                MRScondition = false;
				                break;
				            default:
				                cout << "Invalid choice. Please try again.\n";
				                break;
				        }
				    }
				    break;
				}
			case 4: {
				// reset();
				bool MPMScondition = true;
				int MPMSchoice;

				while(MPMScondition) {
					cout << "Manage Payment Method Section\n\n";
					cout << "- Choose a menu: -\n";
					cout << "1 - Create Payment Method\n";
					cout << "2 - View Payment Method\n";
					cout << "3 - Update Payment Method\n";
					cout << "4 - Remove Payment Method\n";
					cout << "5 - Return\n";
					cout << ": ";
					cin >> MPMSchoice;

					switch(MPMSchoice) {
						case 1: {
							// reset();
							PaymentMethod pm;
							pm.create();
							break;
						}
						case 2: {
							// reset();
							PaymentMethod pm;
							pm.view();
							break;
						}
						case 3: {
							// reset();
							PaymentMethod pm;
							pm.update();
							break;
						}
						case 4: {
							// reset();
							PaymentMethod pm;
							pm.remove();
							break;
						}
						case 5: {
							MPMScondition = false;
							break;
						}
						default:
							cout << "Invalid choice. Please try again.\n";
						}
					}
					// reset();
					break;
				}
			case 5: {
				// reset();
				bool MPRScondition = true;
				int MPRSchoice;

				while(MPRScondition) {
					cout << "Manage Payment Record Section\n\n";
					cout << "- Choose a menu: -\n";
					cout << "1 - Pending Payment Method\n";
					cout << "2 - Overdue Payment Method\n";
					cout << "3 - Completed Payment Method\n";
					cout << "4 - Delete Payment Method\n";
					cout << "5 - Return\n";
					cout << ": ";
					cin >> MPRSchoice;

					switch(MPRSchoice) {
						case 1: {
							// reset();
							PaymentRecord pr;
							pr.pendingPayment();
							break;
						}
						case 2: {
							// reset();
							PaymentRecord pr;
							pr.overduePayment();
							break;
						}
						case 3: {
							// reset();
							PaymentRecord pr;
							pr.completedPayment();
							break;
						}
						case 4: {
							// reset();
							PaymentRecord pr;
							pr.deletePayment();
							break;
						}
						case 5: {
							MPRScondition = false;
							break;
						}
						default:
							cout << "Invalid choice. Please try again.\n";
						}
					}
					// reset();
					break;
				}
			case 6: {
				// reset();
				bool MRScondition = true;
				int MRSchoice;

				while(MRScondition) {
					cout << "Manage Report Section\n\n";
					cout << "- Choose a menu: -\n";
					cout << "1 - Create Report\n";
					cout << "2 - View Report\n";
					cout << "3 - Update Report\n";
					cout << "4 - Delete Report\n";
					cout << "5 - Return\n";
					cout << ": ";
					cin >> MRSchoice;

					switch(MRSchoice) {
						case 1: {
							// reset();
							Report r;
							r.create();
							break;
						}
						case 2: {
							// reset();
							Report r;
							r.view();
							break;
						}
						case 3: {
							// reset();
							Report r;
							r.update();
							break;
						}
						case 4: {
							// reset();
							Report r;
							r.remove();
							break;
						}
						case 5: {
							MRScondition = false;
							break;
						}
						default:
							cout << "Invalid choice. Please try again.\n";
						}
					}
					// reset();
					break;
				}
			case 7: {
				return -1;
				exit(0);
				break;
			}
			default:
				cout << "Invalid choice. Please try again.\n";
		}
	}
};

class AdminLogIn {
public:
	int logIn() {
		string username, password;

		cout << "- Admin Log In -\n\n";

		cout << "Enter username: ";
		cin.ignore();
		getline(cin, username);

		cout << "Enter password: ";
		getline(cin, password);

		// Access the AdminAccount instance
		AdminAccount& adminAccount = AdminAccount::getInstance();

		// Check login credentials
		if (adminAccount.getUsername() == username && adminAccount.getPassword() == password) {
			cout << "Login successful! Welcome, " << username << "!\n\n";
			system("pause");
			system("cls");
			AdminMenu();
			return 0; // Login successful
		}

		cout << "Invalid username or password.\n\n";
		system("pause");
		system("cls");
		return -1; // Login failed
	}
};

class UserMenu : public BaseMenu {
public:
	void menu() override {
		reset();
		bool condition = true;
		int choice;
		AllVenues allVenue;
		Venue v('x', "", "", 0, 0.0, "");
		
		while(condition) {
			cout << "Welcome to the Venue Reservation Management System!\n\n";
			cout << "- Choose a menu: -\n";
			cout << "1 - Search Venues\n";
			cout << "2 - Create Reservations\n";
			cout << "3 - View Reservations\n";
			cout << "4 - Update 	Reservations\n";
			cout << "5 - Delete Reservations\n";
			cout << "6 - Exit system\n";
			cout << ": ";
			cin >> choice;
			reset();
			
			switch(choice) {
				case 1: {
		
					allVenue.view();
					break;
				}
				case 2: {
					string name, date, time;
					cout << "Enter name: ";
				    getline(cin, name);
				    cout << "Enter date: ";
				    getline(cin, date);
				    cout << "enter time: ";
				    getline(cin, time);
				    v.reserveVenue(name, date, time);
					break;
				}
				case 3: {
					//Reservation r;
					//r.view();
					break;
				}
				case 4: {
					//Reservation r;
					//r.update();
					break;
				}
				case 5: {
					//Reservation r;
					//r.remove();
					break;
				}
				case 6: {
					cout << "Exiting system. Thank you for using VRMS!";
					exit(0);
					break;
				}
				default:
					cout << "Invalid choice. Please try again.\n";
			}
		}
	}
};

class UserLogIn {
public:
	int logIn() {
		cout << "- Admin log In account -\n\n";
		
		cout << endl;
		system("pause");
		system("cls");
	}
	
	void registerOrLogIn() {
		bool condition = true;
		int choice;
		
		while(condition) {
			cout << "- Log In or Register: -\n\n";
			cout << "1 - Register\n";
            cout << "2 - Log In\n";
            cout << "3 - Return\n";
            cout << ": ";
            cin >> choice;
            
            switch(choice) {
            	case 1: {
            		UserAccount uc;
            		cout << endl;
					system("pause");
					system("cls");
            		uc.create();
            		break;
            	}
            	case 2: {
            		cout << endl;
					system("pause");
					system("cls");
            		logIn();
            		break;
            	}
            	case 3:
            		condition = false;
            		break;
            	default:
            		cout << "Invalid input. Please try again.\n";
			}
		}
	}
};

class RoleMenu : public BaseMenu {
private:
	const string adminPassword = "yuripogi";  // Static password for admin login

public:
	void menu() override {
		bool condition = true;
		int choice;
		string enterUsername, enterPassword;

		while (condition) {
			reset();
			cout << "- Please enter your role: -\n\n";
			cout << "1 - User\n";
			cout << "2 - Admin\n";
			cout << "3 - Exit system\n";
			cout << ": ";
			cin >> choice;

			switch (choice) {
				case 1: {
					reset();
					UserLogIn ua;
					ua.registerOrLogIn();  // Proceed with user login
					break;
				}
				case 2: {
					AdminLogIn ac;
					ac.logIn();
					break;
				}
				case 3: {
					condition = false;  // Exit the menu loop
					break;
				}
				default:
					cout << "Invalid choice. Please try again.\n";  // Handle invalid input
			}
		}
	}
};

void welcome () {
	cout << "Finals program - Jopia & Lat\n\n";
}

int main() {
	welcome();
	RoleMenu rm;
	rm.menu();
	return 0;
}