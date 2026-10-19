%% OnseArm-AyCxBy-D仿真模型

L(1)= Link('d',0.095,'a',0,'alpha',pi/2,'standard','qlim',[0 0]*pi/180);% 连杆1
L(2)=Link('d',0,'a',0.1135,'alpha',0,'standard','qlim',[0 180]*pi/180);% 连杆2
L(3)=Link('d',0.02134,'a',0.0885,'alpha',pi/2,'standard','qlim',[-90 90]);% 连杆3
L(4)= Link('d',0,'a',0.152,'alpha',0,'standard','qlim',[-90 90]*pi/180);% 连杆4
scara=SerialLink(L,'name','OnseArm-AyCxBy-D');%建立OnseArm-AyCxBy-D机器人模型
q0=[0 0 0 0];%初始关节变量
scara.plot(q0);%绘制机械臂结构
scara.teach(q0);%驱动机械臂
 
%% 工作空间绘制
qL=scara.qlim;%关节运动范围
N=10000;%随机数数量
ws_q=zeros(N,4);%定义N个关节变量向量组成的关节变量矩阵q
a=rand(size(ws_q)); %生成元素数值在0~1之间的与q同维度的随机矩阵
 
for j=1:N
    for i=1:4
        ws_q(j,i)=qL(i,1)+(qL(i,2)-qL(i,1))*a(j,i);%给矩阵q赋q范围内的随机值，以得到足够多的给定范围(矩阵ql)内的机器人的关节变量(矩阵q)值
    end
end
%求机器人位置坐标
ws_x=l(1)*cos(ws_q(:,1))+l(2)*cos(ws_q(:,1)+ ws_q(:,2));%机器人末端x坐标值
ws_y=l(1)*sin(ws_q(:,1))+l(2)*sin(ws_q(:,1)+ws_q(:,2));%机器人末端了坐标值
ws_z=- ws_q(:,3);%机器人末端z坐标值
figure('Name','Scara机器人工作空间')
plot3(ws_x,ws_y,ws_z,'r.')
title('AyCxBy-D Terminal Motion Trajectory'); %命名
grid;
xlabel('x');
ylabel('y');
zlabel('z');
%% 轨迹规划
qA=[0 0 0 0];%起始点关节变量值
qB=[0.7 1.2 0.15 2];%终止点关节变量值
t=0:0.05:2;%产生时间向量
[q,qd,qdd]=jtraj(qA,qB,t);%jtraj()为构建轨迹命令，得到各关节的位移、速度和加速度
%% 正运动学仿真
T=double(scara.fkine(q));%正运动学仿真函数
[x,y,z]=transl(T);%机械臂末端x、y、z坐标值
%% 绘制曲线图
figure('Name','OnseArm-AyCxBy-D正运动学演示');
plot(scara,q)
figure('Name','OnseArm-AyCxBy-D末端运动轨迹')
plot3(x,y,z,'r-o','MarkerFaceColor','r');
title('AyCyBx-D Workspace'); %命名
grid;
xlabel('x');ylabel('y');zlabel('z');
figure('Name','各关节的角位移、速度和加速度曲线');
subplot(3,4,1);
plot(t,q(:,1)); %得到关节1的位移曲线
title('Link1 Angular displacement(rad)'); %命名
grid;
hold on;
xlabel('time(s)');
ylabel('Angular displacement(rad)');
subplot(3,4,5);
plot(t,qd(:,1)); %得到关节1的速度曲线
title('Link1 Velocity(rad/s)'); %命名
grid;
xlabel('time(s)');
ylabel('Velocity(rad/s)');
subplot(3,4,9);
plot(t,qdd(:,1)); %得到关节1的加速度曲线
title('Link1 Acceleration(rad/s^2)'); %命名
grid;
xlabel('time(s)');
ylabel('Acceleration(rad/s^2)');
 
 
subplot(3,4,2);
plot(t,q(:,2)); %得到关节2的位移曲线
title('Link2 Angular displacement(rad)'); %命名
grid;
hold on;
xlabel('time(s)');
ylabel('Angular displacement(rad)');
subplot(3,4,6);
plot(t,qd(:,2)); %得到关节2的速度曲线
title('Link2 Velocity(rad/s)'); %命名
grid;
xlabel('time(s)');
ylabel('Velocity(rad/s)');
subplot(3,4,10);
plot(t,qdd(:,2)); %得到关节2的加速度曲线
title('Link2 Acceleration(rad/s^2)'); %命名
grid;
xlabel('time(s)');
ylabel('Acceleration(rad/s^2)');
 
subplot(3,4,3);
plot(t,q(:,3)); %得到关节3的位移曲线
title('Link3 Angular displacement(rad)'); %命名
grid;
hold on;
xlabel('time(s)');
ylabel('Angular displacement(rad)');
subplot(3,4,7);
plot(t,qd(:,3)); %得到关节3的速度曲线
title('Link3 Velocity(rad/s)'); %命名
grid;
xlabel('time(s)');
ylabel('Velocity(rad/s)');
subplot(3,4,11);
plot(t,qdd(:,3)); %得到关节3的加速度曲线
title('Link3 Acceleration(rad/s^2)'); %命名
grid;
xlabel('time(s)');
ylabel('Acceleration(rad/s^2)');
 
subplot(3,4,4);
plot(t,q(:,4)); %得到关节4的位移曲线
title('Link4 Angular displacement(rad)'); %命名
grid;
hold on;
xlabel('time(s)');
ylabel('Angular displacement(rad)');
subplot(3,4,8);
plot(t,qd(:,4)); %得到关节4的速度曲线
title('Link4 Velocity(rad/s)'); %命名
grid;
xlabel('time(s)');
ylabel('Velocity(rad/s)');
subplot(3,4,12);
plot(t,qdd(:,4)); %得到关节4的加速度曲线
title('Link4 Acceleration(rad/s^2)'); %命名
grid;
xlabel('time(s)');
ylabel('Acceleration(rad/s^2)');
 