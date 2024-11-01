#ifndef RAM_H
#define RAM_H


class Ram{
private:
    const int memoSize = 16 * 16;
    const int maxBits = 2;
    vector< string > memory;
public:
    Ram(){
        memory = vector< string > (memoSize , "0");
    }

    void reset() {
        for(auto &mem : memory) {
            mem = "0";
        }
    }

    int size() {
        return memoSize;
    }
    int bitSize() {
        return int(pow(16 , maxBits));
    }

    string getValueAtCell(int cell){
        if(0 <= cell && cell < memoSize){
            return memory[ cell ];
        }
        else {
            throw out_of_range("Error from ram : Invalid cell location");
        }
    }
    void setValueAtCell(int cell, string value){
        if(0 <= cell && cell < memoSize){
            if(value.size() > 2) {
                throw overflow_error("Error from ram : setting this new value will cause overflow");
            }
            memory[ cell ] = value;
        }
        else {
            throw out_of_range("Error from ram : Invalid cell location");
        }
    }
};

#endif //RAM_H
