#include <string>
#include <sstream>
#include "Parameter.h"
#include "Predicate.h"
using namespace std;

class Rule {
private:
    Predicate headPredicate;
    vector<Predicate> predicates;
    //headPredicate COLON_DASH predicate predicateList PERIOD

public:
    Rule(Predicate headPredicate, vector<Predicate> predicates) : headPredicate(headPredicate), predicates(predicates) {

    }

    string toString() {
        string result = "";
        result += headPredicate.toString() + " :- ";
        result += predicates.at(0).toString();
        for (int i = 1; i<predicates.size(); i++) {
            result += "," + predicates.at(i).toString();

        }
        result += ".";
        return result;
    }

};