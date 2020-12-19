# -*- coding: utf-8 -*-
"""
Created on Sat Dec 19 10:56:52 2020
解析文件的要求：
    1、中文括号变为英文括号()
    2、题干描述必须在同一行， 可以用txt文件
    3、目前只支持选择题， ABCD四个选项占一行， 选项与选项之间有空格（个数无要求）即可
初步练习状态机相关
@author: hzsdl
"""

import re 
import random

class Parse_Test():
    def __init__(self):
        self.number = 0
        self.questions = []
        
    def open_file(self, path, mode):
        self.f = open(path, mode, encoding="utf-8")
        return self.f
        
    def close_file(self):
        self.f.close()
    
    def parse_one_qa(self):
        """传入打开的文件对象,选项和题干各自占一行"""
        f = self.f
        tag = 0
        
        q_pattern = re.compile(r"([0-9]+)[、|.|、]?\s*?([\u4e00-\u9fa5|a-zA-Z0-9|“”：:，,、.]+)(\s*[(]\s*[)].*)")
        a_pattern = re.compile(r"([ABCD])[、.\W]\s*([\u4e00-\u9fa5|\u2460-\u2468|a-zA-Z0-9|“”：:，,、.]*)")
        while 1:
            line = f.readline()
            if line:
                qa = line.strip()
                if tag == 0:
                    question = re.search(q_pattern, qa)
                    if question :
                        seq = question.group(1)
                        descrip = question.group(2)
                        other = question.group(3)
                        if other:
                            other = re.sub("[(]\s*[)]", '', other)
                            other = other.strip()
                            descrip = descrip + other
                    #print(question.group())
                    #print(seq)
                    #print(descrip)
                elif tag == 1:
                    answer = re.findall(a_pattern, qa)
                    if answer :
                        # answer [('A', '何雄楚'), ('B', '梁其键'), ('C', '廖平胜'), ('D', '刘海峰')]
                        answer_dict = dict(answer)
                        tag = 2
                else:
                    pass
                if tag == 2:
                    if question and answer:
                        qa_dict = {'seq':seq, 'descrip':descrip, 'answer':answer_dict}
                        self.number += 1
                        self.questions.append(qa_dict)
                    if question and answer is None:
                        print("匹配失败，不是答案")
                    if answer and question is None:
                        print("匹配失败，不是问题")
                tag = int((tag + 1) % 3)

            else:
                break
        
        return self.questions

class RandomSelect:
    def __init__(self, things, number):
        """things为一个列表"""
        self.max_number = number
        self.things = things

    def select_randint(self, number):
        if number <= self.max_number:
            with open("test.txt", "w") as f:
                selected = set()
                for i in range(0, number):
                    while 1 :
                        q = random.randint(0, self.max_number-1)
                        if q not in selected:
                            break
                    selected.add(q)
                    seq = self.things[q]['seq']
                    descrip = self.things[q]['descrip']
                    answer = self.things[q]['answer']
                    f.write("{0}、{1}\n".format(i+1, descrip))
                    for key, value in answer.items():
                        f.write(key + "、" + value + "\n")
                f.close()
            selected = [q + 1 for q in selected ]
            print("选择了第{0}题".format(selected))
        else:
            print("selected number is too big!")
    



    
if __name__ == "__main__":
    p = Parse_Test()
    p.open_file("questions.txt", "rt+")
    result = p.parse_one_qa()
    p.close_file()
    print("一共提取了{0}/个题目".format(p.number))
    rs = RandomSelect(p.questions, p.number)
    rs.select_randint(20)
