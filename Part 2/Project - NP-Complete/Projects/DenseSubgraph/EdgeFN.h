//
// Created by harrylex on 12/26/22.
//

#ifndef DENSESUBGRAPH_EDGEFN_H
#define DENSESUBGRAPH_EDGEFN_H


class EdgeFN {
public:
    int from, to, index;
    double cap, flow;

    EdgeFN(int from, int to, double cap, double flow, double index);
};


#endif //DENSESUBGRAPH_EDGEFN_H
