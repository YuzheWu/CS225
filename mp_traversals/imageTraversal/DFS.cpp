#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance):png_(png), start_(start) {
  /** @todo [Part 1] */
  tolerance_ = tolerance;
  unsigned x = start.x;
  unsigned y = start.y;
  HSLAPixel start_pixel = png.getPixel(x, y);
  to_visit = std::stack<Point>();
  to_visit.push(start_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS *dfs = new DFS(png_, start_, tolerance_);
  ImageTraversal::Iterator it(dfs, &png_, start_, tolerance_);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  DFS *dfs = new DFS(png_, start_, tolerance_);
  dfs->to_visit = std::stack<Point>();
  ImageTraversal::Iterator it(dfs, &png_, start_, tolerance_);
  return it;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  to_visit.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point result = to_visit.top();
  to_visit.pop();
  return result;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  Point result = to_visit.top();
  return result;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return to_visit.empty();
}
