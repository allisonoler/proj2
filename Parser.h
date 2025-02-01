#include <vector>
#include <iostream>
#include "Token.h"
using namespace std;
//
// Created by allis on 1/28/2025.
//
class Parser {
    private:
        vector<Token> tokens;

    public:
        Parser(const vector<Token>& tokens) : tokens(tokens) {

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
                match(ID);
                idList();
            } else {
                // lambda
            }
        }

        void scheme() {
            if (tokenType() == ID) {
                match(ID);
                match(LEFT_PAREN);
                match(ID);
                idList();
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
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
                match(STRING);
                stringList();
            } else {
                //lambda
            }
        }

        void fact() {
            if (tokenType() == ID) {
                match(ID);
                match(LEFT_PAREN);
                match(STRING);
                stringList();
                match(RIGHT_PAREN);
                match(PERIOD);
            } else {
                throwError();
            }
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
            //ID LEFT_PAREN ID idList RIGHT_PAREN
            if (tokenType() == ID) {
                match(ID);
                match(LEFT_PAREN);
                match(ID);
                idList();
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
        }

        void parameter() {
            //STRING | ID
            if (tokenType() == STRING) {
                match(STRING);
            } else if (tokenType() == ID) {
                match(ID);
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
            if (tokenType() == ID) {
                match(ID);
                match(LEFT_PAREN);
                parameter();
                parameterList();
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
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

        void match(TokenType t) {
            cout << "match: " << t << endl;
            if (tokenType() == END && t!=END) {
                throwError();
            }
            if (tokenType() == t) {
                advanceToken();
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


                //rules
                match(RULES);
                match(COLON);
                ruleList();

                //QUERIES COLON query queryList
                match(QUERIES);
                match(COLON);
                query();
                queryList();

                match(END);
                cout<<"Success!";

            }
            catch(Token token){
                cout<< "Failure!"<<'\n';
                cout<<"  "<<token.toString();
            }
            catch (const std::out_of_range& e) {
                cout<<"no more tokens";
            }
        }
};
