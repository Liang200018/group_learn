# -*- coding: utf-8 -*-
"""
Created on Sat Dec 12 15:29:49 2020

@author: hzsdl
"""
# In[]
import os

import pandas as pd

DIR = "E:\git_repository\python\pydata-book"
datasets_dir = os.path.join(DIR, "datasets")

rnames = ['user_id', 'movie_id', 'rating', 'timestamp']
ratings = pd.read_table(datasets_dir+"\\movielens\\ratings.dat",
                      header=None, names=rnames, delimiter="::", engine='python')
# In[]
# 计算时间段
import time
def timestamp_to_date(x, typer=1, _return_value='str'):
    
    def select_format_typer(typer):
        if typer == 1:
            return format_dict['date_time_24']
        elif typer == 2:
            return format_dict['date_time_12']
        else:
            return format_dict['date_time_week']
        
    if isinstance(x, (int,float)):
        _current_value = 'timestamp'
    elif isinstance(x, time.struct_time):
        _current_value = 'struct_time'
    elif isinstance(x, str):
        _current_value = 'str'
    forma = ['struct_time', 'str', 'timestamp'] 
    format_dict = {
            'date_time_24': "%Y-%m-%d,%H:%M:%S",
            'date_time_12': "%Y-%m-%d,%I:%M:%S",
            'date_time_week': "Y-%m-%d,%A,%I:%M:%S"
            }
    if _current_value == 'timestamp':
        if _return_value == 'str':
            # timestamp转换为str耗时长
            format_str = select_format_typer(typer)
            x_str = time.strftime(format_str, time.localtime(x))
            #x_str = time.localtime(x)
            return x_str
        elif _return_value == 'struct_time':
            return time.localtime(x)
        elif _return_value == 'timestamp':
            return x
        
    elif _current_value == 'struct_time':
        if _return_value == 'str':
            format_str = select_format_typer(typer)
            x_str = time.strftime(format_str, x)
            return x_str
        elif _return_value == 'struct_time':
            return x
        elif _return_value == 'timestamp':
            return time.mktime(x)
        
    elif _current_value == 'str':
        if _return_value == 'str':
            format_str = select_format_typer(typer)
            return x
        elif _return_value == 'struct_time':
            format_str = select_format_typer(typer)
            return time.strptime(x, format_str)
        elif _return_value == 'timestamp':
            format_str = select_format_typer(typer)
            return time.mktime(time.strptime(x, format_str))
# In[]
# 装饰器
def time_decorator(func):
    def wrapper(*args, **kwargs):
        start_time = time.time()
        return_value = func(*args, **kwargs)
        print("execute {0} 消耗了{1}(s)".format(func.__name__, time.time()-start_time))
        return return_value
    return wrapper
# In[]
# 测试map方法、用apply应用自己编写的函数，时间差异
def map_time_str(time_series):
    t1 = time_series.map(lambda x: time.strftime("%Y-%m-%d,%H:%M:%S", time.localtime(x)))
    return t1

def time_str(time_series):
    t1 = time_series.apply(timestamp_to_date, args=(1,'str'))
    return t1

def map_str_tuple(time_series):
    t1 = time_series.map(lambda x: time.strptime(x, "%Y-%m-%d,%H:%M:%S"))
    return t1

def str_tuple(time_series):
    t1 = time_series.apply(timestamp_to_date, args=(1,'struct_time'))
    return t1  

def map_tuple_time(time_series):
    t1 = time_series.map(lambda x: time.mktime(x))
    return t1

def tuple_time(time_series):
    t1 = time_series.apply(timestamp_to_date, args=(1,'timestamp'))
    return t1
 
way1 = time_decorator(map_time_str)
way2 = time_decorator(time_str)
t1 =way1(ratings['timestamp'])
t2 = way2(ratings['timestamp'])
way3 = time_decorator(map_str_tuple)
way4 = time_decorator(str_tuple)
t3 = way3(t1)
t4 = way4(t2)
way5 = time_decorator(map_tuple_time)
way6 = time_decorator(tuple_time)
t5 = way5(t3)
t6 = way6(t4)