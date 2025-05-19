#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct Node;
struct Order;
struct Restaurant;
struct Grid;

bool nextPermutation(int* arr, int n) {
    int i = n - 1;
    while (i > 0 && arr[i - 1] >= arr[i]) {
        i--;
    }
    if (i <= 0) {
        return false;
    }
    int j = n - 1;
    while (arr[j] <= arr[i - 1]) {
        j--;
    }
    swap(arr[i - 1], arr[j]);
    j = n - 1;
    while (i < j) {
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    return true;
}


int calculateDistance(int row1, int col1, int row2, int col2) {
    return abs(row1 - row2) + abs(col1 - col2);
}

void findShortestRoute(int** gridarr, int size, int source, int* destinations, int numDestinations) {
    int minDistance = INT_MAX;
    int* bestRoute = new int[numDestinations];
    int* tempRoute = new int[numDestinations];

    int sourceRow, sourceCol;

	if (source % size == 0)
    {
		sourceRow = (source - 1) / size;
        sourceCol = (size - 1);
	}
    else
    {
		sourceRow = (source - 1) / size;
        sourceCol = (source % size) - 1;
	}
    

    for (int i = 0; i < numDestinations; ++i) {
        tempRoute[i] = destinations[i];
    }

    do {
        int distance = calculateDistance(sourceRow, sourceCol, (tempRoute[0] - 1) / size, (tempRoute[0] - 1) % size);
        for (int i = 1; i < numDestinations; ++i) {
            distance += calculateDistance((tempRoute[i - 1] - 1) / size, (tempRoute[i - 1] - 1) % size, (tempRoute[i] - 1) / size, (tempRoute[i] - 1) % size);
        }
        if (distance < minDistance) {
            minDistance = distance;
            for (int i = 0; i < numDestinations; ++i) {
                bestRoute[i] = tempRoute[i];
            }
        }
    } while (nextPermutation(tempRoute, numDestinations));

    cout << "Shortest time to cover all destinations: " << minDistance << endl;

    delete[] bestRoute;
    delete[] tempRoute;
}


struct Node {
    int id;
    bool isrestaurant;
    Node* right;
    Node* left;
    Node* up;
    Node* down;

    Node(int id = 0) : id(id), isrestaurant(false), right(nullptr), left(nullptr), up(nullptr), down(nullptr) {}

    void insertDown(Node* newNode) {
        Node* current = this;
        while (current->down != nullptr) {
            current = current->down;
        }
        current->down = newNode;
        newNode->up = current;
    }

    void insertRight(Node* newNode) {
        Node* current = this;
        while (current->right != nullptr) {
            current = current->right;
        }
        current->right = newNode;
        newNode->left = current;
    }
};



struct Order
{
    string itemname;
    int deliverylocation;
    int time;

    Order() : itemname(""), deliverylocation(0), time(0) {};

    Order(string n, int l, int t) {
        itemname = n;
        deliverylocation = l;
        time = t;
    }

    void displayOrder() {
        cout << "Order Details:\n";
        cout << "Order Name: " << itemname << endl;
        cout << "Location: " << deliverylocation << endl;
        cout << "Time: " << time << endl;
        cout << "----------------------\n";
    }

    void orderlocations(int* temp, int i) {
		temp[i] = deliverylocation;
    }

};



struct Restaurant
{
    static int counter;
    string name;
    int numorders, location;
    Order* orders;

    Restaurant() : name(""), numorders(0), location(0), orders(nullptr) {}

    Restaurant(string n, int loc, int no) {
        name = n;
        location = loc;
        numorders = no;
        orders = new Order[numorders];
    }

	void displayRestaurant() {
        cout << "----------------------\n";
        cout << "Restaurant Details:\n";
		cout << "Restaurant Name: " << name << endl;
		cout << "Location: " << location << endl;
		cout << "Number of Orders: " << numorders << endl;
        cout << "----------------------\n";
	}

    ~Restaurant()
    {
        delete[] orders;
    }

};

int Restaurant::counter = 0;


struct Grid {
    Node* head;
    int NumOfRiders, NumOfRestaurnants;
    static int count;
    Restaurant* restaurants;

    Grid() {
        head = new Node(1);
        NumOfRiders = 0;
        NumOfRestaurnants = 0;
        restaurants = new Restaurant[1];
    }

    Grid(int s, int nr, int numrest) {
        head = new Node(1);
        NumOfRestaurnants = numrest;
        NumOfRiders = nr;
        restaurants = new Restaurant[numrest];
    }

    ~Grid() {
        delete head;
        delete[] restaurants;
    }

    void gridCreation(int size) {
        Node* rowStart = head;
        for (int i = 1; i < size; i++) {  
            rowStart->insertRight(new Node(count++));
            rowStart = rowStart->right;
        }

        Node* colStart = head;         
        for (int i = 1; i < size; i++) {
            colStart->insertDown(new Node(count++)); 
            Node* rowMarker = colStart->down;
            rowStart = colStart->right;
            Node* current = rowMarker;
            for (int j = 1; j < size; j++) {
                current->insertRight(new Node(count++));
                current = current->right;
                rowStart->down = current;
                current->up = rowStart;
                rowStart = rowStart->right;
            }
            colStart = colStart->down;   
            rowStart = head;
        }
    }

    void display(int size) {
        Node* current = head;
        while (current) {
            Node* temp = current;
            while (temp) {
                cout << temp->id << "\t";
                temp = temp->right;
            }
            cout << endl;
            current = current->down;
        }
    }

    void addrestaurant(int location, string n, int no) {
        Node* current = head;
        while (current) {
            Node* temp = current;
            while (temp) {
                if (temp->id == location) { 
                    if (!temp->isrestaurant) {
                        temp->isrestaurant = true;
                        
                        Restaurant tempRestaurant(n, location, no);

                        restaurants[Restaurant::counter++] = tempRestaurant;
                    }
                    
                    return;
                }
                temp = temp->right;
            }
            current = current->down;
        }
        cout << "Location " << location << " does not exist." << endl;
    }
    
    void initializeGridArray(int** gridarr, int size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				gridarr[i][j] = 0;
			}
		}
        
        for (int i = 0; i < NumOfRestaurnants; i++) {
            int location = restaurants[i].location;
            if (location % size == 0) {
				gridarr[(location - 1) / size][size - 1] = 2;
			}
            else {
                gridarr[(location - 1) / size][(location % size) - 1] = 2; 
            }

            for (int j = 0; j < restaurants[i].numorders; j++) {
				int dellocation = restaurants[i].orders[j].deliverylocation;
                if (dellocation % size == 0) {
                    gridarr[(dellocation - 1) / size][size - 1] = 1; 
                }
				else {
					gridarr[(dellocation - 1) / size][(dellocation % size) - 1] = 1;
				}
                
            }
        }
    }

    void findshortestroutehelper(int restaurantlocation, int size, int** gridarr) {
        int s = restaurants[restaurantlocation].numorders;
        int* temp = new int[s];
        
        for(int i = 0; i < s; i++)
        {
            restaurants[restaurantlocation].orders[i].orderlocations(temp, i);

        }

		int source = restaurants[restaurantlocation].location;
        findShortestRoute(gridarr, size, source, temp, s);

    }
    void findshortestroute(int size) {

        int** gridarr = new int* [size]; 

        for (int i = 0; i < size; i++) {
            gridarr[i] = new int[size]; 
        }


        for (int i = 0; i < NumOfRestaurnants; i++) {
			int restaurantlocation = i;

            initializeGridArray(gridarr, size);

            findshortestroutehelper(restaurantlocation, size, gridarr);
        }
       
        
    }
};


int Grid::count = 2;

void readDataFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    int numTestCases;
    file >> numTestCases;

    for (int testCase = 0; testCase < numTestCases; ++testCase) {
        int size, numRiders, numRestaurants;
        file >> size >> numRiders >> numRestaurants;
        Grid* grid = new Grid(size, numRiders, numRestaurants);
        grid->gridCreation(size);
		cout << "Test Case " << testCase + 1 << ":\n\n";
		cout << "Grid of size " << size << " created:" << endl;
        grid->display(size);
        for (int i = 0; i < numRestaurants; ++i) {
            string name;
            int location, numOrders;
            file >> name >> location >> numOrders;
            grid->addrestaurant(location, name, numOrders);
			grid->restaurants[i].displayRestaurant();
            Order* arr = new Order[numOrders];
            for (int j = 0; j < numOrders; ++j) {
                string ordername;
                int dellocation, deliverytime;
                file >> ordername >> dellocation >> deliverytime;
                Order temporder(ordername, dellocation, deliverytime);
                temporder.displayOrder();
                arr[j] = temporder;
            }
			grid->restaurants[i].orders = arr;
        }
        grid->findshortestroute(size);
        Grid::count = 2;
		Restaurant::counter = 0;
        cout << "\n---------------------------------------------------\n";
        cout << "Enter any Character to proceed to next Testcase: ";
        char m;
        cin >> m;
        system("cls");
    }

    file.close();
}

int main() {

    string filename = "C:\\Users\\umais\\OneDrive\\Desktop\\desktop trash\\stupid shit\\projecttestdata.txt";

    readDataFromFile(filename);

    return 0;
}