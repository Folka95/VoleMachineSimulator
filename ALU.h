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
