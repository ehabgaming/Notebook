// ehabothman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

//To do:
//1. fix errors
//2. fix ui
//3. make the stats on one sport
//4. put the function into the class
//5. 

using namespace std;

// Player class to store the data from the file
class Player {
private:
    string name;
    string team;
    double stat1;
    double stat2;
    double stat3;
    double stat4;
    double stat5;

public:
    // Constructor to initialize player data
    Player(string n, string t, double s1, double s2, double s3, double s4, double s5) {
        name = n;
        team = t;
        stat1 = s1;
        stat2 = s2;
        stat3 = s3;
        stat4 = s4;
        stat5 = s5;
    }

    // Getters and Setters for player attributes
    string getName() { return name; }
    string getTeam() { return team; }
    double getStat1() { return stat1; }
    double getStat2() { return stat2; }
    double getStat3() { return stat3; }
    double getStat4() { return stat4; }
    double getStat5() { return stat5; }

    void setName(string n) { name = n; }
    void setTeam(string t) { team = t; }
    void setStat1(double s) { stat1 = s; }
    void setStat2(double s) { stat2 = s; }
    void setStat3(double s) { stat3 = s; }
    void setStat4(double s) { stat4 = s; }
    void setStat5(double s) { stat5 = s; }

    // Function to print player data
    void printPlayer() {
        cout << "Name: " << name << endl;
        cout << "Team: " << team << endl;
        // Set precision for floating-point numbers
        cout << fixed << setprecision(2);
        cout << "PPG: " << stat1 << endl;
        cout << "RPG: " << stat2 << endl;
        cout << "APG: " << stat3 << endl;
        cout << "BPG: " << stat4 << endl;
        cout << "SPG: " << stat5 << endl;
        cout << defaultfloat; // Reset to default formatting
    }

    // Function prototypes
    void printAllPlayers(vector<Player>& players);
    void printPlayerStats(vector<Player>& players);
    void printTeamData(vector<Player>& players);
    void updatePlayerData(vector<Player>& players);
    void insertNewPlayer(vector<Player>& players);
};

//its better to have these fuction outside the class 
void loadData(vector<Player>& players, string filename);
void exportData(vector<Player>& players, string filename);


int main() {
    vector<Player> players;
    Player p("ejan", "lakers", 10, 102, 30, 40, 50);

    string inputFilename = "input.txt";   // Input file name
    string outputFilename = "Testout.txt"; // Output file name

    // Load data from file
    loadData(players, inputFilename);

    int choice;
    do {
        // Display menu
        cout << "Menu Options:" << endl;
        cout << "1. Print out all users and statistics" << endl;
        cout << "2. Print out the statistics for a specific player" << endl;
        cout << "3. Print out all data for a specific team" << endl;
        cout << "4. Update the data for a specific player" << endl;
        cout << "5. Insert a new player and their statistics" << endl;
        cout << "6. Export the data to an output file" << endl;
        cout << "7. Exit" << endl;

        while (true)
        {
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())                                                  //This function checks if the input the user put causes a error
            {
                cin.clear();                                                 //we first clear the buffer (clearing the error)
                cin.ignore(numeric_limits< streamsize>::max(), '\n');        // than we discard the input for the max
                cout << "Invaild input, you MUST enter a number\n";          
            }
            else                // if the cin.fail = false than we let the user pass
            {
                break;
            }
        }
        
        

        // Perform action based on user's choice
        switch (choice) {
        case 1:
            p.printAllPlayers(players);
            break;
        case 2:
            p.printPlayerStats(players);
            break;
        case 3:
            p.printTeamData(players);
            break;
        case 4:
            p.updatePlayerData(players);
            break;
        case 5:
            p.insertNewPlayer(players);
            break;
        case 6:
            exportData(players, outputFilename);
            break;
        case 7:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
            
        }

    } while (choice != 7);

    return 0;
}

// Function to load data from file
void loadData(vector<Player>& players, string filename) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Error opening input file." << endl;
        return;
    }
    string name, team;
    double s1, s2, s3, s4, s5;

    // Read data for each player from the file
    while (infile >> name >> team >> s1 >> s2 >> s3 >> s4 >> s5) {
        Player p(name, team, s1, s2, s3, s4, s5);
        players.push_back(p);
    }
    infile.close();
}

// Function to print all players and their statistics
void Player::printAllPlayers(vector<Player>& players) {
    for (size_t i = 0; i < players.size(); ++i) {
        cout << "Player " << i + 1 << ":" << endl;
        players[i].printPlayer();
        cout << endl;
    }
}

// Function to print statistics for a specific player
void Player::printPlayerStats(vector<Player>& players) {
    string name;
    cout << "Enter the player's name: ";
    cin >> name;
    bool found = false;
    // Search for the player by name
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getName() == name) {
            players[i].printPlayer();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Player not found." << endl;
    }
}

// Function to print all data for a specific team
void Player::printTeamData(vector<Player>& players) {
    string team;
    cout << "Enter the team name: ";
    cin >> team;
    bool found = false;
    // Search for players in the specified team
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getTeam() == team) {
            players[i].printPlayer();
            cout << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No players found for this team." << endl;
    }
}

// Function to update data for a specific player
void Player::updatePlayerData(vector<Player>& players) {
    string name;
    cout << "Enter the player's name to update: ";
    cin >> name;
    bool found = false;
    // Search for the player by name
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getName() == name) {
            string t;
            double s1, s2, s3, s4, s5;
            cout << "Enter new Team: ";
            cin >> t;
            cout << "Enter new PPG: ";
            cin >> s1;
            cout << "Enter new RPG: ";
            cin >> s2;
            cout << "Enter new APG: ";
            cin >> s3;
            cout << "Enter new BPG: ";
            cin >> s4;
            cout << "Enter new SPG: ";
            cin >> s5;
            // Update player's statistics
            players[i].setTeam(t);
            players[i].setStat1(s1);
            players[i].setStat2(s2);
            players[i].setStat3(s3);
            players[i].setStat4(s4);
            players[i].setStat5(s5);
            cout << "Player data updated." << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Player not found." << endl;
    }
}

// Function to insert a new player and their statistics
void Player::insertNewPlayer(vector<Player>& players) {
    string name, team;
    double s1, s2, s3, s4, s5;
    cout << "Enter player's name: ";
    cin >> name;
    cout << "Enter player's team: ";
    cin >> team;
    cout << "Enter PPG: ";
    cin >> s1;
    cout << "Enter RPG: ";
    cin >> s2;
    cout << "Enter APG: ";
    cin >> s3;
    cout << "Enter BPG: ";
    cin >> s4;
    cout << "Enter SPG: ";
    cin >> s5;
    // Create a new player and add to the list
    Player p(name, team, s1, s2, s3, s4, s5);
    players.push_back(p);
    cout << "New player added." << endl;
}

// Function to export data to an output file
void exportData(vector<Player>& players, string filename) {
    ofstream outfile(filename.c_str());
    if (!outfile) {
        cout << "Error opening output file." << endl;
        return;
    }
    // Write each player's data to the file
    for (size_t i = 0; i < players.size(); ++i) {
        outfile << players[i].getName() << " "
            << players[i].getTeam() << " "
            << players[i].getStat1() << " "
            << players[i].getStat2() << " "
            << players[i].getStat3() << " "
            << players[i].getStat4() << " "
            << players[i].getStat5() << endl;
    }
    outfile.close();
    cout << "Data exported to " << filename << endl;
}
