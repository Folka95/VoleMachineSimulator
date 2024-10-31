#include "CPU.h"
#include "RAM.h"
#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

class VoleMachine{
private:
    Ram myMemo;
    CPU myCpu;

    void printSystemDetails() {
        cout << "# This system is working on : " << endl;
        cout << "  1 - " << myMemo.size() / 1024.0 << " GB of Ram" << endl;
        cout << "  2 - " << myCpu.registersCount() << " registers integrated into the CPU" << endl;
    }

public:

    VoleMachine() {
        cout << endl;
        printSystemDetails();
    }

    void loadInstructions(string allInstructions) {
        int location = 0;
        for(int i = 0; i + 1 < allInstructions.size(); i += 2) {
            string twoBits;
            twoBits += allInstructions[i];
            twoBits += allInstructions[i + 1];
            myMemo.setValueAtCell(location++ , twoBits);
        }
    }
    void execute(){
        myCpu.readInstructions(myMemo);
    }
    void displayState(){
        cout << endl << endl;

        auto digits = [](int a) {
            int len = 0;
            do {
                len++;
                a /= 10;
            }while(a);
            return len;
        };

        for(int i = 0; i < 16; i += 4){
            cout << "Registers from id " << string(3 - digits(i) , ' ') << i;
            cout << " to " << string(3 - digits(i + 4 - 1) , ' ') << i + 4 - 1 << " : ";
            for(int j = i; j < i + 4; j++) {
                string val = myCpu.getRegisterValue(j);
                if(val.size() < 2) {
                    val = "0" + val;
                }
                cout << val << "  |  ";
            }
            cout << endl;
        }
        cout << string(10 , '-') << endl;
        for(int i = 0; i < myMemo.size(); i += 4){
            cout << "Memory from cell " << string(4 - digits(i) , ' ') << i;
            cout << " to " << string(4 - digits(i + 4 - 1) , ' ') << i + 4 - 1 << " : ";
            for(int j = i; j < i + 4; j++) {
                string val = myMemo.getValueAtCell(j);
                if(val.size() < 2) {
                    val = "0" + val;
                }
                cout << val << "  |  ";
            }
            cout << endl;
        }
    }
};

#endif //VOLEMACHINE_H
