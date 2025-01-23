% 텍스트 파일 경로
file_path = 'C:\lidar_data\lidar_data_1.txt'; % 파일 경로 설정

% 데이터 읽기
data = readmatrix(file_path);

% 각도, 거리, 감도 데이터 추출
angles = data(:, 1);       % 첫 번째 열: 각도 (degree)
distances = data(:, 2);    % 두 번째 열: 거리 (mm)
intensities = data(:, 3);  % 세 번째 열: 감도 (신호 강도)

% 거리 데이터를 정규화하여 X, Y 좌표 계산 (D500 LiDAR의 각도는 degree 기준)
x = distances .* cosd(angles); % X 좌표 계산
y = distances .* sind(angles); % Y 좌표 계산

% 비낙상 상태 정의: Y 값이 특정 임계값 이상인 데이터
non_fall_threshold = 500; % 비낙상 상태로 간주할 Y 값 기준 (D500의 데이터 단위가 mm)
non_fall_indices = y > non_fall_threshold; % 비낙상 상태의 데이터 인덱스

% 시각화: 전체 데이터와 비낙상 데이터 강조
figure;
scatter(x, y, 20, intensities, 'filled'); % 전체 데이터 시각화
hold on;
scatter(x(non_fall_indices), y(non_fall_indices), 50, 'green', 'filled'); % 비낙상 데이터 강조
colorbar; % 색상 막대 추가
xlabel('X (mm)');
ylabel('Y (mm)');
title('LiDAR 데이터 시각화 (비낙상 상태 강조)');
grid on;
axis equal;
hold off;

% 비낙상 상태 데이터 출력
non_fall_data = [angles(non_fall_indices), distances(non_fall_indices), intensities(non_fall_indices)];
disp('비낙상 데이터:');
disp(non_fall_data);
