#include <iostream>
#include <cmath>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::fabs;
using std::sqrt;
using std::pow;
using std::swap;

const short RECTANGLE_LEFT_EDGE = -5;
const short RECTANGLE_BOTTOM_EDGE = -2;
const unsigned short RECTANGLE_RIGHT_EDGE = 5;
const unsigned short RECTANGLE_TOP_EDGE = 2;

const double EPSILON = 1e-2;
const double PI_CONSTANT = 3.14;

bool areAlmostEqual(double firstValue, double secondValue) {
    return fabs(firstValue - secondValue) < EPSILON;
}

bool isLeftOfRectangle(double x) {
    return !areAlmostEqual(x, RECTANGLE_LEFT_EDGE) && x < RECTANGLE_LEFT_EDGE;
}

bool isRightOfRectangle(double x) {
    return !areAlmostEqual(x, RECTANGLE_RIGHT_EDGE) && x > RECTANGLE_RIGHT_EDGE;
}

bool isAboveRectangle(double y) {
    return !areAlmostEqual(y, RECTANGLE_TOP_EDGE) && y > RECTANGLE_TOP_EDGE;
}

bool isBelowRectangle(double y) {
    return !areAlmostEqual(y, RECTANGLE_BOTTOM_EDGE) && y < RECTANGLE_BOTTOM_EDGE;
}

bool isOutsideRectangle(double x, double y) {
    return isLeftOfRectangle(x) || isRightOfRectangle(x) || isAboveRectangle(y) || isBelowRectangle(y);
}

double calculateCurvedDistance(double xStart, double yStart, double xEnd, double yEnd) {
    double straightDistance = sqrt(pow(xStart - xEnd, 2) + pow(yStart - yEnd, 2));
    return ((PI_CONSTANT / 2.0) * straightDistance + straightDistance) / 2.0;
}

void getBoundaryIntersection(
    double fromX, double fromY,
    double toX, double toY,
    double& intersectionX, double& intersectionY
) {
    double slope = (fromY - toY) / (fromX - toX);
    double intercept = fromY - slope * fromX;

    double xAtTop = (RECTANGLE_TOP_EDGE - intercept) / slope;
    double xAtBottom = (RECTANGLE_BOTTOM_EDGE - intercept) / slope;
    double yAtLeft = slope * RECTANGLE_LEFT_EDGE  + intercept;
    double yAtRight = slope * RECTANGLE_RIGHT_EDGE + intercept;

    if (!isRightOfRectangle(xAtTop) && !isLeftOfRectangle(xAtTop) && isAboveRectangle(toY)) {
        intersectionX = xAtTop;
        intersectionY = RECTANGLE_TOP_EDGE;
    }
    else if (!isLeftOfRectangle(xAtBottom) && !isRightOfRectangle(xAtBottom) && isBelowRectangle(toY)) {
        intersectionX = xAtBottom;
        intersectionY = RECTANGLE_BOTTOM_EDGE;
    }
    else if (!isAboveRectangle(yAtLeft) && !isBelowRectangle(yAtLeft) && isLeftOfRectangle(toX)) {
        intersectionX = RECTANGLE_LEFT_EDGE;
        intersectionY = yAtLeft;
    }
    else if (!isBelowRectangle(yAtRight) && !isAboveRectangle(yAtRight) && isRightOfRectangle(toX)) {
        intersectionX = RECTANGLE_RIGHT_EDGE;
        intersectionY = yAtRight;
    }
    else {
        intersectionX = toX;
        intersectionY = toY;
    }
}

int main() {
    unsigned long numberOfPoints;
    cin >> numberOfPoints;

    double totalDistance = 0.0;
    double currentX, currentY, nextX, nextY;

    cin >> currentX >> currentY;

    for (int step = 1; step < numberOfPoints; ++step) {
        cin >> nextX >> nextY;

        double originalNextX = nextX;
        double originalNextY = nextY;

        bool isCurrentOutside = isOutsideRectangle(currentX, currentY);
        bool isNextOutside    = isOutsideRectangle(nextX, nextY);

        if (isCurrentOutside && isNextOutside) {
            cout << "Both are out." << endl;
            currentX = originalNextX;
            currentY = originalNextY;
            continue;
        }

        if (!isCurrentOutside && !isNextOutside) {
            cout << "Both are in." << endl;
            totalDistance += calculateCurvedDistance(currentX, currentY, nextX, nextY);
        }
        else {
            if (isCurrentOutside) {
                swap(currentX, nextX);
                swap(currentY, nextY);
            }

            if (areAlmostEqual(currentY, nextY)) {
                double intersectionX = isRightOfRectangle(nextX) ? RECTANGLE_RIGHT_EDGE : RECTANGLE_LEFT_EDGE;
                totalDistance += calculateCurvedDistance(currentX, currentY, intersectionX, nextY);
            }
            else if (areAlmostEqual(currentX, nextX)) {
                double intersectionY = isAboveRectangle(nextY) ? RECTANGLE_TOP_EDGE : RECTANGLE_BOTTOM_EDGE;
                totalDistance += calculateCurvedDistance(currentX, currentY, nextX, intersectionY);
            }
            else {
                double boundaryX, boundaryY;
                getBoundaryIntersection(currentX, currentY, nextX, nextY, boundaryX, boundaryY);
                totalDistance += calculateCurvedDistance(currentX, currentY, boundaryX, boundaryY);
            }
        }

        currentX = originalNextX;
        currentY = originalNextY;
    }

    cout << fixed << setprecision(3) << totalDistance << endl;
    return 0;
}