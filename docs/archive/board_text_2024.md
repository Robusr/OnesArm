# 珠连“臂”合——多场景模块化串联机械臂结构设计与分析优化

# Design and Analysis Optimization of a Multi-Scenario Modular Interconnected Robotic Arm Structure

## 一、研究背景及意义

随着工业自动化程度和医疗救援领域需求的不断提高，对于高精度、高速度、高可靠性的机械臂系统需求日益增加。传统刚性串联机械臂具有体积大、使用场景单一和复杂狭窄环境通过能力差的问题。根据模块化思路与构想，设计了多场景模块化串联机械臂，从系统能耗和工作空间两个方面对机械臂结构组装预处理，基于不同场景变换，通过模块化重组的方式实现由“固定需求映射固定结构”到“不同需求映射不同结构”的实时优化；实现了多场景模块化串联机械臂灵活性通用性高、易于维护和拓展、便于空间优化的目的，满足技术发展不断变化的需求，达到珠联“臂”合。

As the demand for industrial automation and medical rescue continues to rise, there is an increasing need for robotic arm systems that are highly precise, fast, and reliable. Traditional rigid serial robotic arms face challenges such as large size, limited application scenarios, and poor performance in complex and narrow environments. Based on a modular design approach, a multi-scenario modular serial robotic arm has been developed. This design addresses the assembly and preprocessing of the robotic arm's structure from the perspectives of system energy consumption and workspace. By adapting to different scenarios through modular reconfiguration, the system achieves real-time optimization from "fixed requirements mapped to fixed structures" to "different requirements mapped to different structures." This results in a highly flexible and versatile multi-scenario modular serial robotic arm that is easy to maintain and expand while optimizing spatial efficiency, thereby meeting the evolving demands of technological development and achieving seamless integration.

## 二、结构设计

### 1、模块化连杆

为丰富模块化连接方式的多样性，设计了X-X、X-Y方向长连杆和集成化短连杆，各标准化连接节点采用M5螺丝固连，整体采用5mm厚的5052铝合金钣金和碳纤维管结构，保障模块化机械臂的强度和刚度，实现各种结构的灵活连接。

To enhance the diversity of modular connection methods, long rods for X-X and X-Y directions as well as integrated short rods have been designed. Each standardized connection joint is secured with M5 screws, and the entire structure utilizes 5mm thick 5052 aluminum alloy sheet metal and carbon fiber tubes to ensure the strength and rigidity of the modular robotic arm, enabling flexible connections for various configurations.

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\XX渲染.JPG" alt="XX渲染" style="zoom:25%;" />

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\XY渲染.JPG" alt="XY渲染" style="zoom:25%;" />



<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\短连杆渲染.JPG" alt="静应力分析" style="zoom:25%;" />

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\静应力分析.png" alt="静应力分析" style="zoom:50%;" />



### 2、模块化关节

选用42BYGH47步进电机和FLE-42-20行星减速器作为驱动装置，减速比为1:20。配备磁编码闭环控制器、STM32F103C8T6平台CAN协议通讯组件和用于各模块连接的标准化接口，实现模块化机械臂的稳定控制和精确输出力矩。

The 42BYGH47 stepper motor and FLE-42-20 planetary gearbox have been selected as the drive system, with a reduction ratio of 1:20. It is equipped with a magnetic encoder closed-loop controller, a CAN protocol communication component based on the STM32F103C8T6 platform, and standardized interfaces for connecting various modules, enabling stable control and precise torque output for the modular robotic arm.

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\驱动装置渲染.JPG" alt="驱动装置渲染" style="zoom:25%;" />

### 3、工作平台

使用4040欧标铝制型材搭建模块化机械臂的工作平台，安装了350W稳定电源输入、3块测试定位板和STM32F407ZGT6平台的CAN总线控制器，预留出UART协议的通讯接口，根据具体的工作场景和任务需求选择并安装使用。

A working platform for a modular robotic arm has been constructed using 4040 European standard aluminum profiles. It includes a 350W stable power supply input, three testing positioning boards, and a CAN bus controller based on the STM32F407ZGT6 platform. UART protocol communication interfaces have been reserved and will be selected and installed according to specific working scenarios and task requirements.

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\工作平台.JPG" alt="工作平台" style="zoom:50%;" />

## 三、分析优化

### 1、模块化组合分析

根据该机械臂的串联结构，连杆模块与关节模块之间构成面接触的旋转副；连杆模块与连杆模块之间也构成面接触的固连，因此可统一为连接面(Connecting Face)-连接通道(Connecting Channel)-连接面的“FCF结构”

Based on the series structure of the robotic arm, a rotational joint formed by surface contact exists between the link module and the joint module; similarly, a fixed connection through surface contact occurs between the link modules. Therefore, these can be unified under the “FCF structure” of Connecting Face - Connecting Channel - Connecting Face.

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\FCF结构.png" alt="FCF结构" style="zoom:50%;" />

设机械臂各模块从左向右依次固定，整体串联结构可整理为

The modules of the robotic arm are fixed sequentially from left to right, and the overall structure can be organized as a series connection.

![结构整理](F:\Desktop\OnesArm\Presentatiion\展板插图\结构整理.png)

以连杆模块和关节模块的各连接面旋转中心的交点为坐标原点，垂直于各连接面分别建立坐标系

Using the intersection of the rotation centers of the connection surfaces of the link and joint modules as the coordinate origin, establish coordinate systems perpendicular to each connection surface.

![坐标系](F:\Desktop\OnesArm\Presentatiion\展板插图\坐标系.png)

其中X-X长连杆(X-X Long Link)和X-Y长连杆(X-Y Long Link)可抽象为6个连接面，每个连接面有4个连接通道，短连杆(Short Link)可抽象为4个连接面，每个连接面有4个连接通道，关节(Joint)可抽象为2个连接面，有4个连接通道。根据Rodriguez公式和装配关系，删去重合项，得出“FCF结构“对应的方法总数

The X-X Long Link and X-Y Long Link can be abstracted into six connection surfaces, each with four connection channels. The Short Link can be abstracted into four connection surfaces, with each surface also having four connection channels. Joints can be abstracted into two connection surfaces, each with four connection channels. Based on the Rodriguez formula and assembly relationships, overlapping items are removed to derive the total number of methods corresponding to the "FCF structure."

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\FCF方法总数.png" alt="FCF方法总数" style="zoom:50%;" />

得到不同自由度(F)下的模块化组合总数

The total number of modular combinations under different degrees of freedom (F)

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\组合总数.png" alt="组合总数" style="zoom:75%;" />

### 2、模块化重组优化

​	在多种应用场景中，需评估系统总能耗需求，对机械臂组装方式预处理并模块化重组，使系统完成特定工作时所需总功耗最小，根据轨迹函数，对各关节模块对应运行角度的一阶导数（速度）积分，设计优化指标

In various application scenarios, it is necessary to assess the total energy consumption requirements of the system, preprocess the robotic arm assembly methods, and modularly reorganize them to minimize the total power consumption required for the system to perform specific tasks. Based on the trajectory function, the first derivative (speed) of the corresponding operational angles of each joint module is integrated to design optimization criteria.

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\功耗指标.png" alt="功耗指标" style="zoom:75%;" />

功耗优化的同时，需对机械臂的工作空间作出优化，使其完成目标任务时满足最优条件，根据特定装配方式的DH表，建立仿真模型，并输出测试点位的运动轨迹

While optimizing power consumption, it is also necessary to optimize the workspace of the robotic arm to ensure optimal conditions for completing the target tasks. Based on the DH parameters for specific assembly methods, a simulation model will be established, and the motion trajectories of the test points will be outputted.

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\A.png" alt="A" style="zoom:25%;" />



<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\Ap.png" alt="Ap" style="zoom:48%;" />

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\B.png" alt="B" style="zoom:25%;" />

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\Bp.png" alt="Bp" style="zoom:48%;" />

完成特定工作的基本流程

Basic Process for Completing Specific Tasks

<img src="F:\Desktop\OnesArm\Presentatiion\展板插图\优化流程.png" alt="优化流程" style="zoom:50%;" />

## 四、结论与展望

我的家乡宁夏被称为“枸杞之乡”，如今科技飞速发展，自动化枸杞采摘面临着巨大的挑战。传统的震动法由于损耗高、效率低，未能广泛推行。本课题研究的多场景模块化机械臂，在后续的探索过程中，优化结构与算法，根据不同的枸杞采摘需求对机械臂结构预处理，针对相应的品种和树形模块化重组，灵活多变地应对多种场景，加入机器视觉组件，实现花果精确识别分离，提高家乡万亩枸杞果田的生产效率，为美丽宁夏川的建设添砖加瓦。让高新技术产业融入基层生产，智能机械与香甜枸杞珠联璧合！

My hometown, Ningxia, is known as the "hometown of goji berries." With the rapid development of technology, automated goji berry harvesting faces significant challenges. Traditional vibration methods have not been widely adopted due to high loss rates and low efficiency. This study focuses on a modular robotic arm designed for multiple scenarios, optimizing its structure and algorithms throughout the exploration process. It adapts the mechanical arm's structural processing to different harvesting needs, modularly reconfiguring based on specific varieties and plant shapes to flexibly address various situations. By adding machine vision components, it achieves precise identification and separation of flowers and fruits, enhancing production efficiency in the vast goji berry fields of my hometown. This contributes to building a beautiful Ningxia and integrates high-tech industries into grassroots production, making intelligent machinery and sweet goji berries a perfect match!

![枸杞](F:\Desktop\OnesArm\Presentatiion\展板插图\枸杞.jpg)

