#pragma once
#include <iostream>

namespace miit::vector
{

	class Vector final
	{
	public:

		/**
		@brief Создание vector'a по initializer_list
		@param list Лист по которому строится vector
		*/
		Vector(const std::initializer_list<int> list);

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
		void append(int value);

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
		int find(int value) const;

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
		int& operator[](int index);

		/**
		@brief Перегрузка оператора копирования
		@param Vector Вектор для копирования
		@return Скопированный объект типа Vector
		*/
		Vector& operator=(const Vector& vector);

		/*
		@brief Перегрузка move оператора
		@param Vector Список для мува
		@return Объект типа DLList
		*/
		Vector& operator=(Vector&& vector) noexcept;

		/**
		@brief Move конструктор
		@param vector Вектор для мува
		*/
		Vector(const Vector& vector);

		/**
		@brief Конструктор копирования
		@param vector Вектор для копирования
		*/
		Vector(Vector&& vector) noexcept;

		/*
		@brief Перегрузка оператора вывода
		@param os Поток вывода
		@param vector Вектор для вывода
		*/
		friend std::ostream& operator<<(std::ostream& os, Vector& vector) noexcept;

		/**
		@brief Перегрузка оператора равно
		@param rha Первый аргумент для сравнения
		@param lha Второй аргумент для сравнения
		@return false если равны и true если нет
		*/
		friend bool operator==(const Vector& rha, const Vector& lha) noexcept;

		/**
		@brief Перегрузка оператора не равно
		@param rha Первый аргумент для сравнения
		@param lha Второй аргумент для сравнения
		@return true если равны и false если нет
		*/
		friend bool operator!=(const Vector& rha, const Vector& lha) noexcept;

		/**
		@brief Преобразование объета в строку
		@return строка полученная из объекта
		*/
		std::string to_string() const noexcept;

	private:
		size_t size;
		int* values;

	};
};