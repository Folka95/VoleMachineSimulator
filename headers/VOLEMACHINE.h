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

    void resetRam() {
        myMemo.reset();
    }
    void resetCPU() {
        myCpu.reset();
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
        myCpu.followInstructions(myMemo);
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

        for(int i = 0, d = 4; i < 16; i += d){
            int l = i;
            int r = i + d - 1;
            cout << "Registers from id " << string(3 - digits(l) , ' ') << l;
            cout << " to " << string(3 - digits(r) , ' ') << r << "  :     ";
            for(int j = l; j <= r; j++) {
                string val = myCpu.getRegisterValue(j);
                if(val.size() < 2) {
                    val = "0" + val;
                }
                cout << val << ( (j - l) % 2 == 1 ? "    |    " : "  |  ");
            }
            cout << endl;
        }
        cout << string(10 , '-') << endl;
        for(int i = 0, d = 8; i < myMemo.size(); i += d){
            int l = i;
            int r = i + d - 1;
            cout << "Memory from cell " << string(4 - digits(l) , ' ') << l;
            cout << " to " << string(4 - digits(r) , ' ') << r << " :     ";
            for(int j = l; j <= r; j++) {
                string val = myMemo.getValueAtCell(j);
                if(val.size() < 2) {
                    val = "0" + val;
                }
                cout << val << ( (j - l) % 2 == 1 ? "    |    " : "  |  ");
            }
            cout << endl;
        }
    }
};

#endif //VOLEMACHINE_H
