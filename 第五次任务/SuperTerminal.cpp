#include"SuperTerminal.h"

//初始化串口
SuperTerminal::SuperTerminal(const anytype& port_name) :pSerialPort(NULL)
{
	pSerialPort = new serial_port(m_ios);
	if (pSerialPort)
	{
		//设置数据位为8
		init_port(port_name, 8);
	}
}

SuperTerminal::~SuperTerminal()
{
	if (pSerialPort)
	{
		delete pSerialPort;
	}
}

bool SuperTerminal::init_port(const anytype port, const unsigned int char_size)
{
	//如果打开串口失败则返回false
	if (!pSerialPort)  
	{
		return false;
	}

	pSerialPort->open(port, m_ec);
	
	//设置波特率，串口流控制，校验位，停止位，数据位
	pSerialPort->set_option(serial_port::baud_rate(115200), m_ec);
	pSerialPort->set_option(serial_port::flow_control(serial_port::flow_control::none), m_ec);
	pSerialPort->set_option(serial_port::parity(serial_port::parity::none), m_ec);
	pSerialPort->set_option(serial_port::stop_bits(serial_port::stop_bits::one), m_ec);
	pSerialPort->set_option(serial_port::character_size(char_size), m_ec);

	//成功返回true
	return true;
}

void SuperTerminal::write_to_serial(const anytype data)
{
	if (!pSerialPort)
	{
		return;
	}

	//输出输入字符长度
	size_t len = write(*pSerialPort, buffer(data), m_ec);
	cout << len << "\t" << data << endl;
}

//输出从端口读取的数据
void SuperTerminal::handle_read(char buf[], boost::system::error_code ec, std::size_t bytes_transferred)
{
	cout << "\nhandle_read:";
	cout.write(buf, bytes_transferred);
}

//实现从端口读取数据
void SuperTerminal::read_from_serial()
{
	char v[10];
	async_read(*pSerialPort, buffer(v), boost::bind(&SuperTerminal::handle_read, this, v, _1, _2));
}

void SuperTerminal::call_handle()
{
	m_ios.run();
}