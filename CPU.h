#include "ALU.h"
#include "CU.h"
#include "REGISTER.h"
#include "RAM.h"

#ifndef CPU_H
#define CPU_H

class CPU : public ALU, public CU{
private:
    vector< Register > myRegisters;
    int numberOfRegisters;
    int programCounter;
public:
    CPU() {
        numberOfRegisters = 16;
        myRegisters = vector< Register >(numberOfRegisters);
        reset();
    }

    void reset() {
        programCounter = 0;
        for(auto &reg : myRegisters) {
            reg.reset();
        }
    }

    void readInstructions(Ram &myMemo) {
        bool isRunning = true;
        while(isRunning && programCounter + 1 < myMemo.size()) {
            string instruction;
            instruction += myMemo.getValueAtCell(programCounter++);
            instruction += myMemo.getValueAtCell(programCounter++);
            if(isValidInstruction(instruction)) {
                isRunning &= runInstruction(myMemo , instruction);
            }
        }
    }

    bool runInstruction(Ram &myMemo, string instruction) {
        if("C000" == instruction) {
            return false;
        }
        if('1' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            string XY = instruction.substr(2 , 2);
            load(myRegisters[R] , XY);
        }
        else if('2' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            int XY = hexaToDeci(instruction.substr(2 , 2));
            load(myRegisters[R] , myMemo.getValueAtCell(XY));
        }
        else if('3' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            int XY = hexaToDeci(instruction.substr(2 , 2));
            store(myMemo , XY , myRegisters[R]);
        }
        else if('4' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(2 , 1));
            int S = hexaToDeci(instruction.substr(3 , 1));
            move(myRegisters[S] , myRegisters[R]);
        }
        else {
            cout << "Still unsupported" << endl;
        }
        return true;
    }
    string getRegisterValue(int index){
        return myRegisters[index].getValue();
    }
    int registersCount() {
        return numberOfRegisters;
    }
};

#endif //CPU_H
