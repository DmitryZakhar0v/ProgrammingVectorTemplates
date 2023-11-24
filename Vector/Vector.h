#pragma once
#include <iostream>
#include <sstream>

namespace miit::vector
{

	template<typename T> class Vector;

	/**
	@brief Опрератор сдвига.
	@param os Поток вывода.
	@param vector Вектор для вывода.
	@return Изменённый поток вывода.
	*/
	template<typename T>
	std::ostream& operator<< (std::ostream& os, const Vector<T>& vector);

	/**
	@brief Перегрузка оператора равно
	@param rha Первый аргумент для сравнения
	@param lha Второй аргумент для сравнения
	@return false если равны и true если н ет
	*/
	template<typename T>
	bool operator==(const Vector<T>& rha, const Vector<T>& lha) noexcept;

	/**
	@brief Перегрузка оператора не равно
	@param rha Первый аргумент для сравнения
	@param lha Второй аргумент для сравнения
	@return true если равны и false если нет
	*/
	template<typename T>
	bool operator!=(const Vector<T>& rha, const Vector<T>& lha) noexcept;

	template<typename T>
	class Vector final
	{
	public:

		/**
		@brief Создание vector'a по initializer_list
		@param list Лист по которому строится vector
		*/
		Vector(const std::initializer_list<T> list);
		

		/**
		@brief Чистит памать за vector
		*/
		~Vector();

		/**
		@brief Получение длинны vector'a
		@return Количество элементов vector'a
		*/
		size_t get_size() const;

		/**
		@brief Добавление элемента в вектор
		@param Значение элемента
		*/
		void append(const T& value);

		/**
		@brief Получение индекса элемента в списке
		@param value Искомое значение
		@return индекс элемента если он есть в vector и -1 если его в нем нет
		*/
		bool find(const T& value) const;

		/**
		@brief Получение информации об наличии элементов в vector
		@return true если есть элементы и false если нет
		*/
		bool has_elements() const;

		/**
		@brief Перегрузка оператора квадратные скобки
		@param index Индекс элемента в векторе
		@return Элемент из вектора
		*/
		T& operator[](size_t index);

		/**
		@brief Перегрузка оператора квадратные скобки для конастантного объекта
		@param index Индекс элемента в векторе
		@return Элемент из вектора
		*/
		const T& operator[](size_t index) const;

		/**
		@brief Перегрузка оператора копирования
		@param Vector Вектор для копирования
		@return Скопированный объект типа Vector
		*/
		Vector<T>& operator=(const Vector<T>& vector);

		/*
		@brief Перегрузка оператора перемещения
		@param Vector Список для перемещения
		@return Объект типа DLList
		*/
		Vector<T>& operator=(Vector<T>&& vector) noexcept;

		/**
		@brief Move конструктор
		@param vector Вектор для перемещения
		*/
		Vector(const Vector<T>& vector);

		/**
		@brief Конструктор копирования
		@param vector Вектор для копирования
		*/
		Vector(Vector<T>&& vector) noexcept;

		/**
		@brief Преобразование объета в строку
		@return строка полученная из объекта
		*/
		std::string to_string() const noexcept;

	private:
		size_t size;
		T* values;

	};
	
	template<typename T>
	inline Vector<T>::Vector(const std::initializer_list<T> list)
		:size(0)
	{
		for (auto& value : list)
		{
			this->append(value);
		}
	}


	template<typename T>
	inline Vector<T>::~Vector()
	{
		delete[] this->values;
		this->values = nullptr;
	}

	template<typename T>
	inline size_t Vector<T>::get_size() const
	{
		return this->size;
	}

	template<typename T>
	void Vector<T>::append(const T& value)
	{
		T* temp = new T[this->size + 1];
		std::copy(this->values, this->values + this->size, temp);
		temp[this->size] = value;
		delete[] this->values;
		std::swap(temp, this->values);
		this->size++;
	}

	template<typename T>
	Vector<T>::Vector(Vector<T>&& vector) noexcept
		:size(0), values(nullptr)
	{
		std::swap(vector.values, this->values);
		std::swap(vector.size, this->size);
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& vector) noexcept
	{
		if (*this != vector)
		{
			std::swap(vector.values, this->values);
			std::swap(vector.size, this->size);
		}
		return *this;
	}
	
	template<typename T>
	Vector<T>::Vector(const Vector<T>& vector)
		:size(0), values(nullptr)
	{
		Vector temp{};
		for (int i = 0; i < vector.get_size(); i++)
		{
			this->append(temp.values[i]);
		}
		std::swap(this->values, temp.values);
		std::swap(this->size, temp.size);
	}
	
	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector& vector)
	{
		if (*this != vector) 
		{
			Vector temp{};
			for (int i = 0; i < vector.get_size(); i++)
			{
				this->append(temp.values[i]);
			}
			std::swap(this->values, temp.values);
			std::swap(this->size, temp.size);
		}
		return *this;
	}
	
	template<typename T>
	bool Vector<T>::find(const T& value) const
	{
		for (size_t i = 0; i < this->get_size(); i++) 
		{
			if (value == this->values[i])
			{
				return true;
			}
		}
		return false;
	}
	
	template<typename T>
	inline bool Vector<T>::has_elements() const
	{
		return this->size != 0;
	}

	template<typename T>
	inline T& Vector<T>::operator[](size_t index)
	{
		if (!this->has_elements() || index >= this->size)
		{
			throw std::out_of_range("Incorrect Index");
		}
		return this->values[index];
	}

	template<typename T>
	inline const T& Vector<T>::operator[](size_t index) const
	{
		if (!this->has_elements() || index >= this->size)
		{
			throw std::out_of_range("Incorrect Index");
		}
		return this->values[index];
	}

	template<typename T>
	std::string Vector<T>::to_string() const noexcept
	{
		std::stringstream result;
		result << "[ ";
		for (size_t i = 0; i < this->size; i++)
		{
			result << this->values[i] << " ";
		}
		result << "]";
		return result.str();
	}

	template<typename T>
	bool operator==(const Vector<T>& rha, const Vector<T>& lha) noexcept
	{
		return (rha.to_string() == lha.to_string());
	}

	template<typename T>
	bool operator!=(const Vector<T>& rha, const Vector<T>& lha) noexcept
	{
		return !(rha == lha);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vector<T>& vector)
	{
		return os << vector.to_string();
	}
};


