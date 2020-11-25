# -*- coding: utf-8 -*-
"""
Created on Sun Nov 22 21:25:16 2020

@author: hzsdl
"""

# In[]
import urllib
import time
from http.cookiejar import CookieJar

import pytesseract
from PIL import Image
from selenium import webdriver

class VerifyCode():
    def __init__(self):
        self.driver=webdriver.Chrome()
        self.driver.get(r"http://spoc.ccnu.edu.cn/starmoocHomepage")

    def get_picture(self):
        path=r"E:\360MoveData\Users\hzsdl\Desktop\下载.png"
        #系统缩放变成100%
        self.driver.execute_script('document.body.style.zoom="0.8"')
        self.driver.save_screenshot(path)
        verify_img=self.driver.find_element_by_id("verifCodeImg")
        location, size= verify_img.location, verify_img.size
        left, top = location['x'], location['y']
        width, height = size['width'], size['height']
        right, bottom = left + width, top + height
        img=Image.open(path)
        img_snip=img.crop((left,top,right,bottom))
        return img_snip 
        
    def img_to_str(self):
        img=self.get_picture()
        pytesseract.pytesseract.tesseract_cmd = r"E:\安装软件\tesseract\Tesseract-OCR\tesseract.exe"
        result=pytesseract.image_to_string(img)
        print(result)
        return result
        
    def login(self,username,password):
        self.driver.find_element_by_id("verifCode").send_keys(self.img_to_str())
        time.sleep(2)
        self.driver.execute_script('document.body.style.zoom="1"')
        self.driver.find_element_by_id("loginName").send_keys(username)
        self.driver.find_element_by_id("password").send_keys(password)
        submit=self.driver.find_element_by_id("loginBtn")
        submit.click()

ver=VerifyCode()
ver.get_picture()
username=input("请输入你的学号：")
password=input("请输入你的密码：")
ver.login(username,password)
