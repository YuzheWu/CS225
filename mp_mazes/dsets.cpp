/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++){
        _elems.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if(_elems[elem] < 0){
        return elem;
    } else {
        std::vector<int> path;
        while(_elems[elem] >= 0){
            path.push_back(elem);
            elem = _elems[elem];
        }
        for(auto it = path.begin(); it != path.end(); it++){
            _elems[*it] = elem;
        }
        return elem;
    }
}

void DisjointSets::setunion(int a, int b){
    int root1 = find(a);
    int root2 = find(b);
    int newSize = _elems[root1] + _elems[root2];
    if (_elems[root1] <= _elems[root2]){
        _elems[root2] = root1;
        _elems[root1] = newSize;
    } else if(_elems[root1] > _elems[root2]){
        _elems[root1] = root2;
        _elems[root2] = newSize;
    } 
}

int DisjointSets::size(int elem){
    int root = find(elem);
    return _elems[root] * -1;
}	



