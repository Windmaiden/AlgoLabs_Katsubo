// Dynamic Programming code for Optimal Binary Search  
// Tree Problem 
#include <stdio.h> 
#include <limits.h>
#include <vector>
#include <iostream>

// One node of binary tree
template <class T>
struct Node {
	T value;
	Node *left;
	Node *right;
};

// An utility function to copy binary trees
template <class T>
void copy(Node<T>* original, Node<T>* duplicate)
{
	duplicate->value = original->value;
	if (original->left) {
		Node<T>* newLeft = new Node<T>;
		duplicate->left = newLeft;
		copy(original->left, duplicate->left);

	}
	if (original->right) {
		Node<T>* newRight = new Node<T>;
		duplicate->right = newRight;
		copy(original->right, duplicate->right);
	}
}

// An utility function to get sum of array elements
// freq[i] to freq[j] 
int sum(const std::vector<int>& freq, int i, int j)
{
	int s = 0;
	for (int k = i; k <= j; k++)
		s += freq[k];
	return s;
}

// A Dynamic Programming based function that calculates
//minimum cost of a Binary Search Tree.
template <class T>
int optimalSearchTree(const std::vector<T>& keys, const std::vector<int>& freq, int n, Node<T>& tree)
{
	//Create an auxiliary 2D matrix to store results
	//of subproblems
		std::vector<std::vector<int>> cost(n);
	for (std::vector<int>& i : cost)
		i.resize(n);
	// cost[i][j] = Optimal cost of binary search tree
	//that can be  formed from keys[i] to keys[j].
	//cost[0][n - 1] will store the resultant cost 

		// 2D array of subtrees
		std::vector<std::vector<Node<T>>> trees(n);
	for (std::vector<Node<T>>& i : trees)
		i.resize(n);

	// For a single key, cost is equal to frequency of the key 
	for (int i = 0; i < n; i++)
		cost[i][i] = freq[i];

	for (int i = 0; i < n; i++)
		trees[i][i] = { keys[i], nullptr, nullptr };

	// Now we need to consider chains of length 2, 3, ... . 
	// L is chain length. 
	for (int L = 2; L <= n; L++)
	{
		// i is row number in cost[][] 
		for (int i = 0; i < n - L + 1; i++)
		{
			// Get column number j from row number i and  
			// chain length L 
			int j = i + L - 1;
			cost[i][j] = INT_MAX;

			int lastKey = -1;
			int localSum = sum(freq, i, j);
			// Try making all keys in interval keys[i..j] as root 
			for (int r = i; r <= j; r++)
			{
				int firstCost = ((r > i) ? cost[i][r - 1] : 0);
				int secondCost = ((r < j) ? cost[r + 1][j] : 0);
				// c = cost when keys[r] becomes root of this subtree 
				int c = firstCost + secondCost + localSum;
				if (c < cost[i][j])
				{
					cost[i][j] = c;
					lastKey = r;
				}
			}
			if ((lastKey > i) && (lastKey < j))
				trees[i][j] = { keys[lastKey], &trees[i][lastKey - 1], &trees[lastKey + 1][j] };
			else if (lastKey > i)
				trees[i][j] = { keys[lastKey], &trees[i][lastKey - 1], nullptr };
			else
				trees[i][j] = { keys[lastKey], nullptr, &trees[lastKey + 1][j] };
		}
	}

	copy(&trees[0][n - 1], &tree);
	return cost[0][n - 1];
}


// Driver program to represent above functions 
int main()
{
	// Juventus F.C. players's numbers and their probabilities of entering the football field during the game
	std::vector<int> players = { 1,  2,  3,  4,  5,  6,  7,  10, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 30, 33, 37 };
	std::vector<int> freq = { 80, 10, 80, 10, 80, 10, 80,  50, 10, 80, 10,  5, 80, 50, 80, 80,  5,  5, 80,  5,  5, 80, 80 };

	Node<int> tree;

	std::cout << "Cost of Optimal BST is " <<
		optimalSearchTree(players, freq, freq.size(), tree);

	system("pause");
	return 0;
	
}