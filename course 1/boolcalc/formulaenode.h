#pragma once
#include<iostream>
#include <string>
#include "AVL.h"

class FormulaNode {
public:
	virtual bool calc() const = 0;
	virtual std::string str() const = 0;
	virtual ~FormulaNode() {}
};


class UnarNode : public FormulaNode {
protected:
	FormulaNode* next_;
public:
	UnarNode(FormulaNode* node) : next_(node) {}
	~UnarNode() {
		if (next_)
			delete next_;
		next_ = nullptr;
	}
};


class NumNode : public FormulaNode {
	const bool num_;
public:
	NumNode(bool x) : num_(x) { }
	bool calc() const {
		return num_;
	}
	std::string str() const {
		return std::to_string(num_);
	}
};


class BinNode : public FormulaNode {
protected:
	FormulaNode* left_;
	FormulaNode* right_;
public:
	BinNode(FormulaNode* L, FormulaNode* R) : left_(L), right_(R) {}
	~BinNode() {
		delete left_;
		delete right_;
		left_ = right_ = nullptr;
	}
};


class AndNode : public BinNode {
public:
	AndNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return (left_->calc() && right_->calc());
	}
	std::string str() const {
		return "(" + left_->str() + " & " + right_->str() + ")";
	}
};


class OrNode : public BinNode {
public:
	OrNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return (left_->calc() || right_->calc());
	}
	std::string str() const {
		return "(" + left_->str() + " v " + right_->str() + ")";
	}
};


class NoNode : public UnarNode {
public:
	NoNode(FormulaNode* node) : UnarNode(node) {}
	bool calc()const {
		return !(next_->calc());
	}
	std::string str() const {
		return "~ (" + next_->str() + ")";
	}
};


class ImplicationNode : public BinNode {
public:
	ImplicationNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return ((!left_->calc()) || right_->calc());
	}
	std::string str() const {
		return "(" + left_->str() + " > " + right_->str() + ")";
	}
};


class ReImplicationNode : public BinNode {
public:
	ReImplicationNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return (left_->calc() || (!right_->calc()));
	}
	std::string str() const {
		return "(" + left_->str() + " < " + right_->str() + ")";
	}
};


class XorNode : public BinNode {
public:
	XorNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return (left_->calc() ^ right_->calc());
	}
	std::string str() const {
		return "(" + left_->str() + " + " + right_->str() + ")";
	}
};


class EquivalenceNode : public BinNode {
public:
	EquivalenceNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return (left_->calc() == right_->calc());
	}
	std::string str() const {
		return "(" + left_->str() + " = " + right_->str() + ")";
	}
};


class ShefferStrokeNode : public BinNode {
public:
	ShefferStrokeNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return (!(left_->calc() && right_->calc()));
	}
	std::string str() const {
		return "(" + left_->str() + " | " + right_->str() + ")";
	}
};


class PeirceArrowNode : public BinNode {
public:
	PeirceArrowNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		return (!(left_->calc() || right_->calc()));
	}
	std::string str() const {
		return "(" + left_->str() + " ^ " + right_->str() + ")";
	}
};


class ParamValue {
	const char ch_;
	const bool val_;
public:
	ParamValue(char c, bool value) : ch_(c), val_(value) {}
	char getSym() const {
		return ch_;
	}
	bool getValue() const {
		return val_;
	}
	bool operator==(const ParamValue& X) const {
		return ch_ == X.ch_;
	}
	bool operator<(const ParamValue& X) const {
		return ch_ < X.ch_;
	}
};


namespace global {
	extern AVLTree<ParamValue> Workspace;
}

class ParamNode : public FormulaNode {
	const char ch_;
public:
	ParamNode(char s) : ch_(s) { }
	bool calc() const {
		auto pos = global::Workspace.find(ParamValue(ch_, 0));
		if (pos != global::Workspace.end()) {
			return (*pos).getValue();
		}
		else {
			bool tmp;
			std::cout << "x" << (ch_ - 64) << " = ";
			std::cin >> tmp;
			std::cin.ignore();
			global::Workspace.insert(ParamValue(ch_, tmp));
			return tmp;
		}
	}
	std::string str() const {
		std::string res = "x";
		res += std::to_string(ch_ - 'A' + 1);
		return res;
	}
	char getCh() {
		return ch_;
	}
};
