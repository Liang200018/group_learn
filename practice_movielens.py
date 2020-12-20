# -*- coding: utf-8 -*-
"""
Created on Wed Dec  9 22:47:06 2020

@author: hzsdl
"""

# In[]
import os
import json

import pandas as pd
import numpy as np
import seaborn as sbon

DIR = "E:\git_repository\python\pydata-book"
datasets_dir = os.path.join(DIR, "datasets")
unames = ['user_id', 'gender', 'age', 'occupation', 'zip']
users = pd.read_table(datasets_dir+"\\movielens\\users.dat",
                      header=None, names=unames, delimiter="::", engine='python')
rnames = ['user_id', 'movie_id', 'rating', 'timestamp']
ratings = pd.read_table(datasets_dir+"\\movielens\\ratings.dat",
                      header=None, names=rnames, delimiter="::", engine='python')
mnames = ['movie_id', 'title', 'genres']
movies = pd.read_table(datasets_dir+"\\movielens\\movies.dat",
                      header=None, names=mnames, delimiter="::", engine='python')

# In[]
'''
可以做些什么？
一、电影层次
计算电影的综合得分（排分最高的10位）、电影类型的分布、
二、用户层次
用户的各种分布、
三、观影层次（即评分层次）
热度高的电影：一个时间段内，评分数多的电影
性别、年龄相同下，电影的平均得分
'''
# In[]
# 电影类型分布
def gen_bar(count_values):
    '''画条形分布图并且加上数据标签'''
    ax = sbon.barplot(x=count_values.values, y=count_values.index)
    for p in ax.patches:
        height = p.get_height()
        width = p.get_width()
        ax.text(x=width+3, y=p.get_y()+(height/2), s="{:.0f}".format(width), va='center')
        
split_genre = movies['genres'].str.split('|')
# array(list['','',''],list[],list[])需要转换为嵌套的列表
genres_df = pd.DataFrame(list(split_genre.values))
genres_array = genres_df.values.reshape(-1)
flatten_genres_df = pd.DataFrame(genres_array)
count_genres = flatten_genres_df[0].value_counts()
gen_bar(count_genres[:10])

# In[]
gen_bar(count_genres[:])
# In[]
# 观影层次,考虑性别因素，不考虑性别因素
# 用户年龄和性别评分,年龄和职业经过编码
age_typer = {
        '1':  "Under 18",
	    '18':  "18-24",
	    '25':  "25-34",
	    '35':  "35-44",
	    '45':  "45-49",
	    '50':  "50-55",
	    '56':  "56+"}
users_ratings_movies = pd.merge(users, pd.merge(ratings, movies))
users_ratings_movies['age'] = users_ratings_movies['age'].astype('str')
users_ratings_movies['age'].replace(age_typer, inplace=True)
# 全部电影的平均得分
mean_ratings = users_ratings_movies.pivot_table(values='rating', 
                                 index=['title'], columns=['gender'], aggfunc=np.mean)
ratings_by_title = users_ratings_movies.groupby('title').size()
# 评分用户个数大于250的电影
active_titles = ratings_by_title[ratings_by_title>250].index
mean_ratings = mean_ratings.loc[active_titles]

# In[]
# 计算女性用户最喜欢的电影
#import matplotlib.pyplot as plt
#fig, axes = plt.subplots(2,1)
top_female_ratings = mean_ratings.sort_values(by=['F'], ascending=False)
gen_bar(top_female_ratings['F'][:20])
# In[]
# 计算男性用户最喜欢的电影
top_male_ratings = mean_ratings.sort_values(by=['M'], ascending=False)
gen_bar(top_male_ratings['M'][:20])
# In[]
# 计算男女观影差异大
mean_ratings['diff'] = mean_ratings['F'] - mean_ratings['M']
sorted_by_diff = mean_ratings['diff'].sort_values(ascending=False)
gen_bar(sorted_by_diff[0:10])
# In[]
gen_bar(-sorted_by_diff[-10:])

# In[]
# 找出分歧最大的电影，不考虑性别因素
std_ratings = users_ratings_movies.pivot_table(values='rating', 
                                 index=['title'], aggfunc=np.std)
ratings_by_title = users_ratings_movies.groupby('title').size()
# 过滤评分用户个数大于250的电影
active_titles = ratings_by_title[ratings_by_title>250].index
std_ratings = std_ratings.loc[active_titles]
sorted_std_ratings = std_ratings['rating'].sort_values(ascending=False)
gen_bar(sorted_std_ratings[:10])
