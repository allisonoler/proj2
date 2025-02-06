#pragma once
#include <string>
#include <sstream>
#include "Parameter.h"
#include "Predicate.h"
using namespace std;

class Rule {
private:
    Predicate headPredicate;
    vector<Predicate> predicates;

public:
    Rule() : headPredicate(Predicate()), predicates(vector<Predicate>()) {

    }

    void setHeadPredicate(Predicate predicate) {
        headPredicate = predicate;
    }

    void addPredicate(Predicate predicate) {
        predicates.push_back(predicate);
    }

    string toString() {
        string result = "";
        result += headPredicate.toString() + " :- ";
        if (!predicates.empty()) {
            result += predicates.at(0).toString();
            for (int i = 1; i < predicates.size(); i++) {
                result += "," + predicates.at(i).toString();

            }
        }
        result += ".";
        return result;
    }

};