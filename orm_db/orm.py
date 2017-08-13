import sqlite3


class Field(object):

    def __init__(self, field_name, field_type):
        self.field_name = field_name
        self.field_type = field_type

    def __str__(self):
        return '<%s: %s: %s>'\
                % (self.__class__.__name__, self.field_name, self.field_type)


class StringField(Field):

    def __init__(self, field_name):
        super(StringField, self).__init__(field_name, 'varchar(100)')


class IntegerField(Field):

    def __init__(self, field_name):
        super(IntegerField, self).__init__(field_name, 'bigint')


# metaclass
class ModelMetaclass(type):

    def __new__(mcs, name, bases, attrs):
        if name == 'Model':
            return type.__new__(mcs, name, bases, attrs)
        print('Found model: %s' % name)
        mappings = dict()
        for k, v in attrs.items():
            if isinstance(v, Field):
                print('Found mapping: %s ==> %s' % (k, v))
                mappings[k] = v
        for k in mappings:
            attrs.pop(k)
        # 修改原有attrs
        attrs['__mappings__'] = mappings #保存属性和列的映射关系
        attrs['__table__'] = name     #假设表名和类名一致
        # return type(name, bases, attrs)
        #修改父类type的new创建方法的attrs
        return super(ModelMetaclass, mcs).__new__(mcs, name, bases, attrs)

# ModelMetaclass.__new__()
# type("Model", dict, {'__mappings__':mappings, '__table__':"Model"})
# attrs['__mappings__'] = mappings = {k:Field}
# __mappings__ = mappings
# __table__ = name
class Model(dict, metaclass=ModelMetaclass):

    def __init__(self, **kw):
        super(Model, self).__init__(**kw)

    @classmethod
    def add_table_to_db(cls, db_name):

        field_name = []
        field_type = []
        for k, v in cls.__mappings__.items():
            field_name.append(k)
            field_type.append(v.field_type)
        print(field_name, field_type)
        s = []
        length = field_name.__len__()
        for i in range(length):
            if i == 0:
                s.append(field_name[i] + " "\
                        + field_type[i] + " primary key, ")
            elif i == length-1:
                s.append(field_name[i] +" "+ field_type[i])
            else:
                s.append(field_name[i] +" "+ field_type[i])
                s.append(",")
        print(s)
        exe = "".join(s)
        print(exe)

        conn = sqlite3.connect(db_name)
        cursor = conn.cursor()
        create = 'create table %s (%s)'\
                     % (cls.__table__, exe) #(field_name field_type)
        print(create)
        cursor.execute(create)
        print('cursor close')
        cursor.close()
        print('conn commit')
        conn.commit()
        print('conn close')
        conn.close()

    def add_column_to_table(self, db_name):
        conn = sqlite3.connect(db_name)
        cursor = conn.cursor()
        key = []
        val = []
        for k in self.__mappings__.keys():
            key.append(k)
            key.append(',')
            key.append(" ")
            val.append("\'")
            val.append(str(getattr(self, k, None)))
            val.append("\'")
            val.append(",")
            val.append(" ")
        for i in range(2):
            key.pop()
            val.pop()
        insert = 'insert into %s (%s) values (%s)'\
                % (self.__table__, "".join(key), "".join(val))
        print(insert)
        cursor.execute(insert)
        print('cursor rowcount: %s' % cursor.rowcount)
        print('cursor close')
        cursor.close()
        print('conn commit')
        conn.commit()
        print('conn close')
        conn.close()

    @classmethod
    def get_by(cls, db_name, key, value):
        conn = sqlite3.connect(db_name)
        cursor = conn.cursor()
        exe = 'select * from %s where %s=?' % (cls.__table__, key)
        print(exe)
        cursor.execute(exe, value)
        values = cursor.fetchall()
        print(values)
        cursor.close()
        conn.close()

    def __getattr__(self, key):
        try:
            return self[key]
        except KeyError:
            raise AttributeError(r"'Model' object has no attribute '%s'"\
                                                                  % key)

    def __setattr__(self, key, value):
        self[key] = value
