#include <bits/stdc++.h>
using namespace std;
#include "VOLEMACHINE.h"
#include "inputValidator.h"


inputValidator input;

string readInstructions(string fileName) {
    string result;

    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        for (char ch : line) {
            ch = toupper(ch);
            if ('0' <= ch && ch <= '9') {
                result += ch;
            }
            if ('A' <= ch && ch <= 'F') {
                result += ch;
            }
        }
    }
    file.close();
    return result;
}


void menu(VoleMachine &voleM) {
    auto printMenu = []() {
        cout << endl << endl;
        cout << "Vole Machine menu :" << endl;
        cout << "   [1]- Read instructions form file" << endl;
        cout << "   [2]- Import the instructions to the ram" << endl;
        cout << "   [3]- Execute" << endl;
        cout << "   [4]- Print state" << endl;
        cout << "   [5]- Reset ram" << endl;
        cout << "   [6]- Reset cpu" << endl;
        cout << "   [7]- Reset all" << endl;
        cout << "   [8]- Quit the program" << endl << endl;
    };
    string fileName = "123";
    string instructions = "213C224D6312C000";
    while(true) {
        printMenu();
        cout << "Enter a valid choice : ";
        int choice = input.readRangeChoice(1 , 8);
        if (choice == 1) {
            cout << "Enter a valid .txt file name " << endl;
            fileName = input.readFileName("txt");
            instructions = readInstructions(fileName);
        }
        else if(choice == 2) {
            if("123" == fileName) {
                cout << "!!! Please, choose a file before you import instructions." << endl;;
                continue;
            }
            voleM.loadInstructions(instructions);
        }
        else if (choice == 3) {
            voleM.execute();
        }
        else if (choice == 4) {
            voleM.displayState();
        }
        else if (choice == 5) {
            voleM.resetRam();
        }
        else if (choice == 6) {
            voleM.resetCPU();
        }
        else if (choice == 7) {
            voleM.resetRam();
            voleM.resetCPU();
        }
        else {
            break;
        }
    }
}

int main() {
    cout << "I am ON!" << endl;
    VoleMachine voleM;
    menu(voleM);
    cout << "I am OFF!" << endl;
    return 0;
}
