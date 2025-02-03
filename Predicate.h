#include <string>
#include <sstream>
#include "Parameter.h"
using namespace std;

class Predicate {
    private:
        string name;
        vector<Parameter> parameters;
        string type;

    public:
        Predicate(string name, vector<Parameter> parameters, string type) : name(name), parameters(parameters), type(type) {

        }

        string toString() {
            string result = "";
            result += name += "(" + parameters.at(0).toString();
            for (int i = 1; i<parameters.size(); i++) {
                result += "," + parameters.at(i).toString();

            }
            result += ")";
            if (type =="fact") {
                return result +=".";
            } else if (type == "query") {
                return result +="?";
            } else {
                return result;
            }

        }

};