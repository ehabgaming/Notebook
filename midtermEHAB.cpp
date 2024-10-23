// ehabothman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

//To do:
//1. fix errors *DONE*
//2. fix ui  *kinded done :/*
//3. make the stats on one sport *DONE*
//4. put the function into the class *DONE*
//5. make the code more readble *i can read it just fine*

using namespace std;

// Player class to store the data from the file
class Player {
private:
    string FirstName;
    string LastName;
    string team;
    double PPG;
    double RPG;
    double APG;
    double BPG;
    double SPG;

public:
    // Constructor to initialize player data
    Player(string fn,string ln, string t, double s1, double s2, double s3, double s4, double s5) {
        FirstName = fn;
        LastName = ln;
        team = t;
        PPG = s1;
        RPG = s2;
        APG = s3;
        BPG = s4;
        SPG = s5;
    }

    // Getters and Setters for player attributes
    string getFirstName() { return FirstName; }
    string getLastName() { return LastName; }
    string getTeam() { return team; }
    double getPPG() { return PPG; }
    double getRPG() { return RPG; }
    double getAPG() { return APG; }
    double getBPG() { return BPG; }
    double getSPG() { return SPG; }

    void setFirstName(string fn) { FirstName = fn; }
    void setLastName(string ln) { FirstName = ln; }
    void setTeam(string t) { team = t; }
    void setPPG(double s) { PPG = s; }
    void setRPG(double s) { RPG = s; }
    void setAPG(double s) { APG = s; }
    void setBPG(double s) { BPG = s; }
    void setSPG(double s) { SPG = s; }

    // Function to print player data
    void printPlayer() {
        cout << "First Name: " << FirstName << endl;
        cout << "Last Name: " << LastName << endl;
        cout << "Team: " << team << endl;
        // Set precision for floating-point numbers
        cout << fixed << setprecision(2);
        cout << "PPG: " << PPG << endl;
        cout << "RPG: " << RPG << endl;
        cout << "APG: " << APG << endl;
        cout << "BPG: " << BPG << endl;
        cout << "SPG: " << SPG << endl;
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

void HoldandClearConsole() // a fuction to pause the screen and clear it after a key is pressed
{
    cout << "\nPress any key to continue....";
    cin.get();
    cin.get();
}


int main() {
    vector<Player> players;
    Player p("ejan","wood", "lakers", 10, 102, 30, 40, 50);

    string inputFilename = "NBAPlayers.txt";   // Input file name
    string outputFilename = "Testout.txt"; // Output file name

    // Load data from file
    loadData(players, inputFilename);

    int choice;
    do {
        // Display menu
        system("cls");
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
            else                                                             // if the cin.fail = false than we let the user pass
            {
                break;
            }
        }
        
        

        // Perform action based on user's choice
        switch (choice) {
        case 1:
            p.printAllPlayers(players);
            HoldandClearConsole();
            break;
        case 2:
            p.printPlayerStats(players);
            HoldandClearConsole();
            break;
        case 3:
            p.printTeamData(players);
            HoldandClearConsole();
            break;
        case 4:
            p.updatePlayerData(players);
            HoldandClearConsole();
            break;
        case 5:
            p.insertNewPlayer(players);
            HoldandClearConsole();
            break;
        case 6:
            exportData(players, outputFilename);
            HoldandClearConsole();
            break;
        case 7:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
            cin.get();
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
    string FirstName,LastName, team;
    double s1, s2, s3, s4, s5;

    // Read data for each player from the file
    while (infile >> FirstName >> LastName >> team >> s1 >> s2 >> s3 >> s4 >> s5) {
        Player p(FirstName,LastName, team, s1, s2, s3, s4, s5);
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
    string FirstName, LastName;
    cout << "Enter the player's First Name: ";
    cin >> FirstName;
    cout << "Enter the player's Last Name: ";
    cin >> LastName;
    bool found = false;

    // Search for the player by name
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getFirstName() == FirstName || players[i].getFirstName() == LastName) {
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
    string FirstName, LastName;
    cout << "Enter the player's name to update\n";

    cout << "Enter the player's First Name: ";
    cin >> FirstName;

    cout << "Enter the player's Last Name: ";
    cin >> LastName;

    bool found = false;
    // Search for the player by name
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getFirstName() == FirstName || players[i].getFirstName() == LastName) {
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
            players[i].setPPG(s1);
            players[i].setRPG(s2);
            players[i].setAPG(s3);
            players[i].setBPG(s4);
            players[i].setSPG(s5);
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
    string FirstName,LastName, team;
    double s1, s2, s3, s4, s5;
    cout << "Enter player's First name: ";
    cin >> FirstName;
    cout << "Enter player's Last name: ";
    cin >> LastName;
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
    Player p(FirstName,LastName, team, s1, s2, s3, s4, s5);
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
        outfile << players[i].getFirstName() << " "
            << players[i].getLastName() << " "
            << players[i].getTeam() << " "
            << players[i].getPPG() << " "
            << players[i].getRPG() << " "
            << players[i].getAPG() << " "
            << players[i].getBPG() << " "
            << players[i].getSPG() << endl;
    }
    outfile.close();
    cout << "Data exported to " << filename << endl;
}
