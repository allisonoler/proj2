#pragma once
#include <string>
#include <sstream>
using namespace std;
enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END
};

class Token {
	private:
		TokenType type;
		string value;
		int line;

	public:
		Token(TokenType type, string value, int line) : type(type), value(value), line(line) {

		}

        string getValue() {
            return value;
        }

        TokenType getType() const {
            return type;
        }

	string toString() const {
		stringstream out;
		out<< "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
		return out.str();
	}

	string typeName(TokenType type) const {
		if (type == COMMA) {
			return "COMMA";
		} else if (type == PERIOD) {
			return "PERIOD";
		} else if (type == Q_MARK) {
			return "Q_MARK";
		} else if (type == LEFT_PAREN) {
			return "LEFT_PAREN";
		} else if (type == RIGHT_PAREN) {
			return "RIGHT_PAREN";
		} else if (type == COLON) {
			return "COLON";
		} else if (type == COLON_DASH) {
			return "COLON_DASH";
		} else if (type == MULTIPLY) {
			return "MULTIPLY";
		} else if (type == ADD) {
			return "ADD";
		} else if (type == SCHEMES) {
			return "SCHEMES";
		} else if (type == FACTS) {
			return "FACTS";
		} else if (type == RULES) {
			return "RULES";
		} else if (type == QUERIES) {
			return "QUERIES";
		} else if (type == ID) {
			return "ID";
		} else if (type == STRING) {
			return "STRING";
		} else if (type == COMMENT) {
			return "COMMENT";
		} else if (type == UNDEFINED) {
			return "UNDEFINED";
		} else if (type == END) {
			return "END";
		}
		else {
			return "Value not found";
		}
	}
};
