#include "max_flow.h"

// Function to test the given vertex 'w' and visit it if conditions are met
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    // Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    std::queue<Vertex<T> *> q;
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

// Function to find the minimum residual capacity along the augmenting path
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

// Function to augment flow along the augmenting path with the given flow value
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

// Main function implementing the Edmonds-Karp algorithm
template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    // Find source and target vertices in the graph


    //por flows a 0
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);
    while(findAugmentingPath(g,s,t)){
        double value=findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,value);
    }
}