#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include "ros/ros.h"
#include "std_msgs/String.h" //普通文本类型的消息
#include <sstream>
#include "stm32_to_rk3588/stm32_to_rk3588_uart.h"//自定义消息类型
//第一部分代码/
//根据具体的设备修改
/*********************************** */

/*  这是STM32 给 RK3588的 */
const char default_path[] = "/dev/ttyS0";
/*********************************** */
int main(int argc, char *argv[])
{


    ros::init(argc, argv, "stm32_to_rk3588_node");
    ros::NodeHandle nh;
    ros::Publisher uart_pub = nh.advertise<stm32_to_rk3588::stm32_to_rk3588_uart>("RK3588_to_STM32_uart", 1000);
    stm32_to_rk3588::stm32_to_rk3588_uart msg;

    /*************************************************************/   
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

/*************************************************************/   

    ROS_INFO("RK3588 to STM32 serial port communication started.");
    printf("Device %s is set to 115200bps,8N1\n",path);
    tcflush(fd, TCIFLUSH);

    //第四部分代码/
    while (ros::ok()) {
        tcflush(fd, TCIFLUSH);
        //发送字符串
        write(fd, buf, strlen(buf));
        //接收字符串
        res = read(fd, rx_buf, 20);
        if (res > 0) {
            tcflush(fd, TCIFLUSH);
            // //给接收到的字符串加结束符
            // rx_buf[res] = '\0';
            ROS_INFO("RK3588 to STM32 ");
            msg.Rk3588_To_Stm32.assign(0); // 先清零
            for (int i = 0; i < res && i < msg.Rk3588_To_Stm32.size(); ++i) 
            {
                msg.Rk3588_To_Stm32[i] = rx_buf[i];
            }
            uart_pub.publish(msg);

            printf("Receive res = %d bytes data: %s\n", res, rx_buf);
            printf("%d\n", rx_buf[1]);
        } else if (res < 0) {
             ROS_ERROR("Read error, res = %d", res);
            break;
        }
    }
    ros::spinOnce();
    close(fd);
    return 0;
}