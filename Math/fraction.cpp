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

using Frac = Fraction<long long>;

int main() {
    Frac f1(2, 4), f2(3, 9);
    Frac f3 = f1 + f2;
    cout << (long long)f3.first << " " << (long long)f3.second << endl;
}