#define _CRT_SECURE_NO_WARNINGS //needed for c_time and asctime to function

#include "AddTimestamp.h"
//#include "GUICon.h"

#include <Windows.h>
#include <iostream>
#include <assert.h>
#include <ctime>
#include <string>
#include <iomanip>
#include <chrono>
#include <algorithm>

AddTimestamp::AddTimestamp(std::basic_ios<char>& out)
	: out_(out)
	, sink_()
	, newline_(true)
{
	sink_ = out_.rdbuf(this);
	assert(sink_);
}

AddTimestamp::~AddTimestamp()
{
	out_.rdbuf(sink_);
}

AddTimestamp::int_type AddTimestamp::overflow(int_type m) {
	if (traits_type::eq_int_type(m, traits_type::eof()))
		return sink_->pubsync() == -1 ? m : traits_type::not_eof(m);
	if (newline_)
	{   // --   add timestamp here
		std::ostream str(sink_);

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		const int saved_colors = GetConsoleTextAttribute(hConsole);

		// set color for blue before writing time
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		if (!(str << getTime() << "  ")) //attach the timestamp to ostream
			return traits_type::eof(); // error

		SetConsoleTextAttribute(hConsole, saved_colors); // reset color
	}
	newline_ = traits_type::to_char_type(m) == '\n';
	return sink_->sputc(m);
}

std::string AddTimestamp::getTime() {
	/*time_t t; // t passed as argument in function time()
	struct tm * tt; // decalring variable for localtime()
	time(&t); //passing argument to time()
	tt = localtime(&t);
	return asctime(tt);*/

	//std::time_t const now_c = std::time();
	//return std::put_time(std::localtime(&now_c), "%F %T");
	time_t now = time(0);
	char* dt = ctime(&now);
	*std::remove(dt, dt + strlen(dt), '\n') = '\0';
	return dt;
}

// NEEDED FOR COLOR
WORD AddTimestamp::GetConsoleTextAttribute(HANDLE hCon) {
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hCon, &con_info);
	return con_info.wAttributes;
}