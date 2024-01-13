import os
import torch
import pandas as pd
import numpy as np
from torch.utils.data import Dataset
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder

class CustomDataSet(Dataset):
    def __init__(self, csv_file):
        self.data_labels = pd.read_csv(csv_file)
        
    def __len__(self):
        return len(self.data_labels)
    

    def __getitem__(self, idx):
        
        #data_path = os.path.join(self.market_csv, self.data_labels.iloc[idx, 0])
        data_point = self.data_labels.iloc[idx]
        #X = self.Open
        #Y = self.Volume
        #return X,Y
        features = data_point[['Open', 'High', 'Low', 'Close', 'Adj Close', 'Volume']].values.astype(np.float32)
        #features = self.random_noise(features)
        label = data_point['Close'].astype(np.float32)
        features = features.reshape(1,1,6)
    
        return torch.tensor(features), torch.tensor(label)

    def _one_hot_encode(self, labels):
        one_hot_encoder = OneHotEncoder()
        labels_one_hot = one_hot_encoder.fit_transform(labels.values.reshape(-1, 1)).toarray()
        return labels_one_hot
    
dataset = CustomDataSet('Market.csv')

print(len(dataset))

#for i in range(len(dataset)):
    #features, label = dataset[i]
    #print(f"Data point {i + 1}: Features - {features}, Label - {label}")