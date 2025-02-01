#pragma once
#include <cctype>
#include <vector>
#include <string>
#include "Token.h"
using namespace std;

class Scanner {
	private:
		string input;
        int line_number;
        int total_tokens;

	public:
		Scanner(const string& input) : input(input) {
            line_number = 1;
            total_tokens = 0;
        }

        void incrementToken() {
            total_tokens++;
        }

        int getTotalTokens() {
            return total_tokens;
        }

        string getInput() {
            return input;
        }

        bool endOfString(string input_value, int index) {
            if (input_value.size() < index+1) {
                return true;
            } else {
                return false;
            }
        }

        bool validCharacter(char check_char) {
            if (check_char == '(' or check_char == ')' or check_char == ':' or check_char == ':-' or check_char == '?' or check_char == '.' or check_char == '"' or check_char == '#' or check_char == '*' or check_char == '+' or
                    isspace(check_char)) {
                return true;
            } else {
                return false;
            }
        }

        Token scanIdentifiers() {
            int index = 0;
            if (isalpha(input.at(0))) {
                index++;
                if ((not endOfString(input, index)) and (isalpha(input.at(index)) or isdigit(input.at(index)))) {
                    index++;
                    while (not endOfString(input, index) and (isalpha(input.at(index)) or isdigit(input.at(index)))) {
                        index++;
                    }
                    if (endOfString(input, index)) {
                        string return_value = input.substr(0, index);
                        input = input.substr(index);
                        return Token(ID, return_value, line_number);
                    }
                    if ((not endOfString(input, index))) {
                        string return_value = input.substr(0, index);
                        input = input.substr(index);
                        return Token(ID, return_value, line_number);
                    }
                } else {
                    string return_value = input.substr(0, index);
                    input = input.substr(index);
                    return Token(ID, return_value, line_number);
                }
            }
            string return_value = input.substr(0, index+1);
            input = input.substr(index);
            return Token(UNDEFINED, return_value, line_number);
        }

        Token scanSchemes() {
            string schemes = "Schemes";
            if (input.size() < schemes.size()) {
                return scanIdentifiers();
            }
            for (int i = 1; i < schemes.size(); i++) {
                if (input.at(i) == schemes.at(i)) {
                    continue;
                } else if (isalpha(input.at(i)) or isdigit(input.at(i))) {
                    return scanIdentifiers();
                } else {
                    string return_value = input.substr(0, i);
                    input = input.substr(i);
                    return Token(ID, return_value, line_number);
                }
            }
            if ((not endOfString(input, 7)) and (isalpha(input.at(7)) or isdigit(input.at(7)))) {
                return scanIdentifiers();
            }
            input = input.substr(7);
            return Token(SCHEMES, "Schemes", line_number);
        }

    Token scanRules() {
        string rules = "Rules";
        if (input.size() < rules.size()) {
            return scanIdentifiers();
        }
        for (int i = 1; i < rules.size(); i++) {
            if (input.at(i) == rules.at(i)) {
                continue;
            } else if (isalpha(input.at(i)) or isdigit(input.at(i))) {
                return scanIdentifiers();
            } else {
                string return_value = input.substr(0, i);
                input = input.substr(i);
                return Token(ID, return_value, line_number);
            }
        }
        if ((not endOfString(input, 5)) and (isalpha(input.at(5)) or isdigit(input.at(5)))) {
            return scanIdentifiers();
        }
        input = input.substr(5);
        return Token(RULES, "Rules", line_number);
    }

    Token scanFacts() {
        string facts = "Facts";
        if (input.size() < facts.size()) {
            return scanIdentifiers();
        }
        for (int i = 1; i < facts.size(); i++) {
            if (input.at(i) == facts.at(i)) {
                continue;
            } else if (isalpha(input.at(i)) or isdigit(input.at(i))) {
                return scanIdentifiers();
            } else {
                string return_value = input.substr(0, i);
                input = input.substr(i);
                return Token(ID, return_value, line_number);
            }
        }
        if ((not endOfString(input, 5)) and (isalpha(input.at(5)) or isdigit(input.at(5)))) {
            return scanIdentifiers();
        }
        input = input.substr(5);
        return Token(FACTS, "Facts", line_number);
    }

    Token scanQueries() {
        string queries = "Queries";
        if (input.size() < queries.size()) {
            return scanIdentifiers();
        }
        for (int i = 1; i < queries.size(); i++) {
            if (input.at(i) == queries.at(i)) {
                continue;
            } else if (isalpha(input.at(i)) or isdigit(input.at(i))) {
                return scanIdentifiers();
            } else {
                string return_value = input.substr(0, i);
                input = input.substr(i);
                return Token(ID, return_value, line_number);
            }
        }
        if ((not endOfString(input, 7)) and (isalpha(input.at(7)) or isdigit(input.at(7)))) {
            return scanIdentifiers();
        }
        input = input.substr(7);
        return Token(QUERIES, "Queries", line_number);
    }

    Token scanComment() {
        int index = 0;
        while ((not endOfString(input, index)) and input.at(index) != '\n') {
            index++;
        }
        string return_value = input.substr(0, index);
        input = input.substr(index);
        return Token(COMMENT, return_value, line_number);
    }

    Token scanString() {
            int active_line_number = line_number;
            int index = 1;
            while (not endOfString(input, index)) {
                if (input.at(index) == '\'') {
                    string return_value = input.substr(0, index+1);
                    input = input.substr(index+1);
                    return Token(STRING, return_value, active_line_number);
                }
                index++;
                if (endOfString(input, index)) {
                    break;
                }
                if (input.at(index) == '\n') {
                    line_number++;
                }
            }
            string return_value = input.substr(0, index);
            input = input.substr(index);
            return Token(UNDEFINED, return_value, active_line_number);
    }

        Token scanToken() {
            total_tokens++;
            if (input.size() == 0) {
                return Token(END, "", line_number);
            }
            while (isspace(input.at(0))) {
                if (input.at(0) == '\n') {
                    line_number++;
                }
                input = input.substr(1);
                if (input.size() == 0) {
                    return Token(END, "", line_number);
                }
            }
            if (input.at(0) == ',') {
                input = input.substr(1);
                return Token(COMMA, ",", line_number);
            } else if (input.at(0) == ':') {
                if ((not endOfString(input, 1)) and input.at(1) == '-') {
                    input = input.substr(2);
                    return Token(COLON_DASH, ":-", line_number);
                } else {
                    input = input.substr(1);
                    return Token(COLON, ":", line_number);
                }

            } else if (input.at(0) == '.') {
                input = input.substr(1);
                return Token(PERIOD, ".", line_number);
            } else if (input.at(0) == '?') {
                input = input.substr(1);
                return Token(Q_MARK, "?", line_number);
            } else if (input.at(0) == '(') {
                input = input.substr(1);
                return Token(LEFT_PAREN, "(", line_number);
            } else if (input.at(0) == ')') {
                input = input.substr(1);
                return Token(RIGHT_PAREN, ")", line_number);
            } else if (input.at(0) == '*') {
                input = input.substr(1);
                return Token(MULTIPLY, "*", line_number);
            } else if (input.at(0) == '+') {
                input = input.substr(1);
                return Token(ADD, "+", line_number);

            }else if (input.at(0) == '\'') {
                return scanString();

            }else if (input.at(0) == 'S') {
                return scanSchemes();

            } else if (input.at(0) == 'R') {
                return scanRules();
            } else if (input.at(0) == 'F') {
                return scanFacts();
            } else if (input.at(0) == 'Q') {
                return scanQueries();
            } else if (input.at(0) == '#') {
                scanComment();
                return scanToken();
            }
            else if (isalpha(input.at(0))) {
                return scanIdentifiers();
            } else {
                string return_value = input.substr(0,1);
                input = input.substr(1);
                return Token(UNDEFINED, return_value, line_number);
            }
        }

        vector<Token> scanAll() {
            vector<Token> tokens;
            while (!input.empty()) {
                tokens.push_back(scanToken());
                if(input.empty()) {
                    tokens.push_back(Token(END, "", line_number));
                }
            }
            return tokens;
        }
};
