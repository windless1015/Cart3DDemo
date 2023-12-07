// +-------------------------------------------------------------------------
// | aabvh.h
// | 
// | Author: Gilbert Bernstein
// +-------------------------------------------------------------------------
// | COPYRIGHT:
// |    Copyright Gilbert Bernstein 2013
// |    See the included COPYRIGHT file for further details.
// |    
// |    This file is part of the Cork library.
// |
// |    Cork is free software: you can redistribute it and/or modify
// |    it under the terms of the GNU Lesser General Public License as
// |    published by the Free Software Foundation, either version 3 of
// |    the License, or (at your option) any later version.
// |
// |    Cork is distributed in the hope that it will be useful,
// |    but WITHOUT ANY WARRANTY; without even the implied warranty of
// |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// |    GNU Lesser General Public License for more details.
// |
// |    You should have received a copy 
// |    of the GNU Lesser General Public License
// |    along with Cork.  If not, see <http://www.gnu.org/licenses/>.
// +-------------------------------------------------------------------------
#pragma once

#include "bbox.h"
#include <parallel_hashmap/phmap.h>
#include <stack>

// maximum leaf size
static const uint LEAF_SIZE = 8;

template<class GeomIdx>
struct GeomBlob
{
	bool iscall = false;
    BBox3d  bbox;
    Vec3d   point; // representative point, usually the box midpoint
    GeomIdx id;
};

template<class GeomIdx>
struct AABVHNode
{
	
    BBox3d                          bbox;
    std::shared_ptr<AABVHNode<GeomIdx>>left;
    std::shared_ptr<AABVHNode<GeomIdx>>right;
	cork_vector<uint>       blobids;
    inline bool isLeaf() const { return left == nullptr; }
};

template<class GeomIdx>
class AABVH
{
public:
    AABVH(std::vector< ::GeomBlob<GeomIdx> > &geoms,bool needOldData = true) :
        root(nullptr), tmpids(geoms.size())
    {
//        ENSURE(blobs.size() > 0)
		if (needOldData)
			blobs = geoms;
		else
			std::swap(blobs, geoms);
		
        for(uint k=0; k<tmpids.size(); k++)
            tmpids[k] = k;
        
        root = constructTree(0, (uint)tmpids.size(), 2);
    }
    ~AABVH() {}
    
    // query?
    inline void for_each_in_box(
        const BBox3d                        &bbox,
        std::function<void(GeomIdx idx)>    action
    ) {
        // do a recursive search and invoke the action at each
        // piece of geometry
        std::stack< std::shared_ptr<AABVHNode<GeomIdx>> >  nodes;
        nodes.push(root);
        
		//for (auto& id : blobs)
		//{
		//	id.iscall = false;
		//}
        while(!nodes.empty()) {
            std::shared_ptr<AABVHNode<GeomIdx>>node    = nodes.top();
                                          nodes.pop();
            
            // check bounding box isct,判断条件已经足够
			//if ((!hasIsct(node->bbox, bbox))/* && (!inside(node->bbox, bbox))*/)  continue;
            
            // otherwise...
            if(node->isLeaf()) {
                for(uint bid : node->blobids) {
					//if (blobs[bid].iscall) {
					//	continue;
					//}
					//blobs[bid].iscall = true;
					if ((hasIsct(blobs[bid].bbox, bbox)) /*|| (inside(blobs[bid].bbox, bbox))*/)
                        action(blobs[bid].id);
                }
            } else {
				if (hasIsct(node->left->bbox, bbox))
					nodes.push(node->left);
				if (hasIsct(node->right->bbox, bbox))
					nodes.push(node->right);
            }
        }
    }


	inline void for_each_in_box_Tolerance(
		double                          Tolerance,
		const BBox3d                        &bbox,
		std::function<void(GeomIdx idx)>    action
		) {
		// do a recursive search and invoke the action at each
		// piece of geometry
		std::stack< std::shared_ptr<AABVHNode<GeomIdx>> >  nodes;
		nodes.push(root);

		while (!nodes.empty()) {
            std::shared_ptr<AABVHNode<GeomIdx>>node = nodes.top();
			nodes.pop();

			// check bounding box isct
			if ((!hasIsctTolerance(Tolerance,node->bbox, bbox))
				&& (!insideTolerance(Tolerance,node->bbox, bbox)))  continue;

			// otherwise...
			if (node->isLeaf()) {
				for (uint bid : node->blobids) {
					if ((hasIsctTolerance(Tolerance,bbox, blobs[bid].bbox))
						|| (insideTolerance(Tolerance,blobs[bid].bbox, bbox)))
						action(blobs[bid].id);
				}
			}
			else {
				nodes.push(node->left);
				nodes.push(node->right);
			}
		}
	}


	inline void for_each_in_box_stop(
		const BBox3d                        &bbox,
		std::function<bool(GeomIdx idx)>    action
		) {
		// do a recursive search and invoke the action at each
		// piece of geometry
		std::stack< std::shared_ptr<AABVHNode<GeomIdx>> >  nodes;
		nodes.push(root);

		while (!nodes.empty()) {
            std::shared_ptr<AABVHNode<GeomIdx>>node = nodes.top();
			nodes.pop();

			// check bounding box isct
			if ((!hasIsct(node->bbox, bbox)) && (!inside(node->bbox, bbox)))  continue;

			// otherwise...
			if (node->isLeaf()) {
				for (uint bid : node->blobids) {
					if ((hasIsct(blobs[bid].bbox, bbox)) || (inside(blobs[bid].bbox, bbox)))
						if (action(blobs[bid].id))
							return;
				}
			}
			else {
				nodes.push(node->left);
				nodes.push(node->right);
			}
		}
	}
    


    void overlap(const AABVH& bvh, std::function<void(GeomIdx ida, GeomIdx idb)>action)const
    {
        struct QueryNode
        {
            std::shared_ptr<AABVHNode<GeomIdx>> anode;
            std::shared_ptr<AABVHNode<GeomIdx>> bnode;

            static QueryNode make_node(std::shared_ptr<AABVHNode<GeomIdx>> an, std::shared_ptr<AABVHNode<GeomIdx>> bn)
            {
                QueryNode qnode;
                qnode.anode = an;
                qnode.bnode = bn;
                return qnode;
            }

        };
        std::queue<QueryNode> tQ;
        if (root->bbox.overlap(bvh.root->bbox))
            tQ.push(QueryNode::make_node(root, bvh.root));
        while (!tQ.empty())
        {
            auto tp = tQ.front();
            tQ.pop();

            if (tp.anode->isLeaf()) {

                if (tp.bnode->isLeaf()) {
                    for (auto& ia : tp.anode->blobids) {
                        for (auto& ib : tp.bnode->blobids) {
                            if (blobs[ia].bbox.overlap(bvh.blobs[ib].bbox))
                                action(blobs[ia].id, bvh.blobs[ib].id);
                        }
                    }
                }
                else {
                    if (tp.anode->bbox.overlap(tp.bnode->left->bbox))
                        tQ.push(QueryNode::make_node(tp.anode, tp.bnode->left));
                    if (tp.anode->bbox.overlap(tp.bnode->right->bbox))
                        tQ.push(QueryNode::make_node(tp.anode, tp.bnode->right));
                }
            }
            else {
                if (tp.bnode->isLeaf()) {
                    if (tp.anode->left->bbox.overlap(tp.bnode->bbox))
                        tQ.push(QueryNode::make_node(tp.anode->left, tp.bnode));
                    if (tp.anode->right->bbox.overlap(tp.bnode->bbox))
                        tQ.push(QueryNode::make_node(tp.anode->right, tp.bnode));
                }
                else
                {
                    if (tp.anode->left->bbox.overlap(tp.bnode->left->bbox))
                        tQ.push(QueryNode::make_node(tp.anode->left, tp.bnode->left));
                    if (tp.anode->left->bbox.overlap(tp.bnode->right->bbox))
                        tQ.push(QueryNode::make_node(tp.anode->left, tp.bnode->right));

                    if (tp.anode->right->bbox.overlap(tp.bnode->left->bbox))
                        tQ.push(QueryNode::make_node(tp.anode->right, tp.bnode->left));
                    if (tp.anode->right->bbox.overlap(tp.bnode->right->bbox))
                        tQ.push(QueryNode::make_node(tp.anode->right, tp.bnode->right));
                }
            }
        }
    }
private:
    // process range of tmpids including begin, excluding end
    // last_dim provides a hint by saying which dimension a
    // split was last made along
    std::shared_ptr<AABVHNode<GeomIdx>> constructTree(uint begin, uint end, uint last_dim)
    {
 //       ENSURE(end - begin > 0); // don't tell me to build a tree from nothing
        // base case
        if(end-begin <= LEAF_SIZE) {
            std::shared_ptr<AABVHNode<GeomIdx>>node =std::make_shared<AABVHNode<GeomIdx>>();
            node->left = nullptr;
            node->blobids.resize(end-begin);
            for(uint k=0; k<end-begin; k++) {
                uint blobid = node->blobids[k] = tmpids[begin + k];
                node->bbox = convex(node->bbox, blobs[blobid].bbox);
            }
            return node;
        }
        // otherwise, let's try to split this geometry up
        
        uint dim = (last_dim+1)%3;
        uint mid = (begin + end) / 2;
        quickSelect(mid, begin, end, dim);
        
        // now recurse
        std::shared_ptr<AABVHNode<GeomIdx>>node = std::make_shared<AABVHNode<GeomIdx>>();
        node->left = constructTree(begin, mid, dim);
        node->right = constructTree(mid, end, dim);
        node->bbox = convex(node->left->bbox, node->right->bbox);
        return node;
    }
    
    // precondition: begin <= select < end
    void quickSelect(uint select, uint begin, uint end, uint dim)
    {
        // NOTE: values equal to the pivot
        //       may appear on either side of the split
        if(end-1 == select)     return;
        
        // p(ivot)i(ndex) and p(ivot)v(alue)
        uint pi = randMod(end-begin) + begin;
        double pv = blobs[tmpids[pi]].point[dim];
        
        int front = begin;
        int back  = end-1;
        while(front < back) {
            if(blobs[tmpids[front]].point[dim] < pv) {
                front++;
            }
            else if(blobs[tmpids[back]].point[dim] > pv) {
                back--;
            }
            else {
                std::swap(tmpids[front], tmpids[back]);
                front++;
                back--;
            }
        }
        if(front == back && blobs[tmpids[front]].point[dim] <= pv) {
            front++;
        }
        
        if(select < uint(front)) {
            quickSelect(select, begin, front, dim);
        } else {
            quickSelect(select, front, end, dim);
        }
    }
private:
    std::shared_ptr<AABVHNode<GeomIdx>>root;
    std::vector< ::GeomBlob<GeomIdx> >    blobs;
    std::vector<uint>                   tmpids; // used during construction
};























