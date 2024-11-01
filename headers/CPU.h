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

    void followInstructions(Ram &myMemo) {
        bool isRunning = true;
        while(isRunning && programCounter + 1 < myMemo.size()) {
            string instruction;
            instruction += myMemo.getValueAtCell(programCounter++);
            instruction += myMemo.getValueAtCell(programCounter++);

            if(isValidInstruction(instruction)) {
                isRunning &= runInstruction(myMemo , instruction);
            }
        }
        if(isRunning) {
            cerr << "Warning from CPU : No C000 instruction to stop execution!";
        }
    }

    bool runInstruction(Ram &myMemo, string instruction) {
        if('C' == instruction[0]) {
            return false;
        }
        if('1' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            int XY = hexaToDeci(instruction.substr(2 , 2));
            load(myRegisters[R] , myMemo.getValueAtCell(XY));
        }
        else if('2' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            string XY = instruction.substr(2 , 2);
            load(myRegisters[R] , XY);
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
        else if('5' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            int S = hexaToDeci(instruction.substr(2 , 1));
            int T = hexaToDeci(instruction.substr(3 , 1));
            addIntegral(myRegisters[R] , myRegisters[S] , myRegisters[T]);
        }
        else if('6' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            int S = hexaToDeci(instruction.substr(2 , 1));
            int T = hexaToDeci(instruction.substr(3 , 1));
            addFloating(myRegisters[R] , myRegisters[S] , myRegisters[T]);
        }
        else if('B' == instruction[0]) {
            int R = hexaToDeci(instruction.substr(1 , 1));
            string XY = instruction.substr(2 , 2);
            jump(myRegisters[R] , myRegisters[0] , hexaToDeci(XY) , programCounter);
        }
        return true;
    }
    string getRegisterValue(int index){
        if(0 <= index && index < numberOfRegisters) {
            return myRegisters[index].getValue();
        }
        throw out_of_range("Error from CPU : Invalid register number");
    }
    int registersCount() {
        return numberOfRegisters;
    }
};

#endif //CPU_H
