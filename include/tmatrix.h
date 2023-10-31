
#include <iostream>
#include <assert.h>

using namespace std;



const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;

public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz <= 0)
			throw out_of_range("Vector size should be greater than zero");
		if (sz > MAX_VECTOR_SIZE) throw out_of_range("Vector size can't be greater than max vector size");
		pMem = new T[sz]();
	}

	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}

	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz]();
		for (size_t i = 0; i < sz; i++) pMem[i] = v.pMem[i];
	}

	TDynamicVector(TDynamicVector&& v) noexcept : pMem(nullptr)
	{
		if (*this != v) {
			std::swap(v.pMem, pMem);
			sz = v.sz;
		}
	}

	~TDynamicVector()
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v) {
		if (this != &v) {
			delete[] pMem;
			sz = v.sz;
			pMem = new T[sz]();
			for (size_t i = 0; i < sz; i++) {
				pMem[i] = v.pMem[i];
			}
		}
		return *this;
	}

	TDynamicVector& operator=(TDynamicVector&& v) noexcept {
		if (*this != v) {
			std::swap(v.pMem, pMem);
			sz = v.sz;
		}
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index is out of range");
		return pMem[ind];
	}

	const T& operator[](size_t ind) const
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index is out of range");
		return pMem[ind];
	}

	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index is out of range");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index is out of range");
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz) return false;
		for (size_t i = 0; i < sz; i++)
			if (pMem[i] != v.pMem[i]) return false;
		return true;
	}

	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !operator==(v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector<T> result(*this);
		for (size_t i = 0; i < sz; i++) {
			result.pMem[i] += val;
		}
		return result;
	}

	TDynamicVector operator-(T val)
	{
		TDynamicVector<T> result(*this);
		for (size_t i = 0; i < sz; i++) {
			result.pMem[i] -= val;
		}
		return result;
	}

	TDynamicVector operator*(T val)
	{
		TDynamicVector<T> result(*this);
		for (size_t i = 0; i < sz; i++) { result.pMem[i] *= val; }
		return result;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz) throw "Not equal sizes of vectors";
		TDynamicVector<T> result(sz);
		for (size_t i = 0; i < sz; i++) {
			result.pMem[i] = pMem[i] + v.pMem[i];
		}
		return result;
	}


	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz) throw "Not equal sizes of vectors";
		TDynamicVector<T> result(sz);
		for (size_t i = 0; i < sz; i++) {
			result.pMem[i] = pMem[i] - v.pMem[i];
		}
		return result;
	}


	T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
	{
		if (sz != v.sz) throw "Not equal sizes of vectors";
		T result(0);
		for (size_t i = 0; i < sz; i++) {
			result += pMem[i] * v.pMem[i];
		}
		return result;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;

public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s <= 0) throw out_of_range("Size should be greater than 0");
		if (s > MAX_MATRIX_SIZE) throw "Matrix size should be less than 10000";
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		if (sz != m.sz) return false;
		for (size_t i = 0; i < sz; i++)
			if (pMem[i] != m.pMem[i]) return false;
		return true;
	}

	bool operator!=(const TDynamicMatrix& m) const noexcept {
		return !(operator==(m));
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix<T> result(*this);
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				result.pMem[i][j] *= val;
		return result;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.sz) throw invalid_argument("Sizes should be equal");
		TDynamicVector<T> result(sz);


	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz) throw invalid_argument("Sizes should be equal");
		TDynamicMatrix<T> result(m);
		for (size_t i = 0; i < sz; i++) {
			for (size_t j = 0; j < sz; j++)
			{
				result.pMem[i][j] += pMem[i][j];
			}
		}
		return result;
	}

	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz) throw invalid_argument("Sizes should be equal");
		TDynamicMatrix<T> result(*this);
		for (size_t i = 0; i < sz; i++) {
			for (size_t j = 0; j < sz; j++) {
				result.pMem[i][j] -= m.pMem[i][j];
			}
		}
		return result;
	}

	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.sz) throw invalid_argument("Cant multiply matrices of unequal sizes");
		TDynamicMatrix<int> result(sz);

		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				for (size_t k = 0; k < sz; j++)
					result.pMem[i][j] += pMem[i][k] * m.pMem[k][j];

		return result;

	}

	size_t size() const { return sz; }

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++) {
			for (size_t j = 0; j < v.sz; j++)
				istr >> v[i][j];
		}
		return istr;

	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++) {
			for (size_t j = 0; j < v.sz; j++)
				ostr << v[i][j] << " ";
			ostr << endl;
		}
		return ostr;
	}
};
