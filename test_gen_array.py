# -*- coding: utf-8 -*-
"""
Created on Sat Dec 12 20:28:06 2020

@author: hzsdl
"""

# In[]
import time
from decimal import Decimal, getcontext
getcontext().prec=20
import pandas as pd
def time_decorator(func):
    def wrapper(*args, **kwargs):
        s = time.time()
        return_value = func(*args, **kwargs)
        e = (time.time()-s)
        print("execute {0} {1} s".format(func.__name__, e))
        return return_value, e
    return wrapper

# 布尔型数组

def gen_narray(low, high, ndim): 
# 整数数组
    shape = list(ndim) if isinstance(ndim,(list,tuple)) else [ndim]
    ndim = len(shape)
    if ndim == 1:
        return np.array([np.random.randint(low, high) for i in range(0, shape[-1])])
    else:
        arr = []
        for i in range(0, shape[-2]):
            if len(shape) > 2 :
                a = gen_narray(low, high, shape[1:-1])
            else:
                a = gen_narray(low, high, shape[1])
            arr.append(a)
        return np.array(arr)
@time_decorator
def way1(z):
    shape = 2**z
    a = gen_narray(-100, 100, (shape, shape)) 
    return a

@time_decorator
def way2(z):
    shape = 2**z
    a = np.random.randint(-100, 100, size=(shape, shape))
    return a

p = []
for i in range(0,15):
    a1, t1 = way1(i)
    a2, t2 = way2(i)
    try :
        p.append(t1/t2)
    except ZeroDivisionError:
        p.append(Decimal(0))
# In[]
import re
df = pd.read_table(r"E:\360MoveData\Users\hzsdl\Desktop\time.txt" ,header=None)
s_time = df.values.astype(str).flatten()
time_way1 = list(map(
                    lambda x: re.findall("way1 (\d+.\d+)", x)[0], 
                     s_time[0::2]))
time_way2 = list(map(
                    lambda x: re.findall("way2 (\d+.\d+)", x)[0], 
                    s_time[1::2]))
con_time = pd.Series(p, index=range(0,15))
con_time = con_time.astype(float)
clean_time = pd.DataFrame({"way1":time_way1, "way2": time_way2, "rate":con_time}, index=range(0,15))
clean_time[['way1','way2']] = clean_time[['way1','way2']].astype(float)

# In[]
import matplotlib.pyplot as plt
fig,ax1 = plt.subplots()
ax2 = ax1.twinx()
ax1.plot(clean_time.index, clean_time['way1'],'g')
ax1.plot(clean_time.index, clean_time['way2'],'y')
ax2.plot(clean_time.index, clean_time['rate'],'r')
ax1.set_xlabel('matrix 2**n')    
ax2.set_ylabel('rate',color = 'r')
ax1.set_ylabel('seconds',color = 'g')