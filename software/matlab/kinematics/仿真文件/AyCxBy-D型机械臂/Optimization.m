% -------------------------- 配置 --------------------------
csv_path = 'pose_data_sync.csv';  % 中转程序生成的CSV路径
filter_window = 5;  % 滑动平均滤波窗口大小
fps = 30;  % 仿真帧率（与Jetson端匹配）
landmark_num = 33;  % MediaPipe 33个关键点

% -------------------------- 初始化 --------------------------
% 读取CSV数据（实时监控文件变化）
opts = detectImportOptions(csv_path);
opts.VariableTypes = {'double','double','double','double','double','double'};
data = table2array(readtable(csv_path, opts));

% 初始化滤波缓存（33个关键点×3个坐标）
filter_buffer = zeros(landmark_num, 3, filter_window);
pose_3d = zeros(landmark_num, 3);  % 滤波后的3D姿态

% 初始化3D仿真窗口
figure('Name','3D人体姿态仿真','Position',[100,100,1000,800]);
axis equal;
grid on;
xlabel('X'); ylabel('Y'); zlabel('Z');
title('全身姿态同步仿真（滤波后）');
hold on;

% MediaPipe关键点索引（关键关节，简化绘制）
joints = [
    0, 1, 2, 3, 4,   % 面部
    5, 6, 7, 8,       % 左眼
    9, 10, 11, 12,    % 右眼
    13, 14, 15, 16,   % 耳朵
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32  % 身体/四肢
];
% 骨骼连接（MediaPipe POSE_CONNECTIONS）
connections = [
    0,1;1,2;2,3;3,4;  % 鼻-眼-耳
    0,5;5,6;6,7;7,8;
    0,9;9,10;10,11;11,12;
    0,13;13,14;14,15;15,16;
    0,17;17,18;18,19;19,20;20,21;
    17,22;22,23;23,24;24,25;25,26;
    11,23;12,24;      % 肩-髋
    23,24;24,26;26,28;28,30;  % 右腿
    23,25;25,27;27,29;29,31;  % 左腿
    11,13;12,14;      % 肩-肘
    13,15;14,16;      % 肘-腕
];

% -------------------------- 实时仿真循环 --------------------------
while true
    try
        % 读取最新CSV数据
        new_data = table2array(readtable(csv_path, opts));
        if size(new_data,1) < landmark_num
            continue;
        end
        
        % 提取最新一帧的33个关键点坐标
        latest_pose = zeros(landmark_num, 3);
        for i = 1:landmark_num
            % 找到对应关键点ID的行
            row = find(new_data(:,2) == i-1, 1, 'last');  % 关键点ID从0开始
            if ~isempty(row)
                latest_pose(i,:) = new_data(row,3:5);  % x,y,z
            end
        end
        
        % 滑动平均滤波（降低抖动）
        filter_buffer(:,:,2:end) = filter_buffer(:,:,1:end-1);
        filter_buffer(:,:,1) = latest_pose;
        pose_3d = mean(filter_buffer, 3);  % 窗口内平均
        
        % 清空画面，重新绘制3D骨架
        cla;
        axis equal; grid on;
        xlabel('X'); ylabel('Y'); zlabel('Z');
        title(['全身姿态同步仿真（滤波后） | 帧率：',num2str(fps)]);
        hold on;
        
        % 绘制关键点（球体）
        scatter3(pose_3d(:,1), pose_3d(:,2), pose_3d(:,3), 50, 'g', 'filled');
        % 绘制骨架（线条）
        for i = 1:size(connections,1)
            p1 = connections(i,1)+1;  % Matlab索引从1开始
            p2 = connections(i,2)+1;
            line([pose_3d(p1,1), pose_3d(p2,1)], ...
                 [pose_3d(p1,2), pose_3d(p2,2)], ...
                 [pose_3d(p1,3), pose_3d(p2,3)], ...
                 'Color','b','LineWidth',2);
        end
        
        % 仿真帧率控制
        pause(1/fps);
    catch e
        disp(['错误：',e.message]);
        if strcmp(e.message, '文件不存在')
            disp('等待CSV文件生成...');
            pause(1);
        else
            break;
        end
    end
end

% 关闭窗口
hold off;
disp('仿真结束');