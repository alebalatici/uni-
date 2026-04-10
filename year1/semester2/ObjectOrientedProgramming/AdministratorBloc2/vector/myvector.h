#ifndef ADMINISTRATORBLOC_MYVECTOR_H
#define ADMINISTRATORBLOC_MYVECTOR_H
#include <stdexcept>
template <typename TElem>
class MyVector {
private:
    TElem* vector_data;
    size_t vector_size;
    size_t vector_capacity;

    void resize(size_t new_capacity)
    {
        auto* new_data = new TElem[new_capacity];
        for (size_t i = 0; i < vector_size; i++)
        {
            new_data[i] = vector_data[i];
        }
        delete[] vector_data;
        vector_capacity = new_capacity;
        vector_data = new_data;
    }

    public:
    MyVector() : vector_data(nullptr), vector_size(0), vector_capacity(0)
    {
        resize(1);
    }

    ~MyVector()
    {
        delete[] vector_data;
    }

    void push_back(const TElem &elem)
    {
        if (vector_size == vector_capacity)
            resize(vector_capacity * 2);
        vector_data[vector_size++] = elem;
    }

    TElem& at(size_t index)
    {
        if (index >= vector_size)
            throw std::out_of_range("Indexul este in afara limitelor");
        return vector_data[index];
    }

    TElem& operator[](size_t index)
    {
        return vector_data[index];
    }

    const TElem& operator[](size_t index) const
    {
        return vector_data[index];
    }

    [[nodiscard]] size_t size() const
    {
        return vector_size;
    }

    [[nodiscard]] size_t capacity() const
    {
        return vector_capacity;
    }

    TElem* begin()
    {
        return vector_data;
    }

    TElem* end()
    {
        return vector_data + vector_size;
    }

    const TElem* begin() const
    {
        return vector_data;
    }

    const TElem* end() const
    {
        return vector_data + vector_size;
    }

    [[nodiscard]] bool empty() const
    {
        return vector_size == 0;
    }

    void erase(TElem* it)
    {
        if (it < begin() || it >= end())
            throw std::out_of_range("Interatorul este in afara limitelor");

        size_t index = it - vector_data;
        for (size_t i = index; i < vector_size - 1; i++)
        {
            vector_data[i] = vector_data[i + 1];
        }
        vector_size--;
    }

    MyVector(const MyVector& other)
    {
        vector_data = new TElem[other.vector_capacity];
       vector_size = other.vector_size;
        vector_capacity = other.vector_capacity;

        for (size_t i = 0; i < other.vector_size; i++)
            vector_data[i] = other.vector_data[i];
    }

    MyVector& operator=(const MyVector& other)
    {
        if (this != &other)
        {
            delete[] vector_data;
            vector_data = new TElem[other.vector_capacity];
            vector_size = other.vector_size;
            vector_capacity = other.vector_capacity;

            for (size_t i = 0; i < other.vector_size; i++)
                vector_data[i] = other.vector_data[i];
        }
        return *this;
    }

    bool operator==(const MyVector& other) const
    {
        if (vector_size != other.vector_size)
            return false;
        for (size_t i = 0; i < vector_size; i++)
            if (vector_data[i] != other.vector_data[i])
                return false;
        return true;
    }
};
#endif //ADMINISTRATORBLOC_MYVECTOR_H
