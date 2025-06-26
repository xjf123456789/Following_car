#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <stdint.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
const char default_path[] = "/dev/ttyS0";


int fd = -1; // 串口描述符，提升为全局变量
void doMsg(const geometry_msgs::Twist::ConstPtr& msg)
{
  // 提取线速度和角速度
    float linear_x = (msg->linear.x)*10;   // 前进/后退速度（m/s）
    float linear_y = (msg->linear.y)*10;   // 左右速度（m/s）
    float angular_z = (msg->angular.z)*10; // 旋转速度（rad/s）

  /****************接收键盘信息并通过串口发送给stm32************************************* */
    // 打包为字节数组
    uint8_t tx[12] = {0};
    union { float f; uint8_t b[4]; } u;
    u.f = linear_x;
    for (int i = 0; i < 4; ++i) tx[i] = u.b[i];
    u.f = linear_y;
    for (int i = 0; i < 4; ++i) tx[4 + i] = u.b[i];
    u.f = angular_z;
    for (int i = 0; i < 4; ++i) tx[8 + i] = u.b[i];
    // 通过串口发送
    if (fd >= 0) write(fd, tx, 12);  
  /****************接收键盘信息并通过串口发送给stm32************************************* */
    // 打印接收到的速度值
    ROS_INFO("Received cmd_vel: linear.x=%.2f,linear.y=%.2f,angular.z=%.2f", linear_x,linear_y,angular_z);
}
int main(int argc, char **argv)
{
    ros::init(argc,argv,"cmd_vel_car_listener");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/cmd_vel", 1000,doMsg);

    /*************************************************************/   


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
    ROS_INFO("RK3588 to STM32 serial port communication started.");
    printf("Device %s is set to 115200bps,8N1\n",path);
    tcflush(fd, TCIFLUSH);
    /*************************************************************/   

    ros::spin();
    if(fd >= 0) {
        close(fd); // 关闭串口
        fd = -1; // 重置串口描述符
        ROS_INFO("Serial port closed.");
    } else {
        ROS_ERROR("Serial port was not open.");
    }
    return 0;
}

