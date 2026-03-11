#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct submission{
    int id;
    string title;
    string name;
    string email;
    int primary;
    int secondary = -1;
};

vector<submission> parse(string file);