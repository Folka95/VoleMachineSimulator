#ifndef REGISTER_H
#define REGISTER_H

class Register{
private:
    string value;
    const int maxBits = 2;
public:
    Register(){
        reset();
    }
    int bitSize() {
        return int(pow(16 , maxBits));
    }
    void reset() {
        value = "0";
    }
    void setValue(string val){
        value = val;
    }
    string getValue(){
        return value;
    }
};


#endif //REGISTER_H
