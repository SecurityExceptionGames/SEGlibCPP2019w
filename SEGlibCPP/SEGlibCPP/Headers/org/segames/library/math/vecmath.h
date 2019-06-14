#pragma once
#include <org/segames/library/math/math.h>
#include <org/segames/library/object.h>
#include <org/segames/library/index_out_of_bounds_exception.h>
#include <org/segames/library/invalid_value_exception.h>

#include <cstring>

#ifndef SEG_API_VECMATH_ZERO_OFFSET
#define SEG_API_VECMATH_ZERO_OFFSET 0.000000000001l
#endif

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace math
			{

				/*
					Base class for a n-dimensional euclidean vector with templates for different data type and dimensions

					* @author	Philip Rosberg
					* @since	2018-06-21
					* @edited	2018-06-22
				*/
				template<typename T, int dim>
				class BasicVector :
					public Object
				{
				protected:

					/*
						Vector data
					*/
					T data[dim];

				public:

					/*
						Standard vector constructor
					*/
					BasicVector()
					{}

					/*
						Vector mem. pointer constructor. Constructs a vector from the values located at the given pointer
						* @param[in] ptr The pointer to the values
					*/
					template<typename T2>
					explicit BasicVector(const T2* ptr)
					{
						for (int i = 0; i < this->dimensions(); i++)
							data[i] = (T)ptr[i];
					}

					/*
						Vector value constructor. Constructs a vector from the given values
						* @param[in] items The vector data to place in the vector
					*/
					template<typename... T2>
					explicit BasicVector(const T2... items)
					{
#ifdef SEG_API_DEBUG_THROW
						if (sizeof...(items) != dim)
							throw InvalidValueException("Number of elements in parameter pack (" + std::to_string(sizeof...(items)) + ") is not equal to the vector dimensions (" + std::to_string(dim) + ").");
#endif
						T list[sizeof...(items)] = { (T)items... };
						for (int i = 0; i < this->dimensions(); i++)
							data[i] = list[i];
					}

					/*
						Cast vector constructor. A constructor that casts one type of vector into another if the element types are castable
						* @param[in] obj The vector to cast from
					*/
					template<typename T2>
					explicit BasicVector(const BasicVector<T2, dim>& obj)
					{
						for (int i = 0; i < this->dimensions(); i++)
							data[i] = (T)obj.peek(i);
					}

					/*
						Returns the number of dimensions of the vector
					*/
					inline virtual int dimensions() const noexcept
					{
						return dim;
					}

					/*
						Returns the pointer to the first position in the backing data array
					*/
					inline virtual T* getPointer() noexcept
					{
						return data;
					}

					/*
						Returns the value of the element at the given position
						* @param[in] n The position of the element, composant, to return
					*/
					inline virtual const T& peek(const int n) const
					{
						return ((BasicVector<T, dim>&)*this)[n];
					}

					/*
						Returns a reference to the element at the given position
						* @param[in] n The position of the element, composant, to return
					*/
					inline T& operator[](const int n)
					{
#ifdef SEG_API_DEBUG_THROW
						if (n < 0 || (size_t)n >= dim)
							throw IndexOutOfBoundsException("The given vector element is not in the dimension of the vector." + std::to_string(n));
#endif
						return data[n];
					}

					/*
						Returns a string representation of the object
					*/
					virtual std::string toString() const override
					{
						std::string out = "[";
						for (int i = 0; i < dimensions(); i++)
						{
							out += std::to_string(peek(i));
							if (i < dimensions() - 1)
								out += ",";
						}
						return out + "]";
					}

					/*
						Returns true if the the given object is equal to this one
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const override
					{
						if (typeid(obj) == typeid(*this))
						{
							for (int i = 0; i < dimensions(); i++)
								if (((BasicVector<T, dim>&)obj).peek(i) != peek(i))
									return false;
							return true;
						}
						else
							return false;
					}

					/*
						Returns true if the the given vector is equal to this one, calls the equals() method
						* @param[in] obj The vector to check
					*/
					template<typename T2>
					inline bool operator==(const BasicVector<T2, dim>& obj) const
					{
						return equals(obj);
					}

					/*
						Returns true if the the given vector is not equal to this one, inverse of operator==
						* @param[in] obj The vector to check
					*/
					template<typename T2> 
					inline bool operator!=(const BasicVector<T2, dim>& obj) const
					{
						return !(*this == obj);
					}

					/*
						Returns true if the the given vector is equal to this one
						* @param[in] obj The vector to check
					*/
					template<typename T2>
					inline bool equals(const BasicVector<T2, dim>& obj) const
					{
						for (int i = 0; i < dimensions(); i++)
							if (obj.peek(i) != peek(i))
								return false;
						return true;
					}

					/*
						Multiplies the vector by the given scalar
						* @param[in] scalar The scalar to multiply this vector by
					*/
					template<typename T2>
					inline BasicVector<T, dim>& operator*=(const T2 scalar)
					{
						for (int i = 0; i < dimensions(); i++)
							data[i] = (T)(peek(i) * scalar);
						return *this;
					}

					/*
						Adds the given vector to this one
						* @param[in] obj The vector to add to this one
					*/
					template<typename T2>
					inline BasicVector<T, dim>& operator+=(const BasicVector<T2, dim>& obj)
					{
						for (int i = 0; i < dimensions(); i++)
							data[i] = (T)(peek(i) + obj.peek(i));
						return *this;
					}

					/*
						Subtracts the given vector from this one
						* @param[in] obj The vector to subtract from this one
					*/
					template<typename T2>
					inline BasicVector<T, dim>& operator-=(const BasicVector<T2, dim>& obj)
					{
						for (int i = 0; i < dimensions(); i++)
							data[i] = (T)(peek(i) - obj.peek(i));
						return *this;
					}

					/*
						Creates a vector filled with random values in the range [0, 1)
					*/
					inline static BasicVector<T, dim> rand()
					{
						BasicVector<T, dim> out;
						for (int i = 0; i < dim; i++)
							out[i] = (T)random();
						return out;
					}

					/*
						Creates a vector filled with zeros
					*/
					inline static BasicVector<T, dim> zeros()
					{
						BasicVector<T, dim> out;
						for (int i = 0; i < dim; i++)
							out[i] = (T)0;
						return out;
					}

				};

				/*
					Base class for a m x n euclidean matrix with template parameters for data type and size

					* @author	Philip Rosberg
					* @since	2018-06-21
					* @edited	2018-06-22
				*/
				template<typename T, int rows, int cols>
				class BasicMatrix :
					public Object
				{
				protected:

					/*
						The matrix data
					*/
					T data[rows][cols];

				public:

					/*
						Standard matrix constructor
					*/
					BasicMatrix()
					{}

					/*
						Matrix initializer list constructor. Constructs a matrix form the contents of the given initializer list
						* @param[in] list The initializer list with data
					*/
					explicit BasicMatrix(const std::initializer_list<std::initializer_list<T>>& list)
					{
#ifdef SEG_API_DEBUG_THROW
						if (list.size() != (size_t)this->m())
							throw InvalidValueException("Initializer list size is not correct.");
						if (list.begin()->size() != (size_t)this->n())
							throw InvalidValueException("Initializer list size is not correct.");
#endif
						for (int i = 0; i < this->m(); i++)
							memcpy((T*)data[i], list.begin()[i].begin(), sizeof(T) * this->n());
					}

					/*
						Cast matrix constructor. A constructor that casts one type of matrix into another if the element types are castable
						* @param[in] obj The matrix to cast from
					*/
					template<typename T2>
					explicit BasicMatrix(const BasicMatrix<T2, rows, cols>& obj)
					{
						for (int i = 0; i < this->m(); i++)
							for (int j = 0; j < this->n(); j++)
								data[i][j] = (T)obj.peek(i, j);
					}

					/*
						Returns the number of rows in the matrix
					*/
					inline virtual int m() const noexcept
					{
						return rows;
					}

					/*
						Returns the number of columns in the matrix
					*/
					inline virtual int n() const noexcept
					{
						return cols;
					}

					/*
						Returns a pointer to the first element of the matrix data
					*/
					inline virtual T* getPointer() noexcept
					{
						return (T*)data;
					}

					/*
						Returns the value at the given row and column position
						* @param[in] i The index of the row of the element to return
						* @param[in] j The index of the column of the element to return
					*/
					inline virtual const T& peek(const int i, const int j) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (i < 0 || i >= m())
							throw IndexOutOfBoundsException("The index of the requested row is outside of the matrix: " + std::to_string(i));
						if (j < 0 || j >= n())
							throw IndexOutOfBoundsException("The index of the requested column is outside of the matrix: " + std::to_string(j));
#endif
						return data[i][j];
					}

					/*
						Returns a copy of the row of the given index of the given matrix
						* @param[in] i The row index
						* @param[in] a The matrix
					*/
					inline virtual BasicVector<T, cols> row(const int i) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (i < 0 || i >= m())
							throw IndexOutOfBoundsException("The index of the requested row is outside of the matrix: " + std::to_string(i));
#endif
						BasicVector<T, cols> out;
						for (int j = 0; j < cols; j++)
							out[j] = peek(i, j);
						return out;
					}

					/*
						Returns a copy of the column of the given index of the given matrix
						* @param[in] j The column index
						* @param[in] a The matrix
					*/
					inline virtual BasicVector<T, rows> column(const int j) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (j < 0 || j > n())
							throw IndexOutOfBoundsException("The index of the requested column is outside of the matrix: " + std::to_string(j));
#endif
						BasicVector<T, rows> out;
						for (int i = 0; i < rows; i++)
							out[i] = peek(i, j);
						return out;
					}


					/*
						Returns a pointer to the given row of the matrix
						* @param[in] i The index of the row to returns the pointer to
					*/
					inline T* operator[](const int i)
					{
#ifdef SEG_API_DEBUG_THROW
						if (i < 0 || i >= m())
							throw IndexOutOfBoundsException("The index of the requested row is outside of the matrix: " + std::to_string(i));
#endif
						return data[i];
					}

					/*
						Returns a string representation of the object
					*/
					virtual std::string toString() const override
					{
						std::string out = "";
						for (int i = 0; i < m(); i++)
						{
							out += "| ";

							for (int j = 0; j < n(); j++)
							{
								out += std::to_string(peek(i, j));
								if (j < n() - 1)
									out += "\t";
							}

							out += " |\n";
						}

						return out;
					}

					/*
						Returns true if the the given object is equal to this one
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const override
					{
						if (typeid(obj) == typeid(*this))
						{
							for (int i = 0; i < m(); i++)
								for (int j = 0; j < n(); j++)
									if (((BasicMatrix<T, rows, cols>&)obj).peek(i, j) != peek(i, j))
										return false;
							return true;
						}
						else
							return false;
					}

					/*
						Returns true if the the given matrix is equal to this one, calls the equals() method
						* @param[in] obj The matrix to check
					*/
					template<typename T2>
					inline bool operator==(const BasicMatrix<T2, rows, cols>& obj) const
					{
						return equals(obj);
					}

					/*
						Returns true if the the given matrix is not equal to this one, inverse of operator==
						* @param[in] obj The matrix to check
					*/
					template<typename T2>
					inline bool operator!=(const BasicMatrix<T2, rows, cols>& obj) const
					{
						return !(*this == obj);
					}

					/*
						Returns true if the the given matrix is equal to this one
						* @param[in] obj The matrix to check
					*/
					template<typename T2>
					inline bool equals(const BasicMatrix<T2, rows, cols>& obj) const
					{
						for (int i = 0; i < m(); i++)
							for (int j = 0; j < n(); j++)
								if (obj.peek(i, j) != peek(i, j))
									return false;
						return true;
					}

					/*
						Multiplies the matrix by the given scalar
						* @param[in] scalar The scalar of to multiply the matrix with
					*/
					template<typename T2>
					inline BasicMatrix<T, rows, cols>& operator*=(const T2 scalar)
					{
						for (int i = 0; i < m(); i++)
							for (int j = 0; j < n(); j++)
								data[i][j] = (T)(peek(i, j) * scalar);
						return *this;
					}

					/*
						Adds the given matrix to this one
						* @param[in] obj The matrix to add to this one
					*/
					template<typename T2>
					inline BasicMatrix<T, rows, cols>& operator+=(const BasicMatrix<T2, rows, cols>& obj)
					{
						for (int i = 0; i < m(); i++)
							for (int j = 0; j < n(); j++)
								data[i][j] = (T)(peek(i, j) + obj.peek(i, j));
						return *this;
					}

					/*
						Subtracts the given matrix from this one
						* @param[in] obj The matrix to subtract from this one
					*/
					template<typename T2>
					inline BasicMatrix<T, rows, cols>& operator-=(const BasicMatrix<T2, rows, cols>& obj)
					{
						for (int i = 0; i < m(); i++)
							for (int j = 0; j < n(); j++)
								data[i][j] = (T)(peek(i, j) - obj.peek(i, j));
						return *this;
					}

					/*
						Creates a matrix filled with random numbers in the range [0, 1)
					*/
					inline static BasicMatrix<T, rows, cols> rand()
					{
						BasicMatrix<T, rows, cols> out;
						for (int i = 0; i < rows; i++)
							for (int j = 0; j < cols; j++)
								out[i][j] = (T)random();
						return out;
					}

					/*
						Creates a matrix filled with zeros
					*/
					inline static BasicMatrix<T, rows, cols> zeros()
					{
						BasicMatrix<T, rows, cols> out;
						for (int i = 0; i < rows; i++)
							for (int j = 0; j < cols; j++)
								out[i][j] = (T)0;
						return out;
					}

					/*
						Creates an identity matrix
					*/
					inline static BasicMatrix<T, rows, cols> identity()
					{
						BasicMatrix<T, rows, cols> out;
						for (int i = 0; i < rows; i++)
							for (int j = 0; j < cols; j++)
								out[i][j] = (T)((i == j) ? 1 : 0);
						return out;
					}

					/*
						Creates a rotation martirx for a 2d rotation around the z-axis
						* @param[in] angle The angle of the rotation in radians
					*/
					template<typename T2>
					inline static BasicMatrix<T, 2, 2> rotation(const T2 angle)
					{
						return BasicMatrix<T, 2, 2>({
							{ (T)cos((double)angle), (T)sin((double)angle) },
							{ (T)-sin((double)angle), (T)cos((double)angle) }
						});

					}

					/*
						Creates a rotation matrix for a 3d rotation of the given angle around the given axis
						* @param[in] angle The angle of the rotation in radians
						* @param[in] axis The axis to rotate around
					*/
					template<typename T2, typename T3>
					inline static BasicMatrix<T, 3, 3> rotation(const T2 angle, const BasicVector<T3, 3>& axis)
					{
						const BasicVector<T, 3> zAxis = normalize(axis);

						T dotVal;
						if (abs(dotVal = dot(zAxis, BasicVector<T, 3>(1, 0, 0))) == 1)
							return BasicMatrix<T, 3, 3>({
								{ 1, 0, 0 },
								{ 0, (T)cos((double)angle), (T)sin((double)angle) },
								{ 0, (T)-sin((double)angle), (T)cos((double)angle) }
							}) *= dotVal;
						else if (abs(dotVal = dot(zAxis, BasicVector<T, 3>(0, 1, 0))) == 1)
							return BasicMatrix<T, 3, 3>({
								{ (T)cos((double)angle), 0, (T)-sin((double)angle) },
								{ 0, 1, 0 },
								{ (T)sin((double)angle), 0, (T)cos((double)angle) }
							}) *= dotVal;
						else if (abs(dotVal = dot(zAxis, BasicVector<T, 3>(0, 0, 1))) == 1)
							return BasicMatrix<T, 3, 3>({
								{ (T)cos((double)angle), (T)sin((double)angle), 0 },
								{ (T)-sin((double)angle), (T)cos((double)angle), 0 },
								{ 0, 0, 1 }
							}) *= dotVal;
						else
						{
							const BasicVector<T, 3> yAxis = { 0, 1, 0 };
							const BasicVector<T, 3> xAxis = cross(yAxis, zAxis);

							const BasicMatrix<T, 3, 3> transform = {
								{ xAxis.peek(0), yAxis.peek(0), zAxis.peek(0) },
								{ xAxis.peek(1), yAxis.peek(1), zAxis.peek(1) },
								{ xAxis.peek(2), yAxis.peek(2), zAxis.peek(2) }
							};

							const BasicMatrix<T, 3, 3> zRotation = {
								{ (T)cos((double)angle), (T)sin((double)angle), 0 },
								{ (T)-sin((double)angle), (T)cos((double)angle), 0 },
								{ 0, 0, 1 }
							};

							return inv(transform) * zRotation * transform;
						}

					}

					/*
						Creates an orthogonal projection matrix
						* @param[in] left The left clipping pane
						* @param[in] right The right clipping pane
						* @param[in] bottom The bottom clipping pane
						* @param[in] top The top clipping pane
						* @param[in] zNear The near clipping pane
						* @param[in] zFar The far clipping pane
					*/
					inline static BasicMatrix<T, 4, 4> ortho(const T left, const T right, const T bottom, const T top, const T zNear, const T zFar)
					{
						return BasicMatrix<T, 4, 4>({
							{ (T)(2.0 / (right - left)), 0, 0, 0 },
							{ 0, (T)(2.0 / (top - bottom)), 0, 0 },
							{ 0, 0, (T)(-2.0 / (zFar - zNear)), 0 },
							{ (T)(-(right + left) / (right - left)), (T)(-(top + bottom) / (top - bottom)), (T)(-(zFar + zNear) / (zFar - zNear)), 1 }
						});

					}

					/*
						Creates a standard camera projection matrix
						* @param[in] fov The field of view in degrees
						* @param[in] aspect The aspect ratio
					*/
					inline static BasicMatrix<T, 4, 4> projection(const T fov, const T aspect, const T zNear, const T zFar)
					{
						const T top = zNear * tan(radians(fov * 0.5));
						const T bottom = -top;
						const T right = top * aspect;
						const T left = -right;

						return BasicMatrix<T, 4, 4>({
							{ (T)(2.0 * zNear / (right - left)), 0, 0, 0 },
							{ 0, (T)(2.0 * zNear / (top - bottom)), 0, 0 },
							{ (T)((right + left) / (right - left)), (T)((top + bottom) / (top - bottom)), (T)(-((zFar + zNear) / (zFar - zNear))), -1 },
							{ 0, 0, (T)(-(2.0 * zFar * zNear / (zFar - zNear))), 0 }
						});

					}

					/**
						Creates a look-at matrix
						* @param[in] eye the eye position in world space
						* @param[in] target the look at target in world space
						* @param[in] up the upwards vector, standard (0, 1, 0), changes rarely
					*/
					template<typename T2, typename T3, typename T4>
					inline static BasicMatrix<T, 4, 4> lookAt(const BasicVector<T2, 3>& eye, const BasicVector<T3, 3>& target, const BasicVector<T4, 3>& up)
					{
						const BasicVector<T2, 3> zAxis = normalize(eye - target);
						const BasicVector<T4, 3> nUp = normalize(up);
						const T4 upZDiff = dot(nUp, zAxis);

						BasicVector<T4, 3> xAxis;
						if (upZDiff == 1)
							xAxis = { 0, 0, -1 };
						else if (upZDiff == -1)
							xAxis = { 0, 0, 1 };
						else
							xAxis = cross(nUp, zAxis);

						const BasicVector<T2, 3> yAxis = cross(zAxis, xAxis);

						return BasicMatrix<T, 4, 4>({
							{ (T)xAxis.peek(0), (T)yAxis.peek(0), (T)zAxis.peek(0), 0 },
							{ (T)xAxis.peek(1), (T)yAxis.peek(1), (T)zAxis.peek(1), 0 },
							{ (T)xAxis.peek(2), (T)yAxis.peek(2), (T)zAxis.peek(2), 0 },
							{ (T)(-dot(xAxis, eye)), (T)(-dot(yAxis, eye)), (T)(-dot(zAxis, eye)), 1 }
						});

					}

				};

				/*
					Calculates the dot product of the two vectors
					* @param[in] a The first vector
					* @param[in] b The second vector
				*/
				template<typename T, typename T2, int dim>
				inline T dot(const BasicVector<T, dim>& a, const BasicVector<T2, dim>& b)
				{
					T dotVal = 0;
					for (int i = 0; i < dim; i++)
						dotVal = (T)(dotVal + a.peek(i) * b.peek(i));
					return dotVal;
				}

				/*
					Calculates the length of the vector
					* @param[in] a The vector to calculate the length of
				*/
				template<typename T, int dim>
				inline T length(const BasicVector<T, dim>& a)
				{
					return (T)sqrt(dot(a, a));
				}

				/*
					Calculates the length of the vector
					* @param[in] a The vector to calculate the length of
				*/
				template<int dim>
				inline float length(const BasicVector<float, dim>& a)
				{
					return sqrtf(dot(a, a));
				}

				/*
					Calculates the length of the vector
					* @param[in] a The vector to calculate the length of
				*/
				template<int dim>
				inline long double length(const BasicVector<long double, dim>& a)
				{
					return sqrtl(dot(a, a));
				}

				/*
					Copies the given vector and normalizes it (the copy)
					* @param[in] a The vector to normalize
				*/
				template<typename T, int dim>
				inline BasicVector<T, dim> normalize(const BasicVector<T, dim>& a)
				{
					return a * (1.0 / length(a));
				}

				/*
					Copies and multiplies the vector (the copy) with the given scalar
					* @param[in] scalar The scalar
					* @param[in] a The vector
				*/
				template<typename T, typename T2, int dim>
				inline BasicVector<T, dim> operator*(const T2 scalar, const BasicVector<T, dim>& a)
				{
					return BasicVector<T, dim>(a) *= scalar;
				}

				/*
					Copies and multiplies the vector (the copy) with the given scalar
					* @param[in] a The vector
					* @param[in] scalar The scalar
				*/
				template<typename T, typename T2, int dim>
				inline BasicVector<T, dim> operator*(const BasicVector<T, dim>& a, const T2 scalar)
				{
					return scalar * a;
				}

				/*
					Adds the two given vectors
					* @param[in] a The first vector
					* @param[in] b The second vector
				*/
				template<typename T, typename T2, int dim>
				inline BasicVector<T, dim> operator+(const BasicVector<T, dim>& a, const BasicVector<T2, dim>& b)
				{
					return BasicVector<T, dim>(a) += b;
				}

				/*
					Subtracts the second vector from the first and returns the resulting vector
					* @param[in] a The first vector
					* @param[in] b The second vector
				*/
				template<typename T, typename T2, int dim>
				inline BasicVector<T, dim> operator-(const BasicVector<T, dim>& a, const BasicVector<T2, dim>& b)
				{
					return BasicVector<T, dim>(a) -= b;
				}

				/*
					Fills the given vector with the given value
					* @param[out] a The vector to fill
					* @param[in] value The value to fill the vector with
				*/
				template<typename T, typename T2, int dim>
				inline void fill(BasicVector<T, dim>& a, const T2 value)
				{
					for (int i = 0; i < dim; i++)
						a[i] = (T)value;
				}

				/*
					Calculates the cross product of the given vectors
					* @param[in] a The first vector
					* @param[in] b The second vector
				*/
				template<typename T, typename T2>
				inline BasicVector<T, 3> cross(const BasicVector<T, 3>& a, const BasicVector<T2, 3>& b)
				{
					BasicVector<T, 3> out;
					out[0] = a.peek(1) * b.peek(2) - a.peek(2) * b.peek(1);
					out[1] = a.peek(2) * b.peek(0) - a.peek(0) * b.peek(2);
					out[2] = a.peek(0) * b.peek(1) - a.peek(1) * b.peek(0);
					return out;
				}

				/*
					Calculates the determinant of the given matrix
					* @param[in] a The matrix
				*/
				template<typename T, int dim>
				inline T det(const BasicMatrix<T, dim, dim>& a)
				{
					if (dim == 1)
						return a.peek(0, 0);
					else if (dim == 2)
						return a.peek(0, 0) * a.peek(1, 1) - a.peek(1, 0) * a.peek(0, 1);
					else {
						T val = 1;
						BasicMatrix<T, dim, dim> temp = a;

						for (int e = 0; e < dim - 1; e++)
							for (int r = e + 1; r < dim; r++)
							{
								T multiple = temp.peek(r, e) / temp.peek(e, e);
								for (int c = e; c < dim; c++)
									temp[r][c] -= multiple * temp.peek(e, c);
							}
						for (int i = 0; i < dim; i++)
							val *= temp.peek(i, i);
						return val;
					}

				}

				/*
					Horizontally concatenates the given matrix and the given vector, in the given order
					* @param[in] a The matrix
					* @param[in] b The vector
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows, cols + 1> horzCat(const BasicMatrix<T, rows, cols>& a, const BasicVector<T2, rows>& b)
				{
					BasicMatrix<T, rows, cols + 1> out;
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
							out[i][j] = a.peek(i, j);

					for (int i = 0; i < rows; i++)
						out[i][cols] = b.peek(i);
					return out;
				}

				/*
					Horizontally concatenates the given vector and the given matrix, in the given order
					* @param[in] a The vector
					* @param[in] b The matrix
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows, cols + 1> horzCat(const BasicVector<T2, rows>& a, const BasicMatrix<T, rows, cols>& b)
				{
					BasicMatrix<T, rows, cols + 1> out;
					for (int i = 0; i < rows; i++)
						out[i][0] = a.peek(i);

					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
							out[i][j + 1] = b.peek(i, j);
					return out;
				}

				/*
					Vertically concatenates the given matrix and the given vector, in the given order
					* @param[in] a The matrix
					* @param[in] b The vector
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows + 1, cols> vertCat(const BasicMatrix<T, rows, cols>& a, const BasicVector<T2, cols>& b)
				{
					BasicMatrix<T, rows + 1, cols> out;
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
							out[i][j] = a.peek(i, j);

					for (int j = 0; j < cols; j++)
						out[rows][j] = b.peek(j);
					return out;
				}

				/*
					Vertically concatenates the given vector and the given matrix, in the given order
					* @param[in] a The vector
					* @param[in] b The matrix
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows + 1, cols> vertCat(const BasicVector<T2, cols>& a, const BasicMatrix<T, rows, cols>& b)
				{
					BasicMatrix<T, rows + 1, cols> out;
					for (int j = 0; j < cols; j++)
						out[0][j] = a.peek(j);

					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
							out[i + 1][j] = b.peek(i, j);
					return out;
				}

				/*
					Runs a partial gauss elimination
					* @param[in/out] a The matrix to partially reduce
				*/
				template<typename T, int dim>
				inline void partialGauss(BasicMatrix<T, dim, dim>& a)
				{
					int indices[dim];
					partialGauss(a, indices);
				}

				/*
					Runs a partial gauss elimination and stores the pivoting elements in the given array
					* @param[in/out] a The matrix to partially reduce
					* @param[out] index The array of pivot element indices for each row
				*/
				template<typename T, int dim>
				void partialGauss(BasicMatrix<T, dim, dim>& a, int* index)
				{
					for (int i = 0; i < dim; i++)
						index[i] = i;

					//Rescaling factors
					T c[dim];
					for (int i = 0; i < dim; i++)
					{
						T c1 = 0;
						for (int j = 0; j < dim; j++)
						{
							T c0 = abs(a[i][j]);
							if (c0 > c1)
								c1 = c0;
						}
						c[i] = c1;
					}

					//Pivoting element
					int k = 0;
					for (int j = 0; j < dim - 1; j++)
					{
						T pi1 = 0;
						for (int i = j; i < dim; i++)
						{
							T pi0 = abs(a[index[i]][j]);
							pi0 /= c[index[i]];

							if (pi0 > pi1)
							{
								pi1 = pi0;
								k = i;
							}

						}

						std::swap(index[j], index[k]);
						for (int i = j + 1; i < dim; i++)
						{
							T pj = (a[index[i]][j] /= a[index[j]][j]);
							for (int l = j + 1; l < dim; l++)
								a[index[i]][l] -= pj * a[index[i]][l];
						}

					}

				}

				/*
					Calculates and retruns the inverse of the given matrix
					* @param[in] a The matrix to invert
				*/
				template<typename T, int dim>
				BasicMatrix<T, dim, dim> inv(const BasicMatrix<T, dim, dim>& a)
				{
					int index[dim];
					BasicMatrix<T, dim, dim> out;
					BasicMatrix<T, dim, dim> cloned = a;

					T bi[dim][dim];
					for (int i = 0; i < dim; i++)
						for (int j = 0; j < dim; j++)
							bi[i][j] = (i == j);

					partialGauss(cloned, index);

					for (int i = 0; i < dim - 1; i++)
						for (int j = i + 1; j < dim; j++)
							for (int k = 0; k < dim; k++)
								bi[index[j]][k] -= cloned[index[j]][i] * bi[index[i]][k];

					for (int i = 0; i < dim; i++)
					{
						out[dim - 1][i] = bi[index[dim - 1]][i] / cloned[index[dim - 1]][dim - 1];

						for (int j = dim - 2; j >= 0; j--)
						{
							out[j][i] = bi[index[j]][i];

							for (int k = j + 1; k < dim; k++)
								out[j][i] -= cloned[index[j]][k] * out[k][i];
							out[j][i] /= cloned[index[j]][j];
						}

					}

					return out;
				}

				/*
					Produces a reduced row-echelon version of the given matrix
					* @param[in] a The matrix to produce a reduced form of
				*/
				template<typename T, int rows, int cols>
				inline BasicMatrix<T, rows, cols> rref(const BasicMatrix<T, rows, cols>& a)
				{
					const int pivots = min(rows, cols);
					int rIndex[rows];
					for (int i = 0; i < rows; i++)
						rIndex[i] = i;

					BasicMatrix<T, rows, cols> cloned = a;

					int cMrk = 0;
					for (int p = 0; p < pivots && cMrk < cols; p++, cMrk++)
					{
						for (int j = cMrk; j < cols; j++)
							for (int i = p; i < rows; i++)
								if (abs(cloned[rIndex[i]][j]) > SEG_API_VECMATH_ZERO_OFFSET)
								{
									std::swap(rIndex[i], rIndex[p]);
									cMrk = j;
									j = cols;
									break;
								}

						const T pivotValInv = (T)(1.0l / cloned[rIndex[p]][cMrk]);

						for (int j = cMrk; j < cols; j++)
							cloned[rIndex[p]][j] *= pivotValInv;

						for (int i = 0; i < rows; i++)
							if (i != p)
							{
								const T rowVal = (T)cloned[rIndex[i]][cMrk];
								for (int j = cMrk; j < cols; j++)
									cloned[rIndex[i]][j] -= cloned[rIndex[p]][j] * rowVal;
							}

					}

					BasicMatrix<T, rows, cols> out;
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
								out[i][j] = cloned[rIndex[i]][j];
					return out;
				}

				/*
					Creates and returns the transpose of the given matrix
					* @param[in] a The matrix to transpose
				*/
				template<typename T, int rows, int cols>
				inline BasicMatrix<T, cols, rows> transpose(const BasicMatrix<T, rows, cols>& a)
				{
					BasicMatrix<T, cols, rows> out;
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
							out[j][i] = a.peek(i, j);
					return out;
				}

				/*
					Adds the given matrices
					* @param[in] a The first matrix
					* @param[in] b The second matrix
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows, cols> operator+(const BasicMatrix<T, rows, cols>& a, const BasicMatrix<T2, rows, cols>& b)
				{
					return BasicMatrix<T, rows, cols>(a) += b;
				}

				/*
					Subtracts second matrix from the first
					* @param[in] a The first matrix
					* @param[in] b The second matrix
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows, cols> operator-(const BasicMatrix<T, rows, cols>& a, const BasicMatrix<T2, rows, cols>& b)
				{
					return BasicMatrix<T, rows, cols>(a) -= b;
				}

				/*
					Multiplies the given matrix by the given scalar
					* @param[in] scalar The scalar
					* @param[in] a The matrix
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows, cols> operator*(const T2 scalar, const BasicMatrix<T, rows, cols>& a)
				{
					return BasicMatrix<T, rows, cols>(a) *= scalar;
				}

				/*
					Multiplies the given matrix by the given scalar
					* @param[in] a The matrix
					* @param[in] scalar The scalar
				*/
				template<typename T, typename T2, int rows, int cols>
				inline BasicMatrix<T, rows, cols> operator*(const BasicMatrix<T, rows, cols>& a, const T2 scalar)
				{
					return scalar * a;
				}

				/*
					Multiplies the given matrices
					* @param[in] a The first matrix
					* @param[in] b The second matrix
				*/
				template<typename T, typename T2, int rows, int colsA, int colsB>
				inline BasicMatrix<T, rows, colsB> operator*(const BasicMatrix<T, rows, colsA>& a, const BasicMatrix<T2, colsA, colsB>& b)
				{
					BasicMatrix<T, rows, colsB> out;
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < colsB; j++)
							out[i][j] = dot(a.row(i), b.column(j));
					return out;
				}

				/*
					Fills the matrix with the given value
					* @param[in] a The matrix
					* @param[in] value The value
				*/
				template<typename T, typename T2, int rows, int cols>
				inline void fill(BasicMatrix<T, rows, cols>& a, const T2 value)
				{
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
							a[i][j] = (T)value;
				}

#ifndef SEG_API_VECMATH_NO_TYPEDEFS

				template<int dim> using Vector = BasicVector<double, dim>;
				template<int dim> using Vectorf = BasicVector<float, dim>;
				template<int dim> using Vectorl = BasicVector<long double, dim>;
				using vec2 = Vector<2>;
				using vec3 = Vector<3>;
				using vec4 = Vector<4>;
				using vec2f = Vectorf<2>;
				using vec3f = Vectorf<3>;
				using vec4f = Vectorf<4>;
				using vec2l = Vectorl<2>;
				using vec3l = Vectorl<3>;
				using vec4l = Vectorl<4>;

				template<int rows, int cols> using Matrix = BasicMatrix<double, rows, cols>;
				template<int rows, int cols> using Matrixf = BasicMatrix<float, rows, cols>;
				template<int rows, int cols> using Matrixl = BasicMatrix<long double, rows, cols>;
				using mat2 = Matrix<2, 2>;
				using mat3 = Matrix<3, 3>;
				using mat4 = Matrix<4, 4>;
				using mat2f = Matrixf<2, 2>;
				using mat3f = Matrixf<3, 3>;
				using mat4f = Matrixf<4, 4>;
				using mat2l = Matrixl<2, 2>;
				using mat3l = Matrixl<3, 3>;
				using mat4l = Matrixl<4, 4>;

#endif
			}

		}

	}

}
