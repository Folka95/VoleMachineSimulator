#include "REGISTER.h"
#include "RAM.h"
#ifndef CU_H
#define CU_H

class CU{
private:

public:

    void jump(Register &regR, Register &reg0, int XY ,int &programCounter) {
        if(regR.getValue() == reg0.getValue()) {
            if(XY < programCounter) {
                cerr << "Warning from CU : Jumping to a previous cell, infinite loop is expected!" << endl;
            }
            if(XY == programCounter) {
                throw runtime_error("Error from CU : Jumping to the same cell causes stucking in infinite loop");
            }
            programCounter = XY;
        }
    }
    void load(Register &reg, string value) {
        reg.setValue(value);
    }
    void store(Ram &memo, int cell, Register &reg) {
        cout << cell << endl;
        memo.setValueAtCell(cell , reg.getValue());
    }
    void move(Register &regS, Register &regR) {
        regS.setValue(regR.getValue());
    }
};

#endif //CU_H
