#pragma once
#include <iostream>
#include <sstream>

namespace miit::vector
{
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
		int get_size() const;

		/**
		@brief Добавление элемента в вектор
		@param Значение элемента
		*/
		void append(T value);

		/**
		@brief Удаление элемента из vector по индексу
		@param index Индекс элемента
		*/
		void pop(int index);

		/**
		@brief Получение индекса элемента в списке
		@param value Искомое значение
		@return индекс элемента если он есть в vector и -1 если его в нем нет
		*/
		int find(T value) const;

		/**
		@brief Получение информации об отсутствии элементов в vector
		@return true если есть элементы и false если нет
		*/
		bool is_empty() const;

		/**
		@brief Перегрузка оператора квадратные скобки
		@param index Индекс элемента в векторе
		@return Элемент из вектора
		*/
		T& operator[](int index);

		/**
		@brief Перегрузка оператора копирования
		@param Vector Вектор для копирования
		@return Скопированный объект типа Vector
		*/
		Vector<T>& operator=(const Vector<T>& vector);

		/*
		@brief Перегрузка move оператора
		@param Vector Список для мува
		@return Объект типа DLList
		*/
		Vector<T>& operator=(Vector<T>&& vector) noexcept;

		/**
		@brief Move конструктор
		@param vector Вектор для мува
		*/
		Vector(const Vector<T>& vector);

		/**
		@brief Конструктор копирования
		@param vector Вектор для копирования
		*/
		Vector(Vector<T>&& vector) noexcept;

		/*
		@brief Перегрузка оператора вывода
		@param os Поток вывода
		@param vector Вектор для вывода
		*/
		friend std::ostream& operator<<(std::ostream& os, Vector<T>& vector) noexcept;

		/**
		@brief Перегрузка оператора равно
		@param rha Первый аргумент для сравнения
		@param lha Второй аргумент для сравнения
		@return false если равны и true если нет
		*/
		friend bool operator==(const Vector<T>& rha, const Vector<T>& lha) noexcept;

		/**
		@brief Перегрузка оператора не равно
		@param rha Первый аргумент для сравнения
		@param lha Второй аргумент для сравнения
		@return true если равны и false если нет
		*/
		friend bool operator!=(const Vector<T>& rha, const Vector<T>& lha) noexcept;

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
		for (int value : list)
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
	inline int Vector<T>::get_size() const
	{
		return this->size;
	}

	template<typename T>
	void Vector<T>::append(T value)
	{
		int* new_values = new int[this->size + 1];
		for (size_t i = 0; i < this->size; i++)
		{
			new_values[i] = this->values[i];
		}
		new_values[this->size] = value;
		delete[] this->values;
		this->values = new_values;
		this->size++;
	}


	template<typename T>
	bool Vector<T>::is_empty() const
	{
		return (this->size == 0);
	}

	
	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& vector) noexcept
	{
		std::swap(vector.values, this->values);
		std::swap(vector.size, this->size);
		return *this;
	}

	template<typename T>
	Vector<T>::Vector(const Vector<T>& vector)
		:size(0), values(nullptr)
	{
		if (!this->is_empty())
		{
			delete[] this->values;
			this->values = nullptr;
			this->size = 0;
		}
		for (int i = 0; i < vector.get_size(); i++)
		{
			this->append(vector.values[i]);
		}

	}

	template<typename T>
	Vector<T>::Vector(Vector<T>&& vector) noexcept
		:size(0), values(nullptr)
	{
		std::swap(vector.values, this->values);
		std::swap(vector.size, this->size);
	}

	template<typename T>
	T& Vector<T>::operator[](int index)
	{
		if (this->is_empty() || index >= this->size or index < 0)
		{
			throw std::out_of_range("Incorrect Index");
		}
		return this->values[index];
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector& vector)
	{
		if (!this->is_empty())
		{
			delete[] this->values;
			this->values = nullptr;
			this->size = 0;
		}
		for (int i = 0; i < vector.get_size(); i++)
		{
			this->append(vector.values[i]);
		}
		return *this;
	}

	
	template<typename T>
	void Vector<T>::pop(int index)
	{
		if (this->size == 0 or index < 0 or index >= this->size)
		{
			throw std::out_of_range("Incorrect Index");
		}
		int* vector_1 = new int[this->size - 1];
		size_t current = 0;
		for (size_t i = 0; i < this->size; i++)
		{
			if (i != index)
			{
				vector_1[current] = this->values[i];
				current++;
			}
		}
		delete[] this->values;
		this->values = vector_1;
		this->size--;
	}

	template<typename T>
	int Vector<T>::find(T value) const
	{
		if (this->is_empty())
		{
			return -1;
		}

		int index = 0;
		while ((index < this->size) && this->values[index] != value)
		{
			index++;
		}
		if (index == this->size)
		{
			return -1;
		}
		else
		{
			return index;
		}
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
	std::ostream& operator<<(std::ostream& os, Vector<T>& vector) noexcept
	{
		return os << vector.to_string();
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


};


