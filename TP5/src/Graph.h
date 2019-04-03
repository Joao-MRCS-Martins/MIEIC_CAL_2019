/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <values.h>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	Edge<T> addEdge(Vertex<T> *orig,Vertex<T> *dest, double w);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
Edge<T> Vertex<T>::addEdge(Vertex<T> *o,Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(o,d, w));
	return Edge<T>(o,d,w);
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class   Edge {
    Vertex<T>* orig;
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *o, Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o,Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	vector<Edge<T>> edgeSet;

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	edgeSet.push_back(v1->addEdge(v1,v2,w));
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for(Vertex<T>* vertex : this->vertexSet) {
    	vertex->visited = false;
        vertex->dist = INF;
        vertex->path = NULL;
    }
    Vertex<T>* orig = findVertex(origin);
    orig->dist = 0;
    MutablePriorityQueue<Vertex<T>> queue ;
    queue.insert(orig);

    while(!queue.empty()) {
        Vertex<T>* next = queue.extractMin();

        for(Edge<T> edge : next->adj) {
            if(edge.dest->dist > (next->dist + edge.weight)) {
                edge.dest->dist = next->dist + edge.weight;
                edge.dest->path = next;
                if( queue.find(edge.dest))
					queue.decreaseKey(edge.dest);
				else
					queue.insert(edge.dest);
            }
        }
    }


}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	res.push_back(dest);
	Vertex<T>* next = findVertex(dest);
	while((next = next->getPath()) != NULL) {
	    if(next->getInfo() == origin) {
	        res.push_back(origin);
	        break;
	    }
	    res.push_back(next->getInfo());
	}
	reverse(res.begin(),res.end());
	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	for(Vertex<T>* vertex: this->vertexSet) {
	    vertex->dist = INF;
	    vertex->path = NULL;
	}
    Vertex<T>* vert = findVertex(orig);
	vert->dist = 0;
	queue<Vertex<T>*> queue;
	queue.push(vert);
	while(!queue.empty()) {
	    Vertex<T>* next = queue.front();
	    queue.pop();
	    for(Edge<T> edge : next->adj) {
	        if(edge.dest->dist == INF) {
	            queue.push(edge.dest);
	            edge.dest->dist = next->dist +1;
	            edge.dest->path = next;
	        }
	    }
	}
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for(Vertex<T>* vertex: this->vertexSet) {
        vertex->dist = INF;
        vertex->path = NULL;
    }
    Vertex<T>* vert = findVertex(orig);
    vert->dist = 0;
    for(int i = 1; i < this->vertexSet.size(); i++) {
        for(Edge<T> edge : this->edgeSet) {
            if(edge.dest->dist > edge.orig->dist + edge.weight) {
                edge.dest->dist = edge.orig->dist + edge.weight;
                edge.dest->path = edge.orig;
            }
        }
    }
    for(Edge<T> edge : this->edgeSet) {
        if(edge.orig->dist + edge.weight < edge.dest->dist) {
            cerr << "there cycles of negative weight";
            return;
        }
    }
}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
