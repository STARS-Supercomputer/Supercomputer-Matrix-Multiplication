#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <string>
#include <initializer_list>
/*template<class TYPE>
class vector_iterator : public std::iterator<std::random_access_iterator_tag, TYPE>{
public:
	vector_iterator& operator++(){p++; return *this;}
	TYPE& operator*() {return *p;}
private:
	TYPE* p;
};*/

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
	TYPE* pop_back_col();
	void push_bottom_row(TYPE* i);
	TYPE* pop_bottom_row();

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
	TYPE* front();
	TYPE* top();
	TYPE* back();
	TYPE* bottom();
	void swap(const size_type& row_i,const size_type& col_i,const size_type& row_i, const size_type& col_i);


private:
	size_type _rows,_cols;
	size_type _max_rows, _max_cols;
	TYPE** _array;
protected:
};

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::matrix(){
	_max_rows=8;
	_max_cols=8;
	_rows=0;
	_cols=0
	_array= new TYPE*[_max_rows];
	for(int i=0;i<_max_rows;i++){
		_array= new TYPE[_max_cols];
	}
}

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::matrix(const size_type& max_rows, const size_type& max_cols):
	_max_cols(max_cols), _max_rows(max_rows)
{
	_rows=0;
	_cols=0;
	_array= new TYPE*[_max_rows];
	for(int i=0;i<_max_rows;i++){
		_array= new TYPE[_max_cols];
	}
}

//read:1, compiled:0, tested:0
template <class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::matrix(TYPE** array, const SIZE_TYPE& rows, const SIZE_TYPE& cols):
	_array(array),
	_rows(rows),_max_rows(rows),
	_cols(cols),_max_cols(cols)
{
}

//read:1, compiled:0, tested:0
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
		j=0;
	}
}

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
matrix<TYPE,SIZE_TYPE>::~matrix(){
	for(i=0;i<_max_rows;++i)
		delete [] _array[i];
	delete [] _array;
}

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
void matrix<TYPE,SIZE_TYPE>::push_back_col(TYPE* in, SIZE_TYPE rows=_rows){
	_cols++;
	SIZE_TYPE _old_max_rows=_max_rows;
	SIZE_TYPE _old_max_cols=_max_cols;
	int i=0;
	if(rows>_rows){
		if(rows>_max_rows){
			_max_rows=rows*2;
		}
	}
	if(_cols > _max_cols){
		_max_cols *=2;
		TYPE** temp = new TYPE*[_max_rows];
		for(i=0; i<_max_rows; i++){
			temp[i]=new TYPE[_max_cols];
		}

		for(i=0; i< _old_max_rows; ++i){
			memcpy(temp[i],_array[i],sizeof(TYPE)*_old_max_cols);
		}
		for(;i<rows;++i){
			for(int j=0;j<_cols-1;j++)
				temp[i][j]=0;
		}

		for(i=0; i<_max_rows;i++)
			delete [] _array[i];
		delete [] _array;
		_array = temp;
	}
	for(i=0; i<rows; i++)
		array[i][_cols-1]=in;
	for(;i<_rows;i++)
		array[i][_cols-1]=0;
	if(rows>_rows)_rows=rows;
}

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::pop_back_col(){
	_cols--;
	TYPE temp[_rows];
	for(int i=0; i<_rows; i++)
		temp[i]=_array[i][_cols];
	return temp;
}

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
void matrix<TYPE,SIZE_TYPE>::push_bottom_row(TYPE* in, SIZE_TYPE cols=_cols){
	_rows++;
	SIZE_TYPE _old_max_cols=_max_cols;
	SIZE_TYPE _old_max_rows=_max_rows;
	int i=0;
	if(cols>_cols){
		if(cols>_max_cols){
			_max_cols=cols*2;
		}
	}
	if(_rows > _max_rows){
		_max_rows *=2;
		TYPE** temp = new TYPE[_max_rows];
		for(i=0;i<_max_rows;i++){
			temp[i]=new TYPE[_max_cols];
		}
		for(i=0; i< _old_max_rows; ++i){
			memcpy(temp[i],_array[i],sizeof(TYPE)*_old_max_cols);
		}
		for(;i<rows;++i){
			for(int j=0;j<cols;j++)
				temp[i][j]=0;
		}
		for(i=0; i<_max_rows;i++)
			delete [] _array[i];
		delete [] _array;
		_array = temp;
	}
	for(i=0; i<cols; i++)
		array[_rows-1][i]=in;
	for(;i<_cols;i++)
		array[_rows-1][i]=0;
	if(cols>_cols) _cols=cols;
}

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::pop_bottom_row(){
	_rows--;
	TYPE temp[_cols];
	for(int i=0; i<_cols; i++)
		temp[i]=_array[_rows][i];
	return temp;
}

//read:1, compiled:0, tested:0
template<class TYPE, class SIZE_TYPE>
TYPE& matrix<TYPE,SIZE_TYPE>::at(const SIZE_TYPE& row, const SIZE_TYPE& col){
	return array[row][col];
}
//read:1, compiled:0, tested:0
template<class TYPE,class SIZE_TYPE>
TYPE*& matrix<TYPE,SIZE_TYPE>::operator[](const SIZE_TYPE& row){
	return _array[row];
}
//read:1, compiled:0, tested:0
template<class TYPE,class SIZE_TYPE>
bool matrix<TYPE,SIZE_TYPE>::empty(){
	if(_rows==0 && _cols==0){
		return true;
	}
	return false;
}
//read:1, compiled:0, tested:0

template<class TYPE, class SIZE_TYPE>
typename matrix<TYPE,SIZE_TYPE>::size_type matrix<TYPE,SIZE_TYPE>::capacity_rows(){
	return _max_rows;
}
//read:1, compiled:0, tested:0

template<class TYPE, class SIZE_TYPE>
typename matrix<TYPE,SIZE_TYPE>::size_type matrix<TYPE,SIZE_TYPE>::capacity_cols(){
	return _max_cols;
}
//read:1, compiled:0, tested:0

template<class TYPE, class SIZE_TYPE>
void matrix<TYPE,SIZE_TYPE>::reserve_cols(const SIZE_TYPE& max_cols){
	if(max_cols > _max_cols){
		TYPE** temp = new TYPE*[_max_rows];
		for(int i=0;i<_max_rows;i++){
			temp[i]=new TYPE[max_cols];
		}
		for(int i=0; i< _max_rows; ++i){
			memcpy(temp[i],_array[i],sizeof(TYPE)*_max_cols);
		}
		for(int i=0; i<_max_rows;i++)
			delete [] _array[i];
		delete [] _array;
		_array = temp;
		_max_cols=max_cols;
	}
}
//read:1, compiled:0, tested:0

template<class TYPE, class SIZE_TYPE>
void matrix<TYPE,SIZE_TYPE>::reserve_rows(const SIZE_TYPE& max_rows){
	if(max_rows > _max_rows){
		TYPE** temp = new TYPE*[max_rows];
		for(int i=0;i<max_rows;i++){
			temp[i]=new TYPE[_max_cols];
		}
		for(int i=0; i< _max_rows; ++i){
			memcpy(temp[i],_array[i],sizeof(TYPE)*_max_cols);
		}
		for(int i=0; i<_max_rows;i++)
			delete [] _array[i];
		delete [] _array;
		_array = temp;
		_max_cols=max_cols;
	}
}

//read:1, compiled:0, tested:0

template<class TYPE,class SIZE_TYPE>
typename matrix<TYPE,SIZE_TYPE>::size_type matrix<TYPE,SIZE_TYPE>::size_cols(){
	return _cols;
}
//read:1, compiled:0, tested:0

template<class TYPE,class SIZE_TYPE>
typename matrix<TYPE,SIZE_TYPE>::size_type matrix<TYPE,SIZE_TYPE>::size_cols(){
	return _rows;
}
//read:1, compiled:0, tested:0

template<class TYPE,class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::front(){
	TYPE temp[_rows];
	for(int i=0; i<_rows; i++)
		temp[i]=_array[i][0];
	return temp;
}
//read:1, compiled:0, tested:0

template<class TYPE,class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::back(){
	TYPE temp[_rows];
	for(int i=0; i<_rows; i++)
		temp[i]=_array[i][_cols-1];
	return temp;
}
//read:1, compiled:0, tested:0

template<class TYPE,class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::top(){
	TYPE temp[_cols];
	for(int i=0; i<_cols; i++)
		temp[i]=_array[0][i];
	return temp;
}
//read:1, compiled:0, tested:0

template<class TYPE,class SIZE_TYPE>
TYPE* matrix<TYPE,SIZE_TYPE>::front(){
	TYPE temp[_cols];
	for(int i=0; i<_cols; i++)
		temp[i]=_array[_rows-1][i];
	return temp;
}

//read:1, compiled:0, tested:0

template<class TYPE,class SIZE_TYPE>
void matrix<TYPE,SIZE_TYPE>::swap(const SIZE_TYPE& row_i, const SIZE_TYPE& col_i, const SIZE_TYPE& row_j, const SIZE_TYPE& col_j){
	value_type t=_array[row_i][col_i];
	_array[row_i][col_i]=_array[row_j][col_j];
	_array[row_j][col_j]=t;
}
