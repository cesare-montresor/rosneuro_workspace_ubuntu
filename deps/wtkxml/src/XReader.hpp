#ifndef XREADER_HPP
#define XREADER_HPP

#include <assert.h>
#include <vector>
#include <utility>
#include <cstdio>
#include <iostream>

#include "XException.hpp"
#include "XType.hpp"
#include "XDocument.hpp"
#include "rapidxml.hpp"

using namespace rapidxml;

namespace wtk {
	namespace xml {

class XReader {
	public:
		XReader(const std::string& rootname);
		virtual ~XReader(void);
		virtual void ImportFileEx(const std::string& filename);
		virtual void ImportBufferEx(const std::string& filename);

		XReader* RootEx(void);
		XReader* GoEx(const std::string& blockname);
		XReader* QuickEx(const std::string& blockpath);
		std::string GetRawEx(void);
		XReader* GetRawEx(std::string* value);
		XType GetEx(void);
		XReader* GetEx(XType* value);
		std::string GetAttrEx(const std::string& name);
		XReader* SetBranch(void);
		XReader* BranchEx(void);
		XNode Parent(void);
		XNode Leaf(void);
		XNode Child(void);
		XNode NextSibling(void);
		void Dump(void);
		std::string QuickStringEx(const std::string& str);
		bool QuickBoolEx(const std::string& str);
		float QuickFloatEx(const std::string& str);
		int QuickIntEx(const std::string& str);
		unsigned int QuickGDFIntEx(const std::string& str);
	protected:
		void SearchRoot(void);
		void CheckRootEx(void);
		void CheckBranchEx(void);
		void CheckLeafEx(void);
	private:
		static void Tokenize(const std::string& str, 
				std::vector<std::string>& tokens, 
				const std::string& delimiters = "/");

	private:
		std::string _rootname;
		XDocument _document;
		XNode _nRoot;
		XNode _nBranch;
		XNode _nLeaf;
};

	}
}

#endif
