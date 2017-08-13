# 一个ORM框架

`OrmDB`是利用Python元类实现ORM

## 使用这个ORM框架

1. 定义一个User类来操作对应的数据库表User

        class User(Model):
            # 定义类的属性到列的映射：
            # 第一个值为主键
            id = IntegerField('id')
            name = StringField('username')
            email = StringField('email')
            password = StringField('password')

2. 创建一个实例：

        u = User(id=12345, name='Michael', email='test@orm.org', password='my-pwd')

3. 保存到数据库：

        User.add_table_to_db('test.db')
        u.add_column_to_table('test.db')
