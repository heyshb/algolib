#include <bits/stdc++.h>

using namespace std;
template <typename ValType>
struct Fraction: public pair<ValType, ValType>{
    Fraction(){}
    Fraction(ValType v1, ValType v2): pair<ValType, ValType>(v1, v2) {Normolize();}
    Fraction(ValType v): pair<ValType, ValType>(v, 1) {}
	void Normolize() {
		ValType g = __gcd(x, y);
		this->first /= g;
		this->second /= g;
		if (this->second < 0) {
			this->first = -this->first;
			this->second = -this->second;
		}
	}
    Fraction operator+ (const Fraction& rhs) const {
        ValType x = this->first * rhs.second + this->second * rhs.first;
        ValType y = this->second * rhs.second;
		return Fraction(x, y);
    }
    Fraction operator- (const Fraction& rhs) const {
        ValType x = this->first * rhs.second - this->second * rhs.first;
        ValType y = this->second * rhs.second;
		return Fraction(x, y);
    }
    Fraction operator* (const Fraction& rhs) const {
        ValType x = this->first * rhs.first;
        ValType y = this->second * rhs.second;
		return Fraction(x, y);
    }
    Fraction operator/ (const Fraction& rhs) const {
        ValType x = this->first * rhs.second;
        ValType y = this->second * rhs.first;
		return Fraction(x, y);
    }
	Fraction operator- () const {
		return Fraction(-this->first, this->second);
	}
	bool operator< (const Fraction& rhs) const {
		return this->first * rhs.second < this->second * rhs.first;
	}
	bool operator<= (const Fraction& rhs) const {
		return this->first * rhs.second <= this->second * rhs.first;
	}
};

using CoordinateType = Fraction<int>;

struct Point {
	CoordinateType x, y;
	Point(){}
	Point(CoordinateType x, CoordinateType y) : x(x), y(y) {}
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend CoordinateType operator % (const Point &a, const Point &b) { // a dot b
		return a.x * b.x + a.y * b.y;
	}
	friend CoordinateType operator * (const Point &a, const Point &b) { // a cross b
		return a.x * b.y - a.y * b.x;
	}
	friend Point operator - (const Point &a) {
		return Point(-a.x, -a.y);
	}
	friend Point operator * (const Point &a, CoordinateType u) {
		return Point(a.x * u, a.y * u);
	}
	friend bool operator == (const Point &a, const Point &b) {
		return a.x == b.x && a.y == b.y;
	}
	CoordinateType SqrLen() {
		return x * x + y * y;
	}
};

struct Seg {
	Point u, v;
	Seg(){}
	Seg(const Point& u, const Point& v) : u(u), v(v) {}
	CoordinateType SqrLen() {
		return (v - u).SqrLen();
	}
};

bool IsParallel(const Seg &s1, const Seg &s2) {
	return (s1.v - s1.u) * (s2.v - s2.u) == CoordinateType(0);
}

bool PointOnSegment(const Point &p, const Seg& s) {
	return (s.u - p) * (s.v - p) == CoordinateType(0) && (s.u - p) % (s.v - p) <= CoordinateType(0);
}

// The first value is the number of intersection points. 0 / 1 / 2, 2 for inf.
// If there are infinity number of intersection points, return the two points that is the endpoints of the intersection.
tuple<int, Point, Point> Intersect(const Seg &s1, const Seg &s2) {
	if (IsParallel(s1, s2)) return {0, Point(), Point()};
	Point p1 = s1.u, p2 = s1.v, p3 = s2.u, p4 = s2.v;
	// TODO
}

int main() {
}