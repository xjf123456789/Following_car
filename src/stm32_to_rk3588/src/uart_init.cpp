#include "stm32_to_rk3588/uart_init.h"

int Rk3588_Uart_Init(int argc, char *argv[])
{
    int fd;
    int res;
    char *path;
    char buf[20]="Hello STM32!"; //发送的字符串
    //接收缓冲区
    uint8_t rx_buf[20] = {0}; 

    //第二部分代码/
    //若无输入参数则使用默认终端设备
    if (argc > 1)
        path = argv[1];
    else
        path = (char *)default_path;

    //获取串口设备描述符
    printf("This is tty/usart demo.\n");
    fd = open(path, O_RDWR);
    if (fd < 0) {
        printf("Fail to Open %s device\n", path);
        return 0;
    }


    //第三部分代码/
    struct termios opt;
    //清空串口接收缓冲区
    tcflush(fd, TCIOFLUSH);
    // 获取串口参数opt
    tcgetattr(fd, &opt);
    //设置串口输出波特率
    cfsetospeed(&opt, B115200);
    //设置串口输入波特率
    cfsetispeed(&opt, B115200);
    
    //设置数据位数
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    //校验位
    opt.c_cflag &= ~PARENB;
    opt.c_iflag &= ~INPCK;
    //设置停止位
    opt.c_cflag &= ~CSTOPB;    
    cfmakeraw(&opt);
    //更新配置
    tcsetattr(fd, TCSANOW, &opt);
}