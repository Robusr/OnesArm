
%% 基于MATLAB的OnesArm AyCxBy型仿真

%% 参数定义
clear;
close all;
clc;
 
%角度转换
angle=pi/180;  %转化为角度制
 
%D-H参数表
theta1 = 0;   D1 = 0.095;   A1 = 0; alpha1 = pi/2; offset1 = 0;
theta2 = 0;   D2 = 0;     A2 = 0.1135;  alpha2 = pi/2;    offset2 = 0;
theta3 = 0;   D3 = 0.02134;     A3 = 0.0885; alpha3 = pi/2; offset3 = 0;
theta4 = 0;   D4 = 0;     A4 = 0.152;     alpha4 = 0; offset4 = 0;
 
%% DH法建立模型,关节转角，关节距离，连杆长度，连杆转角，关节类型（0转动，1移动），'standard'：建立标准型D-H参数
L(1) = Link([theta1, D1, A1, alpha1, offset1], 'standard');
L(2) = Link([theta2, D2, A2, alpha2, offset2], 'standard');
L(3) = Link([theta3, D3, A3, alpha3, offset3], 'standard');
L(4) = Link([theta4, D4, A4, alpha4, offset4], 'standard');
 
% 定义关节范围
L(1).qlim =[0,0];
L(2).qlim =[0*angle, 180*angle];
L(3).qlim =[-90*angle, 90*angle];
L(4).qlim =[-90*angle, 90*angle];
 
%% 显示机械臂（把上述连杆“串起来”）
robot0 = SerialLink(L,'name','OnesArm');
theta = [0 pi/2 0 0];				%初始关节角度
figure(1)
robot0.plot(theta);
title('OnesArm AyCxBy-D Simulation');

%% 加入teach指令，则可调整各个关节角度
robot1 = SerialLink(L,'name','OnseArm');
figure(2)
robot1.plot(theta);
robot1.teach
title('OnesArm AyCxBy-D Simulation');