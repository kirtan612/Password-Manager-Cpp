#include <iostream>
#include <string>
#include<fstream>
using namespace std;

const string MASTER_PASSWORD = "kirtan15";
string xorCipher(string text, char key = '@') {
    for (char &c : text) {
        c = c ^ key;
    }
    return text;
}

bool authenticate()
{
    string input;
    cout << "Enter master password: ";
    cin >> input;

    if (input == MASTER_PASSWORD) {
        cout << "Access granted \n";
        return true;
    } else {
        cout << "Access denied \n";
        return false;
    }
}
void addCredential()
{
    string website, username, password;



    cout << "\n--- Add New Credential ---\n";
    cout << "Website: ";
    cin >> website;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    string encryptedPassword = xorCipher(password);

    ofstream file("password.txt", ios::app); // add at the end without deleting
    if (file.is_open()) {
        file << website << " || " << username << " || " << encryptedPassword << endl;
        file.close();
        cout << "Credential saved securely!\n";
    } else {
        cout << "Error opening file!\n";
    }
}

void searchCredential() {
    string searchWebsite;
    cout << "Enter the website to search credentials for: ";
    cin >> searchWebsite;

    ifstream file("password.txt");
    string line;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            size_t first = line.find("||");
            size_t second = line.rfind("||");

            if (first != string::npos && second != string::npos && first != second) {
                string website = line.substr(0, first);
                string username = line.substr(first + 2, second - first - 2);
                string encryptedPassword = line.substr(second + 2);

                // Trim spaces
                website.erase(website.find_last_not_of(" \t") + 1);
                username.erase(0, username.find_first_not_of(" \t"));
                username.erase(username.find_last_not_of(" \t") + 1);
                encryptedPassword.erase(0, encryptedPassword.find_first_not_of(" \t"));

                if (website == searchWebsite) {
                    string decryptedPassword = xorCipher(encryptedPassword);
                    cout << "Website: " << website << endl;
                    cout << "Username: " << username << endl;
                    cout << "Password: " << decryptedPassword << endl;
                    found = true;
                    break;  // Stop searching after first match
                }
            }
        }
        file.close();

        if (!found) {
            cout << "No credentials found for " << searchWebsite << ".\n";
        }
    } else {
        cout << "Unable to open the password file.\n";
    }
}

int main() {

    int choice;
    if (!authenticate()) {
        return 0;
    }

    cout << "Welcome to Password Manager!\n";

      while (true) {
        cout << "\n---- Password Manager Menu ----\n";
        cout << "1. Add new password\n";
        cout << "2. Search the file\n";
         cout << "3. Exit the Program\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addCredential();
                break;
            case 2:
                  searchCredential();
                  break;
            case 3:
                cout << "Exiting... \n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }


    return 0;
}

