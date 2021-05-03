#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <stdlib.h>

namespace wtk {
	namespace core {

template <class Sender>
class Callback0 {
	public:
		Callback0(void) {
			this->_method = NULL;
			this->_instance = NULL;
		}
		
		typedef void (Sender::*Method)(void);
		
		virtual void Execute(void) const {
			if(IsRegistered() == false)
				return;  
			(this->_instance->*_method)();
		}

		void Register(Sender *instance, Method function) {
			this->_method = function;
			this->_instance = instance;
		}

		bool IsRegistered(void) const {
			return (this->_instance != NULL);
		}

	private:
		Sender *_instance;
		Method _method;
};

/*! \brief Callback template class
 *
 * Implements a 1 argument callback.
 */
template <class Sender, typename Arg>
class Callback1 {
	public:
		Callback1(void) {
			this->_method = NULL;
			this->_instance = NULL;
		}
		
		typedef void (Sender::*Method)(Arg argument);
		
		virtual void Execute(Arg argument) const {
			if(IsRegistered() == false)
				return;  
			(this->_instance->*_method)(argument);
		}

		void Register(Sender *instance, Method function) {
			this->_method = function;
			this->_instance = instance;
		}

		bool IsRegistered(void) const {
			return (this->_instance != NULL);
		}

	private:
		Sender *_instance;
		Method _method;
};

/*! \brief Callback template class
 *
 * Implements a 2 arguments callback.
 */
template <class Sender, typename Arg1, typename Arg2>
class Callback2 {
	public:
		Callback2(void) {
			this->_method = NULL;
			this->_instance = NULL; 
		}

		typedef void (Sender::*Method)(Arg1 argument, Arg2 argument2);
		
		virtual void Execute(Arg1 argument1, Arg2 argument2) const {
			if(IsRegistered() == false)
				return;  
			(this->_instance->*_method)(argument1, argument2);
		}

		void Register(Sender *instance, Method function) {
			this->_method = function;
			this->_instance = instance;
		}

		bool IsRegistered(void) const {
			return (this->_instance != NULL);
		}

	private:
		Sender *_instance;
		Method _method;
};

/*! \brief Callback template class
 *
 * Implements a 3 arguments callback.
 */
template <class Sender, typename Arg1, typename Arg2, typename Arg3>
class Callback3 {
	public:
		Callback3(void) {
			this->_method = NULL;
			this->_instance = NULL; 
		}

		typedef void (Sender::*Method)(Arg1 argument, Arg2 argument2,
				Arg3 argument3);
		
		virtual void Execute(Arg1 argument1, Arg2 argument2, Arg3
				argument3) const {
			if(IsRegistered() == false)
				return;  
			(this->_instance->*_method)(argument1, argument2, argument3);
		}

		void Register(Sender *instance, Method function) {
			this->_method = function;
			this->_instance = instance;
		}

		bool IsRegistered(void) const {
			return (this->_instance != NULL);
		}

	private:
		Sender *_instance;
		Method _method;
};

#define Callback_Register(sender_event, receiver_type, receiver_ptr, method) \
	sender_event.Register((receiver_type*)receiver_ptr, &receiver_type::method);

	}
}

#endif
