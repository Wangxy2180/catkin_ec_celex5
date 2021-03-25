import numpy as np

file_path = r"testdata/data.csv"

with open(file_path,encoding = 'utf-8') as f:
    csv = np.loadtxt(file_path, delimiter = ',', dtype = "int")
    
# 不知道为啥，数字的宽度和空格的不一致，只能加个制表符了
np.savetxt(r'testdata/data.txt',csv,fmt='%-20d\t',encoding='UTF-8')

# pandas实现方法
# import pandas as pd

# file_path = r"testdata/data.csv"
# csv = pd.read_csv(file_path)
# for item in csv:
#     print(item)
