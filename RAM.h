#ifndef RAM_H
#define RAM_H


class Ram{
private:
    const int memoSize = 16 * 16;
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
    string getValueAtCell(int cell){
        if(0 <= cell && cell < memoSize){
            return memory[ cell ];
        }
        else {
            throw invalid_argument("Error from ram : Invalid cell location");
        }
    }
    void setValueAtCell(int cell, string value){
        if(0 <= cell && cell < memoSize){
            memory[ cell ] = value;
        }
        else {
            throw invalid_argument("Error from ram : Invalid cell location");
        }
    }
};

#endif //RAM_H
