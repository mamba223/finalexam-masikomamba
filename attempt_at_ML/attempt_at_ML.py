from numpy.random.mtrand import f
import torch
from torch import nn 
import torch.nn.functional as F
from torch.optim import Adam
from torch.utils.data import DataLoader
from torchvision import datasets 
from torchvision.transforms import ToTensor
from dataset import CustomDataSet
from sklearn.model_selection import train_test_split

train = CustomDataSet('Market.csv')

Dataset = DataLoader(train, batch_size=32, shuffle = True)

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1,32,2, padding = 1)
        self.conv2 = nn.Conv2d(32,64,2, padding = 1)
        self.pool = nn.MaxPool2d(2,2)
        self.fc1 = nn.Linear(64 * 1 * 1, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)
        self.pool = nn.MaxPool2d(2,2)
        
    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 64 * 1 * 1)  # Reshape to match the input size for the fully connected layer
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

clf = Net().to('cpu')
optimiser = Adam(clf.parameters(), lr=1e-3)
lossFunction= nn.CrossEntropyLoss()

#training Flow

if __name__ == "__main__":
    for epoch in range(9):
        for batch in Dataset:
            X,Y = batch
            X,Y = X.to('cpu'), Y.to('cpu')
            yhaf = clf(X)
            yhaf = yhaf[:Y.size(0)]
            #yhaf = F.log_softmax(yhaf, dim=1)
            Y = Y.long()
            
            print(f"Model output shape: {yhaf.shape}")
            #max_label = torch.max(Y)

            print(f"Min label: {torch.min(Y)}, Max label: {torch.max(Y)}")
            #print(f"max label is: {max_label}")
            Loss = lossFunction(yhaf,Y)
            
            optimiser.zero_grad()
            Loss.backward()
            optimiser.step()
        
print(f"epoch: {epoch} loss is {Loss.item()}")