# Changelog for package elevation_net

tros_2.2.0 (2024-07-19)
------------------
1. 新增x5模型适配。

tros_2.1.0 (2024-03-28)
------------------
1. 新增适配ros2 humble零拷贝。
2. 适配重构dnn_node。
3. 零拷贝通信使用的qos的Reliability由RMW_QOS_POLICY_RELIABILITY_RELIABLE（rclcpp::QoS()）变更为RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT（rclcpp::SensorDataQoS()）。

tros_2.0.1 (2023-07-14)
------------------
1. 规范Rdkultra产品名。

tros_2.0.0 (2023-05-11)
------------------
1. 更新package.xml，支持应用独立打包

tros_1.1.6a (2023-02-16)
------------------
1. 适配x86版本功能

tros_1.1.4 (2022-12-13)
------------------
1. 在README文档中，增加板端编译时开关零拷贝的方法说明。


hhp_1.0.4 (2022-07-26)
------------------
1. 适配hhp_1.0.4版本dnn_node。
