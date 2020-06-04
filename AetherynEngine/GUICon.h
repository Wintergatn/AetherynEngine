/*#pragma once

class GUICon
{

public:

	void RedirectIOToConsole();
	WORD GetConsoleTextAttribute(HANDLE hCon);

};*/

#ifndef __GUICON_H__
#define __GUICON_H__

	#ifdef _DEBUG

		void RedirectIOToConsole();
		//WORD GetConsoleTextAttribute(HANDLE hCon);

	#endif

#endif
