#include "REGISTER.h"
#ifndef ALU_H
#define ALU_H

class ALU{
private:
    vector<char> nums = {
        '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F'
    };
public:

    bool isValidInstruction(string instruction) {
        if (instruction.size() != 4) {
            return false;
        }
        if('C' == instruction[0]) {
            return ("C000" == instruction);
        }

        vector<char> nums2 = {
            '1', '2', '3', '4',
            '5', '6', 'B'
        };

        if (find(nums2.begin(), nums2.end(), instruction[0]) == nums2.end()) {
            return false;
        }

        string subString = instruction.substr(1 , 3);

        int j = 0;
        if('4' == instruction[0]) {
            j = 1;
            if(subString[0] != '0') {
                return false;
            }
        }

        for (int i = j; i < subString.size(); i++) {
            if (find(nums.begin(), nums.end(), subString[i]) == nums.end()) {
                return false;
            }
        }
        return true;
    }

    void addIntegral(Register &regV, Register &regA, Register &regB) {
        int a = hexaToDeci(regA.getValue());
        int b = hexaToDeci(regB.getValue());
        int result = (a + b) % regV.bitSize();
        regV.setValue( deciToHexa(result) );
    }

    float hexaToFloat(string hexaVal) {
        int val = hexaToDeci(hexaVal);
        int e = ((val / 16) & 7) - 8;
        float m = (val & 15);
        return m * pow(2.0 , e);
    }

    string floatToHexa(float val) {
        const float mx = hexaToFloat("FF");
        const float mn = hexaToFloat("0");
        if (val > mx) {
            return "FF";
        }
        if (val < mn) {
            return "0";
        }

        int integer = int(val * 256);
        int exp = 0;
        while (integer > 16) {
            integer >>= 1;
            exp++;
        }
        return deciToHexa(((exp << 4) | integer));
    }

    void addFloating(Register &regV, Register &regA, Register &regB) {
        float a = hexaToFloat(regA.getValue());
        float b = hexaToFloat(regB.getValue());
        string result = floatToHexa(a + b);
        regV.setValue(result);
    }

    int hexaToDeci(string s){
        int decimalValue = 0;
        int base = 1;

        for (int i = (int)s.size() - 1; i >= 0; i--) {
            char ch = s[i];
            for(int equi = 0; equi < (int)nums.size(); equi++){
                if(ch == nums[equi]){
                    decimalValue += equi * base;
                }
            }
            base *= 16;
        }

        return decimalValue;
    }

    string deciToHexa(int value){
        string hexaValue = "";

        do{
            hexaValue = nums[value % 16] + hexaValue;
            value /= 16;
        } while (value);

        return hexaValue;
    }
};

#endif //ALU_H
