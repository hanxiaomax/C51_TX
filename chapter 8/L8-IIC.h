/*提供部分MCS51模拟IIC总线时序所需要的函数*/
void START();//起始信号
void STOP();//停止信号
void RESPONS();//应答信号
void INIT();//初始化
void write_byte(unsigned char DATA);//写数据
unsigned char read_byte();//读数据
void delay();
void delay_ms(unsigned int time);
void write_add(unsigned char address,unsigned char DATA);//向某个地址写数据
unsigned char read_add(unsigned char address);//从某个地址读取数据