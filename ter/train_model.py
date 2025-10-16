import numpy as np
import struct
from sklearn.ensemble import RandomForestRegressor
from sklearn.preprocessing import OneHotEncoder, MinMaxScaler
from sklearn.compose import ColumnTransformer
from sklearn.multioutput import MultiOutputRegressor
import pickle

# 文件路径
TRAIN_DATA_PATH = 'train_data.bin'
MODEL_FILE = 'tetris_random_forest.pkl'

# 特征和目标的索引
FEATURE_START = 0
FEATURE_END = 3 + 25  # 3代表当前块种类、下一个块种类和位置，25代表场地形状
TARGET_X_INDEX = FEATURE_END
TARGET_DEGREE_INDEX = TARGET_X_INDEX + 1
SCORE_INDEX = TARGET_DEGREE_INDEX + 1

# 定义特征预处理
def preprocess_features(X):
    # 特征: 当前块种类, 下一个块种类, 场地形状
    # 分类特征: 当前块种类(1-7), 下一个块种类(1-7)
    categorical_features = [0, 1]  # 当前块种类和下一个块种类
    
    # 对分类特征进行独热编码，对场地形状保持原始数值
    preprocessor = ColumnTransformer(
        transformers=[
            ('cat', OneHotEncoder(handle_unknown='ignore'), categorical_features)
        ],
        remainder='passthrough'
    )
    
    X_processed = preprocessor.fit_transform(X)
    return X_processed, preprocessor

# 目标变量预处理（归一化到0-1范围）
def preprocess_targets(y):
    scaler = MinMaxScaler(feature_range=(0, 1))
    y_scaled = scaler.fit_transform(y)
    return y_scaled, scaler

# 读取训练数据
def read_train_data():
    with open(TRAIN_DATA_PATH, 'rb') as f:
        # 计算样本数
        sample_size = struct.calcsize('3c25c2c')
        data = f.read()
        num_samples = len(data) // sample_size
        
        X_data = []
        y_data = []
        sample_weights = []
        
        for i in range(num_samples):
            start_pos = i * sample_size
            end_pos = (i + 1) * sample_size
            
            # 解析每一行数据
            data_row = struct.unpack(f'{sample_size}b', data[start_pos:end_pos])
            
            # 特征
            current_block = data_row[0]
            next_block = data_row[1]
            field = list(data_row[2:27])  # 前两个是当前和下一个块种类，然后是25字节的场地形状
            
            # 组合特征
            features = [current_block, next_block] + field
            
            # 目标
            x = data_row[27]
            degree = data_row[28]
            score = data_row[29]
            
            # 计算权重（以得分为权重）
            weight = score
            
            X_data.append(features)
            y_data.append([x, degree])
            sample_weights.append(weight)
        
        return np.array(X_data), np.array(y_data), np.array(sample_weights)

# 训练随机森林模型
def train_random_forest(X, y, sample_weights):
    # 预处理特征
    X_processed, preprocessor = preprocess_features(X)
    
    # 预处理目标变量（归一化到0-1范围）
    y_scaled, scaler_y = preprocess_targets(y)
    
    # 使用MultiOutputRegressor包装随机森林，使其可以同时预测多个目标
    multi_target_model = MultiOutputRegressor(RandomForestRegressor(
        n_estimators=100,
        max_depth=10,
        min_samples_split=2,
        min_samples_leaf=1,
        random_state=42
    ))
    multi_target_model.fit(X_processed, y_scaled, sample_weight=sample_weights)
    
    # 保存模型和预处理器
    with open(MODEL_FILE, 'wb') as f:
        pickle.dump({
            'model': multi_target_model,
            'preprocessor': preprocessor,
            'scaler_y': scaler_y
        }, f)
    
    print("随机森林模型训练完成并已保存")

if __name__ == '__main__':
    X, y, sample_weights = read_train_data()
    train_random_forest(X, y, sample_weights)
