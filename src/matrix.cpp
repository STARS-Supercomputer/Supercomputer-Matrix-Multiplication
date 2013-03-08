#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <string>
#include <initializer_list>
template<class TYPE>
class vector_iterator : public std::iterator<std::random_access_iterator_tag, TYPE>{
public:
	vector_iterator& operator++(){p++; return *this;}
	TYPE& operator*() {return *p;}
private:
	TYPE* p;
};

template<class TYPE, class SIZE_TYPE=size_t>
class matrix{
public:
	typedef TYPE value_type;
	typedef SIZE_TYPE size_type;
	typedef vector_iterator<TYPE*> iterator;

	matrix();
	matrix(const size_type& max_rows,const size_type& max_cols)/*:
		_max_cols(max_cols),
		_max_rows(max_rows)*/;
	matrix(TYPE** array, const SIZE_TYPE& rows, const SIZE_TYPE& cols );
	matrix(std::initializer_list<std::initializer_list<TYPE>> array);
	~matrix();

	void push_back_col(TYPE* i);
	TYPE& pop_back_col();
	void push_bottom_row(TYPE* i);
	TYPE& pop_bottom_row();

	TYPE& at(const size_type& row, const size_type& col);
	TYPE*& operator[](const size_type& i);

	//at this point I looked up some stl specification for vectors
	bool empty();
	size_type capacity_rows();
	size_type capacity_cols();
	void reserve_rows(const size_type& t);
	void reserve_cols(const size_type& t);
	size_type size_rows();
	size_type size_cols();
	TYPE*& front();
	TYPE*& back();
	void swap(const size_type$ row_i,const size_type& col_i,const size_type& row_i, const size_type& col_i);


private:
	size_type _rows,_cols;
	size_type _max_rows, _max_cols;
	TYPE** _array;
protected:
};

//O(1)?
template<class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::matrix(){
	_max_rows=8;
	_max_cols=8;
	_rows=0;
	_cols=0
	_array= new TYPE[_max_rows][_max_cols];
}

//O(1)?
template<class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::matrix(const size_type& max_rows, const size_type& max_cols):
	_max_cols(max_cols), _max_rows(max_rows)
{
	_rows=0;
	_cols=0;
	_array= new TYPE[_max_rows][_max_cols];
}
//O(1)?
template <class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::matrix(TYPE** array, const SIZE_TYPE& rows, const SIZE_TYPE& cols):
	_array(array),
	_rows(rows),_max_rows(rows),
	_cols(cols),_max_cols(cols)
{
}
//O(rows*cols)
template <class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::matrix(std::initializer_list<std::initializer_list<TYPE>> array):
	_rows(array.size()),_max_rows(array.size())
{
	_array= new TYPE*[_max_rows];
	unsigned i=0;
	unsigned j=0;
	for(std::initializer_list<TYPE> x : array){
		if(_max_cols<x.size())
			_max_cols=x.size();
	}
	_cols=_max_cols;
	for(std::initializer_list<TYPE> x : array){
		_array[i]= new TYPE[_max_cols];
		for(TYPE y : x){
			_array[i][j++]=y;
		}
		for(;j<_max_cols;){
			_array[i][j++]=(TYPE)0;
		}
		i++;
	}
}

//O(rows)
template<class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::~matrix(){
	for(i=0;i<_max_rows;++i)
		delete [] _array[i];
	delete [] _array;
}


template<class TYPE, class SIZE_TYPE>
void matrix<TYPE,SIZE_TYPE>::push_back_col(TYPE* in, SIZE_TYPE rows=_rows){
	_cols++;
	SIZE_TYPE _old_max_rows=_max_rows;
	int i=0;
	if(rows>_rows){
		if(rows>_max_rows){
			_max_rows=rows*2;
		}
	}
	if(_cols > _max_cols){
		_max_cols *=2;
		TYPE** temp = new TYPE[_max_rows][_max_cols];
		for(i=0; i< _old_max_rows; ++i){
			memcpy(temp[i],_array[i],sizeof(TYPE)*_max_cols);
			
		}
		for(;i<_max_rows;++i){
			if(rows>_rows && rows>=i){
				for(int j=0;j<cols;j++)
					temp[i][j]=0;}
		}

		for(i=0; i<_max_rows;i++)
			delete [] _array[i];
		delete [] _array;
		array = temp;
	}
	for(i=0; i<rows; i++)
		array[i][_cols-1]=i;
	for(;i<_rows;i++)
		array[i][_cols]=0;
	if(rows>_rows)_rows=rows;
}


template<class TYPE, class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::pop_back_col(){
	_cols--;
	TYPE temp[_rows];
	for(int i=0; i<_rows; i++)
		temp[i]=_array[i];
	return temp;
}

template<class TYPE, class SIZE_TYPE>
void matrix<TYPE,SIZE_TYPE>::push_bottom_row(TYPE* in, SIZE_TYPE cols=_cols){
	_rows++;
	if(cols>_cols){
		if(cols>_max_cols){
			_max_cols=cols*2;
		}
		_cols=cols;
	}
	if(_rows > _max_rows){
		_max_rows *=2;
		TYPE** temp = new TYPE[_max_rows][_max_cols];
		for(int i=0; i< _max_rows; ++i){
			memcpy(temp[i],_array[i],sizeof(TYPE)*_max_cols);
			if(&& rows>=i){
				for(int j=0;j<cols;j++)
					temp[i][j]=0;}
		}
		for(i=0; i<_max_rows;i++)
			delete [] _array[i];
		delete [] _array;
		array = temp;
	}
	int i=0;
	for(i=0; i<rows; i++)
		array[i][_cols-1]=i;
	for(;i<_rows;i++)
		array[i][_cols]=0;
	if(cols>_cols) _cols=cols;
}


template<class TYPE, class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::pop_back_row(){
	_cols--;
	TYPE temp[_rows];
	for(int i=0; i<_rows; i++)
		temp[i]=_array[i];
	return temp;
}

//O(1)
template<class TYPE>
TYPE& vector<TYPE>::at(size_t i){
	return array[i];
}
//O(1)
template<class TYPE>
TYPE& vector<TYPE>::operator[](size_t i){
	return array[i];
}
//O(1)
template<class TYPE>
bool vector<TYPE>::empty(){
	if(length==0){
		return true;
	}
	return false;
}
//O(1)
template<class TYPE>
typename vector<TYPE>::size_type vector<TYPE>::capacity(){
	return max;
}
//O(n)
template<class TYPE>
void vector<TYPE>::reserve(size_type t){
	if(t > max){
		max =t;
		TYPE* temp = new TYPE[max];
		memcpy(temp, array, sizeof(TYPE)*length);
		delete [] array;
		array = temp;
	}
}
//O(1)
template<class TYPE>
typename vector<TYPE>::size_type vector<TYPE>::size(){
	return length;
}
//O(1)
template<class TYPE>
TYPE& vector<TYPE>::front(){
	return array[0];
}
//O(1)
template<class TYPE>
TYPE& vector<TYPE>::back(){
	return array[length-1];
}
//O(1)
template<class TYPE>
void vector<TYPE>::swap(size_type i, size_type j){
	value_type t=array[i];
	array[i]=array[j];
	array[j]=t;
}
