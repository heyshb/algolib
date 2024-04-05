#include <bits/stdc++.h>

using namespace std;
template <typename ValType>
struct Fraction: public pair<ValType, ValType>{
    Fraction(){}
    Fraction(ValType v1, ValType v2): pair<ValType, ValType>(v1, v2) {Normolize();}
    Fraction(ValType v): pair<ValType, ValType>(v, 1) {}
	void Normolize() {
		ValType g = __gcd(this->first, this->second);
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
	Fraction operator - () const {
		return Fraction(-this->first, this->second);
	}
	bool operator < (const Fraction& rhs) const {
		return this->first * rhs.second < this->second * rhs.first;
	}
	bool operator <= (const Fraction& rhs) const {
		return this->first * rhs.second <= this->second * rhs.first;
	}
	bool operator > (const Fraction& rhs) const {
		return this->first * rhs.second > this->second * rhs.first;
	}
	bool operator >= (const Fraction& rhs) const {
		return this->first * rhs.second >= this->second * rhs.first;
	}
};

using CoordinateType = Fraction<int>;

struct Point {
	CoordinateType x, y;
	Point(){}
	Point(CoordinateType x, CoordinateType y) : x(x), y(y) {}
	Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	CoordinateType operator % (const Point &rhs) const { // lhs dot rhs
		return x * rhs.x + y * rhs.y;
	}
	CoordinateType operator * (const Point &rhs) const { // lhs cross rhs
		return x * rhs.y - y * rhs.x;
	}
	Point operator - () const {
		return Point(-x, -y);
	}
	Point operator * (CoordinateType u) const {
		return Point(x * u, y * u);
	}
	bool operator == (const Point &rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const Point &rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
	bool operator <= (const Point &rhs) const {
		return x < rhs.x || (x == rhs.x && y <= rhs.y);
	}
	bool operator > (const Point &rhs) const {
		return x > rhs.x || (x == rhs.x && y > rhs.y);
	}
	bool operator >= (const Point &rhs) const {
		return x > rhs.x || (x == rhs.x && y >= rhs.y);
	}
	CoordinateType SqrLen() const {
		return x * x + y * y;
	}
};

struct Seg {
	Point u, v;
	Seg(){}
	Seg(const Point& u, const Point& v) : u(u), v(v) {}
	CoordinateType SqrLen() const {
		return (v - u).SqrLen();
	}
};

bool IsParallel(const Seg &s1, const Seg &s2) {
	return (s1.v - s1.u) * (s2.v - s2.u) == CoordinateType(0);
}

bool PointOnSegment(const Point &p, const Seg& s) {
	return (s.u - p) * (s.v - p) == CoordinateType(0) && (s.u - p) % (s.v - p) <= CoordinateType(0);
}

void print(CoordinateType v) {
	printf("%d/%d\n", v.first, v.second);
}

// The first value is the number of intersection points. 0 / 1 / 2, 2 for inf.
// If there are infinity number of intersection points, return the two points that is the endpoints of the intersection.
tuple<int, Point, Point> Intersect(Seg s1, Seg s2) {
	if (s1.SqrLen() > s2.SqrLen()) swap(s1, s2);
	if (s1.SqrLen() == CoordinateType(0)) {
		if (PointOnSegment(s1.u, s2)) return {1, s1.u, Point()};
		return {0, Point(), Point()};
	}
	Point p1 = s1.u, p2 = s1.v, p3 = s2.u, p4 = s2.v;
	if (p2 < p1) swap(p1, p2);
	if (p4 < p3) swap(p3, p4);
	if (IsParallel(s1, s2)) {
		if ((s1.v - s1.u) * (s2.u - s1.u) == CoordinateType(0)) {
			// co-line
			Point R = p2 < p4 ? p2 : p4;
			Point L = p3 < p1 ? p1 : p3;
			if (R < L) return {0, Point(), Point()};
			if (R == L) return {1, R, Point()};
			return {2, L, R};
		}
		return {0, Point(), Point()};
	}
	CoordinateType cross_1 = (p2 - p1) * (p3 - p1);
	CoordinateType cross_2 = (p2 - p1) * (p4 - p1);
	if (cross_1 * cross_2 > CoordinateType(0)) return {0, Point(), Point()};
	CoordinateType cross_3 = (p4 - p3) * (p1 - p3);
	CoordinateType cross_4 = (p4 - p3) * (p2 - p3);
	if (cross_3 * cross_4 > CoordinateType(0)) return {0, Point(), Point()};
	CoordinateType k = ((p3 - p1) * (p4 - p3)) / ((p2 - p1) * (p4 - p3));
	return {1, p1 + (p2 - p1) * k, Point()};
}

int main() {
	Seg s1, s2;
	s1.u = Point(1, 1);
	s1.v = Point(2, 0);
	s2.u = Point(0, -1);
	s2.v = Point(2, 2);
	auto ret = Intersect(s1, s2);
	int cnt = get<0>(ret);
	Point p1 = get<1>(ret);
	Point p2 = get<2>(ret);
	printf("%d\n", cnt);
	if (cnt >= 1) {
		printf("(%d/%d, %d/%d)\n", p1.x.first, p1.x.second, p1.y.first, p1.y.second);
	}
	if (cnt >= 2) {
		printf("(%d/%d, %d/%d)\n", p2.x.first, p2.x.second, p2.y.first, p2.y.second);
	}
}