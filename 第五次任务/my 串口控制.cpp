#include<vector>
#include<string>

#define BOOST_REGEX_NO_LIB
#define BOOST_DATE_TIME_SOURCE
#define BOOST_SYSTEM_NO_LIB
#include"SuperTerminal.h"

int main()
{
	try
	{
		//选择端口号
		SuperTerminal sp("COM3");
		//输入传入的数据
		sp.write_to_serial("Hello World!");
		sp.read_from_serial();
		sp.call_handle();
		return 0;
	}
	catch (std::exception& e)
	{
		cout << e.what();
	}
}