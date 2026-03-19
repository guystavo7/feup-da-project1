#include "graph.h"

template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);

template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t);

template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);

template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);

template <class T>
void edmondsKarp(Graph<T> *g, int source, int target);