#ifndef XTYPE_HPP
#define XTYPE_HPP

#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "XException.hpp"

namespace wtk {
	namespace xml {

typedef int XTypeData;

class XType {
	public:
		XType(bool verbose = false);
		XType(std::string buffer, bool verbose = false);
		XType(const char* buffer, bool verbose = false);
		virtual ~XType(void);
	
		virtual void SetKey(std::string key);
		virtual void SetKey(const char* key);
		virtual std::string Key(void);
		virtual void SetId(std::string key);
		virtual void SetId(const char* id);
		virtual std::string Id(void);

		virtual XTypeData Guess(std::string buffer);
		virtual XTypeData Guess(const char* buffer);

		virtual bool Bool(void);
		virtual float Float(void);
		virtual int  Int(void);
		virtual int GDFInt(void);
		virtual std::string String(void);

	public:
		static const XTypeData TypeNone   = 0;
		static const XTypeData TypeBool   = 1;
		static const XTypeData TypeFloat  = 2;
		static const XTypeData TypeInt    = 3;
		static const XTypeData TypeString = 4;
		static const XTypeData TypeGDFInt = 5;

	protected:
		std::string _key;
		std::string _id;
		
		bool _vbool;
		float _vfloat;
		int _vint;
		std::string _vstring;
		unsigned int _vgdf;

		int _type;
		bool _verbose;
};
	}
}

#endif
