# -*- coding: utf-8 -*-
"""
Created on Sat Dec  5 12:37:35 2020

@author: hzsdl
"""
import os

file_path = r"E:\pdf电子书"

def walk(file):
    # 如果是目录，返回目录，并且遍历目录下的文件
    if os.path.isdir(file):
        # yield file+"\\"
        for f in os.listdir(file):
            yield from walk(file+"\\"+f)
    # 如果是文件，直接返回文件
    else:
        yield file
        
def select(name, and_filter=None, or_filter=None, verbose=False):
    '''根据关键词筛选,verbose留作筛选选项'''
    and_filter = [] if and_filter is None else and_filter
    or_filter = [] if or_filter is None else or_filter
    if not (isinstance(and_filter,list) and isinstance(or_filter,list)):
        raise TypeError("请传入一个列表")    
    for part in and_filter:
        if part in name or part.lower() in name:
            pass
        else:
            return False
    if or_filter == []:
        return True
    else:
        for part in or_filter:
            if part in name or part.lower() in name:
                return True
        return False
    
def print_verbose(file,option=False):
    '''option默认不打印路径，只打印文件名字'''
    if option == False:
        dirs, name = os.path.split(file)
        print(name)
    else:
        print(file)
        
    
count = 0
and_filter = ['.pdf']
or_filter = ['Python','机器学习', 'SQL']
for file in walk(file_path):
    dirs, name = os.path.split(file)
    if select(name, and_filter,or_filter):
        count =count + 1
        print_verbose(file, option=False)
print("\n你还有{}本书要看！".format(count))    