#ifndef REGISTER_H
#define REGISTER_H

class Register{
private:
    string value;
public:
    Register(){
        reset();
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
