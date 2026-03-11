#include "parser.h"

int main(){
    vector<submission> subs = parse("input1.csv");
    cout << subs.size() << "\n";
    for (submission sub : subs){
        cout << sub.id << " + " << sub.title << " + " << sub.name << " + " << sub.email << " + " << sub.primary << " + " << sub.secondary << "\n";
    }

    return 0;
}

