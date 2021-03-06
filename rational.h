#pragma once
#ifndef _RATIONAL_TEMPLATE_H
#define _RATIONAL_TEMPLATE_H
#include <string>
#include <algorithm>
#include <cmath>

namespace Number
{
	template <typename T>
	class Rational
	{
	public:
		using Type = T;

		Rational() : Rational(0, 1) {};
		Rational(const Type &num) : Rational(num, 1) {};
		Rational(const Type &num, const Type &den) { initialize(num, den); };

		Rational& initialize(const Type &num, const Type &den) {
			Type g = gcd(num, den);
			numerator = num / g;
			denominator = den / g;
			if (denominator < 0) {
				denominator = -denominator;
				numerator = -numerator;
			}
			return *this;
		}

		Rational& operator=(const Rational &r) {
			this->numerator = r.numerator;
			this->denominator = r.denominator;
			return *this;
		}

		Rational& operator+=(const Rational &r) {
			return initialize(numerator * r.denominator + r.numerator * denominator, denominator * r.denominator);
		}

		Rational& operator-=(const Rational &r) {
			return initialize(numerator * r.denominator - r.numerator * denominator, denominator * r.denominator);
		}

		Rational& operator*=(const Rational &r) {
			return initialize(numerator * r.numerator, denominator * r.denominator);
		}

		Rational& operator/=(const Rational &r) {
			return initialize(numerator * r.denominator, denominator * r.numerator);
		}

		const Rational operator-() const {
			return Rational(-numerator, denominator);
		}
		const Rational operator~() const {
			return Rational(denominator, numerator);
		}

		bool isNaN() const {
			return (denominator == 0 && numerator == 0) || (denominator < 0);
		}
		bool isInf() const {
			return (denominator == 0 && numerator != 0);
		}
		bool isInt() const {
			return denominator == 1;
		}
		bool isPositive() const {
			return numerator > 0;
		}
		bool isZero() const {
			return numerator == 0;
		}
		bool isNegative() const {
			return numerator < 0;
		}

	private:
		Type numerator;
		Type denominator;
		static Type gcd(Type a, Type b) {
			while (b != 0) {
				a = a % b;
				std::swap(a, b);
			}
			return a;
		}
	public:
		const Type& getnum() const {
			return numerator;
		}
		const Type& getden() const {
			return denominator;
		}

		friend Type floor(const Rational &r) { return r.floor(); }
		friend Type ceil(const Rational &r) { return r.ceil(); }
		friend Type fix(const Rational &r) { return r.fix(); }
		friend bool operator==(const Rational &lhs, const Rational &rhs) {
			return lhs.equal(rhs);
		}
		friend bool operator!=(const Rational &lhs, const Rational &rhs) {
			return !lhs.equal(rhs);
		}

	private:
		bool equal(const Rational &r) const {
			return r.numerator == this->numerator && r.denominator == this->denominator;
		}

		Type floor() const {
			if (isInf())
				return std::numeric_limits<Type>::max();
			else if (isNaN())
				return Type(0);
			else if (isZero())
				return Type(0);
			else if (isInt())
				return numerator;
			else
				return isPositive() ? (numerator / denominator) : (numerator / denominator - 1);
		}

		Type ceil() const {
			if (isInf())
				return std::numeric_limits<Type>::max();
			else if (isNaN())
				return Type(0);
			else if (isZero())
				return Type(0);
			else if (isInt())
				return numerator;
			else
				return isPositive() ? (numerator / denominator + 1) : (numerator / denominator);
		}

		Type fix() const {
			return isPositive() ? floor() : ceil();
		}
	};

	template <typename T>
	inline const Rational<T> operator+(const Rational<T> &a, const Rational<T> &b) {
		return Rational<T>(a) += b;
	}
	template <typename T>
	inline const Rational<T> operator-(const Rational<T> &a, const Rational<T> &b) {
		return Rational<T>(a) -= b;
	}

	template <typename T>
	inline const Rational<T> operator*(const Rational<T> &a, const Rational<T> &b) {
		return Rational<T>(a) *= b;
	}

	template <typename T>
	inline const Rational<T> operator/(const Rational<T> &a, const Rational<T> &b) {
		return Rational<T>(a) /= b;
	}

	template <typename T>
	inline const typename Rational<T>::Type compare(const Rational<T> &a, const Rational<T> &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum();
	}

	template <typename T>
	inline bool operator>(const Rational<T> &a, const Rational<T> &b) {
		return compare(a, b) > 0;
	}

	template <typename T>
	inline bool operator>=(const Rational<T> &a, const Rational<T> &b) {
		return compare(a, b) >= 0;
	}

	template <typename T>
	inline bool operator<(const Rational<T> &a, const Rational<T> &b) {
		return compare(a, b) < 0;
	}

	template <typename T>
	inline bool operator<=(const Rational<T> &a, const Rational<T> &b) {
		return compare(a, b) <= 0;
	}

	template <typename T>
	inline const Rational<T> abs(const Rational<T> &a) {
		using std::abs;

		return Rational<T>(abs(a.getnum()), a.getden());
	}

	template <typename T>
	inline const Rational<T> mod(const Rational<T> &a, const Rational<T> &b) {
		return a - (b * floor(a / b));
	}

	template <typename T>
	inline const Rational<T> rem(const Rational<T> &a, const Rational<T> &b) {
		return  a - (b * fix(a / b));
	}

	template <typename T>
	inline std::string to_string(const Rational<T> &a) {
		using std::to_string;

		if (a.isInt())
			return to_string(a.getnum());
		else if (a.isInf())
			return "Inf";
		else if (a.isNaN())
			return "NaN";
		else
			return to_string(a.getnum()) + "/" + to_string(a.getden());
	}
}

#endif
