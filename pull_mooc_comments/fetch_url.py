# -*- coding: utf-8 -*-
"""
Created on Mon Nov  9 20:37:42 2020

@author: hzsdl
"""
import re
import time
import os
from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException


def create_a_file(types):
    f=open(save_path+"\\"+str(course_types[i])+".txt","a+")
    return f
def get_one_page_all_course_urls(types):
    """
    返回课程数目
    """
    
    f=create_a_file(types)
    #等待javascript加载
    try:
        time.sleep(2)
        clicks=driver.find_elements_by_css_selector('div[class="_1gBJC"]>*')
        for button_course in clicks:
            #获取一个页面所有课程的url
            webdriver.ActionChains(driver).move_to_element(button_course).click(button_course).perform()
            driver.switch_to.window(driver.window_handles[-1])
            #将处理对象变为新标签页面，否则浏览器操作对象会找不到要操作页面中的元素
            driver.find_element_by_css_selector("div[class='ux-dropdown course-enroll-info_course-info_term-select_dropdown']").click()
            term_link_buttons=driver.find_elements_by_css_selector("ul[class='ux-dropdown_listview th-bd2']>*")
            term_link_buttons[0].click()
            temp_url=driver.current_url
            #https://www.icourse163.org/course/SWJTU-1001911007,course替换成learn
            true_url=re.sub(r"/course","/learn",temp_url)
            print(true_url)
            f.write(true_url+"\n")
            driver.close()
            driver.switch_to.window(driver.window_handles[0])
    except:
        pass
    finally:
        f.close()
    return len(clicks)
    

def go_to_next_clicks(types):
    #得到下一页的课程url
    """
    """
    try:
        driver.find_element_by_link_text("下一页").click()
        last_tag=get_one_page_all_course_urls(types)
        return last_tag
    except NoSuchElementException as e:
        #捕获最后一页异常
        print(e)

def select_course_type(i):
    """
    选择计算机、经管等课程类别
    i为[0,10]
    """
    url="https://www.icourse163.org/channel/2001.htm"
    driver=webdriver.Chrome(r"C:\Users\hzsdl\AppData\Local\Programs\Python\Python38\chromedriver.exe")
    driver.get(url)
    course_types=driver.find_elements_by_xpath("//span[@class='_2MR7-']")
    course_types[i].click()
    return driver
    
def save_a_type(driver,types="course_urls"):
    """
    真正抓取和保存的逻辑
    """
    print(types)
    get_one_page_all_course_urls(types)
    
    last_tag=20
    while last_tag==20:
        last_tag=go_to_next_clicks(types)
    return 1
start_time=time.time()

#save_path=r"E:\360MoveData\Users\hzsdl\Desktop"
save_path=os.getcwd()
course_types=["计算机","理学","工学","经济管理","文史哲","艺术设计","心理学","医药卫生","法学","教育教学","农林园艺"]

for i in range(0,11):
    driver=select_course_type(i)
    save_a_type(driver,i)
end_time=time.time()
print("程序执行了",(end_time-start_time)/60)
