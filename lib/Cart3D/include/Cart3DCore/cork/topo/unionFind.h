
#pragma once

#include "prelude.h"
#include <topofwd.h>

class UnionFind {
public:
    UnionFind(uint N) : ids(N), rank(N, 0) {
        for(uint i=0; i<N; i++)
            ids[i] = i;
    }
    
    uint find(uint i) {
        uint id = i;
        while(ids[id] != id)
            id = ids[id];
        ids[i] = id; // path compression optimization
        return id;
    }
    uint unionIds(uint i, uint j) {
        uint iid = find(i);
        uint jid = find(j);
        if(iid == jid) // no need to merge the same tree with itself
            return iid;
        // simple implementation (not used)
        // return ids[iid] = jid;
        // instead we attempt to rank balance
        if(rank[iid] > rank[jid]) {
            return ids[jid] = iid;
        } else if(rank[iid] < rank[jid]) {
            return ids[iid] = jid;
        } else { // equal ranks
            rank[jid]++;
            return ids[jid] = iid;
        }
    }
	cork_vector<uint> dump() {
		cork_vector<uint> result(ids.size());
        for(uint i=0; i<ids.size(); i++)
            result[i] = find(i);
        return result;
    }
    
private:
    cork_vector<uint> ids;
    cork_vector<uint> rank;
};
