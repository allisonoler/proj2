#pragma once
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
        Predicate() : name(""), parameters(vector<Parameter>()), type("") {

        }


    void setName(const string &name) {
        Predicate::name = name;
    }


    void addParameter(Parameter parameter) {
            parameters.push_back(parameter);

        }

    void setType(const string &type) {
        Predicate::type = type;
    }



    string toString() {
            string result = "";
            if (!parameters.empty()) {
                result += name += "(" + parameters.at(0).toString();
                for (int i = 1; i < parameters.size(); i++) {
                    result += "," + parameters.at(i).toString();

                }
                result += ")";
            }

            if (type =="fact") {
                return result +=".";
            } else if (type == "query") {
                return result +="?";
            } else if (type=="colon_style") {
                return result+=":";
            } else {
                return result;
            }

        }

};