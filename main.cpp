#include <bits/stdc++.h>
using namespace std;
#include "VOLEMACHINE.h"

int main() {
    string ins = "140F34B1200434B2C000";
    VoleMachine voleM;
    voleM.displayState();
    voleM.loadInstructions(ins);
    voleM.execute();
    voleM.displayState();
    cout << "I am working!" << endl;
    return 0;
}
