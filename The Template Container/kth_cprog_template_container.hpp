#include <stdexcept>
#include <iostream>
#include <algorithm>  

template <class T>
class Vector {
	static_assert(std::is_move_constructible<T>::value, "type is not move constructible.");
	static_assert(std::is_move_assignable<T>::value, "type is not move assignable.");
	public:
		//Default constructor
        Vector ();
		//Default constructorwith size
		explicit Vector (const std::size_t size);
		//Default constructorwith size and set all index to value
        Vector (const std::size_t size, const T& v);
		//initializer_list constructor
		Vector (const std::initializer_list<T> list);
		//Copy constructor
		Vector (Vector const& v);
		//Move constructor
		Vector (Vector&& v);
		//Destructor
		~Vector ();
		//Copy-Assignment
		Vector& operator= (Vector const& v);
		//Move-Assignment
		Vector& operator= (Vector&& v);
		//Pointer to beginning of the array
		T* begin ();
		//Constant pointer to beginning of the array
		T const* begin () const;
		//pointer to beginning of the array
		T* end ();
		//Constant pointer to beginning of the array
		T const* end () const;
		//Pointer to the sought item
		T* find (T const&);
		//Contant pointer to the sought item
		T const* find(T const&) const;
		//Operator[] read
		T const& operator[] (std::size_t index) const;
		//Operator[] write
		T& operator[] (std::size_t index);
		//Insert item to the end of the array
		void push_back(T item);
		//Insert item to the index location
		void insert (std::size_t index, T item);
		//Remove item from given index
		void erase (std::size_t index);
		//Clear the array, remove everything to the size is 0, but capacty is left
		void clear ();
		//Set all values to 0
		void reset ();
		//Sort items
		void sort(bool);
		//Return size
		std::size_t size () const;
		//Return capacity
		std::size_t capacity () const;

	private:
		void increase_capacity();		//Increase size function when buffer is reached
		std::size_t _size;				//Visiable size
		std::size_t _capacity;			//Buffered size
		T* _data;					//Array
};

//Default constructor (With default of 10 elements)
template <class T>
Vector<T>::Vector () {
	_size = 0;
	_capacity = 0;
	_data = new T[_capacity];
}

//Default constructor with size
template <class T>
Vector<T>::Vector (const size_t capacity){
	_size = capacity;
	_capacity = capacity;
	_data = new T[_capacity];
	reset();
}

//Default constructor with size and set all index to value
template <class T>
Vector<T>::Vector (const size_t capacity, const T& item){
	_capacity = capacity;
	_size = capacity;
	_data = new T[_capacity];
	for (auto i = 0; i < _capacity; i++) {
		_data[i] = item;
	}
}

//initializer_list constructor
template <class T>
Vector<T>::Vector (const std::initializer_list<T> list){
	_size = list.size();
	_capacity = list.size();

	_data = new T[_capacity];
	int n = 0;
	for (auto i : list) {
		_data[n] = i;
        ++n;
    }
}

//Copy constructor
template <class T>
Vector<T>::Vector (Vector const& v){
	_size = v._size;
	_capacity = v._capacity;
	_data = new T[_capacity];
	for (auto i = 0; i < _capacity; i++) {
		_data[i] = v._data[i];
	}

}

//Move constructor
template <class T>
Vector<T>::Vector (Vector&& v){
	_size = v._size;
    _capacity = v._capacity;
	
    std::swap(_data, v._data);

	//delete v
	v._size = 0;
    v._capacity = 0;
	delete[] v._data;
	v._data = nullptr;
}

//Destructor
template <class T>
Vector<T>::~Vector (){
	delete[] _data;
}

//Copy-Assignment
template <class T>
Vector<T>& Vector<T>::operator= (Vector const& v){
	if(&v == this) 		//Check if the your trying to copy yourself
		return *this;

	_size = v._size;
	_capacity = v._capacity;
	delete[] _data;
	_data = new T[_capacity];
	for (std::size_t i = 0; i < _size; i++){
		_data[i] = v._data[i];
	}
	return *this;
}

//Move-Assignment
template <class T>
Vector<T>& Vector<T>::operator= (Vector&& v){
	if (&v == this)		//Check if the your trying to move yourself
		return *this;

	_size = v._size;
	_capacity = v._capacity;

    std::swap(_data, v._data);

	//Reset v
	v._size = 0;
	v._capacity = 0;
	delete[] v._data;
	v._data = nullptr;

	return *this;
}

//
template <class T>
T* Vector<T>::begin (){
	return &_data[0];
}

template <class T>
T const* Vector<T>::begin () const{
	return &_data[0];
}

template <class T>
T* Vector<T>::end (){
    if(_size == 0){
        return &_data[0];
    }
	return &_data[_size];
}

template <class T>
T const* Vector<T>::end () const{
    if(_size == 0){
        return &_data[0];
    }
    return &_data[_size];
}


template <class T>
T* Vector<T>::find (T const& item){
	for (std::size_t i = 0; i < _size; i++){
		if(item == _data[i]){
			return &_data[i];
		}
	}
	return end();
}

template <class T>
T const* Vector<T>::find(T const& item) const{
    for (std::size_t i = 0; i < _size; i++){
        if(item == _data[i]){
            return &_data[i];
        }
    }
    return end();
}

template <class T>
T const& Vector<T>::operator[] (size_t index) const{
	if(index < _size){
		return _data[index];
	}else{
		throw std::out_of_range("indes out_of_range in operator[] // read");
	}
}

template <class T>
T& Vector<T>::operator[] (size_t index){
	if(index < _size){
		return _data[index];
	}else{
		throw std::out_of_range("indes out_of_range in operator[] // write");
	}
}

template <class T>
void Vector<T>::push_back(T item){
	if (_size == _capacity)
        increase_capacity();
	_data[_size] = item;
	++_size;
}

template <class T>
void Vector<T>::insert (size_t index, T item){
    if(index == _size){
        push_back(item);
        return;
    }
    if (index > _size)
        throw std::out_of_range("index out of bounds");
	if (_size == _capacity)
        increase_capacity();
	for (std::size_t i = _size; i > index; --i) {
		_data[i] = _data[i-1];
	}
	++_size;
	_data[index] = item;


}

template <class T>
void Vector<T>::erase (size_t index){			
	if (index >= _size)
		throw std::out_of_range("index out of bounds in erase");
	for (std::size_t i = index; i < _size-1; ++i) {
		_data[i]  = _data[i+1];
	}
	_size--;
}

template <class T>
void Vector<T>::clear (){	
	_size = 0;
}

template <class T>
void Vector<T>::reset (){							
	for(unsigned int i = 0; i < _size; i++){
		_data[i] = { };
	}
}

template <class T>
size_t Vector<T>::size () const{				
	return _size;
}

template <class T>
size_t Vector<T>::capacity () const{
	return _capacity;
}

template <class T>
void Vector<T>::increase_capacity() {
    if(_capacity < 10){
        _capacity = 10;
    }else{
        _capacity = _capacity * 2; //Double the size.
    }


	T* tmp = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		tmp[i] = _data[i];
	}

	std::swap(_data,tmp);

	delete[] tmp;
}

template<class T>
void Vector<T>::sort(bool b){
	if(!b){
		std::reverse(begin(),end());
	}else{
		std::sort(begin(),end());
	}
}

