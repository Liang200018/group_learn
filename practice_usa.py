# -*- coding: utf-8 -*-
"""
Created on Mon Dec  7 21:32:58 2020

@author: hzsdl
"""
import os
import json
from collections import defaultdict
from collections import Counter
from operator import itemgetter

import pandas as pd
import numpy as np
import seaborn as sbon

DIR = "E:\git_repository\python\pydata-book"
datasets_dir = os.path.join(DIR, "datasets")

f = open(datasets_dir+"\\bitly_usagov\\example.txt")

lines = (line for line in f)
records = [json.loads(line) for line in lines]
# In[1]
#采用defaudict和list
def get_counts(sequence):
    '''传入生成器，得到排名字典'''
    tz_dict = defaultdict(int)
    for t in sequence:
        if t.get('tz'):
            country, city = t['tz'].split('/',1)
            tz_dict[(country,city)] += 1
        else :
            pass
    
    return tz_dict

def topn(count_dict, n=10):
    '''得到前n名'''
    count_list = [(tz,count) for tz, count in zip(count_dict.keys(),count_dict.values())]
    #print(names)
    
    # 按country, city排序
    #tz_list.sort()
    #print(tz_list)
    # 按值排序
    count_list.sort(key=itemgetter(1), reverse=True)
    print(count_list[0:n])
    return count_list[0:n]

tz_dict = get_counts(records)    
rank = topn(tz_dict,10)
# In[]
# 采用Counter计数
counts=Counter(tz_dict)
counts.most_common(10)

# In[2]
# 采用pandas计数
#data = pd.DataFrame(data=tz_list)
#print(data.sort_values(by=data.columns[1],ascending=True))
tz = [t['tz'] for t in records if t.get('tz')]
df = pd.DataFrame(data=records)
print(df.info())

# In[3]
tz_counts = df['tz'].value_counts()
print(tz_counts[0:10])
# In[]
# 处理数据缺失值和空值
clean_tz = df['tz'].fillna("Missing")
clean_tz[clean_tz == ''] = "Unknown" 
clean_counts = clean_tz.value_counts()

def bar_topn(clean_counts,n=10):
    subset = clean_counts[0:n]
    plt = sbon.barplot(y=subset.index, x=subset.values)
bar_topn(clean_counts,10)
# In[]
# 浏览器
clean_a = df['a'].fillna("Missing")
clean_a[clean_a == ''] ="Unknown"
results = pd.Series([x.split()[0] 
                        for x in clean_a
                    ])
clean_a_counts = results.value_counts()
bar_topn(clean_a_counts, n=10)

# In[]
cdf = df[df.a.notnull()]
cdf['os'] = np.where(cdf.a.str.contains('Windows'), 'Winodws', 'Not Windows')
clean_tz= cdf['tz'].fillna("Missing")
clean_tz[clean_tz == ''] ="Unknown"
cdf['tz'] = clean_tz
by_os_tz = cdf.groupby(['tz','os'])
agg_counts = by_os_tz.size().unstack().fillna(0)
indexer = agg_counts.sum(1).sort_values()
subset_index = indexer[-10:].index
count_subset = agg_counts.loc[subset_index]
count_subset = count_subset.stack()
count_subset.name = 'total'
count_subset = count_subset.reset_index()
sbon.barplot(x='total', y='tz', hue='os', data=count_subset)

# In[]
# 标准化
def normed_total(group):
    group['total'] =group['total'] / group['total'].sum()
    return group
results = count_subset.groupby('tz').apply(normed_total)
sbon.barplot(x='total', y='tz', hue='os', data=results)