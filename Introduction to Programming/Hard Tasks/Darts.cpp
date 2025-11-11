#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

const unsigned short SMALLEST_CIRCLE = 1;
const unsigned short MIDDLE_CIRCLE = 3;
const unsigned short BIGGEST_CIRCLE = 8;

const unsigned short SMALLEST_CIRCLE_POINTS = 60;
const unsigned short MIDDLE_CIRCLE_POINTS = 20;
const unsigned short BIGGEST_CIRCLE_POINTS = 10;
const unsigned short NO_POINTS = 0;

const double REGULATOR = 1e-4; // to 0.0001

int main() {
	double x, y, u, v;
	cout << "Enter the point that Integralcho is trying to hit: ";
	cin >> x >> y;
	cout << "Enter the deviation of his gaze : ";
	cin >> u >> v;

	x += u;
	y += v;

	double distance = sqrt((x * x) + (y * y));

	if (( distance - SMALLEST_CIRCLE ) < -REGULATOR ) {
		cout << "Result: " << SMALLEST_CIRCLE_POINTS;
	}
	else if ((( distance - MIDDLE_CIRCLE ) < -REGULATOR ) && (( distance - SMALLEST_CIRCLE ) > REGULATOR ))  {
		cout << "Result: " << MIDDLE_CIRCLE_POINTS;
	}
	else if ((( distance - BIGGEST_CIRCLE ) < -REGULATOR ) && (( distance - MIDDLE_CIRCLE ) > REGULATOR )) {
		cout << "Result: " << BIGGEST_CIRCLE_POINTS;
	}
	else {
		cout << "Result: " << NO_POINTS;
	}
	
	return 0;
}
