#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <unordered_map>

namespace wtk {
	namespace core {


template<typename T, typename U>
class Container {

	public:
		Container(void) {};
		virtual ~Container(void) {};

		virtual bool Set(T key, U value) {
			std::pair<T, U> elem(key, value);
			return this->map_.insert(elem).second;
		}
		
		U Get(T key) {
			auto it = this->map_.find(key);	
		
			if(it != this->map_.end()) {
				return it->second;
			} else {
				throw std::runtime_error(std::string("No item with key "));
			}
		}

		void Remove(T key) {
			this->map_.erase(key);
		}

		size_t Size(void) {
			return this->map_.size();
		}

		typename std::unordered_map<T, U>::iterator Begin(void) {
			return this->map_.begin();
		}
		
		typename std::unordered_map<T, U>::iterator End(void) {
			return this->map_.end();
		}
		
	protected:
		typename std::unordered_map<T, U> map_;



};

	}
}





#endif
