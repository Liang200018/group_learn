# -*- coding: utf-8 -*-
"""
Created on Thu Nov 19 12:58:41 2020

@author: hzsdl
"""

import os
import os.path

from get_discussion import get_all_discussion

cur_dir=os.getcwd()
print(cur_dir)
files=os.listdir(cur_dir)
for file in files:
    #遍历每个课程类型的文件夹
    path_file=cur_dir+"\\"+file  #E:\360MoveData\Users\hzsdl\Desktop\pull_mooc_comments\医药卫生.txt
    print(path_file)
    name,txt=os.path.splitext(path_file)
    # name=E:\360MoveData\Users\hzsdl\Desktop\pull_mooc_comments\医药卫生
    # txt=".txt"
    if txt == ".txt":
        #创建文件夹
        if not os.path.exists(name):
            save_path=os.mkdir(name)
            
        #遍历url文件中的链接
        with open(file) as f:
            course_urls=f.readlines()
            for course_url in course_urls:
                course_url=course_url.strip("\n")
                get_all_discussion(course_url,name)
            f.close()
            
            
