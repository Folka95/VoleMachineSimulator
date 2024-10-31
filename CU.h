#include "REGISTER.h"
#include "RAM.h"
#ifndef CU_H
#define CU_H

class CU{
private:

public:

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
    bool isValidInstruction(string instruction) {
        return 4 == (int)instruction.size();
    }
};

#endif //CU_H
