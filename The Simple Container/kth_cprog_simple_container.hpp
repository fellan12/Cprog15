#include <stdexcept>
#include <iostream>

class UIntVector {
public:
	//Default
	explicit UIntVector(std::size_t size);

	//Constructor using initializer list
	UIntVector(std::initializer_list<unsigned int> list);

	//Copy constructor
	UIntVector(UIntVector const& v);
	
	//Move constructor
	UIntVector(UIntVector&& v);
	
	//Destructor
	~UIntVector();
	
	//Copy-assignment operator
	UIntVector& operator=(const UIntVector& v);
	
	//Move-assignment operator
	UIntVector& operator=(UIntVector&& v);
	
	//Operator [] read
	unsigned int operator[](std::size_t index) const;

	//Operator [] write
	unsigned int& operator[](std::size_t index);	

	//Reset all the elements
	void reset();
	
	//Return the size of the vector
	std::size_t size() const;

private:
	std::size_t _size;
	unsigned int* _data;

};

//Default
UIntVector::UIntVector (std::size_t size) {
	_size = size;
	_data = new unsigned int[size];
	reset();
}

//initializer_list
UIntVector::UIntVector(std::initializer_list<unsigned int> list): _size(list.size()){
	_data = new unsigned int[_size];
	unsigned int n = 0;
	for(unsigned int i : list){
		_data[n] = i;
		n++;
	}
}

//Copy
UIntVector::UIntVector(UIntVector const& v){
	_size = v._size;
	_data = new unsigned int[v._size];
	for (unsigned int i = 0; i < v._size; i++){
		_data[i] = v._data[i];
	}
}

//Move
UIntVector::UIntVector(UIntVector&& v){
	_size = v._size;

	unsigned int * tmp = v._data;
	v._data = _data;
	_data = tmp;

	//Reset v
	v._size = 0;
	delete[] v._data;
	v._data = nullptr;	
}

//Destructor
UIntVector::~UIntVector(){
	delete[] _data;
}

//Copy-assignment
UIntVector& UIntVector::operator=(const UIntVector& v){
	if(&v == this) 		//Check if the your trying to copy yourself
		return *this;

	_size = v._size;
	delete[] _data;
	_data = new unsigned int[v._size];
	for (unsigned int i = 0; i < v._size; i++){
		_data[i] = v._data[i];
	}
	return *this;
}

//Move-assingment
UIntVector& UIntVector::operator=(UIntVector&& v) {
	if (&v == this)		//Check if the your trying to move yourself
		return *this;

	_size = v._size;

	unsigned int * tmp = v._data;
	v._data = _data;
	_data = tmp;

	//Reset v
	v._size = 0;
	delete[] v._data;
	v._data = nullptr;

	return *this;
}

//Operator [] read
unsigned int UIntVector::operator[] (std::size_t index) const {
	if(index < _size){
		return _data[index];
	}else {
		throw std::out_of_range("index out of bounds");
	}
}

//Operator [] write
unsigned int& UIntVector::operator[] (std::size_t index){
	if(index < _size){
		return _data[index];
	}else{
		throw std::out_of_range("index out of bounds");
	}
}

//Reset vector
void UIntVector::reset(){
	for(unsigned int i = 0; i < _size; i++){
		_data[i] = (unsigned int) 0;
	}
}

//Size of vector
size_t UIntVector::size() const{
	return _size;
}