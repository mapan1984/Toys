#!/usr/bin/env python3
# -*- coding:utf-8 -*-

import os
from orm import Model, IntegerField, StringField

# type("User", Model,
#       __mappings__ = {'id':IntegerField('id'), "name":StringField('username')}
#       __table__ = 'User')
class User(Model):
    id = IntegerField('id')
    email = StringField('email')
    name = StringField('username')


# __mappings__ = {'id':IntegerField('id'),'name':StringField('username')}
# __table__ = 'User'
# id = 123
# name = 'mapan'
# email = 'lala@papa.com'
user = User(id = 1, name = 'mapan', email = "lala@papa.com")

db_file = os.path.join(os.path.dirname(__file__), 'test.db')
if os.path.isfile(db_file):
    os.remove(db_file)

User.add_table_to_db(db_file)
user.add_column_to_table(db_file)
User.get_by(db_file, 'id', '1')
