#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <sstream>

using namespace std;

// Struct to hold character mappings
struct CharacterMapping {
    char character;
    string encryptedValue;
};

class CipherTool {
private:
    vector<CharacterMapping> mappings; // Use a vector for mappings

public:
    // Constructor to initialize character mappings
    CipherTool() {
        const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{};:'\",.<>?/|\\`~ ";
        for (size_t i = 0; i < characters.size(); i++) {
            mappings.push_back({characters[i], to_string(i + 1)});
        }
    }

    // Function to encrypt the message
    string encrypt(const string& message) {
        string encryptedMessage;
        for (char c : message) {
            for (const auto& mapping : mappings) {
                if (mapping.character == c) {
                    encryptedMessage += mapping.encryptedValue + " ";
                    break;
                }
            }
        }
        return encryptedMessage;
    }

    // Function to decrypt the message
    string decrypt(const string& message) {
        string decryptedMessage;
        string currentNumber;
        istringstream iss(message);

        while (iss >> currentNumber) {
            for (const auto& mapping : mappings) {
                if (mapping.encryptedValue == currentNumber) {
                    decryptedMessage += mapping.character;
                    break;
                }
            }
        }
        return decryptedMessage;
    }

    // Function to save encrypted message to a file
    void saveToFile(const string& filename, const string& content) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        outFile << content;
        outFile.close();
    }

    // Function to load message from a file
    string loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error opening file for reading." << endl;
            return "";
        }
        string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();
        return content;
    }
};

// Function for user interaction
void userInteraction() {
    unique_ptr<CipherTool> cipherTool = make_unique<CipherTool>();
    int choice;
    string message;
    string filename;
    //display menu bar
    do {
        cout << "\n--- Welcome to the Cryptography Tool ---" << endl;
        cout << "1. Encrypt a message" << endl;
        cout << "2. Decrypt a message" << endl;
        cout << "3. Save encrypted message to file" << endl;
        cout << "4. Load message from file and decrypt" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option (1-5): ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the choice input

        switch (choice) {
            case 1:
                cout << "Enter the message to encrypt: ";
                getline(cin, message);
                cout << "Encrypted Message: " << cipherTool->encrypt(message) << endl;
                break;
            case 2:
                cout << "Enter the message to decrypt: ";
                getline(cin, message);
                cout << "Decrypted Message: " << cipherTool->decrypt(message) << endl;
                break;
            case 3:
                cout << "Enter filename to save the encrypted message: ";
                getline(cin, filename);
                cout << "Enter the message to encrypt: ";
                getline(cin, message);
                cipherTool->saveToFile(filename, cipherTool->encrypt(message));
                cout << "Message saved to " << filename << endl;
                break;
            case 4:
                cout << "Enter filename to load and decrypt: ";
                getline(cin, filename);
                message = cipherTool->loadFromFile(filename);
                if (!message.empty()) {
                    cout << "Decrypted Message: " << cipherTool->decrypt(message) << endl;
                }
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);
}

int main() {
    // call the the funtion
    userInteraction();
    return 0;
}
