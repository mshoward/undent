#include <vector>
#include <string>

using std::string;
using std::vector;

class syntaxChecker
{
	/*
		Assumming every opening block character has a closing block character,
		that the code must be well-formed, i.e. for a given opening character
		the next block character must either be it's companion closing character,
		or an opening character.


		aka for a given statement S and example alphabet Z = { '{', '(', ')', '}'} :
		S -> R || E, where E is the empty string
		R -> (S) || E
		R -> {S} || E

		"Easymode" implementation specifies that the user define opening and closing characters.
		
	*/

public:
	bool valid;
	int opens;
	int closes;
	vector<char> pile;
	vector<char> OpenLang;
	vector<char> CloseLang;
	int syntaxChecker::get(vector<char> &a, char b)
	{
		int i;
		for(i = 0; i < a.size(); i++)
		{
			if(a[i] == b)
				return i;
		}
		return i;
	}
	bool syntaxChecker::has(vector<char> &a, char b)
	{
		for(int i = 0; i < a.size(); i++)
		{
			if (a[i] == b)
				return true;
		}
		return false;
	}
private:
	//bool has(vector<char> &a, char b); //returns true if the vector has b as an element, else false
	//int  get(vector<char> &a, char b);  //returns index of b in a if a has b, else a.size()

	void push(char a)
	{
			pile.push_back(a);
	}

public:
	//bool valid;
	//int opens;
	//int closes;
	//vector<char> pile;
	//vector<char> OpenLang;
	//vector<char> CloseLang;
	vector<int> ops;
	vector<int> clos;
	syntaxChecker()
	{
		valid = true;
		opens = 0;
		closes = 0;
		pile.clear();
		OpenLang.clear();
		CloseLang.clear();
		ops.clear();
		clos.clear();

	}
	~syntaxChecker()
	{
	}
		
	/*
		operator() returns true if syntactically correct thus far.
		Expects dangling opens to be closed in the future, so it can
		be run independent of parsing the entire document.

		Detects mismatched characters, on the basis of too many closes cannot be fixed
		by more opens, but too many opens can be fixed by more closes, and closes must
		match the previous open.
	*/



	bool operator()()
	{
		if (opens < closes)
			return false;
		int start, clo;
		bool retVal = true;
		start = 0;
		
		clo = 0;
		for(int i = 0; (i < pile.size()) && retVal; i++)
		{
			if (has(OpenLang, pile[i]))
			{
				ops.push_back(get(OpenLang, pile[i]));
				start++;
			}
			else if(has(CloseLang, pile[i]))
			{
				clo = get(CloseLang, pile[i]);
				////////////////////////////////
				////////////////////////////////
				// IMPORTANT, if language definition isn't proper,
				// this next bit of logic doesn't make sense.
				////////////////////////////////
				////////////////////////////////

				if (ops.empty() || (clo != (CloseLang.size() - 1) - ops.back())) //check matching
					return false;
				ops.pop_back();

				start--;
			}
			else
				return false; //language is broken, there is no hope, cannot be syntactically correct now.
		}
		ops.clear();
		return start >= 0;
	}
	/*
		IMPORTANT:
		define opening and closing strings in reverse order, e.g.
		"{([" "])}"
		because "Easymode" specifications specify so.

	*/
	void defineOpen(string &str)
	{
		for(int i = 0; i < str.length(); i++)
		{
			OpenLang.push_back(str[i]);
		}
	}
	void defineClose(string &str)
	{
		for(int i = 0; i < str.length(); i++)
		{
			CloseLang.push_back(str[i]);
		}
	}
	void clear()
	{
		OpenLang.clear();
		pile.clear();
		CloseLang.clear();
	}

	void pushOpen(char a)
	{
		opens++;
		push(a);
		if(!has(OpenLang, a))
			OpenLang.push_back(a);
	}
	void pushClose(char a)
	{
		closes++;
		push(a);
		if(!has(CloseLang, a))
			CloseLang.push_back(a);
	}

	//returns -1 if stack is empty, else last element
	int pop()
	{
		if (!pile.empty())
		{
			int temp =(int) pile.back();
			pile.pop_back();
			return temp;
		}
		else
			return -1;
	}

	//push to use if opening and closing langs are predefined
	void pushAlt(char a)
	{
		if (has(OpenLang, a))
			pushOpen(a);
		else if (has(CloseLang, a))
			pushClose(a);
	}

};

