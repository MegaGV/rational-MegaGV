#pragma once
#include <string>
#include <algorithm>
#include <cmath>
#include <gmpxx.h>

namespace Number_template
{
	/*template <typename T>
	struct ToInt;
	struct ToInt<float>
	{
		using Type = int;
	};
	struct ToInt<mpf_class>
	{
		using Type = mpz_class;
	};*/
	template <typename T>
	class Rational
	{
	public:
		using Type = T;
		//typename ToFloat<T>::Type;
		Rational(Type num, Type den) { initialize(num, den); };
		Rational() :numerator(1), denominator(1) {};//()invoke the constructor 
		Rational(Type num) :numerator(num), denominator(1) {};

		void initialize(const Type& num, const Type& den) {
			Type g = gcd(num, den);
			numerator = num / g;
			denominator = den / g;
			adjust(numerator, denominator);
		}

		static void adjust(Type &num, Type &den) {
			bool _isnegative = false;
			if (num < 0) {
				num = -num;
				_isnegative = !_isnegative;
			}
			if (den < 0) {
				den = -den;
				_isnegative = !_isnegative;
			}

			if (_isnegative) {
				num = -num;
			}
		}

		Rational& operator=(const Rational &r) {
			this->numerator = r.numerator;
			this->denominator = r.denominator;
			return *this;
		}

		Rational& operator+=(const Rational &r) {
			initialize(numerator * r.denominator + r.numerator * denominator, denominator * r.denominator);
			return *this;
		}

		Rational& operator-=(const Rational &r) {
			initialize(numerator * r.denominator - r.numerator * denominator, denominator * r.denominator);
			return *this;
		}

		Rational& operator*=(const Rational &r) {
			initialize(numerator * r.numerator, denominator * r.denominator);
			return *this;
		}

		Rational& operator/=(const Rational &r) {
			initialize(numerator * r.denominator, denominator * r.numerator);
			return *this;
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

	private:
		Type numerator;
		Type denominator;
		static Type gcd(Type a, Type b) {
			using std::max;  
			for (Type divisor = max(a, b); divisor >= 1; divisor--) {
				if (a % divisor == 0 && b % divisor == 0)
					return divisor;
			}
			return 1;
		}
	public:
		const Type& getnum() const {
			return numerator;
		}
		const Type& getden() const {
			return denominator;
		}
	};

	template <>
	class Rational<mpz_class>
	{
	public:
		using Type = mpz_class;
		Rational(Type num, Type den) { initialize(num, den); };
		Rational() :numerator(1), denominator(1) {};
		Rational(Type num) :numerator(num), denominator(1) {};

		void initialize(const Type& num, const Type& den) {
			Type g = gcd(num, den);
			numerator = num / g;
			denominator = den / g;
			adjust(numerator, denominator);
		}

		static void adjust(Type &num, Type &den) {
			bool _isnegative = false;
			if (num < 0) {
				num = -num;
				_isnegative = !_isnegative;
			}
			if (den < 0) {
				den = -den;
				_isnegative = !_isnegative;
			}

			if (_isnegative) {
				num = -num;
			}
		}

		Rational& operator=(const Rational &r) {
			this->numerator = r.numerator;
			this->denominator = r.denominator;
			return *this;
		}

		Rational& operator+=(const Rational &r) {
			initialize(numerator * r.denominator + r.numerator * denominator, denominator * r.denominator);
			return *this;
		}

		Rational& operator-=(const Rational &r) {
			initialize(numerator * r.denominator - r.numerator * denominator, denominator * r.denominator);
			return *this;
		}

		Rational& operator*=(const Rational &r) {
			initialize(numerator * r.numerator, denominator * r.denominator);
			return *this;
		}

		Rational& operator/=(const Rational &r) {
			initialize(numerator * r.denominator, denominator * r.numerator);
			return *this;
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

	private:
		Type numerator;
		Type denominator;
		static Type gcd(Type a, Type b) {
			while (b != 0) {
				a = a % b;
				swap(a, b);
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
	};

	template<typename Type>
	inline const Rational<Type> operator+(const Rational<Type> &a, const Rational<Type> &b) {
		return Rational(a.getnum() * b.getden() + b.getnum() * a.getden(), a.getden() * b.getden());
	}
	template<typename Type>
	inline const Rational<Type> operator-(const Rational<Type> &a, const Rational<Type> &b) {
		return Rational(a.getnum() * b.getden() - b.getnum() * a.getden(), a.getden() * b.getden());
	}

	template<typename Type>
	inline const Rational<Type> operator*(const Rational<Type> &a, const Rational<Type> &b) {
		return Rational(a.getnum() * b.getnum(), a.getden() * b.getden());
	}

	template<typename Type>
	inline const Rational<Type> operator/(const Rational<Type> &a, const Rational<Type> &b) {
		return Rational(a.getnum() * b.getden(), a.getden() * b.getnum());
	}

	template<typename Type>
	inline const Rational<Type> operator-(const Rational<Type> &a) {
		return Rational(-a.getnum(), a.getden());
	}

	template<typename Type>
	inline const Rational<Type> operator~(const Rational<Type> &a) {
		return Rational(a.getden(), a.getnum());
	}

	template<typename Type>
	inline bool operator>(const Rational<Type> &a, const Rational<Type> &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() > 0;
	}

	template<typename Type>
	inline bool operator>=(const Rational<Type> &a, const Rational<Type> &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() >= 0;
	}

	template<typename Type>
	inline bool operator==(const Rational<Type> &a, const Rational<Type> &b) {
		return a.getnum() * b.getden() == b.getnum() * a.getnum();
	}

	template<typename Type>
	inline bool operator!=(const Rational<Type> &a, const Rational<Type> &b) {
		return a.getnum() * b.getden() != b.getnum() * a.getnum();
	}

	template<typename Type>
	inline bool operator<(const Rational<Type> &a, const Rational<Type> &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() < 0;
	}

	template<typename Type>
	inline bool operator<=(const Rational<Type> &a, const Rational<Type> &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() <= 0;
	}

	template<typename Type>
	inline const Rational<Type> abs(const Rational<Type> &a) {
		return Rational(std::abs(a.getnum()), a.getden());
	}

	template <>
	inline const Rational<mpz_class> abs(const Rational<mpz_class> &a) {
		return Rational<mpz_class>(abs(a));
	}

	template<typename Type>
	inline typename Rational<Type>::Type floor(const Rational<Type> &a) {
		if (a.isInf())
			return std::numeric_limits<typename Rational<Type>::Type>::max();
		if (a.isNaN())
			return 0;
		else
			return (a.getnum() % a.getden() != 0 && a.getnum() < 0) ? (a.getnum() / a.getden() - 1): (a.getnum() / a.getden());
	}

	template<typename Type>
	inline typename Rational<Type>::Type ceil(const Rational<Type> &a) {
		if (a.isInf())
			return std::numeric_limits<typename Rational<Type>::Type>::max();
		if (a.isNaN())
			return 0;
		else
			return (a.getnum() % a.getden() != 0 && a.getnum() > 0) ? (a.getnum() / a.getden() + 1) : (a.getnum() / a.getden());
	}

	template<typename Type>
	inline typename Rational<Type>::Type fix(const Rational<Type> &a) {
		if (a.getnum() > 0)
			return floor(a);
		else
			return ceil(a);
	}

	template<typename Type>
	inline const Rational<Type> mod(const Rational<Type> &a, const Rational<Type> &b) {
		return a - (b * floor(a / b));
	}

	template<typename Type>
	inline const Rational<Type> rem(const Rational<Type> &a, const Rational<Type> &b) {
		return  a - (b * fix(a / b));
	}

	template <typename Type>
	inline std::string to_string(const Rational<Type> &a) {
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

	template <>
	inline std::string to_string<mpz_class>(const Rational<mpz_class> &a) {
		using std::to_string;
		using ::Number_template::to_string;

		if (a.isInt())
			return a.getnum().get_str();
		else if (a.isInf())
			return "Inf";
		else if (a.isNaN())
			return "NaN";
		else
			return a.getnum().get_str() + "/" + a.getden().get_str();
	}
	
	inline std::string to_string(const mpz_class &v) {
		return v.get_str();
	}
}
