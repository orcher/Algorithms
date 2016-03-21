#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cmath>

/*
	Returns greatest devisor of a and b
*/
int gcd(int a, int b)
{
	if (b == 0) 
		return a;
	else 
		return gcd(b, a % b);
}

/*
	Prints points that could be used to draw a circle
	<a, b> - circle centre coords
	r - circle radius
	prec - defines drawing precision
*/
void drawCircle(float a, float b, float r, float prec)
{
	float y;
	for (float x = 0.00f; x <= r; x += prec)
	{
		y = sqrt(r*r - x*x);
		printf("x %f, y %f\n", x + a, y + b);
		printf("x %f, y %f\n", x + a, -y + b);
		printf("x %f, y %f\n", -x + a, y + b);
		printf("x %f, y %f\n", -x + a, -y + b);
	}
}

/*
	Swaps values of int poiters a and b
*/
template<typename T> void swap(T *a, T *b)
{
	if (*a == *b) return;

	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

/*
	QuickSort sorting algorithm
	arr - reference to some array that are to be sorted
	<begin, end> - sorting range
*/
template<typename T> void quickSort(T &arr, unsigned int begin, unsigned int end)
{
	int pivot = arr[(end + begin) / 2];
	unsigned int i = begin;
	unsigned int j = end;

	while (i <= j)
	{
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;
		if (i <= j)
		{
			swap(&arr[i], &arr[j]);
			i++;
			j--;
		}
	}

	if (begin < j)
		quickSort(arr, begin, j);
	if (i < end)
		quickSort(arr, i, end);
}

/*
	BubleSort sorting algorithm
	arr - reference to vector of ints that are to be sorted
	<begin, end> - sorting range
*/
void bubleSort(std::vector<int> &arr, unsigned int start, unsigned int end)
{
	if (start >= end)
		return;

	for (unsigned int j = end; j > start; j--)
	{
		for (unsigned int i = start; i < j; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
			}
		}
	}
}

/*
	Implementation of double linked list
*/
class List
{
	struct Node
	{
		int data;
		Node *next;
		Node(int value)
		{
			data = value;
			next = nullptr;
		}
	};
	
	Node *first;

public:
	List()
	{
		first = nullptr;
	};
	void add(int value)
	{
		if (!first)
		{
			first = new Node(value);
		}
		else
		{
			Node *newNode = new Node(value);
			Node *last = first;
			while (last->next)
				last = last->next;
			last->next = newNode;
		}
	}
	void print()
	{
		Node *node = first;
		while (node)
		{
			printf("%d\n", node->data);
			node = node->next;
		}
		printf("\n");
	}
	void revese()
	{
		Node *curr = first;
		Node *next = nullptr;
		Node *prev = nullptr;
		while (curr)
		{
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		first = prev;
	}
};

/*
	Implementation of multi-language dictionary tree
*/
class Dictionary
{
	typedef std::map<char, std::pair<Dictionary *, std::bitset<2> > > nodeType;

public:
	static enum class Lng
	{
		NONE = -1,
		MIN = 0,
		PL = MIN,
		ENG,
		MAX = ENG
	};

	int add(const std::string &word, Lng language)
	{
		if (language < Lng::MIN || language > Lng::MAX)
			return -1;

		Dictionary *node = this;
		nodeType::const_iterator it;
		for (unsigned int c = 0; c < word.size(); c++)
		{
			if (node->_nodes.size())
			{
				it = node->_nodes.find(word[c]);
				if (it != node->_nodes.end())
				{
					node = it->second.first;
					continue;
				}
			}
			node->_nodes.insert(std::make_pair(word[c], std::make_pair<Dictionary *, std::bitset<2> >(new Dictionary, std::bitset<2>())));
			if (c == word.size() - 1)
				node->_nodes[word[c]].second.set((int)language);
			node = node->_nodes[word[c]].first;
		}
		
		return 0;
	}

	Lng contains(const std::string &word)
	{
		Dictionary *node = this;
		nodeType::const_iterator it;
		unsigned int c;
		for (c = 0; c < word.size(); c++)
		{
			if (node->_nodes.size())
			{
				it = node->_nodes.find(word[c]);
				if (it != node->_nodes.end())
				{
					if (c < word.size() - 1)
						node = it->second.first;
					continue;
				}
			}
			return Lng::NONE;
		}
		
		for (int lng = (int)Lng::PL; lng <= (int)Lng::ENG; lng++)
		{
			if (node->_nodes[word[c - 1]].second[lng])
				return (Lng)lng;
		}

		return Lng::NONE;
	}

private:
	nodeType _nodes;
};

/*
	Function that does some basic work on Dictionary class
*/
void testDictionaryClass()
{
	Dictionary dic;

	printf("Adding word Adam as polish word...\n");
	dic.add("Adam", Dictionary::Lng::PL);
	printf("Adding word Aga as polish word...\n");
	dic.add("Aga", Dictionary::Lng::PL);
	printf("Adding word Sam as english word...\n");
	dic.add("Sam", Dictionary::Lng::ENG);

	std::string word = "Sam";
	printf("\nChecking for word %s in dictionary...\n", word.c_str());
	Dictionary::Lng lng = dic.contains(word);
	if (lng != Dictionary::Lng::NONE)
	{
		printf("Dictrionary contains %s\n", word.c_str());
		if (lng != Dictionary::Lng::NONE)
			printf("It's %s word\n", (lng == Dictionary::Lng::PL) ? "a polish" : "an english");
	}
	else
	{
		printf("Dictrionary doesn't contain %s\n", word.c_str());
	}
}

/*
	Checks if all chars in string str are unique
*/
bool allUniqueChars(std::string str)
{
	quickSort(str, 0, str.size() - 1);

	int i = 0;
	while (i < str.size() - 1 && str[i] != str[i + 1]){ i++; }

	return (i == str.size() - 1);
}


void main()
{

	getchar();
}