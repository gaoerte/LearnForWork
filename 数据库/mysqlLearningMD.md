# sql学习笔记

## DISTINCT

顾名思义，它指示数据库只返回不同的值

DISTINCT 关键字作用于所有的列，不仅仅是跟在其后的那一列。例 如，你指定 SELECT DISTINCT vend_id, prod_price，则 9 行里的 6 行都会被检索出来，因为指定的两列组合起来有 6 个不同的结果。

## 限制结果

📊 主流数据库限制查询行数方法对比

| 数据库类型       | 语法方案        | 示例                                      | 特点说明                     |
|------------------|----------------|------------------------------------------|----------------------------|
| MySQL/MariaDB    | `LIMIT`子句    | `SELECT * FROM table LIMIT 5`            | 最简单直观的语法             |
| PostgreSQL       | `LIMIT`子句    | `SELECT * FROM table LIMIT 5`            | 同MySQL语法                |
| SQL Server       | `TOP`关键词    | `SELECT TOP 5 * FROM table`              | 需放在SELECT后              |
| Oracle           | `ROWNUM`伪列   | `SELECT * FROM table WHERE ROWNUM <= 5` | 需在WHERE中使用             |
| SQLite           | `LIMIT`子句    | `SELECT * FROM table LIMIT 5`            | 同MySQL语法                |
| DB2              | `FETCH`子句    | `SELECT * FROM table FETCH FIRST 5 ROWS ONLY` | 标准SQL语法（最规范）      |

## offset

`LIMIT 5 OFFSET 5`指示 MySQL 等 DBMS 返回从第 5 行起的 5 行数据。 第一个数字是检索的行数，第二个数字是指从哪儿开始(索引从0开始)。

MySQL、MariaDB 和 SQLite 可以把`LIMIT 4 OFFSET 3`语句简化为`LIMIT 3,4`。使用这个语法，逗号之前的值对应 OFFSET，逗号之后的值对应 LIMIT（反着的，要小心）。

## 注释

```sql

-- 这是一条注释

# 这在有些dbms是一条注释

/* 多行注释*/ 
SELECT  vend_id, prod_price
FROM products
limit 5,2;
```

## 排序

### ORDER BY 默认升序

在指定一条`ORDER BY`子句时，应该保证它是`SELECT`语句中最后一 条子句。如果它不是最后的子句，将会出错。

### DESC 降序

```sql
SELECT prod_id, prod_price, prod_name FROM Products
ORDER BY prod_price DESC, prod_name;
```

DESC 关键字只应用到直接位于其前面的列名。

### ASC 升序(默认,一般不用)

在字典（dictionary）排序顺序中，A 被视为与 a 相同，这是大多数数 据库管理系统的默认做法。但是，许多 DBMS 允许数据库管理员在需 要时改变这种行为（如果你的数据库包含大量外语字符，可能必须这 样做）。
这里的关键问题是，如果确实需要改变这种排序顺序，用简单的`ORDER BY`子句可能做不到。你必须请求数据库管理员的帮助。

## 过滤

`NULL`和非匹配 通过过滤选择不包含指定值的所有行时，你可能希望返回含`NULL`值的行。但是这做不到。因为`NULL`比较特殊，所以在进行匹配过滤或非匹配过滤时，不会返回这些结果。

### WHERE

#### 操作符

| 操作符类型       | 操作符符号      | 描述                           | 示例                                            |
|------------------|----------------|-------------------------------|------------------------------------------------|
| **比较操作符**   | `=`            | 等于                           | `WHERE age = 25`                               |
|                  | `<>` 或 `!=`   | 不等于                         | `WHERE status <> 'inactive'`                  |
|                  | `<`            | 小于                           | `WHERE price < 100`                           |
|                  | `>`            | 大于                           | `WHERE score > 90`                            |
|                  | `<=`           | 小于等于                       | `WHERE quantity <= 10`                        |
|                  | `>=`           | 大于等于                       | `WHERE rating >= 4.5`                          |
| **范围操作符**   | `BETWEEN`      | 在某个范围内                   | `WHERE age BETWEEN 18 AND 30`                 |
|                  | `IN (...)`     | 在指定值列表中                 | `WHERE country IN ('US', 'CA', 'UK')`         |
|                  | `NOT IN (...)` | 不在指定值列表中             | `WHERE department NOT IN (2, 5)`              |
| **模式匹配**     | `LIKE`         | 模式匹配（区分大小写）         | `WHERE name LIKE 'John%'`                     |
|                  | `ILIKE`        | 模式匹配（不区分大小写）       | `WHERE email ILIKE '%@gmail.com'` (PostgreSQL)|
|                  | `NOT LIKE`     | 不匹配指定模式                 | `WHERE filename NOT LIKE '%.tmp'`             |
| **空值判断**     | `IS NULL`      | 值为空                         | `WHERE phone IS NULL`                         |
|                  | `IS NOT NULL`  | 值不为空                       | `WHERE email IS NOT NULL`                     |
| **逻辑操作符**   | `AND`          | 逻辑与（两个条件都满足）       | `WHERE age > 18 AND country = 'US'`           |
|                  | `OR`           | 逻辑或（满足任一条件）         | `WHERE status = 'active' OR balance > 0`     |
|                  | `NOT`          | 逻辑非                         | `WHERE NOT (status = 'canceled')`             |
| **组合查询**     | `EXISTS`       | 子查询返回结果                 | `WHERE EXISTS (SELECT 1 FROM orders)`         |
|                  | `ANY`/`SOME`   | 满足子查询任一结果             | `WHERE salary > ANY (SELECT base_salary...)` |
|                  | `ALL`          | 满足子查询所有结果             | `WHERE score >= ALL (SELECT passing_score...)`|
| **JSON操作**     | `->>`          | 提取JSON值并转为文本           | `WHERE profile->>'role' = 'admin'` (JSON字段)|
|                  | `@>`           | JSON包含（PostgreSQL）         | `WHERE tags @> '["urgent"]'`                 |
| **高级操作**     | `SIMILAR TO`   | 正则表达式匹配                 | `WHERE name SIMILAR TO 'M(ar)?k'`            |
|                  | `~`            | POSIX正则匹配（区分大小写）    | `WHERE email ~ '^[a-z]+@[a-z]+\\.com$'`      |
|                  | `~*`           | POSIX正则匹配（不区分大小写）  | `WHERE email ~* 'gmail\\.com$'`             |

### BETWEEN

在使用`BETWEEN`时，必须指定两个值——所需范围的低端值和高端值，且左边小于右边。这两个值必须用`AND`关键字分隔。`BETWEEN`匹配范围中所有的值，包括指定的开始值和结束值。

### AND

要通过不止一个列进行过滤，可以使用`AND`操作符给`WHERE`子句附加条件。

### OR

`OR`操作符与`AND`操作符正好相反，它指示DBMS检索匹配任一条件的行。事实上，许多DBMS在`OR WHERE`子句的第一个条件得到满足的情况下，就不再计算第二个条件了

### 求值顺序

```sql
SELECT prod_name, prod_price FROM Products
WHERE vend_id = 'DLL01' OR vend_id = 'BRS01'
AND prod_price >= 10;
```

SQL（像多数语言一样）在处理`OR`操作符前，优先处理`AND`操作符。 换句话说，由于 AND 在求值过程中优先级更高，操作符被错误地组合了。此问题的解决方法是使用圆括号对操作符进行明确分组。

任何时候使用具有`AND`和`OR`操作符的`WHERE`子句，都应该使用圆括号明确地分组操作符。不要过分依赖默认求值顺序，即使它确实如你希望的那样。

### IN

```sql
SELECT prod_name, prod_price FROM Products
WHERE vend_id IN ('DLL01','BRS01') ORDER BY prod_name;
```

`IN`操作符的优点如下。

- 在有很多合法选项时，`IN`操作符的语法更清楚，更直观。
- 在与其他`AND`和`OR`操作符组合使用`IN`时，求值顺序更容易管理。
- `IN`操作符一般比一组`OR`操作符执行得更快。
- `IN`的最大优点是可以包含其他`SELECT`语句，能够更动态地建立`WHERE`子句。

### NOT

大多数DBMS允许使用 `NOT` 否定任何条件

## 谓词，操作符和通配符

| 概念                 | 定义                             | 功能角色             | 在SQL中的定位                  | 典型示例                                  |
|----------------------|----------------------------------|---------------------|--------------------------------|------------------------------------------|
| **谓词 (Predicate)** | 用于筛选数据的布尔表达式         | 整体过滤器           | WHERE/HAVING子句的核心内容      | `WHERE age > 18 AND name LIKE 'J%'`      |
| **操作符 (Operator)** | 执行特定操作的符号/关键字        | 谓词的组成单元       | 构建谓词的基本元素              | `>`, `=`, `LIKE`, `AND`, `IN`, `BETWEEN` |
| **通配符 (Wildcard)**| 用于模式匹配的特殊字符           | 操作符的辅助工具     | 特定操作符的参数                | `%`, `_`, `[a-z]`, `*`                   |

通配符搜索只能用于文本字段（字符串），非文本数据类型字段不能使用通配符搜索。

### LIKE

#### %

最常使用的通配符是百分号（%）。在搜索串中，`%`表示任何字符出现任意次数。例如，为了找出所有以词 `Fish` 起头的产品，可写以下的 `SELECT` 语句：

```sql
SELECT prod_id, prod_name FROM Products
WHERE prod_name LIKE 'Fish%y' 
  OR prod_name LIKE '%bean bag%';
```

根据 DBMS 的不同及其配置，搜索可以是区分大小写的。

有些 DBMS 用空格来填补字段的内容。例如，如果某列有 50 个字符， 而存储的文本为`Fish bean bag toy`（17 个字符），则为填满该列需 要在文本后附加 33 个空格。这样做一般对数据及其使用没有影响，但 是可能对上述 SQL 语句有负面影响。子句 `WHERE prod_name LIKE 'F%y'`只匹配以 F 开头、以 y 结尾的 prod_name。如果值后面跟空格， 则不是以 y 结尾，所以 `Fish bean bag toy` 就不会检索出来。简单 的解决办法是给搜索模式再增加一个%号：`'F%y%'`还匹配 y 之后的字符（或空格）。更好的解决办法是用函数去掉空格。

#### _

匹配单个字符，且DB2不支持`_`。

```sql
SELECT prod_id, prod_name FROM Products
WHERE prod_name LIKE '__ inch teddy bear';
```



## 一些需要注意的地方

### 精度

黄金法则：​涉及金钱计算必用 DECIMAL，地理坐标可用 DOUBLE，其他场景优先测试误差容忍度。

### 字符串

使用''

