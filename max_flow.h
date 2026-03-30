/**
 * @file max_flow.h
 * @brief Implementation of the Edmonds-Karp algorithm for maximum flow.
 *
 * This module provides functions to compute the maximum flow in a directed graph
 * using the Edmonds-Karp algorithm.
 *
 * The graph is assumed to represent a flow network where:
 * - Edge weights represent capacities
 * - Edge flows are updated during execution
 */
#ifndef MAX_FLOW_H
#define MAX_FLOW_H

#include "graph.h"

/**
 * @brief Auxiliary function to explore vertices during BFS.
 *
 * Visits a vertex if it has not been visited and there is residual capacity.
 * Updates the path and puts the vertex in the queue.
 *
 * @param q BFS queue
 * @param e Edge being explored
 * @param w Destination vertex
 * @param residual Residual capacity of the edge
 *
 * complexity O(1)
 */
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);

/**
 * @brief Finds an augmenting path using BFS.
 *
 * This function searches for a path from source to sink in the residual graph.
 * It considers both forward edges (with remaining capacity) and backward edges
 * (with existing flow).
 *
 * @param g Pointer to the graph
 * @param s Source vertex
 * @param t Target vertex
 * @return true if an augmenting path is found, false otherwise
 *
 * complexity O(V+E)
 */
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t);

/**
 * @brief Computes the minimum residual capacity along an augmenting path.
 *
 * Traverses the path from sink to source and determines the bottleneck
 * capacity that limits the flow.
 *
 * @param s Source vertex
 * @param t Target vertex
 * @return Minimum residual capacity along the path
 *
 * complexity O(V)
 */
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);

/**
 * @brief Augments flow along an augmenting path.
 *
 * Updates the flow values along the path by adding the given flow value.
 * Handles both forward and backward edges in the residual graph.
 *
 * @param s Source vertex
 * @param t Target vertex
 * @param f Flow value to add
 *
 * complexity O(V)
 */
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);

/**
 * @brief Computes the maximum flow using the Edmonds-Karp algorithm.
 *
 * Repeatedly finds augmenting paths using BFS and augments flow along
 * those paths until no more augmenting paths exist.
 *
 * Algorithm steps:
 * 1. Initialize all flows to zero
 * 2. While an augmenting path exists:
 *    - Find the minimum residual capacity (bottleneck)
 *    - Augment flow along the path
 *
 * @param g Pointer to the graph
 * @param source Source node identifier
 * @param target Target node identifier
 *
 * complexity O(V*E^2)
 */
template <class T>
void edmondsKarp(Graph<T> *g, int source, int target);

/**
 * @brief Implementation of the BFS test.
 */
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
        //w->setDist(w->getDist()+1);
        // q.decreaseKey(w);
    }
}

/**
 * @brief Implementation of augmenting path search.
 */
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    // Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    std::queue< Vertex<T>*> q;
    q.push(s);
    while(!q.empty()){
        Vertex<T> *v=q.front();
        q.pop();

        for(Edge<T> *e : v->getAdj()){
            if(e->getFlow()<e->getWeight() && !e->getDest()->isVisited()) {
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                q.push(e->getDest());
            }
        }
        for(Edge<T> *e:v->getIncoming()){
            testAndVisit(q,e,e->getOrig(),e->getFlow());
        }
    }
    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

/**
 * @brief Implementation of minimum residual capacity along the augmenting path search.
 */
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;

    bool flag=true;
    Vertex<T> *v=t;
    while(flag){
        Edge<T> *e=v->getPath();
        if(e->getOrig()==v){
            f=std::min(f,e->getFlow());
            v=e->getDest();
        }
        else{
            double residual=e->getWeight()-e->getFlow();
            if(residual<f)f=residual;
            v=e->getOrig();
        }
        if(v==s)break;
    }

    // Return the minimum residual capacity
    return f;
}


/**
 * @brief Implementation of flow augmentation along the augmenting path.
 */
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    // Traverse the augmenting path and update the flow values accordingly
    bool flag=true;
    Vertex<T> *v=t;
    while(flag){
        Edge<T> *e=v->getPath();
        if(e->getOrig()==v){
            e->setFlow(e->getFlow()-f);
            v=e->getDest();
        }
        else{
            e->setFlow(e->getFlow()+f);
            v=e->getOrig();
        }
        if(v==s)break;
    }
}

/**
 * @brief Implementation of Edmonds-Karp algorithm.
 */
template <class T>
void edmondsKarp(Graph<T> *g, T source, T target) {
    // Find source and target vertices in the graph


    for(auto v : g->getVertexSet()) {
        v->setDist(0);
    }

    for(auto v : g->getVertexSet()) {
        for(auto e: v->getAdj()){
            e->setFlow(0);
        }
    }
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);
    while(findAugmentingPath(g,s,t)){
        double value=findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,value);
    }
}
#endif
