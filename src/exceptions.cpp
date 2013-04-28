#include "exceptions.h"

namespace Exception {
	Base::Base(const Code code, const char* message) {

		this->code = code;
		this->message = message;
	}
	Base::Base(const Code code, const char* message, const char* info) {

		this->code = code;
		this->message = message;
		this->message += ": ";
		this->message += info;
	}
	Base::~Base() throw() {

	}
	const char* Base::what() const throw() {

		return message.c_str();
	}
}
