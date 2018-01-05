//=============================================
//Algoritmos y Programacion II (95.12)
//TP1 - Programacion en C++
//Archivo: vector.h
//Header correspondientes a clase vector
//=============================================
#ifndef _VECTOR_H_INCLUDED_
#define _VECTOR_H_INCLUDED_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>

using namespace std;

template <class T>
class vector;

template <class T>
std::ostream& operator<<(std::ostream &,const vector<T> &);

template <class T>
class vector
{
	private:
		T * array;
		size_t used_size;
		size_t size;
	public:
		vector(size_t l=1);
		vector( const vector <T> & );
		~vector();
		int length();
		const T& operator[](const size_t) const;
		T & operator[](const size_t );		
		vector<T> & operator=(const vector<T> &);
		void set(const int &, const T&);
		void deletelast();
		void append(const T &);
		void swap(const int &,const int &);
		int max();
		int min();
		void extendvector();
	
	friend std::ostream& operator<< <>(std::ostream &,const vector &);
};

template <class T>
vector<T>::vector(size_t l )
{
	if(l<0)
	{
		l=1;
	}
	array=new T[l];
	size=l;
	used_size=0;
}

//Constructor por copia

template <class T>
vector<T> ::vector( const vector <T> & b )
{	
	if( this != &b )
	{
	
	size=b.size;
	used_size=b.used_size;	

	array=new T[size];

	for( int i=0; i< used_size ; i++ )
		array[i]=b.array[i];

	}
}

//Destructor
template <class T>
vector<T>::~vector()
{
	if( array )
	{
		delete [] array;
	}
}

//Metodo que retorna el tamaño utilizado del
//espacio total disponible
template <class T>
int vector<T>::length()
{
	return used_size;
}

//Sobrecarga de operador indexaccion
template <class T>
const T & vector<T>::operator[](const size_t i) const
{
	if(i>used_size)
	{
		exit(EXIT_FAILURE);
	}
	return array[i];
}

//Sobrecarga de operador indexaccion
template <class T>
T & vector<T>::operator[](const size_t i)
{
	if(i<size)
	{
		if(i>=used_size)
		{
			extendvector();
		}	
		return array[i];
	}
	else
	{
		return *array;
	}
}

//Sobrecarga del operador asignacion
template <class T>
vector<T> & vector<T>::operator=(const vector<T> & v)
{
	int i, length, alloc;

	if(this!=&v)
	{
		if(array)
		{
			delete [] array;
		}

		length=v.used_size;

		if (!(alloc=length)){
			alloc=1;		
		}

		array = new T [alloc];

		size=alloc;
		used_size=0;

		for(i=0;i<length;i++)
		{
			append(v.array[i]);
		}
	}
	return *this;
	
}

//Ingresa valor recibido por referencia en el 
//segundo argumento en la posicion "pos" recibida en 
//el primer argumento

template <class T>
void vector<T>::set(const int & pos, const T & data)
{
	if(pos < 0 || pos > used_size )
		return;

	if(pos==used_size )
	{
		if(used_size==size)
		{
			T * temp=new T[size*2];

			std::copy(array, array+size, temp);
			size*=2; 

			delete [] array;
			array = temp;
		}	
	}
	
	array[pos]=data;
	used_size++;
}

//Ingresa el valor recibido por referencia al
//final del vector.

template <class T>
void vector<T>::append(const T & data)
{
	if(used_size==size)
	{       

		T * temp=new T[size*2];
		std::copy(array, array+size, temp);
		size*=2; 
		delete [] array;
		array = temp;
	}

	array[used_size]=data;
	used_size++;
}

//Elimina ultimo elemento del vector

template <class T>
void vector<T>::deletelast()
{
	if(used_size>0)
	{	
		used_size--;
	}	
}

//Intercambia los valores que se encuentran en las
//posiciones a y b del vector ingresadas por argumento

template <class T>
void vector<T>::swap(const int & a,const int & b)
{
	T aux;
	if(a>=0 && a<used_size && b>=0 && b<used_size)
	{	
		if(a==b)
		{
			return;
		}
		aux=array[a];
		array[a]=array[b];
		array[b]=aux;
	}
}
//Retorna por nombre el valor de la posicion 
//donde se encuentra el valor maximo 
//de los valores ingresados.

template <class T>
int vector<T>::max()
{
	int i,max;
	if(used_size>0)
	{
		max=0;
		for(i=1;i<used_size;i++)
		{
			if(array[i]>array[max])
			{
				max=i;
			}
		}
		
	}	
	return max;
}

//Retorna por nombre el valor de la posicion 
//donde se encuentra el valor minimo 
//de los valores ingresados.

template <class T>
int vector<T>::min()
{
	int i,min;
	if(used_size>0)
	{
		min=0;
		for(i=1;i<used_size;i++)
		{
			if(array[i]<array[min])
			{
				min=i;
			}
		}
		
	}	
	return min;
}

//Solicita memoria dinamica para incrementar
//el tamaño actual del vector.

template <class T>
void vector<T>::extendvector()
{
	if(used_size+1 == size)
	{
		T * temp=new T[size*2];

		std::copy(array, array+size, temp);
		size*=2; 

		delete [] array;
		array = temp;
	}
	used_size++;
}

//Sobrecarga del operador de salida "<<"

template <class T>
std::ostream& operator<<(std::ostream & os,const vector<T> & v)
{
	size_t i,l;
	l=v.used_size;

	if(l==1)
	{
		os<<"["<<v[0]<<"]";
		return os;
	}

	for(i=0;i<l;i++)
	{
		if(i==0)
		{
			os<<"["<<v[i];
		}
		else if(i==(l-1))
		{
			os<<","<<v[i]<<"]";
		}
		else
		{
			os<<","<<v[i];
		}	
	}
	return os;
}

#endif
