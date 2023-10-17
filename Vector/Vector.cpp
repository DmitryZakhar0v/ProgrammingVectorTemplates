#include "Vector.h"
#include <iostream>
#include <sstream>


miit::vector::Vector::Vector(const std::initializer_list<int> list)
	:size(0)
{
	for (int value : list)
	{
		this->append(value);
	}
}

miit::vector::Vector::~Vector()
{
	delete[] this->values;
	this->values = nullptr;
}

int miit::vector::Vector::get_size() const
{
	return this->size;
}

void miit::vector::Vector::append(int value)
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



bool miit::vector::Vector::is_empty() const
{
	return (this->size == 0);
}

miit::vector::Vector& miit::vector::Vector::operator=(const Vector& vector)
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

miit::vector::Vector& miit::vector::Vector::operator=(Vector&& vector) noexcept
{
	std::swap(vector.values, this->values);
	std::swap(vector.size, this->size);
	return *this;
}

miit::vector::Vector::Vector(const Vector& vector)
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

miit::vector::Vector::Vector(Vector&& vector) noexcept
	:size(0), values(nullptr)
{
	std::swap(vector.values, this->values);
	std::swap(vector.size, this->size);
}

int& miit::vector::Vector::operator[](int index)
{
	if (this->is_empty() || index >= this->size or index < 0)
	{
		throw std::out_of_range("Incorrect Index");
	}
	return this->values[index];
}

void miit::vector::Vector::pop(int index)
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

int miit::vector::Vector::find(int value) const
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



std::string miit::vector::Vector::to_string() const noexcept
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

std::ostream& miit::vector::operator<<(std::ostream& os, Vector& vector) noexcept
{
	return os << vector.to_string();
}

bool miit::vector::operator==(const Vector& rha, const Vector& lha) noexcept
{
	return (rha.to_string() == lha.to_string());
}

bool miit::vector::operator!=(const Vector& rha, const Vector& lha) noexcept
{
	return !(rha == lha);
}
