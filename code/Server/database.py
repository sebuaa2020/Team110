# coding = utf-8
import pymysql
import time


class DataBase:

    def __init__(self):
        self.db = pymysql.connect("localhost", "root", "EricZY1231", "ros_user", charset='utf8')
        self.cursor = self.db.cursor()
        self.user = "root"

    def logIn(self, user, pwd):
        user = user.strip()
        sql = "select pwd from User where Id = '{}'".format(user)
        try:
            self.cursor.execute(sql)
            result = self.cursor.fetchall()
            if len(result) > 0:
                row = result[0]
                if pwd == row[0]:
                    self.user = user
                    return 1
                else:
                    return 0
            else:
                return -1
        except:
            return -2

    def signUp(self, user, pwd):
        user = user.strip()
        if len(user) == 0 or len(pwd) == 0:
            return -2
        try:
            sql = "select * from User where Id ='{}'".format(user)
            self.cursor.execute(sql)
            if len(self.cursor.fetchall()) > 0:
                return -1
            sql = "insert into User(Id, pwd) values ('{}', '{}')".format(user, pwd)
            self.cursor.execute(sql)
            self.db.commit()
            self.user = user
            return 1
        except:
            self.db.rollback()
            return -2

    def advice(self, advice):
        current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
        sql = "insert into Advice(Id, advice, `time`) values ('{}', '{}', '{}')".format(self.user, advice, current_time)
        try:
            self.cursor.execute(sql)
            self.db.commit()
            return 1
        except:
            self.db.rollback()
            return -1

    def connect(self):
        self.db = pymysql.connect("localhost", "root", "EricZY1231", "ros_user", charset='utf8')
        self.cursor = self.db.cursor()
        self.user = "root"

    def disconnect(self):
        self.db.close()
        self.user = "root"
