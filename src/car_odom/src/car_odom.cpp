#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv) 
{
    // 1. ROS节点初始化
    ros::init(argc, argv, "car_drive_odom");
    ros::NodeHandle nh;

    // 2. 创建TF2广播器和里程计发布器
    tf2_ros::TransformBroadcaster tf_broadcaster;
    ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);

    // 3. 初始化机器人位姿和差速参数
    double x = 0.0, y = 0.0, th = 0.0;   // 初始位姿
    double wheel_base = 0.18;             // 轮距（根据实际小车尺寸调整）
    
    // 4. 初始化轮速（模拟值，实际使用时应替换为真实轮速）
    double left_wheel_vel = 0.0;          // 左轮速度(m/s)
    double right_wheel_vel = 0.;          // 右轮速度(m/s)

    ros::Time current_time = ros::Time::now();
    ros::Time last_time = current_time;
    ros::Rate rate(80.0);                 // 80Hz更新频率

    while (nh.ok()) {
        current_time = ros::Time::now();
        double dt = (current_time - last_time).toSec();

        // 5. 差速模型计算
        double v = (left_wheel_vel + right_wheel_vel) / 2.0;          // 中心线速度
        double omega = (right_wheel_vel - left_wheel_vel) / wheel_base; // 角速度

        // 6. 更新位姿（差速运动模型）
        double delta_x = v * cos(th) * dt;
        double delta_y = v * sin(th) * dt;
        double delta_th = omega * dt;
        x += delta_x;
        y += delta_y;
        th += delta_th;

        // 7. 将朝向角转为四元数
        tf2::Quaternion q;
        q.setRPY(0, 0, th);
        geometry_msgs::Quaternion odom_quat;
        odom_quat.x = q.x();
        odom_quat.y = q.y();
        odom_quat.z = q.z();
        odom_quat.w = q.w();

        // 8. 发布TF变换：odom → base_link
        geometry_msgs::TransformStamped transformStamped;
        transformStamped.header.stamp = current_time;
        transformStamped.header.frame_id = "odom";
        transformStamped.child_frame_id = "base_link";
        transformStamped.transform.translation.x = x;
        transformStamped.transform.translation.y = y;
        transformStamped.transform.translation.z = 0.0;
        transformStamped.transform.rotation = odom_quat;
        tf_broadcaster.sendTransform(transformStamped);

        // 9. 发布里程计消息（差速专用）
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.orientation = odom_quat;
        ROS_INFO("odom: x: %f, y: %f, quat: [%f, %f, %f, %f]", x, y, odom_quat.x, odom_quat.y, odom_quat.z, odom_quat.w);
        // 关键修正：使用差速模型计算的速度值
        odom.twist.twist.linear.x = v;       // 使用中心线速度v
        odom.twist.twist.angular.z = omega;   // 使用角速度omega
        
        odom_pub.publish(odom);

        last_time = current_time;
        rate.sleep();
    }
    return 0;
}

/*
int main(int argc, char** argv) {
    // 1. ROS节点初始化
    ros::init(argc, argv, "car_odom_tf2");
    ros::NodeHandle nh;

    // 2. 创建 TF2 广播器和里程计发布器
    tf2_ros::TransformBroadcaster tf_broadcaster; // TF2广播器[2,3](@ref)
    ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);

    // 3. 初始化机器人位姿和速度
    double x = 0.0, y = 0.0, th = 0.0;   // 初始位姿
    double vx = 0.1, vy = 0.0, vth = 0.2; // 运动速度（圆周模型）
    ros::Time current_time = ros::Time::now();
    ros::Time last_time = current_time;
    ros::Rate rate(80.0); // 20Hz频率

    while (nh.ok()) {
        current_time = ros::Time::now();
        double dt = (current_time - last_time).toSec(); // 时间间隔

        // 4. 更新位姿（匀速圆周运动）
        double delta_x = vx * cos(th) * dt;
        double delta_y = vx * sin(th) * dt;
        double delta_th = vth * dt;
        x += delta_x;
        y += delta_y;
        th += delta_th;

        // 5. 将朝向角转为四元数（TF2 方式）
        tf2::Quaternion q;
        q.setRPY(0, 0, th); // 欧拉角转四元数[3](@ref)
        geometry_msgs::Quaternion odom_quat;
        odom_quat.x = q.x();
        odom_quat.y = q.y();
        odom_quat.z = q.z();
        odom_quat.w = q.w();

        // 6. 发布 TF 变换：odom → base_link
        geometry_msgs::TransformStamped transformStamped;
        transformStamped.header.stamp = current_time;
        transformStamped.header.frame_id = "odom";
        transformStamped.child_frame_id = "base_link";
        transformStamped.transform.translation.x = x;
        transformStamped.transform.translation.y = y;
        transformStamped.transform.translation.z = 0.0;
        transformStamped.transform.rotation = odom_quat;
        tf_broadcaster.sendTransform(transformStamped); // 广播TF[2,3](@ref)

        // 7. 发布里程计消息（可选，用于Rviz显示）
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.orientation = odom_quat;
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.angular.z = vth;
        odom_pub.publish(odom);

        last_time = current_time;
        rate.sleep();
    }
    return 0;
}

 */






/*

第二版


#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>
#include <tf2/LinearMath/Quaternion.h>
#include <sensor_msgs/JointState.h>  // 新增：编码器消息类型

// 全局变量存储轮速（通过回调函数更新）
double left_wheel_vel = 0.0;
double right_wheel_vel = 0.0;

// 编码器回调函数[1,4](@ref)
void wheelCallback(const sensor_msgs::JointState::ConstPtr& msg) {
    if (msg->name.size() >= 2 && msg->velocity.size() >= 2) {
        left_wheel_vel = msg->velocity[0];
        right_wheel_vel = msg->velocity[1];
    }
}

int main(int argc, char** argv) {
    // 1. ROS节点初始化
    ros::init(argc, argv, "diff_drive_odom");
    ros::NodeHandle nh;
    
    // 2. 创建TF2广播器和里程计发布器
    tf2_ros::TransformBroadcaster tf_broadcaster;
    ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);
    
    // 3. 订阅编码器数据[4](@ref)
    ros::Subscriber wheel_sub = nh.subscribe("/wheel_speeds", 10, wheelCallback);
    
    // 4. 初始化参数（从参数服务器获取）
    double wheel_base = 0.18;
    nh.param<double>("wheel_base", wheel_base, 0.18);  // 默认值0.18m[5](@ref)
    
    double x = 0.0, y = 0.0, th = 0.0;   // 初始位姿
    ros::Time current_time = ros::Time::now();
    ros::Time last_time = current_time;
    ros::Rate rate(30.0); // 提高至30Hz（降低离散化误差）[4](@ref)

    while (nh.ok()) {
        ros::spinOnce();  // 处理回调
        current_time = ros::Time::now();
        double dt = (current_time - last_time).toSec();

        // 5. 差速模型计算[5](@ref)
        double v = (left_wheel_vel + right_wheel_vel) / 2.0;      // 线速度(m/s)
        double omega = (right_wheel_vel - left_wheel_vel) / wheel_base; // 角速度(rad/s)
        
        // 6. 更新位姿（前向欧拉积分）
        double delta_x = v * cos(th) * dt;
        double delta_y = v * sin(th) * dt;
        double delta_th = omega * dt;
        x += delta_x;
        y += delta_y;
        th += delta_th;

        // 7. 四元数转换（TF2方式）
        tf2::Quaternion q;
        q.setRPY(0, 0, th);
        geometry_msgs::Quaternion odom_quat;
        odom_quat.x = q.x();
        odom_quat.y = q.y();
        odom_quat.z = q.z();
        odom_quat.w = q.w();

        // 8. 发布TF变换：odom → base_link
        geometry_msgs::TransformStamped transformStamped;
        transformStamped.header.stamp = current_time;
        transformStamped.header.frame_id = "odom";
        transformStamped.child_frame_id = "base_link";
        transformStamped.transform.translation.x = x;
        transformStamped.transform.translation.y = y;
        transformStamped.transform.translation.z = 0.0;
        transformStamped.transform.rotation = odom_quat;
        tf_broadcaster.sendTransform(transformStamped);

        // 9. 发布里程计消息（带协方差）[7](@ref)
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";
        
        // 位姿
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.orientation = odom_quat;
        
        // 速度
        odom.twist.twist.linear.x = v;
        odom.twist.twist.angular.z = omega;
        
        // 协方差矩阵（提高定位精度）[7](@ref)
        odom.pose.covariance = {{
            0.01, 0,    0,    0,    0,    0,    // X方差
            0,    0.01, 0,    0,    0,    0,    // Y方差
            0,    0,    0.01, 0,    0,    0,    // Z方差
            0,    0,    0,    0.05, 0,    0,    // 旋转方差
            0,    0,    0,    0,    0.05, 0,
            0,    0,    0,    0,    0,    0.05
        }};
        
        odom_pub.publish(odom);

        last_time = current_time;
        rate.sleep();
    }
    return 0;
}
*/