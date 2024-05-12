//Project Name : The Inter-Galactic Traders.
//Coders : 
//->Asaf Khan 23p-3048
//->Ahmad Jan
/*
Code Purpose:
-------------

The code is simulating space resource collection and trading between different planets. There are Planet classes that represent different planets in the galaxy.
Each planet has attributes like name, distance from a central point, and what resources are available on that planet.
There are also Resource classes that define different types of resources. Each resource has properties like its name, type, rarity, and description.
The DemandResources class inherits from Planet class. This represents planets that need specific resources. 
It has an additional attribute to define what resources are needed.There is a Spaceship class that can be used to travel between planets. 
It has health attribute to track its condition.Event is an abstract class that defines events that can happen like SpacePirateAttacks. 
This inherits from Spaceship since attacks involve spaceships.The code would have functions to calculate distances and costs to travel between planets, 
check what resources are available or needed on different planets, simulate events like attacks, and allow trading/collection of resources to fulfill demands.
The main() function likely creates objects of the different classes, sets their attributes and relationships, and then calls functions to simulate the resource 
trading/collection between planets over time.
*/

#include <iostream>
#include <string>
#include<vector>
#include<windows.h>
#include<time.h>

using namespace std;
class Event {
	public:
		virtual void occur(bool highSecurity) = 0;
};

class Spaceship {
	public:
		int health;
		Spaceship() : health(100) {}
};

int basicAttack(Spaceship ship, bool highSecurity) {
	int damage = rand() % 10 + 10;
	if (highSecurity) {
		damage -= 5;
	}
	ship.health -= damage;
	cout << "Your spaceship took " << damage << " damage from the pirate's basic attack!\n";

	Sleep(2000);
	if (ship.health <= 0) {
		cout << "Your spaceship has been destroyed!" << endl;
		Sleep(2000);
		exit(0);
	}
	return damage;
}

int heavyAttack(Spaceship ship, bool highSecurity) {
	int damage = rand() % 20 + 15;
	if (!highSecurity) {
		damage += 5;

	}
	ship.health -= damage;

	cout << "Your spaceship took " << damage << " damage from the pirate's heavy attack!\n";

	Sleep(2000);
	if (ship.health <= 0) {
		cout << "Your spaceship has been destroyed!" << endl;
		Sleep(2000);
		exit(0);
	}
	return damage;
}


class SpacePirateAttack : public Event,public Spaceship {
	public:
		void occur(bool highSecurity)  {
			cout << "ALERT!!! Space Pirate Attack Detected!" << endl;
			Sleep(1500);
			cout << "Incoming enemy ships are targeting our trade routes!" << endl;
			Sleep(2000);

			cout << "All hands to battle stations!" << endl;
			Sleep(1500);

			int numPirates = rand() % 5 + 1;
			if (numPirates == 1) {
				cout << "Enemy force detected: " << numPirates << " pirate ship approaching!\n";
			} else {
				cout << "Enemy force detected: " << numPirates << " pirate ships approaching!\n";
			}
			cout << "\n\t<<<<<<-Brace for impact!->>>>>>\n" << endl;
			Sleep(4000);
			Spaceship Ship;
			for (int i = 1; i <= numPirates; ++i) {
				cout << "(!) Engaging enemy ship " + to_string(i) + "..." << endl;
				int attackType = rand() % 2;
				switch (attackType) {
					case 0:
						Ship.health-=basicAttack(Ship, highSecurity);
						break;
					case 1:
						Ship.health-=heavyAttack(Ship, highSecurity);
						break;
				}
				cout << "\nREMAINING HEALTH: " << Ship.health << "%\n" << endl;
				Sleep(2000);
			}

			cout << "Space pirate threat neutralized. Returning to normal operations.";
			Sleep(1000);
			system("cls");
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
			resources_available = new Resourse[3];
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


		void setResourcesAvailable(string array1[3],string array2[3],string array3[3],string array4[3]) {
			for (int i = 0; i < 3; i++) {
				resources_available[i].resourse = array1[i];
				resources_available[i].type = array2[i];
				resources_available[i].rarity = array3[i];
				resources_available[i].description = array4[i];
			}
		}

		~Planet() {
			delete[] resources_available;
		}
		friend void calculateDistanceAndCost(const Planet& planet1, const Planet& planet2, bool highSecurity);


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
void drawShip(int x) {
	for (int i = 0; i < x; ++i) {
		cout << " ";
	}
	cout << " ^/|\\  " << endl;
	for (int i = 0; i < x; ++i) {
		cout << " ";
	}
	cout << " v\\|/ " << endl;
	for (int i = 0; i < x; ++i) {
		cout << " ";
	}

}
void fun(bool highsecurity) {
	int startX = 0;
	int endX = 20;
	int currentX = startX;
	SpacePirateAttack ship;
	int random = rand() %10;
	while (currentX <= endX) {
		system("cls");
		drawShip(currentX);
		Sleep(1000);
		currentX++;
		if(currentX == random) {
			ship.occur(highsecurity);
		}

	}
}
void travelSequence(bool highSecurity) {
	cout << "Initiating space travel sequence...\n";
	Sleep(1000);
	cout << "Preparing engines...\n";
	Sleep(2000);
	cout << "Engines primed. Initiating takeoff...\n";
	Sleep(3000);
	cout << "Liftoff! The spaceship is now on its way to the destination...\n";
	Sleep(5000);
	cout << "Traveling through hyperspace...\n";

	fun(highSecurity);


	Sleep(7000);
	cout << "Approaching destination...\n";
	Sleep(3000);
	cout << "Entering orbit...\n";
	Sleep(2000);
	cout << "Spacecraft successfully entered orbit around the destination planet.\n";
	Sleep(1000);
	cout << "Preparing to dock...\n";
	Sleep(2000);
	cout << "Docking sequence initiated...\n";
	Sleep(3000);
	cout << "Ship has reached its destination!\n"
	     << "Contact your nearest Report centre to recieve your shipment\n\t\tHappy Trading ^_^"<<endl;
	Sleep(2000);
}


void calculateDistanceAndCost(Planet planet1,Demand_Resources planet2, bool highSecurity) {
	double distance = planet2.getDistance()-planet1.getDistance();
	int cost;


	if (distance >= 1 && distance <= 200) {
		cost = 300;
	} else if (distance >=201 && distance <= 1000) {
		cost = 400;
	} else if (distance >= 1001 && distance <= 100000) {
		cost = 650;
	} else {
		cost = 1000;
	}


	if (highSecurity) {
		cost += 150;
	} else {
		cost += 70;
	}
	cout<<"Travel cost : "<<cost<<endl;
	Sleep(1000);
	system("cls");
	travelSequence(highSecurity);

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
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'b':
		case 'B':
			trade.resourse = "Cybermatter";
			trade.type = "Material";
			trade.rarity = "Medium";
			trade.description = "Advanced material with unique properties.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'c':
		case 'C':
			trade.resourse = "Iridium Alloys";
			trade.type = "Metal";
			trade.rarity = "Exotic";
			trade.description = "Versatile alloys used in construction and technology.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'd':
		case 'D':
			trade.resourse = "Kryptonite";
			trade.type = "Mineral";
			trade.rarity = "Rare";
			trade.description = "Radioactive mineral harmful to Kryptonians.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'e':
		case 'E':
			trade.resourse = "Kryptonian Technology Artifacts";
			trade.type = "Technology";
			trade.rarity = "Rare";
			trade.description = "Advanced technology remnants of Krypton.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'f':
		case 'F':
			trade.resourse = "Rare Crystals";
			trade.type = "Crystal";
			trade.rarity = "Medium";
			trade.description = "Mystical crystals with unique properties.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'g':
		case 'G':
			trade.resourse = "Unobtanium";
			trade.type = "Mineral";
			trade.rarity = "Rare";
			trade.description = "Highly valuable mineral with anti-gravity properties.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'h':
		case 'H':
			trade.resourse = "Helicoradian";
			trade.type = "Flora";
			trade.rarity = "Medium";
			trade.description = "Bioluminescent plant used for energy.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'i':
		case 'I':
			trade.resourse = "Eywa's Blessing";
			trade.type = "Flora";
			trade.rarity = "Common";
			trade.description = "Medicinal plant revered by Na'vi.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;


		case 'j':
		case 'J':
			trade.resourse = "Solarite";
			trade.type = "Energy";
			trade.rarity = "Rare";
			trade.description = "Rare energy crystal with powerful properties.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;
		case 'k':
		case 'K':
			trade.resourse = "Quicksilver";
			trade.type = "Metal";
			trade.rarity = "Common";
			trade.description = "Versatile metal used in various industries.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'l':
		case 'L':
			trade.resourse = "Chrono Blossom";
			trade.type = "Flora";
			trade.rarity = "Medium";
			trade.description = "Medicinal plant with time-altering effects.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'm':
		case 'M':
			trade.resourse = "Nebula Gas";
			trade.type = "Gas";
			trade.rarity = "Rare";
			trade.description = "Gas harvested from nebulas for advanced propulsion.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'n':
		case 'N':
			trade.resourse = "Exo-Flora";
			trade.type = "Flora";
			trade.rarity = "Medium";
			trade.description = "Bioluminescent plant with bioengineering applications.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

			break;

		case 'o':
		case 'O':
			trade.resourse = "Neutronite";
			trade.type = "Metal";
			trade.rarity = "Rare";
			trade.description = "High-density metal for starship construction.";
			cout<<"You have select :\n"
			    <<"Resource    : "<<trade.resourse<<"\n"
			    <<"Type        : "<<trade.type<<"\n"
			    <<"Rarity      : "<<trade.rarity<<"\n"
			    <<"Description : "<<trade.description<<endl;

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
		system("cls");
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
	SpacePirateAttack ship;
	do {
		cout << "--------Welcome-------" << endl
		     << "1. Cybertron" << endl
		     << "2. Krypton" << endl
		     << "3. Pandora" << endl
		     << "4. Aldoria" << endl
		     << "5. Nebulon-9"<< endl
		     << "6. Exit "<<endl
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
				Type[2] = "Matel";
				Rarity[2] = "Common";
				Description[2]= "Versatile alloys used in construction and technology.";
				obj.setResourcesAvailable(initial_Resources,Type,Rarity,Description);

				do {
					cout<<"[A] Energon    [B] Cybermatter                     [C] Iridium Alloys \n"
					    <<"[D] Kryptonite [E] Kryptonian Technology Artifacts [F] Rare Crystals \n"
					    <<"[G] Unobtanium [H] Helicoradian                    [I] Eywa's Blessing \n"
					    <<"[J] Solarite   [K] Quicksilver                     [L] Chrono Blossom \n"
					    <<"[M] Nebula Gas [N] Exo-Flora                       [O] Neutronite\n"
					    <<"[X] Exit\n"
					    <<"Select Resources you need or press x : ";
					cin>>choice_resources;
					if(choice_resources == 'x') {
						if(obj.resources_needed.empty()) {
							return 0;
						}
					}
					system("cls");
					obj1 = need(choice_resources);
					if (obj.resources_needed.size() > 0) {
						obj.resources_needed[0] = obj1;
					} else {

						obj.resources_needed.push_back(obj1);
					}
				} while (choice_resources !='x' && choice_resources != 'X');
				Deal();

				cout << "Enter security level (1 for high, 0 for low): ";
				cin >> highSecurity;
				system("cls");


				calculateDistanceAndCost(origin, obj, highSecurity);





				break;

			case '2':
				obj.setName("Krypton");
				cout << "Enter its distance from Ragnork (in light years(1-100000)): ";
				cin >> distance;
				obj.setDistance(distance);
				system("cls");

				initial_Resources[0] = "Kryptonite";
				Type[0] = "Mineral";
				Rarity[0] = "Rare";
				Description[0]= "Radioactive mineral harmful to Kryptonians.";
				initial_Resources[1] = "Kryptonian Technology Artifacts";
				Type[1] = "Technology";
				Rarity[1] = "Rare";
				Description[1]= "Advanced technology remnants of Krypton.";
				initial_Resources[2] = "Rare Crystals";
				Type[2] = "Crystals";
				Rarity[2] = "Medium";
				Description[2]= "Mystical crystals with unique properties.";
				obj.setResourcesAvailable(initial_Resources,Type,Rarity,Description);

				do {
					cout<<"[A] Energon    [B] Cybermatter                     [C] Iridium Alloys \n"
					    <<"[D] Kryptonite [E] Kryptonian Technology Artifacts [F] Rare Crystals \n"
					    <<"[G] Unobtanium [H] Helicoradian                    [I] Eywa's Blessing \n"
					    <<"[J] Solarite   [K] Quicksilver                     [L] Chrono Blossom \n"
					    <<"[M] Nebula Gas [N] Exo-Flora                       [O] Neutronite\n"
					    <<"[X] Exit\n"
					    <<"Select Resources you need or press x : ";
					cin>>choice_resources;
					if(choice_resources == 'x') {
						if(obj.resources_needed.empty()) {
							return 0;
						}
					}
					system("cls");
					obj1 = need(choice_resources);
					if (obj.resources_needed.size() > 0) {
						obj.resources_needed[0] = obj1;
					} else {

						obj.resources_needed.push_back(obj1);
					}
				} while (choice_resources !='x' && choice_resources != 'X');
				Deal();

				cout << "Enter security level (1 for high, 0 for low): ";
				cin >> highSecurity;
				system("cls");


				calculateDistanceAndCost(origin, obj, highSecurity);


				break;

			case '3':
				obj.setName("Pandora");
				cout << "Enter its distance from Ragnork (in light years(1-100000)): ";
				cin >> distance;
				obj.setDistance(distance);
				system("cls");

				initial_Resources[0] = "Unobtanium";
				Type[0] = "Mineral";
				Rarity[0] = "Rare";
				Description[0]= "Highly valuable mineral with anti-gravity properties.";
				initial_Resources[1] = "Helicoradian";
				Type[1] = "Flora";
				Rarity[1] = "Medium";
				Description[1]= "Bioluminescent plant used for energy.";
				initial_Resources[2] = "Eywa's Blessing";
				Type[2] = "Flora";
				Rarity[2] = "Common";
				Description[2]= "Medicinal plant revered by Na'vi.";
				obj.setResourcesAvailable(initial_Resources,Type,Rarity,Description);

				do {
					cout<<"[A] Energon    [B] Cybermatter                     [C] Iridium Alloys \n"
					    <<"[D] Kryptonite [E] Kryptonian Technology Artifacts [F] Rare Crystals \n"
					    <<"[G] Unobtanium [H] Helicoradian                    [I] Eywa's Blessing \n"
					    <<"[J] Solarite   [K] Quicksilver                     [L] Chrono Blossom \n"
					    <<"[M] Nebula Gas [N] Exo-Flora                       [O] Neutronite\n"
					    <<"[X] Exit\n"
					    <<"Select Resources you need or press x : ";
					cin>>choice_resources;
					if(choice_resources == 'x') {
						if(obj.resources_needed.empty()) {
							return 0;
						}
					}
					system("cls");
					obj1 = need(choice_resources);
					if (obj.resources_needed.size() > 0) {
						obj.resources_needed[0] = obj1;
					} else {

						obj.resources_needed.push_back(obj1);
					}
				} while (choice_resources !='x' && choice_resources != 'X');
				Deal();

				cout << "Enter security level (1 for high, 0 for low): ";
				cin >> highSecurity;
				system("cls");


				calculateDistanceAndCost(origin, obj, highSecurity);

				break;

			case '4':

				obj.setName("Aldoria");
				cout << "Enter its distance from Ragnork (in light years(1-100000)): ";
				cin >> distance;
				obj.setDistance(distance);
				system("cls");

				initial_Resources[0] = "Solarite";
				Type[0] = "Energy";
				Rarity[0] = "Rare";
				Description[0]= "Rare energy crystal with powerful properties.";
				initial_Resources[1] = " Quicksilver";
				Type[1] = "Metal";
				Rarity[1] = "Common";
				Description[1]= "Versatile metal used in various industries.";
				initial_Resources[2] = "Chrono Blossom";
				Type[2] = "Flora";
				Rarity[2] = "Common";
				Description[2]= "Medicinal plant with time-altering effects.";
				obj.setResourcesAvailable(initial_Resources,Type,Rarity,Description);

				do {
					cout<<"[A] Energon    [B] Cybermatter                     [C] Iridium Alloys \n"
					    <<"[D] Kryptonite [E] Kryptonian Technology Artifacts [F] Rare Crystals \n"
					    <<"[G] Unobtanium [H] Helicoradian                    [I] Eywa's Blessing \n"
					    <<"[J] Solarite   [K] Quicksilver                     [L] Chrono Blossom \n"
					    <<"[M] Nebula Gas [N] Exo-Flora                       [O] Neutronite\n"
					    <<"[X] Exit\n"
					    <<"Select Resources you need or press x : ";
					cin>>choice_resources;
					if(choice_resources == 'x') {
						if(obj.resources_needed.empty()) {
							return 0;
						}
					}
					system("cls");
					obj1 = need(choice_resources);
					if (obj.resources_needed.size() > 0) {
						obj.resources_needed[0] = obj1;
					} else {

						obj.resources_needed.push_back(obj1);
					}
				} while (choice_resources !='x' && choice_resources != 'X');
				Deal();

				cout << "Enter security level (1 for high, 0 for low): ";
				cin >> highSecurity;
				system("cls");


				calculateDistanceAndCost(origin, obj, highSecurity);


				break;

			case '5':
				obj.setName("Nebulon-9");
				cout << "Enter its distance from Ragnork (in light years(1-100000)): ";
				cin >> distance;
				obj.setDistance(distance);
				system("cls");

				initial_Resources[0] = "Nebula Gas";
				Type[0] = "Gas";
				Rarity[0] = "Rare";
				Description[0]= "Gas harvested from nebulas for advanced propulsion.";
				initial_Resources[1] = " Exo-Flora";
				Type[1] = "Flora";
				Rarity[1] = "Medium";
				Description[1]= "Bioluminescent plant with bioengineering applications.";
				initial_Resources[2] = "Neutronite";
				Type[2] = "Metal";
				Rarity[2] = "Rare";
				Description[2]= "High-density metal for starship construction.";
				obj.setResourcesAvailable(initial_Resources,Type,Rarity,Description);

				do {
					cout<<"[A] Energon    [B] Cybermatter                     [C] Iridium Alloys \n"
					    <<"[D] Kryptonite [E] Kryptonian Technology Artifacts [F] Rare Crystals \n"
					    <<"[G] Unobtanium [H] Helicoradian                    [I] Eywa's Blessing \n"
					    <<"[J] Solarite   [K] Quicksilver                     [L] Chrono Blossom \n"
					    <<"[M] Nebula Gas [N] Exo-Flora                       [O] Neutronite\n"
					    <<"[X] Exit\n"
					    <<"Select Resources you need or press x : ";
					cin>>choice_resources;
					if(choice_resources == 'x') {
						if(obj.resources_needed.empty()) {
							return 0;
						}
					}
					system("cls");
					obj1 = need(choice_resources);
					if (obj.resources_needed.size() > 0) {
						obj.resources_needed[0] = obj1;
					} else {
						obj.resources_needed.push_back(obj1);
					}
				} while (choice_resources !='x' && choice_resources != 'X');
				Deal();

				cout << "Enter security level (1 for high, 0 for low): ";
				cin >> highSecurity;
				system("cls");


				calculateDistanceAndCost(origin, obj, highSecurity);


				break;
			case '6':
				cout<<"Good Bye ^_^"<<endl;
				break;
			default:
				cout << "Invalid choice. Please choose a valid planet." << endl;
				break;
		}
	} while(choice_planet !='6');

	return 0;
}
