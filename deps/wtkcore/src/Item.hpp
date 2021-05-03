#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>


namespace wtk {
	namespace core {

class Item {
	
	public:
		Item(std::string value);
		~Item(void);

		float 		AsFloat(void);
		int 		AsInt(void);
		unsigned int 	AsUInt(void);
		int 		AsHex(void);
		double 		AsDouble(void);
		std::string 	AsString(void);

	private:
		std::string value_;

};

	}
}


#endif

