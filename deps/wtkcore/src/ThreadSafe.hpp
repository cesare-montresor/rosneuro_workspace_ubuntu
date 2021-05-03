#ifndef THREADSAFE_HPP
#define THREADSAFE_HPP

#include "Object.hpp"
#include "Semaphore.hpp"

namespace wtk {
	namespace core {

/*! \brief Thread safe container
 */
template <class T = bool>
class ThreadSafe : public Object {
	public:
		ThreadSafe(void);
		ThreadSafe(T value);
		void Set(T value);
		T Get(void);
		T Get(T reset);
		bool TrySet(T value);
		bool TryGet(T* value);
		bool TryGet(T* value, T reset);
	private:
		T _data;
		Semaphore _semdata;
};

template <class T> 
ThreadSafe<T>::ThreadSafe(void) {
	this->_semdata.Post();
}
		
template <class T> 
ThreadSafe<T>::ThreadSafe(T value) {
	this->_data = value;
	this->_semdata.Post();
}

template <class T> 
void ThreadSafe<T>::Set(T value) {
	this->_semdata.Wait();
	this->_data = value;
	this->_semdata.Post();
}

template <class T> 
T ThreadSafe<T>::Get(void) {
	this->_semdata.Wait();
	T value = this->_data;
	this->_semdata.Post();
	return value;
}

template <class T> 
T ThreadSafe<T>::Get(T reset) {
	this->_semdata.Wait();
	T value = this->_data;
	this->_data = reset;
	this->_semdata.Post();
	return value;
}

template <class T> 
bool ThreadSafe<T>::TrySet(T value) {
	if(this->_semdata.TryWait()) {
		this->_data = value;
		this->_semdata.Post();
		return true;
	}
	return false;
}

template <class T> 
bool ThreadSafe<T>::TryGet(T* value) {
	if(this->_semdata.TryWait()) {
		*value = this->_data;
		this->_semdata.Post();
		return true;
	}
	return false;
}

template <class T> 
bool ThreadSafe<T>::TryGet(T* value, T reset) {
	if(this->_semdata.TryWait()) {
		*value = this->_data;
		this->_data = reset;
		this->_semdata.Post();
		return true;
	}
	return false;
}

	}
}
#endif
