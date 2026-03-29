//
// Created by gustavobastos on 28/03/26.
//

#include "Risk.h"

#include <set>

void set_tranfer_capacity( Graph<int_node>* g,int source_domain,const map<int,domain_flow_analisys>& domain_flow,const std::map<int_node,const reviewer*>& reviewerData  ,  map<int_node,int>&transfer_capacity) {


    map<Vertex<int_node>*,Vertex<int_node>*>pred;
    std::queue< Vertex<int_node>*> q;

    for (auto v:g->getVertexSet()) {
        v->setVisited(false);
        pred[v]=nullptr;

    }

    for (auto s : domain_flow.at(source_domain).rv) {
        q.push(s);
    }

    int minReviewsPerSubmission=g->findVertex({-1,false})->getAdj()[0]->getWeight();
    int maxReviewsPerReviewer=domain_flow.begin()->second.rv[0]->getAdj()[0]->getWeight();


    while(!q.empty()) {
        Vertex<int_node>*v=q.front();
        v->setVisited(true);
        q.pop();
        if (v->getInfo().is_sub) {
            int transfer_cap=minReviewsPerSubmission;
            int pred_domain=reviewerData.at(pred[v]->getInfo())->primary;
            for(auto e:v->getAdj()) {
                Vertex<int_node>*w=e->getDest();

                int domain= reviewerData.at(w->getInfo())->primary;
                if (domain==pred_domain and e->getFlow()==1) {
                    transfer_cap--;
                }
                if ( !w->isVisited()) {
                    pred[w]=v;
                    q.push(w);
                    w->setVisited(true);
                }

            }
            transfer_capacity[v->getInfo()]=transfer_cap;
        }
        else
        {
            for(auto e:v->getIncoming()) {
                Vertex<int_node>*w=e->getOrig();
                if (!w->isVisited()) {
                    pred[w]=v;
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
    }
}

void set_drainage_flow(Graph<int_node>* g,int source_domain,map<int,domain_flow_analisys>& domain_flow,const std::map<int_node,const reviewer*>& reviewerData) {

    map<int_node,int>transfer_capacity;

    set_tranfer_capacity(g,source_domain,domain_flow,reviewerData,transfer_capacity);

    map<int,domain_flow_analisys> comp_domain_flow;

    for (auto p:domain_flow) {
        comp_domain_flow.insert(p);
    }


    std::queue< Vertex<int_node>*> q;

    for (auto v:g->getVertexSet()) {
        v->setVisited(false);
    }


    for (auto s : domain_flow[source_domain].rv) {
        q.push(s);
    }



    while(!q.empty()) {
        Vertex<int_node>*v=q.front();
        v->setVisited(true);
        q.pop();
        if (v->getInfo().is_sub) {

            set<int> visitedDomains;
            for(auto e:v->getAdj()) {
                Vertex<int_node>*w=e->getDest();
                int domain= reviewerData.at(w->getInfo())->primary;
                if ( !w->isVisited() and visitedDomains.find(domain)==visitedDomains.end() and e->getFlow()==1) {
                    if (domain_flow[source_domain].residual_capacity> domain_flow[domain].drainage_capacity-comp_domain_flow[domain].drainage_capacity) {
                        domain_flow[domain].drainage_capacity+=1;
                    }
                    visitedDomains.insert(domain);
                    q.push(w);
                }

            }
        }
        else
        {
            for(auto e:v->getIncoming()) {
                Vertex<int_node>*w=e->getOrig();
                if (transfer_capacity[w->getInfo()]>0 and e->getFlow()==0) {
                    q.push(w);
                    w->setVisited(true);
                    transfer_capacity[w->getInfo()]--;
                }
            }
        }
    }




}

std::vector<int> risk_analisys(Graph<int_node>* g,const std::map<int_node,const reviewer*>& reviewerData) {
    std::vector<int> ans;

    map<int,bool>domain_added;

    std::vector <const Vertex<int_node>*>  rev_nodes;

    map<int,domain_flow_analisys> domain_flow;
    for ( Vertex<int_node> *node:g->getVertexSet()) {
        if (node->getInfo().integer>=0 and node->getInfo().is_sub==false) {
            rev_nodes.push_back(node);
            int residual_capacity = node->getAdj()[0]->getWeight()-node->getAdj()[0]->getFlow();
            int domain=reviewerData.at((node->getInfo()))->primary;
            if (domain_flow.find( domain)==domain_flow.end()) {
                domain_flow[domain]={residual_capacity,{node},{}};
                domain_added[domain]=false;
            }

            else{
                domain_flow[domain].rv.push_back(node);
                if (residual_capacity>0) {
                    domain_flow[domain].residual_capacity+=residual_capacity;

                }
            }


        }
    }

    int maxReviewsPerReviewer=domain_flow.begin()->second.rv[0]->getAdj()[0]->getWeight();

    Vertex<int_node>*source=g->findVertex({-1,false});
    int minReviewsPerSubmission=source->getAdj()[0]->getWeight();

    for (const auto & p: domain_flow) {
        if (p.second.residual_capacity>0) {
            set_drainage_flow(g,p.first,domain_flow,reviewerData);
        }
    }

    for (const auto & p: domain_flow) {
        if (p.second.residual_capacity+p.second.drainage_capacity<maxReviewsPerReviewer ) {
            for (auto e:p.second.rv) {
                ans.push_back(e->getInfo().integer);
            }
            domain_added[p.first]=true;
        }
    }

    for (auto e:source->getAdj()) {
        Vertex<int_node>*w=e->getDest();
        if (w->getAdj().size()<=minReviewsPerSubmission) {
            for (auto e1:w->getAdj()) {
                Vertex<int_node>*w1=e1->getDest();
                int domain=reviewerData.at(w1->getInfo())->primary;
                if (!domain_added[domain]) {
                    for (auto rv:domain_flow[domain].rv) {
                        ans.push_back(rv->getInfo().integer);
                    }
                    domain_added[domain]=true;
                }
            }
        }
    }



    return ans;
}


void risk_analisys(const string & output_filepath,Graph<int_node> *g,const std::map<int_node,const reviewer*>& reviewerData,bool allAssigned) {

    if (!allAssigned) {
        FILE* file=fopen(output_filepath.c_str(),"a");
        fprintf(file,"#Risk Analysis: 1\n");
        fflush(file);
        fclose(file);
        return;
    }
    vector<int> risk_rv=risk_analisys(g,reviewerData);
    sort(risk_rv.begin(),risk_rv.end());
    FILE* file=fopen(output_filepath.c_str(),"a");
    fprintf(file,"#Risk Analysis: 1\n");
    if (!risk_rv.empty()) {
        fprintf(file,"%d",risk_rv[0]);
    }
    for (int i=1;i<risk_rv.size();i++) {
        fprintf(file,", %d",risk_rv[i]);
    }
    fflush(file);
    fclose(file);
}