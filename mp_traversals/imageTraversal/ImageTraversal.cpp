#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, const PNG * png, Point start, double tolerance) {
  /** @todo [Part 1] */
  traversal_ = traversal;
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  visited.push_back(start_);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point point = traversal_->peek();
  traversal_->pop();
  HSLAPixel start_pixel = png_->getPixel(start_.x, start_.y);
  unsigned int height = png_->height();
  unsigned int width = png_->width();
  unsigned x = point.x;
  unsigned y = point.y;


  if(x + 1 < width) {
    HSLAPixel right = png_->getPixel(x + 1, y);
    Point right_point(x + 1, y);
    if (ImageTraversal::calculateDelta(start_pixel, right) < tolerance_ && std::find(visited.begin(), visited.end(), right_point) == visited.end()) {
      traversal_->add(right_point);
      visited.push_back(right_point);
    }
  }
  if(y + 1 < height) {
    HSLAPixel below = png_->getPixel(x, y + 1);
    Point below_point(x , y + 1);
    if (ImageTraversal::calculateDelta(start_pixel, below) < tolerance_ && std::find(visited.begin(), visited.end(), below_point) == visited.end()) {
      traversal_->add(below_point);
      visited.push_back(below_point);
    }
  }
  if(x > 0) {
    HSLAPixel left = png_->getPixel(x - 1, y);
    Point left_point(x - 1 , y);
    if (ImageTraversal::calculateDelta(start_pixel, left) < tolerance_ && std::find(visited.begin(), visited.end(), left_point) == visited.end()) {
      traversal_->add(left_point);
      visited.push_back(left_point);
    }
  }
  if(y > 0) {
    HSLAPixel above = png_->getPixel(x, y - 1);
    Point above_point(x , y - 1);
    if (ImageTraversal::calculateDelta(start_pixel, above) < tolerance_ && std::find(visited.begin(), visited.end(), above_point) == visited.end()) {
      traversal_->add(above_point);
      visited.push_back(above_point);
    }
  }

  return *this;
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return traversal_->peek();
}


/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(this->traversal_->empty() || other.traversal_->empty()) {
    if(this->traversal_->empty() && other.traversal_->empty()) {
      return false;
    } else {
      return true;
    }
  }
  if (traversal_->peek() == other.traversal_->peek()) {
    return false;
  }
  else
  {
    return true;
  }

}
