#include <iostream>
#include <string>
#include<vector>
#include<windows.h>
#include<time.h>

using namespace std;
class Event {
	public:
		virtual void occur(bool highSecurity) = 0; // Pure virtual function with security level parameter
};

class Spaceship {
	public:
		int health;
		Spaceship() : health(100) {} // Initialize health to 100
};

void basicAttack(Spaceship ship, bool highSecurity) {
	int damage = rand() % 10 + 10; // Random damage between 10 and 20
	if (highSecurity) {
		damage -= 5; // Decrease damage by 5 if high security

	}
	ship.health -= damage;
	cout << "Your spaceship took " << damage << " damage from the pirate's basic attack!\n";
	if (ship.health <= 0) {
		cout << "Your spaceship has been destroyed!" << endl;
		exit(0); // Exit the game if spaceship health reaches 0
	}
}

void heavyAttack(Spaceship ship, bool highSecurity) {
	int damage = rand() % 20 + 15; // Random damage between 20 and 35
	if (!highSecurity) {
		damage += 5; // Increase damage by 5 if low security

	}
	ship.health -= damage;

	cout << "Your spaceship took " << damage << " damage from the pirate's heavy attack!\n";
	if (ship.health <= 0) {
		cout << "Your spaceship has been destroyed!" << endl;
		exit(0); // Exit the game if spaceship health reaches 0
	}
}

class SpacePirateAttack : public Event,public Spaceship {
	public:
		void occur(bool highSecurity)  { // Override the occur function with the security level parameter
			cout << "ALERT!!! Space Pirate Attack Detected!" << endl;
			Sleep(1500);
			cout << "Incoming enemy ships are targeting our trade routes!" << endl;
			Sleep(2000);

			cout << "All hands to battle stations!" << endl;
			Sleep(1500);

			int numPirates = rand() % 5 + 1; // Random number of pirate ships (1 to 5)
			if (numPirates == 1) {
				cout << "Enemy force detected: " << numPirates << " pirate ship approaching!\n";
			} else {
				cout << "Enemy force detected: " << numPirates << " pirate ships approaching!\n";
			}
			cout << "\n\t***Brace for impact!***\n" << endl;
			Sleep(4000);
			Spaceship playerShip; // Create player's spaceship object
			for (int i = 1; i <= numPirates; ++i) {
				cout << "(!) Engaging enemy ship " + to_string(i) + "..." << endl;
				int attackType = rand() % 2; // Randomly select attack type
				switch (attackType) {
					case 0:
						basicAttack(playerShip, highSecurity);
						break;
					case 1:
						heavyAttack(playerShip, highSecurity);
						break;
				}
				cout << "\nREMAINING HEALTH: " << playerShip.health << "%\n" << endl;
				Sleep(2000);
			}

			cout << "Space pirate threat neutralized. Returning to normal operations.";
		}
};

class DistanceAndCost {
	private:
		double distance; // in light-years
		int cost; // in gold coins
	public:
		// Constructor
		DistanceAndCost() {}
		DistanceAndCost(double dist, int c) : distance(dist), cost(c) {}
		DistanceAndCost(const DistanceAndCost &obj) {
			distance = obj.distance;
			cost = obj.cost;
		}

		// Getter methods
		double getDistance() const {
			return distance;
		}
		int getCost() const {
			return cost;
		}
};

class Resourse {
	public :
		string resourse,rarity,type,description;
		Resourse() {}

		void setResourse(string resourse) {
			this->resourse =resourse;
		}
		void setrarity(string rarity) {
			this->rarity = rarity;
		}
		void settype(string type) {
			this->type = type;
		}
		void operator=(const Resourse obj) {
			resourse = obj.resourse;
			rarity = obj.rarity;
			type  =obj.type;
			description = obj.description;
		}
};

class Planet {
	private:
		string Name;
		double distance;
	public:
		Resourse *resources_available;
		Planet() {
			resources_available = new Resourse[3]; // Allocate memory for 3 resource strings
		}
		Planet(string n,double d) {
			Name = n;
			distance = d;
		}

		void setName(string name) {
			Name = name;
		}
		void setDistance(double distance) {
			this->distance = distance;
		}
		double getDistance() {
			return distance;
		}

		// Method to set the available resources
		void setResourcesAvailable(string array1[3],string array2[3],string array3[3],string array4[3]) {
			for (int i = 0; i < 3; i++) {
				resources_available[i].resourse = array1[i]; // Copy each resource from the array
				resources_available[i].type = array2[i];
				resources_available[i].rarity = array3[i];
				resources_available[i].description = array4[i];
			}
		}

		~Planet() {
			delete[] resources_available; // Free the allocated memory for resources
		}
		friend DistanceAndCost calculateDistanceAndCost(const Planet& planet1, const Planet& planet2, bool highSecurity);


};
class Demand_Resources : public Planet {

	public :
		vector<Resourse> resources_needed;
		Demand_Resources():Planet() {}
		void function(string resource,string type,string rarity,string description) {
			for(int i=0 ; i<resources_needed.size(); i++) {
				this->resources_needed[i].resourse = resource;
				this->resources_needed[i].type = type;
				this->resources_needed[i].rarity = rarity;
				this->resources_needed[i].description = description;
			}
		}
		void show() {
			for(int i=0 ; i<resources_needed.size(); i++) {
				cout<<"Resource    : "<<resources_needed[i].resourse<<"\n"
				    <<"Type        : "<<resources_needed[i].type<<"\n"
				    <<"Rarity      : "<<resources_needed[i].rarity<<"\n"
				    <<"Description : "<<resources_needed[i].description<<endl;
			}
		}

};

DistanceAndCost calculateDistanceAndCost(Planet planet1,Demand_Resources planet2, bool highSecurity) {
	double distance = planet2.getDistance()-planet1.getDistance();
	int cost;

	// Custom pricing scheme based on the distance and security level
	if (distance >= 1 && distance <= 200) {
		cost = 300; // $300 gold coins per light-year
	} else if (distance >=201 && distance <= 1000) {
		cost = 400; // $400 gold coins per light-year
	} else if (distance >= 1001 && distance <= 100000) {
		cost = 650; // $650 gold coins per light-year
	} else {
		cost = 1000; // $50 gold coins per light-year
	}

	// Adjust cost based on security level
	if (highSecurity) {
		cost += 150; // $150 additional gold coins for high security
	} else {
		cost += 70; // $70 additional gold coins for low security
	}
	DistanceAndCost calculation(distance,cost);

	return calculation;
}

Resourse need(char x) {
	Resourse trade;
	switch (x) {
		case 'a':
		case 'A':
			trade.resourse = "Energon";
			trade.type = "Energy";
			trade.rarity = "Rare";
			trade.description = "Essential energy source for Transformers.";
			break;

		case 'b':
		case 'B':
			trade.resourse = "Cybermatter";
			trade.type = "Material";
			trade.rarity = "Medium";
			trade.description = "Advanced material with unique properties.";
			break;

		case 'c':
		case 'C':
			trade.resourse = "Iridium Alloys";
			trade.type = "Metal";
			trade.rarity = "Exotic";
			trade.description = "Versatile alloys used in construction and technology.";
			break;

		case 'd':
		case 'D':
			trade.resourse = "Kryptonite";
			trade.type = "Mineral";
			trade.rarity = "Rare";
			trade.description = "Radioactive mineral harmful to Kryptonians.";
			break;

		case 'e':
		case 'E':
			trade.resourse = "Kryptonian Technology Artifacts";
			trade.type = "Technology";
			trade.rarity = "Rare";
			trade.description = "Advanced technology remnants of Krypton.";
			break;

		case 'f':
		case 'F':
			trade.resourse = "Rare Crystals";
			trade.type = "Crystal";
			trade.rarity = "Medium";
			trade.description = "Mystical crystals with unique properties.";
			break;

		case 'g':
		case 'G':
			trade.resourse = "Unobtanium";
			trade.type = "Mineral";
			trade.rarity = "Rare";
			trade.description = "Highly valuable mineral with anti-gravity properties.";
			break;

		case 'h':
		case 'H':
			trade.resourse = "Helicoradian";
			trade.type = "Flora";
			trade.rarity = "Medium";
			trade.description = "Bioluminescent plant used for energy.";
			break;

		case 'i':
		case 'I':
			trade.resourse = "Eywa's Blessing";
			trade.type = "Flora";
			trade.rarity = "Common";
			trade.description = "Medicinal plant revered by Na'vi.";
			break;


		case 'j':
		case 'J':
			trade.resourse = "Solarite";
			trade.type = "Energy";
			trade.rarity = "Rare";
			trade.description = "Rare energy crystal with powerful properties.";
			break;
		case 'k':
		case 'K':
			trade.resourse = "Quicksilver";
			trade.type = "Metal";
			trade.rarity = "Common";
			trade.description = "Versatile metal used in various industries.";
			break;

		case 'l':
		case 'L':
			trade.resourse = "Chrono Blossom";
			trade.type = "Flora";
			trade.rarity = "Medium";
			trade.description = "Medicinal plant with time-altering effects.";
			break;

		case 'm':
		case 'M':
			trade.resourse = "Nebula Gas";
			trade.type = "Gas";
			trade.rarity = "Rare";
			trade.description = "Gas harvested from nebulas for advanced propulsion.";
			break;

		case 'n':
		case 'N':
			trade.resourse = "Exo-Flora";
			trade.type = "Flora";
			trade.rarity = "Medium";
			trade.description = "Bioluminescent plant with bioengineering applications.";
			break;

		case 'o':
		case 'O':
			trade.resourse = "Neutronite";
			trade.type = "Metal";
			trade.rarity = "Rare";
			trade.description = "High-density metal for starship construction.";
			break;

		case 'x' :
		case 'X' :
			break;


		default:
			cout<<"Invalid Input!"<<endl;
			break;
	}
	return trade;
}
void Deal() {
	char deal,deal2;
	cout<<"To finalize the deal you'll have to TRADE :\n\n"
	    <<"2 Medium rarity resources for 1 Rare  resource or \n"
	    <<"4 Common rarity resources for 1 Rare  resource \n\n"
	    <<"2 Common rarity resources for 1 Medium rarity resource\n\n"
	    <<"\tWhat do you say deal or not (1/0): ";
	cin>>deal;
	if(deal=='1') {
		cout<<"Your order will soon be sent to the shipment.\n";
	} else {
		cout<<"Ok what do you say about : \n\n"
		    <<"1 Medium and 1 Common rarity resource for 1 Rare resource or\n"
		    <<"3 Common rarity resource for 1 Rare resource\n\n"
		    <<"1 Common rarity resource for 1 medium rarity resource\n\n"
		    <<"\tNow it's a deal or not(1/0)";
		cin>>deal2;
		if(deal2=='1') {
			cout<<"Your order will soon be sent to the shipment.\n";
		} else {
			cout<<"Sorry to say but we can't do any further\n\t\tGOOD BYE\n";
			return;
		}
	}
}

int main() {
	srand(time(NULL));
	char choice_planet,choice_resources;
	bool highSecurity;
	double distance;
	string initial_Resources[3],Type[3],Rarity[3],Description[3];
	Demand_Resources obj;
	Resourse obj1;
	Planet origin("Ragnork",0);
	DistanceAndCost result;
	SpacePirateAttack ship;
	cout << "--------Welcome-------" << endl
	     << "1. Cybertron" << endl
	     << "2. Krypton" << endl
	     << "3. Pandora" << endl
	     << "4. Aldoria" << endl
	     << "5. Nebulon-9"<< endl
	     << "Choose a planet (1-5): ";
	cin >> choice_planet;

	switch (choice_planet) {
		case '1':
			obj.setName("Cybertron");
			cout << "Enter its distance from Ragnork (in light years(1-100000)): ";
			cin >> distance;
			obj.setDistance(distance);
			system("cls");

			initial_Resources[0] = "Energon";
			Type[0] = "Energy";
			Rarity[0] = "Rare";
			Description[0]= "Essential energy source for Transformers";
			initial_Resources[1] = "Cybermatter";
			Type[1] = "Material";
			Rarity[1] = "Medium";
			Description[1]= "Advanced material with unique properties";
			initial_Resources[2] = "Iridium alloys";
			Type[1] = "Matel";
			Rarity[1] = "Common";
			Description[1]= "Versatile alloys used in construction and technology.";
			obj.setResourcesAvailable(initial_Resources,Type,Rarity,Description);

			do {
				cout<<"[A] Energon    [B] Cybermatter                     [C] Iridium Alloys \n"
				    <<"[D] Kryptonite [E] Kryptonian Technology Artifacts [F] Rare Crystals \n"
				    <<"[G] Unobtanium [H] Helicoradian                    [I] Eywa's Blessing \n"
				    <<"[J] Solarite   [K] Quicksilver                     [L] Chrono Blossom \n"
				    <<"[M] Nebula Gas [N] Exo-Flora                       [O] Neutronite\n"
				    <<"[X] Exit\n"
				    <<"Select Resources you need or press x:";
				cin>>choice_resources;
				system("cls");
				obj1 = need(choice_resources);
				if (obj.resources_needed.size() > 0) {
					obj.resources_needed[0] = obj1; // Assigning to existing element
				} else {
					// If resources_needed is empty, use push_back to add obj1
					obj.resources_needed.push_back(obj1);
				}
			} while (choice_resources !='x' && choice_resources != 'X');
			Deal();

			cout << "Enter security level (1 for high, 0 for low): ";
			cin >> highSecurity;
			system("cls");


			result = calculateDistanceAndCost(origin, obj, highSecurity);

			cout << "Travel cost: " << result.getCost() << " gold coins" << endl;
			Sleep(1000);
			system("cls");
			ship.occur(highSecurity);


//////CASE->1//////////
			break;

		// Add cases for other planets (Krypton, Pandora)

		default:
			cout << "Invalid choice. Please choose a valid planet." << endl;
			break;
	}

	return 0;
}