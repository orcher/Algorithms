#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <list>
#include <exception>
#include <stdexcept>

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
template<class T>
void swap(T *a, T *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

/*
	QuickSort sorting algorithm
	arr - reference to vector of ints that are to be sorted
	<begin, end> - sorting range
*/
void quickSort(std::vector<int> &arr, unsigned int begin, unsigned int end)
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
    Merge function for MergeSort algorithm
*/
void merge(std::vector<int> &arr, unsigned int start, unsigned int end)
{
    unsigned int mid = (start + end) / 2;
    std::vector<int> tmp;
    for (unsigned int z = start; z <= mid; z++)
        tmp.push_back(arr[z]);

    unsigned int i = 0;
    unsigned int j = mid + 1;
    unsigned int k = start;
    while (i < tmp.size() && j <= end)
    {
        if (tmp[i] < arr[j])
        {
            arr[k] = tmp[i];
            k++;
            i++;
        }
        else
        {
            arr[k] = arr[j];
            k++;
            j++;
        }
    }

    while (i < tmp.size())
    {
        arr[k] = tmp[i];
        k++;
        i++;
    }
    while (j <= end)
    {
        arr[k] = arr[j];
        k++;
        j++;
    }
}

/*
    MergeSort sorting algorithm
    arr - reference to vector of ints that are to be sorted
    <begin, end> - sorting range
*/
void mergeSort(std::vector<int> &arr, unsigned int start, unsigned int end)
{
    if (start >= end) return;
    unsigned int mid = (start + end) / 2;
    if (mid > start)
    {
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
    }
    merge(arr, start, end);
}

/*
	BubleSort sorting algorithm
	arr - reference to vector of ints that are to be sorted
	<begin, end> - sorting range
*/
void bubleSort(int arr[], unsigned int start, unsigned int end)
{
	if (start >= end)
		return;

	bool sorted;
	for (unsigned int j = end; j > start; j--)
	{
		sorted = true;
		for (unsigned int i = start; i < j; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				sorted = false;
			}
		}
		if (sorted) return;
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
			printf("%d ", node->data);
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
    void reverseRevursive(Node *current = nullptr, Node *previous = nullptr)
    {
        if (!current) 
            current = first;

        if (current->next)
            reverseRevursive(current->next, current);
        else
            first = current;

        current->next = previous;

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
    String rotation funstion (roationon by 1 to the right)
*/
void rotate(std::string &s)
{
    for (unsigned int i = 0; i < s.size() - 1; i++)
        swap(&s[s.size() - 2 - i], &s[s.size() - 1 - i]);
}

/*
    Heaps' algorithm printing all possible permutations
*/
void permut(std::string &s, int n)
{
    if (n == 1)
        printf("%s\n", s.c_str());
    else
    {
        for (int i = 0; i < n - 1; i++)
        {
            permut(s, n - 1);
            if (n % 2 == 0)
                swap(&s[i], &s[n - 1]);
            else
                swap(&s[0], &s[n - 1]);
        }
        permut(s, n - 1);
    }
}

/*
    Returns maximum sub sum of a vector (O(n))
*/
int maxSubSum(std::vector<int> a)
{
    int max_sum_so_far = 0;
    int max_current_sum = 0;
    for (unsigned int i = 0; i < a.size(); i++)
    {
        max_current_sum = std::max(max_current_sum + a[i], 0);
        max_sum_so_far = std::max(max_current_sum, max_sum_so_far);
    }

    return max_sum_so_far;
}

/*
    Finds substring in a string (O(n))
*/
bool findNeedle(std::string n, std::string h)
{
    for (int i = 0; i < h.size(); i++)
    {
        if (h[i] != n[0]) continue;
        for (int j = 1; j < n.size(); j++)
        {
            if (h[i + j] != n[j])
            {
                i += j;
                break;
            }
            if (j == n.size() - 1)
                return true;
        }
    }
    return false;
}

/*
    Does string to int conversion (O(n))
*/
int myAtoi(char *str)
{
    int index = -1;
    while (str[++index] != '\0'){}

    int val = 0, i = 1;
    while (--index >= 0)
    {
        if (str[index] == '-')
            val = -val;
        else
        {
            val += (str[index] - '0') * i;
            i *= 10;
        }
    }

    return val;
}

/*
    Recursive version of myAtio (O(n))
*/
void recursiveAtoi(char *str, int &i, int &val)
{
    if (*str != '\0')
        recursiveAtoi(str + 1, i, val);
    else
        return;

    if (*str == '-')
        val = -val;
    else
    {
        val += (*str - '0') * i;
        i *= 10;
    }
}

void parenthesis(std::string str, int max, int n = 1)
{
    if (str.size() >= max)
    {
        std::cout << str << std::endl;
        return;
    }

    for (int i = n; i <= str.size(); i++)
    {
        str.insert(str.begin() + i, ')');
        parenthesis(str, max, n + 2);
        str.erase(str.begin() + i);
    }
}

/*
    Prints subsets (combinations) of str 
*/
void subSets(std::string str, std::string tmp, int i)
{
    for (int j = i; j < str.size(); j++)
    {
        std::cout << tmp + str[j] << std::endl;
        subSets(str, tmp + str[j], i + 1);
    }
}

/*
    Prints all n! permutations of string str
*/
void permut(std::string str, std::string tmp, int i)
{
    if (tmp.size() == str.size())
    {
        std::cout << tmp << std::endl;
        return;
    }

    for (int k = 0; k <= tmp.size(); k++)
    {
        tmp.insert(tmp.begin() + k, str[i]);
        permut(str, tmp, i + 1);
        tmp.erase(tmp.begin() + k);
    }
}

/*
    In how many ways one can jump up the stairs
    jumping 1, 2 or 3 steps at a time
*/
int jump(int n, std::string str = std::string(), int sum = 0)
{
    if (sum == n)
    {
        std::cout << str << std::endl;
        return 1;
    }
    else if (sum > n)
        return 0;

    return jump(n, str + '1', sum + 1) + jump(n, str + '2', sum + 2) + jump(n, str + '3', sum + 3);
}

/*
    Prints all possible splits o n cents
*/
void find(int n, int a = 0, int b = 0, int c = 0, int d = 0)
{
    int sum = 25 * a + 10 * b + 5 * c + 1 * d;
    if (sum == n)
    {
        std::cout << "25*" << a << " + 10*" << b << " + 5*" << c << " + 1*" << d << std::endl;
        return;
    }

    if (sum + 1 <= n) find(n, a, b, c, d + 1);
    if (sum + 5 <= n) find(n, a, b, c + 1, d);
    if (sum + 10 <= n) find(n, a, b + 1, c, d);
    if (sum + 25 <= n) find(n, a + 1, b, c, d);
}

void hanoi(int disk, int source, int dest, int aux)
{
    if (disk == 0)
    {
        std::cout << "Move disc " << disk << " from rod " << source << " to rod " << dest << std::endl;
    }
    else
    {
        hanoi(disk - 1, source, aux, dest);
        std::cout << "Move disc " << disk << " from rod " << source << " to rod " << dest << std::endl;
        hanoi(disk - 1, aux, dest, source);
    }
}

void removeDuplicates(std::string &str)
{
    bool chars[256];
    memset(chars, false, 256);

    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (chars[str[i]])
            str.erase(str.begin() + i);
        chars[str[i]] = true;
    }
}

bool areAnagrams(std::string str1, std::string str2)
{
    if (str1.size() != str2.size()) return false;

    std::bitset<256> set1;
    std::bitset<256> set2;

    for (int i = 0; i < str1.size(); i++)
    {
        set1.at(str1[i]);
        set2.at(str2[i]);
    }

    return (set1 == set2);
}

void getMaxGain(int a[], int i, int act, int opt, int gain, int &maxGain)
{
    if (i >= 6)
    {
        maxGain = std::max(maxGain, gain);
        return;
    }

    switch (opt)
    {
    case 0: gain -= a[i]; act += 1; break; // buy
    case 1: gain += a[i]; act -= 1; break; // sell
    case 2: break; // skip
    }

    getMaxGain(a, i + 1, act, 0, gain, maxGain); // buy
    if(act > 0) 
        getMaxGain(a, i + 1, act, 1, gain, maxGain); // sell
    getMaxGain(a, i + 1, act, 2, gain, maxGain); // do nothing
}

int getMaxProfit(int stockPricesYesterday[]) {

    int minPrice = stockPricesYesterday[0];
    int maxProfit = 0;

    for (int i = 0; i < 6; i++) {

        int currentPrice = stockPricesYesterday[i];

        // ensure min_price is the lowest price we've seen so far
        minPrice = std::min(minPrice, currentPrice);

        // see what our profit would be if we bought at the
        // min price and sold at the current price
        int potentialProfit = currentPrice - minPrice;

        // update maxProfit if we can do better
        maxProfit = std::max(maxProfit, potentialProfit);
    }

    return maxProfit;
}

int maks(int a, int b)
{
    if (!(a^b)) return a;
    
    int bMorea = ((a - b) & (1 << ((sizeof(a) * 8) - 2))) >> 30;
    int aMoreb = ((b - a) & (1 << ((sizeof(a) * 8) - 2))) >> 30;

    a = a >> (((sizeof(a) * 8)-1) * bMorea);
    b = b >> (((sizeof(b) * 8)-1) * aMoreb);

    return a | b;
}

void main()
{
    std::cout << maks(14, 23);

    getchar();
}