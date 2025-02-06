#pragma once
#include <vector>
#include <iostream>
#include <set>
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
using namespace std;
//
// Created by allis on 1/28/2025.
//
class Parser {
    private:
    DatalogProgram datalogProgram;
        vector<Token> tokens;
        Predicate currentPredicate;
        Rule currentRule;
        bool ruleTime;
        bool queryTime;


    public:
        Parser(const vector<Token>& tokens) : tokens(tokens), datalogProgram(DatalogProgram()) {
            ruleTime = false;
            queryTime = false;
        }

        TokenType tokenType() const {
            return tokens.at(0).getType();
        }

        void advanceToken() {
            tokens.erase(tokens.begin());
        }

        void throwError() {
            throw tokens.at(0);
            //throw the token so it can be caught at the top
        }

        void idList() {
            if (tokenType() == COMMA) {
                match(COMMA);
                currentPredicate.addParameter(Parameter(match(ID).getValue()));
                idList();
            } else {
                // lambda
            }
        }

        void scheme() {
            currentPredicate = Predicate();
            if (tokenType() == ID) {
                currentPredicate.setName(match(ID).getValue());
                match(LEFT_PAREN);
                currentPredicate.addParameter(match(ID).getValue());
                idList();
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
            datalogProgram.addScheme(currentPredicate);
        }

        void schemeList() {
            if (tokenType() == ID) {
                scheme();
                schemeList();
            } else {
                //lambda
            }
        }

        void stringList() {
            //COMMA STRING stringList | lambda
            if (tokenType() == COMMA) {
                match(COMMA);
//                match(STRING);
                string value = match(STRING).getValue();
                currentPredicate.addParameter(value);
                datalogProgram.addDomain(value);
                stringList();
            } else {
                //lambda
            }
        }

        void fact() {
            currentPredicate = Predicate();
            if (tokenType() == ID) {
                currentPredicate.setName(match(ID).getValue());
                match(LEFT_PAREN);
//                match(STRING);
//                currentPredicate.addParameter(match(STRING).getValue());
                string value = match(STRING).getValue();
                currentPredicate.addParameter(value);
                datalogProgram.addDomain(value);
                stringList();
                match(RIGHT_PAREN);
                match(PERIOD);
            } else {
                throwError();
            }
            currentPredicate.setType("fact");
            datalogProgram.addFact(currentPredicate);

            //ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
        }

        void factList() {
            if (tokenType() == ID) {
                fact();
                factList();
            } else {
                //lambda
            }
        }

        void headPredicate() {
            currentPredicate = Predicate();
            //ID LEFT_PAREN ID idList RIGHT_PAREN
            if (tokenType() == ID) {
//                match(ID);
                currentPredicate.setName(match(ID).getValue());
                match(LEFT_PAREN);
                currentPredicate.addParameter(Parameter(match(ID).getValue()));
//                match(ID);
                idList();
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
            currentRule.setHeadPredicate(currentPredicate);
        }

        void parameter() {
            //STRING | ID
            if (tokenType() == STRING) {
                currentPredicate.addParameter(match(STRING).getValue());
//                match(STRING);
            } else if (tokenType() == ID) {
//                match(ID);
                currentPredicate.addParameter(match(ID).getValue());
            } else {
                throwError();
            }
        }

        void parameterList() {
            if (tokenType() == COMMA) {
                match(COMMA);
                parameter();
                parameterList();
            } else {
                //lambda
            }
            //COMMA parameter parameterList | lambda
        }

        void predicate(){
            //ID LEFT_PAREN parameter parameterList RIGHT_PAREN
            currentPredicate = Predicate();
            if (tokenType() == ID) {
//                match(ID);
                currentPredicate.setName(match(ID).getValue());
                match(LEFT_PAREN);
                parameter();
                parameterList();
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
            if (ruleTime) {
                currentRule.addPredicate(currentPredicate);
            }
            if (queryTime) {
                currentPredicate.setType("query");
                datalogProgram.addQuery(currentPredicate);
            }
//            }
        }

        void predicateList() {
            if (tokenType()==COMMA) {
                match(COMMA);
                predicate();
                predicateList();
            } else {
                //lambda
            }
            //COMMA predicate predicateList | lambda
        }

        void rule(){
            currentRule = Rule();
            //headPredicate COLON_DASH predicate predicateList PERIOD
            if (tokenType() == ID) {
                headPredicate();
                match(COLON_DASH);
                predicate();
                predicateList();
                match(PERIOD);
            } else {
                throwError();
            }
            datalogProgram.addRule(currentRule);
        }

        void ruleList() {

            //rule ruleList | lambda
            if (tokenType() == ID) {
                rule();
                ruleList();
            } else {
                //lambda
            }
        }

        void query() {
            if (tokenType()==ID) {
                predicate();
                match(Q_MARK);
            } else {
                throwError();
            }
            //predicate Q_MARK
        }

        void queryList() {
            //query queryList | lambda
            if (tokenType()==ID) {
                query();
                queryList();
            } else {
                //lambda
            }
        }

        Token match(TokenType t) {
//            cout << "match: " << t << endl;
            if (tokenType() == END && t!=END) {
                throwError();
            }
            if (tokenType() == t) {
                Token returnToken = tokens.at(0);
                advanceToken();
                return returnToken;
            } else {
                throwError();
            }
        }

        void parseProgram() {
            try {


                //scheme
                match(SCHEMES);
                match(COLON);
                scheme();
                schemeList();

                //facts
                match(FACTS);
                match(COLON);
                factList();

                ruleTime = true;
                //rules
                match(RULES);
                match(COLON);
                ruleList();
                ruleTime = false;

                //QUERIES COLON query queryList
                queryTime = true;
                match(QUERIES);
                match(COLON);
                query();
                queryList();
                queryTime = false;

                match(END);
                cout<<"Success!\n";
                cout<<datalogProgram.toString();

            }
            catch(Token token){
                cout<< "Failure!"<<'\n';
                cout<<"  "<<token.toString();
            }
//            catch (const std::out_of_range& e) {
//                cout<<"no more tokens";
//            }
        }
};
