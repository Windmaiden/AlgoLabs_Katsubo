#include <stdint.h>
#include <string>
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

#include <list>
#include <queue>
#include <functional>
#include <limits.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
struct Node
{
	uint16_t key;
	T value;

	bool mark;
	uint16_t degree;

	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	Node<T>* child;
};

template <class T>
using FibHeap = std::pair<uint16_t*, Node<T>*>;

template <class T>
FibHeap<T> MakeFibHeap(uint16_t key, const T& value)
{
	Node<T>* node = new Node<T>();

	node->key = key;
	node->value = value;

	node->mark = false;
	node->degree = 0;

	node->parent = nullptr;
	node->left = node;
	node->right = node;
	node->child = nullptr;

	return std::make_pair(new uint16_t(1), node);
}

template <class T>
void AddNodeToList(Node<T>* root, Node<T>* node)
{
	if (root == nullptr)
	{
		root = node;
		node->left = node;
		node->right = node;
	}
	else if (root->left == root)
	{
		root->left = node;
		root->right = node;

		node->left = root;
		node->right = root;
	}
	else
	{
		Node<T>* lnode = root->left;
		root->left = node;

		node->right = root;
		node->left = lnode;

		lnode->right = node;
	}

	if (node->key < root->key)
		root = node;
}

template <class T>
void AddNodeToRootList(FibHeap<T>& heap, Node<T>* node)
{
	if (heap.second == nullptr)
	{
		heap.second = node;
		node->left = node;
		node->right = node;
		heap = std::make_pair(heap.first, node);;
	}
	else if (heap.second->left == heap.second)
	{
		heap.second->left = node;
		heap.second->right = node;

		node->left = heap.second;
		node->right = heap.second;
	}
	else
	{
		Node<T>* lnode = heap.second->left;
		heap.second->left = node;

		node->right = heap.second;
		node->left = lnode;

		lnode->right = node;
	}

	if (node->key < heap.second->key)
		heap.second = node;
}

template <class T>
Node<T>* Insert(FibHeap<T>& heap, uint16_t key, const T& value)
{
	Node<T>* node = new Node<T>();

	node->key = key;
	node->value = value;

	node->mark = false;
	node->degree = 0;

	node->parent = nullptr;
	node->left = node;
	node->right = node;
	node->child = nullptr;

	AddNodeToRootList(heap, node);
	(*heap.first)++;

	return node;
}

template <class T>
FibHeap<T> GetMin(const FibHeap<T> heap)
{
	return heap;
}

template <class T>
FibHeap<T> Unite(FibHeap<T> heap1, FibHeap<T> heap2)
{
	if (!heap1.second) return heap2;
	if (!heap2.second) return heap1;

	Node<T>* lnode = heap1.second->left;
	heap1.second->left = heap2.second;

	Node<T>* rnode = heap2.second->right;
	heap2.second->right = heap1.second;

	lnode->right = rnode;
	rnode->left = lnode;

	return std::make_pair(new uint16_t(*heap1.first + *heap2.first),
		heap1.second->key < heap2.second->key ? heap1.second : heap2.second);
}

template <class T>
void RemoveNodeFromRootList(FibHeap<T>& heap, Node<T>* node)
{
	Node<T>* lnode = node->left;
	Node<T>* rnode = node->right;

	lnode->right = rnode;
	rnode->left = lnode;

	if (node == heap.second)
		heap.second = rnode;
}

template <class T>
void Adopt(FibHeap<T>& heap, Node<T>* child, Node<T>* parent)
{
	RemoveNodeFromRootList(heap, child);
	AddNodeToList(parent->child, child);

	parent->child = child;
	child->parent = parent;
	parent->degree++;
	parent->mark = false;
}

template <class T>
std::vector<Node<T>*> GetRoots(Node<T>* node)
{
	std::vector<Node<T>*> roots(1, node);
	Node<T>* cur = node;
	while (true)
	{
		cur = cur->right;
		if (cur == roots[0])
			break;
		roots.push_back(cur);
	}
	return roots;
}

template <class T>
void Consolidate(FibHeap<T>& heap)
{
	std::vector<Node<T>*> A(std::floor(std::log2(*heap.first)) + 1, nullptr);

	std::vector<Node<T>*> roots = GetRoots(heap.second);

	for (auto w : roots)
	{
		if (w->parent)
			continue;
		Node<T>* x = w;
		uint16_t d = x->degree;

		while (A[d])
		{
			Node<T>* y = A[d];
			if (x->key > y->key)
				std::swap(x, y);
			Adopt(heap, y, x);
			A[d] = nullptr;
			d++;
		}
		A[d] = x;
	}
	heap.second = nullptr;

	FibHeap<T> newHeap = std::make_pair(new uint16_t(0), nullptr);
	for (auto i : A)
	{
		if (i)
		{
			AddNodeToRootList(newHeap, i);
		}
	}
	heap = std::make_pair(heap.first, newHeap.second);;
}

template <class T>
Node<T>* ExtractMin(FibHeap<T>& heap)
{
	Node<T>* z = heap.second;
	if (z)
	{
		std::vector<Node<T>*> childs(z->degree, nullptr);
		Node<T>* cur = z->child;
		for (int i = 0; i < z->degree; i++)
		{
			childs[i] = cur;
			cur = cur->right;
		}

		for (auto x : childs)
		{
			AddNodeToList(z, x);
			x->parent = nullptr;
		}

		RemoveNodeFromRootList(heap, z);
		if (z == z->right)
		{
			heap.second = nullptr;
			(*heap.first)--;
		}
		else
		{
			heap.second = z->right;
			(*heap.first)--;
			Consolidate(heap);
		}
	}

	return z;
}

template <class T>
void Cut(FibHeap<T>& heap, Node<T>* x, Node<T>* y)
{
	if (y->child == x)
		y->child = x->right;

	y->degree--;

	Node<T>* lnode = x->left;
	Node<T>* rnode = x->right;

	lnode->right = rnode;
	rnode->left = lnode;

	AddNodeToList(heap.second, x);
	x->parent = nullptr;
	x->mark = false;
}

template <class T>
void CascadingCut(FibHeap<T>& heap, Node<T>* y)
{
	Node<T>* z = y->parent;
	if (z)
	{
		if (!y->mark)
			y->mark = true;
		else
		{
			Cut(heap, y, z);
			CascadingCut(heap, z);
		}
	}
}

template <class T>
void DecreaseKey(FibHeap<T>& heap, Node<T>* node, uint16_t newKey)
{
	if (newKey > node->key)
		throw std::logic_error("New key is larger than current key");

	node->key = newKey;
	Node<T>* y = node->parent;
	if (y && node->key < y->key)
	{
		Cut(heap, node, y);
		CascadingCut(heap, y);
	}
	if (node->key < heap.second->key)
		heap.second = node;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;
# define INF 0x3f3f3f3f 

// iPair ==> Integer Pair 
typedef pair<int, int> iPair;

struct Edge
{
	Edge(int v, int w) : dest(v), weight(w) {};
	int dest, weight;
};

// This class represents a directed graph using 
// adjacency list representation 
class Graph
{
	int V; // No. of vertices 
	int E; // No. of edges 

		   // In a weighted graph, we need to store vertex 
		   // and weight pair for every edge 
	//list< pair<int, int> > *adj;
	std::vector<std::list<Edge>> adj;

public:
	Graph(int V); // Constructor 

				  // function to add an edge to graph 
	void addEdge(int u, int v, int w);

	// prints shortest path from s 
	void Dijkstra(int s);
	std::vector<int> BellmanFord(int src);
	void Johnson();
};

// Allocates memory for adjacency list 
Graph::Graph(int V)
{
	this->V = V;
	this->E = 0;
	adj = std::vector<std::list<Edge>>(V, std::list<Edge>());
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(Edge(v, w));
	E++;
}

// An utility function used to print the solution 
void printArr(std::vector<int>& dist, int n)
{
	printf("Vertex   Distance from Source\n");
	for (int i = 0; i < n; ++i)
		if (dist[i] != INF)
			printf("%d \t\t %d\n", i, dist[i]);
}

// Prints shortest paths from src to all other vertices 
void Graph::Dijkstra(int src)
{
	// Create a vector for distances and initialize all 
	// distances as infinite (INF) 
	vector<int> dist(V, INF);

	// Insert source itself in priority queue and initialize 
	// its distance as 0.
	FibHeap<int> heap = MakeFibHeap(0, src);
	dist[src] = 0;

	/* Looping till priority queue becomes empty (or all
	distances are not finalized) */
	while (*heap.first != 0)
	{
		// The first vertex in pair is the minimum distance 
		// vertex, extract it from priority queue. 
		// vertex label is stored in second of pair (it 
		// has to be done this way to keep the vertices 
		// sorted distance (distance must be first item 
		// in pair) 
		int u = heap.second->value;
		ExtractMin(heap);

		// 'i' is used to get all adjacent vertices of a vertex 
		list< Edge >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get vertex label and weight of current adjacent 
			// of u. 
			int v = (*i).dest;
			int weight = (*i).weight;

			// If there is shorted path to v through u. 
			if (dist[v] > dist[u] + weight)
			{
				// Updating distance of v 
				dist[v] = dist[u] + weight;
				Insert<int>(heap, dist[v], v);
			}
		}
	}

	printArr(dist, V);
}

// The main function that finds shortest distances from src to 
// all other vertices using Bellman-Ford algorithm.  The function 
// also detects negative weight cycle 
std::vector<int> Graph::BellmanFord(int src)
{
	std::vector<int> dist(V, 0);

	// Step 1: Initialize distances from src to all other vertices 
	// as INFINITE 
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	// Step 2: Relax all edges |V| - 1 times. A simple shortest  
	// path from src to any other vertex can have at-most |V| - 1  
	// edges 
	for (int i = 1; i <= V - 1; i++)
	{
		for (int k = 0; k < V; k++)
		{
			list< Edge >::iterator it;
			for (it = adj[k].begin(); it != adj[k].end(); ++it)
			{
				int u = k;
				int v = it->dest;
				int weight = it->weight;
				if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
					dist[v] = dist[u] + weight;
			}
		}
	}

	// Step 3: check for negative-weight cycles.  The above step  
	// guarantees shortest distances if graph doesn't contain  
	// negative weight cycle.  If we get a shorter path, then there 
	// is a cycle.

	for (int i = 0; i < V; i++)
	{
		list< Edge >::iterator it;
		for (it = adj[i].begin(); it != adj[i].end(); ++it)
		{
			int u = i;
			int v = it->dest;
			int weight = it->weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				throw std::logic_error("Graph contains negative weight cycle");
		}
	}

	//printArr(dist, V);

	return dist;
}

void Graph::Johnson()
{
	V++;
	adj.push_back(std::list<Edge>(std::list<Edge>()));
	for (int i = 0; i < V - 1; i++)
		addEdge(V - 1, i, 0);

	std::vector<int> h = BellmanFord(V - 1);

	V--;
	adj.erase(adj.begin() + V);
	E -= V;

	Graph g(V);
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			std::list<Edge>::iterator it = std::find_if(adj[i].begin(), adj[i].end(), [&](const Edge e) { return e.dest == j; });
			if (it != adj[i].end())
				if (it->weight != INF)
					g.addEdge(i, j, it->weight + h[i] - h[j]);
		}
	}

	for (int src = 0; src < V; src++)
	{
		std::cout << "\nShortest Distance with vertex " << src << " as the source:\n";
		g.Dijkstra(src);
	}
}

// Driver program to test above functions 
int main()
{
	int V = 9;
	Graph g(V);

	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.Johnson();

	return 0;
}