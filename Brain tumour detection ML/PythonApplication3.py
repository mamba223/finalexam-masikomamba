import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms, models
import os
import multiprocessing
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

def main():
    data_transforms = {
        'train': transforms.Compose([
            transforms.RandomResizedCrop(720),
            transforms.RandomHorizontalFlip(),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ]),
        'val': transforms.Compose([
            transforms.Resize(1080),
            transforms.CenterCrop(720),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ]),
    }

    data_dir = r'C:\Users\masiko\Desktop\C++ homeworks\picture_analysis_ML\archive (3)'

    image_datasets = {x: datasets.ImageFolder(os.path.join(data_dir, x), data_transforms[x]) for x in ['train', 'val']}

    dataloaders = {x: torch.utils.data.DataLoader(image_datasets[x], batch_size=4, shuffle=True, num_workers=4) for x in ['train', 'val']}
    dataset_sizes = {x: len(image_datasets[x]) for x in ['train', 'val']}
    print(dataset_sizes)

    class_names = image_datasets['train'].classes
    print(class_names)

    model = models.resnet18(pretrained=True)

    for name, param in model.named_parameters():
        if "fc" in name:
            param.requires_grad = True
        else:
            param.requires_grad = False

    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=0.001, momentum=0.9)

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = model.to(device)

    num_epochs = 10
    for epoch in range(num_epochs):
        for phase in ['train', 'val']:
            if phase in ['train', 'val']:
                if phase == 'train':
                    model.train()
                else:
                    model.eval()

                running_loss = 0.0
                running_corrects = 0

                for inputs, labels in dataloaders[phase]:
                    inputs = inputs.to(device)
                    labels = labels.to(device)

                    optimizer.zero_grad()

                    with torch.set_grad_enabled(phase == 'train'):
                        outputs = model(inputs)
                        _, preds = torch.max(outputs, 1)
                        loss = criterion(outputs, labels)

                        if phase == 'train':
                            loss.backward()
                            optimizer.step()

                    running_loss += loss.item() * inputs.size(0)
                    running_corrects += torch.sum(preds == labels.data)

                epoch_loss = running_loss / dataset_sizes[phase]
                epoch_acc = running_corrects.double() / dataset_sizes[phase]

                print(f'{phase} Loss: {epoch_loss:.4f} Acc: {epoch_acc:.4f}')

    print("Training complete")
    
    torch.save(model.state_dict(), 'tumour_classification_model.pth')
    
    model = models.resnet18(pretrained = True)
    model.fc = nn.Linear(model.fc.in_features, 1000)
    model.load_state_dict(torch.load('tumour_classification_model.pth'))
    model.eval()
    
    new_model = models.resnet18(pretrained = True)
    new_model.fc = nn.Linear(new_model.fc.in_features, 2)
    
    new_model.fc.weight.data = model.fc.weight.data[0:2]
    new_model.fc.bias.data = model.fc.bias.data[0:2]
    
    image_path = r'C:\Users\masiko\Desktop\C++ homeworks\picture_analysis_ML\archive (3)\val\no\No12.jpg'
    
    image = Image.open(image_path)
    
    preprocess = transforms.Compose([
        transforms.Resize(256),
        #transforms.CenterCrop(224),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
    ])
    
    input_tensor = preprocess(image)
    input_batch = input_tensor.unsqueeze(0)
    
    with torch.no_grad():
        output = model(input_batch)
        
    _, predicted_class =output.max(1)
    
    class_names = ['no', 'yes']
    predicted_class_name = class_names[predicted_class.item()]
    
    print(f'the predicted class is: {predicted_class_name}')
    
    image = np.array(image)
    plt.imshow(image)
    plt.axis('off')
    plt.text(101,10, f'Predicted: {predicted_class_name}', fontsize=12, color = 'white', backgroundcolor='red')
    plt.show()
    
if __name__ == '__main__':
    multiprocessing.freeze_support()
    main()
