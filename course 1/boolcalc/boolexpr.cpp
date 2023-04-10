#include "boolexpr.h"
#include <algorithm>
#include <stack>
#include "Errors.h"

const unsigned char BooleanExpression::ActionsTable[][13] = {
	//\0  +  =  >  <  v  ^  &  |  ~  (  )  P
	  {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 6}, // \0
	  {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 6}, // +
	  {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 6}, // =
	  {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 6}, // >
	  {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 6}, // < 
	  {2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 6}, // v
	  {2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 6}, // ^
	  {2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 6}, // &
	  {2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 6}, // |
	  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 6}, // ~
	  {7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 6}  // (

	  //1 - из строки в стек
	  //2 - извлечь из стека в выходную строку
	  //3 - удалить ( из входной и ) из стека
	  //4 - финиш
	  //5 - ошибка скобок
	  //6 - из входной в выходную
	  //7 - ошибка скобок

	  //алгоритм:
	  //1) скобки
	  //2) инверсия
	  //3) конъюнкция, штрих Шеффера
	  //4) дизъюнкция, стрелка Пирса
	  //5) сложение по модулю 2, эквивалентность, импликация
};

int BooleanExpression::ActionsRowNumber(char ch) {
	switch (ch) {
	case 0:
		return 0;
	case '+':
		return 1;
	case '=':
		return 2;
	case '>':
		return 3;
	case '<':
		return 4;
	case 'v':
		return 5;
	case '^':
		return 6;
	case '&':
		return 7;
	case '|':
		return 8;
	case '~':
		return 9;
	case '(':
		return 10;
	}
	return 0;
}

int BooleanExpression::ActionsColNumber(char ch) {
	switch (ch) {
	case 0:
		return 0;
	case '+':
		return 1;
	case '=':
		return 2;
	case '>':
		return 3;
	case '<':
		return 4;
	case 'v':
		return 5;
	case '^':
		return 6;
	case '&':
		return 7;
	case '|':
		return 8;
	case '~':
		return 9;
	case '(':
		return 10;
	case ')':
		return 11;
	}
	if (ch >= 'A' && ch <= 'Z')
		return 12;
	if (ch >= '0' && ch <= '9')
		return 12;
	return 0;
}

void BooleanExpression::InfixFilter_(const char* instr, char* outstr) {
	int i = 0;
	int j = 0; // i - индекс во входной строке, j - в выходной
	char ch;
	char prev = 0;
	char buf[256]; 
	int bufLen = 0;
	while ((ch = instr[i++]) != 0) {
		if (ch == ' ' || ch == '\t')
			continue;
		if (ch == 'x') {
			buf[bufLen++] = ch;
			ch = instr[i++];
			buf[bufLen++] = ch;
		} else {
			if (bufLen == 1) {
				outstr[j++] = ch;
				bufLen = 0;
			}
			else if (bufLen > 1) {
				buf[bufLen] = '\0';
				outstr[j++] = (buf[1] - '0' + 64);
				bufLen = 0;
			}
			outstr[j++] = ch;
		}
		prev = ch;
	}
	if (bufLen == 1) {
		outstr[j++] = prev;
	}
	if (bufLen == 2) {
		outstr[j++] = (buf[1] - '0' + 64);
	}
	outstr[j] = '\0';
}

void BooleanExpression::Infix2Postfix_(const char* instr, char* outstr) {
	int i = 0;
	int j = 0; // i - индекс во входной строке, j - в выходной
	int row, col;
	unsigned char action;
	std::stack<char> S;
	do {
		col = ActionsColNumber(instr[i]);
		row = S.empty() ? 0 : ActionsRowNumber(S.top());
		action = ActionsTable[row][col];
		switch (action) {
		case 1:
			S.push(instr[i]);
			++i;
			break;
		case 2:
			outstr[j] = S.top();
			++j;
			S.pop();
			break;
		case 3:
			S.pop();
			++i;
			break;
		case 4:
			outstr[j] = '\0';
			break;
		case 5:
			throw ErrorBracketsClose(instr, i);
			break;
		case 6:
			outstr[j] = instr[i];
			++j;
			++i;
			break;
		case 7:
			throw ErrorBracketsOpen(instr, i);
			break;
		}
	} while (action != 4);
}

FormulaNode* BooleanExpression::Postfix2Tree_(const char* str) {
	int index = 0;
	std::stack<FormulaNode*> S;
	char ch;
	FormulaNode* result, * left, * right;
	try {
		while ((ch = str[index]) != '\0') {
			left = right = nullptr;
			switch (ch) {
			case '&':
				if (S.empty()) {
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty()) {
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new AndNode(left, right);
				break;
			case 'v':
				if (S.empty()) {
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty()) {
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new OrNode(left, right);
				break;
			case '~':
				if (S.empty())
				{
					throw 1;
				}
				right = S.top();
				S.pop();
				result = new NoNode(right);
				break;
			case '>':
				if (S.empty())
				{
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty())
				{
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new ImplicationNode(left, right);
				break;
			case '<':
				if (S.empty())
				{
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty())
				{
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new ReImplicationNode(left, right);
				break;
			case '+':
				if (S.empty())
				{
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty())
				{
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new XorNode(left, right);
				break;
			case '=':
				if (S.empty())
				{
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty())
				{
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new EquivalenceNode(left, right);
				break;
			case '|':
				if (S.empty())
				{
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty())
				{
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new ShefferStrokeNode(left, right);
				break;
			case '^':
				if (S.empty())
				{
					throw 1;
				}
				right = S.top();
				S.pop();
				if (S.empty())
				{
					throw 1;
				}
				left = S.top();
				S.pop();
				result = new PeirceArrowNode(left, right);
				break;
			default:
				if (ch == '0') {
					result = new NumNode(0);
				}
				else if (ch == '1') {
					result = new NumNode(1);
				}
				else if (ch >= 'A' && ch <= 'Z') {
					int idx = ch - 65;
					if (vars_[idx] == 0) {
						vars_[idx] = 1;
					}
					result = new ParamNode(ch);
				}
			}
			S.push(result);
			++index;
		}
		if (S.size() > 1) {
			left = right = nullptr;
			throw 2;
		}
		result = S.top();
		return result;
	}
	catch (int E) {
		if (left)
			delete left;
		if (right)
			delete right;
		while (!S.empty()) {
			left = S.top();
			S.pop();
			delete left;
		}
		throw ErrorPostfix(str, index);
	}
}

bool BooleanExpression::calc() {
	if (root_)
		return root_->calc();
	return 0;
}

BooleanExpression::operator std::string() const {
	if (root_)
		return root_->str();
	return std::string("");
}

std::string BooleanExpression::str() const {
	if (root_)
		return root_->str();
	return std::string("");
}

//запрашивает размеры таблицы и индексы того, что вернуть
bool fillTable(int row, int col, int id1, int id2) {
	bool** tab = new bool* [row];
	for (int i = 0; i < row; ++i) {
		tab[i] = new bool[col];
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			tab[i][col - 1 - j] = (i >> j) & 1;
		}
	}
	bool res;
	res = tab[id1][id2];

	for (int i = 0; i < row; ++i) {
		delete[] tab[i];
	}
	delete[] tab;
	return res;
}

void BooleanExpression::truthTable() const  {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}
	std::cout << "Truth Table" << std::endl;
	for (int i = 0; i < parSize; ++i) {
		std::cout << 'x' << std::to_string(parameters[i] - 'A' + 1) << " | ";
	}
	std::cout << "F  |" << std::endl;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << table[i][j] << "  | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
}

BooleanExpression BooleanExpression::cnf() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}

	std::string tmp = "";
	for (int i = 0; i < rows; ++i) {
		if (table[i][cols - 1] == 0) {
			tmp += '(';
			for (int j = 0; j < parSize - 1; ++j) {
				if (table[i][j] == 0) {
					tmp += 'x' + std::to_string(parameters[j] - 'A' + 1) + 'v';
				}
				else {
					tmp += "~x" + std::to_string(parameters[j] - 'A' + 1) + 'v';
				}
			}
			if (table[i][parSize - 1] == 0) {
				tmp += 'x' + std::to_string(parameters[parSize - 1] - 'A' + 1);
			}
			else {
				tmp += "~x" + std::to_string(parameters[parSize - 1] - 'A' + 1);
			}
			tmp += ")&";
		}
	}
	char answ[256];
	for (int i = 0; i < tmp.size() - 1; ++i) {
		answ[i] = tmp[i];
	}

	answ[tmp.size()] = '\0';

	BooleanExpression res(answ);

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
	return res;
}

BooleanExpression BooleanExpression::dnf() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}

	std::string tmp = "";
	for (int i = 0; i < rows; ++i) {
		if (table[i][cols - 1] == 1) {
			for (int j = 0; j < parSize - 1; ++j) {
				if (table[i][j] == 1) {
					tmp += 'x' + std::to_string(parameters[j] - 'A' + 1) + '&';
				}
				else {
					tmp += "~x" + std::to_string(parameters[j] - 'A' + 1) + '&';
				}
			}
			if (table[i][parSize - 1] == 1) {
				tmp += 'x' + std::to_string(parameters[parSize - 1] - 'A' + 1);
			}
			else {
				tmp += "~x" + std::to_string(parameters[parSize - 1] - 'A' + 1);
			}
			tmp += 'v';
		}
	}
	char answ[256];
	for (int i = 0; i < tmp.size() - 1; ++i) {
		answ[i] = tmp[i];
	}

	answ[tmp.size()] = '\0';

	BooleanExpression res(answ);

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
	return res;
}

BooleanExpression BooleanExpression::zhegalkin() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}

	//вспомогательная треугольная таблица 
	bool** tmpTable = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		tmpTable[i] = new bool[rows];
	}

	//первый столбец совпадает с значением функции в таблице истинности
	for (int i = 0; i < rows; ++i) {
		tmpTable[i][0] = table[i][cols - 1];
	}

	//ячейка в каждом последующем столбце получается сложением по мод 2 ячеек предыдущего столбца
	//стоящей в той же строке и строкой ниже
	int idx = rows - 1;
	for (int i = 1; i < rows; ++i) {
		for (int j = 0; j < idx; ++j) {
			tmpTable[j][i] = tmpTable[j][i - 1] ^ tmpTable[j + 1][i - 1];
		}
		--idx;
	}

	std::string tmp = "";
	if (tmpTable[0][0] == 1) {
		tmp += "1+";
	}
	else {
		tmp += "0+";
	}

	for (int i = 1; i < rows; ++i) {
		if (tmpTable[0][i] == 1) {
			for (int j = 0; j < parSize; ++j) {
				if (table[i][j] == 1) {
					tmp += 'x' + std::to_string(parameters[j] - 'A' + 1) + '&';
				}
			}
			tmp[tmp.size() - 1] = '+';
		}
	}
	char answ[256];
	for (int i = 0; i < tmp.size() - 1; ++i) {
		answ[i] = tmp[i];
	}

	answ[tmp.size()] = '\0';

	BooleanExpression res(answ);

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;

	for (int i = 0; i < rows; ++i) {
		delete[] tmpTable[i];
	}
	delete[] tmpTable;

	return res;
}

bool BooleanExpression::classT0() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}

	bool res = 1;
	for (int i = 0; i < rows; ++i) {
		if (table[i][cols - 1] == 1) {
			res = 0;
			break;
		}
	}

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
	return res;
}

bool BooleanExpression::classT1() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}

	bool res = 1;
	for (int i = 0; i < rows; ++i) {
		if (table[i][cols - 1] == 0) {
			res = 0;
			break;
		}
	}

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
	return res;
}

bool BooleanExpression::classS() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}
	bool* tmp = new bool[rows];
	for (int i = 0; i < rows; ++i) {
		tmp[i] = !(table[i][cols - 1]);
	}

	bool res = 1;
	for (int i = 0; i < rows; ++i) {
		if (tmp[i] != table[rows - 1 - i][cols - 1]) {
			res = 0;
			break;
		}
	}

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
	delete[] tmp;
	return res;
}

bool BooleanExpression::classM() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}

	bool res = 1;
	bool tmp = table[0][cols - 1];
	for (int i = 0; i < rows; ++i) {
		if (tmp <= table[i][cols - 1]) {
			tmp = table[i][cols - 1];
		}
		else {
			res = 0;
			break;
		}
	}

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
	return res;
}

bool BooleanExpression::classL() const {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	int parSize = parameters.size();
	int cols = 1 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize; ++j) {
			table[i][j] = fillTable(rows, parSize, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 1] = root_->calc();
		global::Workspace.clear();
	}

	bool** tmpTable = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		tmpTable[i] = new bool[rows];
	}
	for (int i = 0; i < rows; ++i) {
		tmpTable[i][0] = table[i][cols - 1];
	}
	int idx = rows - 1;
	for (int i = 1; i < rows; ++i) {
		for (int j = 0; j < idx; ++j) {
			tmpTable[j][i] = tmpTable[j][i - 1] ^ tmpTable[j + 1][i - 1];
		}
		--idx;
	}
	bool res = 1;
	int tmp = 1;
	for (int i = 1; i < rows; ++i) {
		if (i == tmp) {
			tmp *= 2;
			continue;
		} else {
			if (tmpTable[0][i] == 1) {
				res = false;
				break;
			}
		}
	}

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;

	for (int i = 0; i < rows; ++i) {
		delete[] tmpTable[i];
	}
	delete[] tmpTable;
	return res;
}

bool isFullSystem(const std::vector<BooleanExpression>& vec) {
	bool is_m = 0, is_t0 = 0, is_t1 = 0, is_s = 0, is_l = 0;
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i].classT0() == 0) {
			is_t0 = 1;
		}
		if (vec[i].classT1() == 0) {
			is_t1 = 1;
		}
		if (vec[i].classS() == 0) {
			is_s = 1;
		}
		if (vec[i].classM() == 0) {
			is_m = 1;
		}
		if (vec[i].classL() == 0) {
			is_l = 1;
		}
	}
	bool res = 0;
	if (is_t0 == 1 && is_t1 == 1 && is_m == 1 && is_s == 1 && is_l == 1) {
		res = 1;
	}
	return res;
}

//для тестов
bool operator==(const BooleanExpression& l, const BooleanExpression& r) {
	global::Workspace.clear();
	std::vector<char> parameters;
	for (int i = 0; i < 26; ++i) {
		if (l.vars_[i] != 0) {
			parameters.push_back(i + 65);
		}
	}
	std::vector<char> parameters2;
	for (int i = 0; i < 26; ++i) {
		if (r.vars_[i] != 0) {
			parameters2.push_back(i + 65);
		}
	}
	if (parameters.size() != parameters2.size())
		return false;
	int parSize = parameters.size();
	int cols = 2 + parSize;
	int rows = 1;
	for (int i = 0; i < parSize; ++i) {
		rows *= 2;
	}
	bool** table = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		table[i] = new bool[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < parSize - 1; ++j) {
			table[i][j] = fillTable(rows, parSize - 1, i, j);
			global::Workspace.insert(ParamValue(parameters[j], table[i][j]));
		}
		table[i][cols - 2] = l.root_->calc();
		table[i][cols - 1] = r.root_->calc();
		global::Workspace.clear();
	}


	bool res = 1;
	for (int i = 0; i < rows; ++i) {
		if (table[i][cols - 1] != table[i][cols - 2]) {
			res = 0;
			break;
		}
	}

	for (int i = 0; i < rows; ++i) {
		delete[] table[i];
	}
	delete[] table;
	return res;
}