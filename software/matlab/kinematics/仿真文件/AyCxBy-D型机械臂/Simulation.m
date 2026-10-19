clc;
clear;
%% 机械臂建模
% 定义SDH参数
%          theta       d           a        alpha
L1=Link([     0       0.095        0          0], 'standard'); % [四个DH参数], options
L2=Link([     0       0            0.1135     pi/2], 'standard');
L3=Link([     0       0.02134      0.0885      pi/2], 'standard');
L4=Link([     0       0            0.152       0], 'standard');
b=isrevolute(L1);
robot=SerialLink([L1,L2,L3,L4],'name','Irvingao Arm'); % 将四个连杆组成机械臂
robot.name='4DOF Robotic Arm';
robot.display();

%% 轨迹规划
% 初始值及目标值
init_ang=[0 pi/2 pi/3 pi/4];
targ_ang=[0, -pi/4, -pi/3, pi/2];
step=200;

[q,qd,qdd]=jtraj(init_ang,targ_ang,step); %关节空间规划轨迹，得到机器人末端运动的[位置，速度，加速度]
T0=robot.fkine(init_ang); % 正运动学解算
Tf=robot.fkine(targ_ang);
subplot(2,4,3); i=1:4; plot(q(:,i)); title("Position"); grid on;
subplot(2,4,4); i=1:4; plot(qd(:,i)); title("Velocity"); grid on;
subplot(2,4,7); i=1:4; plot(qdd(:,i)); title("Acceleration"); grid on;

Tc=ctraj(T0,Tf,step);
Tjtraj=transl(Tc);
subplot(2,4,8); plot2(Tjtraj, 'r');
title('Straight line trajectory'); grid on;
subplot(2,4,[1,2,5,6]);
plot3(Tjtraj(:,1),Tjtraj(:,2),Tjtraj(:,3),"b"); grid on;
hold on;
view(3); 
