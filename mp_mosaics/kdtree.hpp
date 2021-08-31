/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
        return true;
    } else if (first[curDim] == second[curDim]) {
        return first < second;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int currentDistSquared = 0;
     for (int i=0; i<Dim; i++)
        currentDistSquared += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
     int potentialDistSquared = 0;
     for (int i=0; i<Dim; i++)
        potentialDistSquared += (target[i] - potential[i]) * (target[i] - potential[i]);
     if (potentialDistSquared < currentDistSquared) {
         return true;
     } else if (potentialDistSquared == currentDistSquared) {
         return potential < currentBest;
     }
     return false;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int left, int right, int pivotIndex, int curDim) {
    Point<Dim> pivotPoint = points[pivotIndex];
    swap(points[pivotIndex], points[right]);
    int storeIndex = left;
    for (int i = left; i<right; i++) {
        if (smallerDimVal(points[i], pivotPoint, curDim)) {
            swap(points[storeIndex], points[i]);
            storeIndex++;
        }
    }
    swap(points[right], points[storeIndex]);
    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& points, int left, int right, int k, int curDim) {
    while (left != right) {
        int pivotIndex = partition(points, left, right, k, curDim);
        if (k == pivotIndex) {
            return points[k];
        } else if (k < pivotIndex) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
    return points[left];
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildSubTree(vector<Point<Dim>>& points, int left, int right, int curDim) {
    if (left > right)
        return NULL;
    int medianIdx = (left + right) / 2;
    Point<Dim> curPoint = quickSelect(points, left, right, medianIdx, curDim);
    KDTreeNode* result = new KDTreeNode(curPoint);
    result->left = buildSubTree(points, left, medianIdx - 1, (curDim + 1) % Dim);
    result->right = buildSubTree(points, medianIdx + 1, right, (curDim + 1) % Dim);
    return result;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<Dim>> points;
     for (size_t i = 0; i < newPoints.size(); i++)
        points.push_back(newPoints[i]);
    if (points.empty()) {
        root = NULL;
    } else {
        root = buildSubTree(points, 0, newPoints.size() - 1, 0);
    }
        size = newPoints.size();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
    if (this != &rhs) {
       clear(root);
       copy(rhs);
    }
   return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* current)
{
    if (current == NULL)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& rhs) {
    root = copy(rhs.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* current) {
    if (current == NULL)
        return NULL;
    KDTreeNode* node = new KDTreeNode(current->point);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor_(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor_(const Point<Dim>& query, int currDim, KDTreeNode* subRoot) const {
    Point<Dim> currNearest;
    int currRadius;
    if (subRoot->left == NULL && subRoot->right == NULL) {
        return subRoot->point;
    } else if (subRoot->left == NULL) {
        currNearest = findNearestNeighbor_(query, (currDim + 1) % Dim, subRoot->right);
        if (shouldReplace(query, currNearest, subRoot->point))
            currNearest = subRoot->point;
        return currNearest;
    } else if (subRoot->right == NULL) {
        currNearest = findNearestNeighbor_(query, (currDim + 1) % Dim, subRoot->left);
        if (shouldReplace(query, currNearest, subRoot->point))
            currNearest = subRoot->point;
        return currNearest;
    }

    if (smallerDimVal(query, subRoot->point, currDim)) {
        currNearest = findNearestNeighbor_(query, (currDim + 1) % Dim, subRoot->left);
    } else {
        currNearest = findNearestNeighbor_(query, (currDim + 1) % Dim, subRoot->right);
    }
    if (shouldReplace(query, currNearest, subRoot->point))
        currNearest = subRoot->point;
    int currRadiusSquared = 0;
    for (int i=0; i<Dim; i++)
       currRadiusSquared += (query[i] - currNearest[i]) * (query[i] - currNearest[i]);
    Point<Dim> tempNearest;
    if ((query[currDim] - subRoot->point[currDim]) * (query[currDim] - subRoot->point[currDim]) <= currRadiusSquared) {
        if (smallerDimVal(query, subRoot->point, currDim)) {
            tempNearest = findNearestNeighbor_(query, (currDim + 1) % Dim, subRoot->right);
        } else {
            tempNearest = findNearestNeighbor_(query, (currDim + 1) % Dim, subRoot->left);
        }
        if (shouldReplace(query, currNearest, tempNearest))
            currNearest = tempNearest;
    }
    return currNearest;
}
