import numpy as np
import struct
import pickle

# 文件路径
MODEL_FILE = 'tetris_decision_tree.pkl'
CURRENT_DATA_PATH = 'current.bin'
DECISION_OUTPUT_PATH = 'decision.bin'

def load_model():
    with open(MODEL_FILE, 'rb') as f:
        model_data = pickle.load(f)
    return model_data['model'], model_data['preprocessor'], model_data['scaler_y']

def read_current_data():
    # 读取当前数据
    with open(CURRENT_DATA_PATH, 'rb') as f:
        data = f.read(1 + 1 + 25)  # 当前块种类(1字节), 下一个块种类(1字节), 场地形状(25字节)
        
    # 解析当前数据
    current_block, next_block = struct.unpack('2b', data[:2])
    field = list(struct.unpack('25b', data[2:27]))
    
    # 组合特征
    features = [current_block, next_block] + field
    
    return np.array([features])

def make_prediction(model, preprocessor, scaler_y, current_features):
    # 预处理特征
    current_processed = preprocessor.transform(current_features)
    
    # 预测归一化后的x坐标和角度
    y_pred_scaled = model.predict(current_processed)[0]
    
    # 检查预测的归一化值是否有NaN值
    if np.isnan(y_pred_scaled).any():
        print("预测的归一化值包含NaN值")
        y_pred_scaled = np.nan_to_num(y_pred_scaled, nan=0.5)  # 替换NaN值为0.5
    
    # 反归一化预测结果
    y_pred = scaler_y.inverse_transform([y_pred_scaled])[0]
    
    # 检查反归一化后的预测值是否有NaN值
    if np.isnan(y_pred).any():
        print("反归一化后的预测值包含NaN值")
        y_pred = np.nan_to_num(y_pred, nan=0.5)  # 替换NaN值为0.5
    
    # 四舍五入得到整数预测值
    x_pred = round(y_pred[0])
    degree_pred = round(y_pred[1])
    
    return x_pred, degree_pred

def write_decision(x, degree):
    with open(DECISION_OUTPUT_PATH, 'wb') as f:
        # 写入x和角度，每个占1字节
        f.write(struct.pack('2b', x, degree))

if __name__ == '__main__':
    model, preprocessor, scaler_y = load_model()
    current_features = read_current_data()
    x_pred, degree_pred = make_prediction(model, preprocessor, scaler_y, current_features)
    write_decision(x_pred, degree_pred)
    print(f"预测结果: x={x_pred}, degree={degree_pred}")
