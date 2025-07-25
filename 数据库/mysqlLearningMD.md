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

#### []

方括号通配符用来指定一个字符集，它必须匹配指定位置（通配符的位置）的一个字符。

**说明**：与前面描述的通配符不一样，并不是所有 DBMS 都支持用来创建集合的[]。微软的 `SQL Server` 支持集合，但是 `MySQL`，`Oracle`，`DB2`，`SQLite` 都不支持。

例如，找出所有名字以 J 或 M 起头的联系人，可进行如下查询：

```sql
SELECT cust_contact FROM Customers
WHERE cust_contact LIKE '[JM]%' ORDER BY cust_contact;
```

[JM]匹配方括号中任意一个字符，它也只能匹配单个字符。 因此，任何多于一个字符的名字都不匹配。[JM]之后的`%`通配符匹配第 一个字符之后的任意数目的字符，返回所需结果。
此通配符可以用前缀字符 `^`（脱字号）来否定。当然，也可以使用 `NOT` 操作符得出类似的结果。 `^` 的唯一优点是在使用多个 `WHERE` 子句时可以简化语法。

#### 使用通配符的技巧

通配符搜 索一般比前面讨论的其他搜索要耗费更长的处理时间。
**tips:**

- 不要过度使用通配符。如果其他操作符能达到相同的目的，应该使用
其他操作符。
- 在确实需要使用通配符时，也尽量不要把它们用在搜索模式的开始
处。把通配符置于开始处，搜索起来是最慢的。
- 仔细注意通配符的位置。如果放错地方，可能不会返回想要的数据。

## 计算字段

### 字段field

基本上与列（column）的意思相同，经常互换使用，不过数据库列一 般称为列，而字段这个术语通常在计算字段这种场合下使用。需要特别注意，只有数据库知道`SELECT`语句中哪些列是实际的表列， 哪些列是计算字段。从客户端（如应用程序）来看，计算字段的数据与 其他列的数据的返回方式相同。

在 SQL 语句内可完成的许多转换和格式化工作都可以直接在客户端 应用程序内完成。但一般来说，在数据库服务器上完成这些操作比在 客户端中完成要快得多。

### 拼接字段

#### 使用`+`, `||`和`concat()`函数

在 SQL 中的 `SELECT` 语句中，可使用一个特殊的操作符来拼接两个列。根据你所使用的 DBMS，此操作符可用`+`或两个`||`表示。SQL Server 使用 `+`。DB2、Oracle、PostgreSQL 和 SQLite 使用 `||`。在 MySQL 和 MariaDB 中，必须使用 特殊的函数。
MySQL中使用`concat()`函数。

```sql
SELECT concat(vend_name, ' (', vend_country, ')') AS vendor_info
FROM vendors
ORDER BY vend_name;
```

#### 使用`RTRIM()`, `LTRIM()`, `TRIM()`函数

分别是去掉字符串右边，左边的空格

```sql
SELECT RTRIM(vend_name) || ' (' || RTRIM(vend_country) || ')' FROM Vendors
ORDER BY vend_name;
```

#### `AS`和别名

在很多 DBMS 中，`AS` 关键字是可选的，不过最好使用它，这被视为一条最佳实践。
别名的名字既可以是一个单词，也可以是一个字符串。如果是后者，字符串应该括在引号中。虽然这种做法是合法的，但不建议这么去做。 多单词的名字可读性高，不过会给客户端应用带来各种问题。因此，别名最常见的使用是将多个单词的列名重命名为一个单词的名字。
别名有时也称为导出列（derived column），不管怎么叫，它们所代表 的是相同的东西。
别名还有其他用途。常见的用途包括在实际的表列名包含不合法的 字符（如空格）时重新命名它，在原来的名字含混或容易误解时扩 充它。

### 执行算术计算

```sql
SELECT prod_id,quantity,item_price, 
quantity*item_price 
AS expanded_price 
FROM OrderItems
WHERE order_num = 20008;
```

`SELECT` 语句为测试、检验函数和计算提供了很好的方法。虽然 `SELECT` 通常用于从表中检索数据，但是省略了 `FROM` 子句后就是简单地访问和 处理表达式，例如 `SELECT 3 * 2`;将返回 `6`，`SELECT Trim(' abc ')`; 将返回 `abc`，`SELECT Curdate()`;使用 `Curdate()`函数返回当前日期 和时间。现在你明白了，可以根据需要使用 `SELECT` 语句进行检验。

## 函数

一个 DBMS 都有特定的函数。事实上，只有少数几个函数被所有主要的 DBMS 等同地支持。

### 主流数据库系统函数语法差异对照表

| 功能描述                  | DB2                     | Oracle                   | PostgreSQL               | SQLite                 | MariaDB/MySQL         | SQL Server            |
|---------------------------|-------------------------|--------------------------|--------------------------|------------------------|-----------------------|-----------------------|
| **提取子字符串**          | `SUBSTR(string, start)` | `SUBSTR(string, start)`  | `SUBSTR(string, start)`  | `SUBSTR(string, start)`| `SUBSTRING(string, start)` | `SUBSTRING(string, start)` |
| **数据类型转换**          | `CAST(value AS type)`   | `TO_CHAR()`/`TO_NUMBER()`| `CAST(value AS type)`    | `CAST(value AS type)`  | `CONVERT(type, value)`| `CONVERT(type, value)` |
| **获取当前日期**          | `CURRENT_DATE`          | `SYSDATE`                | `CURRENT_DATE`           | `DATE('now')`          | `CURDATE()`           | `GETDATE()`           |
| **获取当前时间戳**        | `CURRENT_TIMESTAMP`     | `SYSTIMESTAMP`           | `CURRENT_TIMESTAMP`      | `DATETIME('now')`      | `NOW()`               | `CURRENT_TIMESTAMP`   |
| **空值处理**              | `COALESCE()`            | `NVL()`                  | `COALESCE()`             | `IFNULL()`             | `IFNULL()`            | `ISNULL()`            |
| **正则表达式匹配**        | `REGEXP_LIKE()`         | `REGEXP_LIKE()`          | `~` 运算符               | `REGEXP` 运算符        | `REGEXP` 运算符       | `LIKE` (有限支持)     |
| **日期格式化**            | `TO_CHAR(date, fmt)`    | `TO_CHAR(date, fmt)`     | `TO_CHAR(date, fmt)`     | `STRFTIME(fmt, date)`  | `DATE_FORMAT(date, fmt)` | `FORMAT(date, fmt)`   |
| **计算日期差**            | `DAYS_BETWEEN(date1, date2)` | `date1 - date2`      | `date1 - date2`          | `JULIANDAY(date1) - JULIANDAY(date2)` | `DATEDIFF(date2, date1)` | `DATEDIFF(unit, date1, date2)` |
| **生成唯一ID**            | `GENERATE_UNIQUE()`     | `SYS_GUID()`             | `GEN_RANDOM_UUID()`      | `RANDOMBLOB(16)`       | `UUID()`              | `NEWID()`             |
| **分页查询**              | `FETCH FIRST n ROWS`    | `ROWNUM`                 | `LIMIT n`                | `LIMIT n`              | `LIMIT n`             | `OFFSET n ROWS`       |
| **条件判断**              | `CASE...WHEN`           | `DECODE()`               | `CASE...WHEN`            | `CASE...WHEN`          | `IF(expr, true, false)` | `IIF(expr, true, false)` |
| **计算行号**              | `ROW_NUMBER() OVER()`   | `ROWNUM`                 | `ROW_NUMBER() OVER()`    | `ROW_NUMBER() OVER()`  | `ROW_NUMBER() OVER()` | `ROW_NUMBER() OVER()` |
| **数据类型检测**          | `TYPEOF()`              | `DUMP()`                 | `PG_TYPEOF()`            | `TYPEOF()`             | `CASE...WHEN`         | `SQL_VARIANT_PROPERTY()` |

### 文本处理函数

#### SQL 字符串函数速查表

| 函数名称             | 描述                            | 常见数据库实现差异                                     |
|----------------------|---------------------------------|-------------------------------------------------------|
| **LEFT(str, len)**   | 返回字符串左边的字符            | SQL Server: `LEFT()`；Oracle/MySQL: `SUBSTR(str, 1, len)` |
| **RIGHT(str, len)**  | 返回字符串右边的字符            | SQL Server: `RIGHT()`；PostgreSQL: `SUBSTR(str, LENGTH(str)-len+1)` |
| **LENGTH(str)**      | 返回字符串的长度                | MySQL: `CHAR_LENGTH()`；SQL Server: `LEN()`；Oracle: `LENGTHB()` (字节数) |
| **LOWER(str)**       | 将字符串转换为小写              | 所有数据库通用实现                                     |
| **UPPER(str)**       | 将字符串转换为大写              | 所有数据库通用实现                                     |
| **LTRIM(str)**       | 去掉字符串左边的空格            | 所有数据库通用实现                                     |
| **RTRIM(str)**       | 去掉字符串右边的空格            | 所有数据库通用实现                                     |
| **TRIM(str)**        | 去掉字符串两端的空格            | 标准SQL函数，多数现代数据库支持                        |
| **SUBSTR(...)**      | 提取子字符串                    | SQL Standard: `SUBSTRING()`；Oracle/DB2: `SUBSTR()`；SQL Server: `SUBSTRING()` |
| **SOUNDEX(str)**     | 返回字符串的SOUNDEX值 (语音匹配)| MySQL/MSSQL支持；PostgreSQL需扩展 `fuzzystrmatch`       |
| **REVERSE(str)**     | 反转字符串                      | MySQL/SQL Server: `REVERSE()`；PostgreSQL: 无原生支持 |

**notice:** `SUBSTR(string, pos, len)`函数中，pos从1开始计数

SOUNDEX 是一个将任何文 本串转换为描述其语音表示的字母数字模式的算法。SOUNDEX 考虑了类似的发音字符和音节，使得能对字符串进行发音比较而不是字母比 较。虽然 SOUNDEX 不是 SQL 概念，但多数 DBMS 都提供对 SOUNDEX 的支持。

### 日期处理函数

#### SQL 日期处理函数速查表

| 功能描述                  | 标准SQL                | MySQL/MariaDB         | PostgreSQL           | SQL Server           | Oracle               | SQLite              |
|---------------------------|------------------------|-----------------------|----------------------|----------------------|----------------------|---------------------|
| **当前日期**              | `CURRENT_DATE`         | `CURDATE()`           | `CURRENT_DATE`       | `CAST(GETDATE() AS DATE)` | `TRUNC(SYSDATE)`     | `DATE('now')`       |
| **当前时间**              | `CURRENT_TIME`         | `CURTIME()`           | `CURRENT_TIME`       | `CAST(GETDATE() AS TIME)` | `CURRENT_TIME`       | `TIME('now')`       |
| **当前时间戳**            | `CURRENT_TIMESTAMP`    | `NOW()`               | `CURRENT_TIMESTAMP`  | `GETDATE()`          | `SYSTIMESTAMP`       | `DATETIME('now')`   |
| **日期格式化**            | `TO_CHAR(date, fmt)`   | `DATE_FORMAT(date, fmt)` | `TO_CHAR(date, fmt)` | `FORMAT(date, fmt)` | `TO_CHAR(date, fmt)` | `STRFTIME(fmt, date)` |
| **日期解析**              | `CAST(string AS DATE)` | `STR_TO_DATE(str, fmt)` | `TO_DATE(str, fmt)`  | `CAST(string AS DATE)` | `TO_DATE(str, fmt)`  | 无直接函数          |
| **日期加减**              | `date + INTERVAL expr` | `DATE_ADD(date, INTERVAL expr)` | `date + INTERVAL expr` | `DATEADD(unit, num, date)` | `date + NUMTODSINTERVAL(num, 'DAY')` | `DATE(date, '±num day')` |
| **日期差计算**            | `EXTRACT(unit FROM (date2 - date1))` | `DATEDIFF(date2, date1)` | `date2 - date1` | `DATEDIFF(unit, date1, date2)` | `(date2 - date1)` | `JULIANDAY(date2) - JULIANDAY(date1)` |
| **提取日期部分**          | `EXTRACT(unit FROM date)` | `EXTRACT(unit FROM date)` | `EXTRACT(unit FROM date)` | `DATEPART(unit, date)` | `EXTRACT(unit FROM date)` | `STRFTIME('%unit', date)` |
| **构建日期**              | `DATE_FROM_PARTS(year, month, day)` | `MAKEDATE(year, day_of_year)` | `MAKE_DATE(year, month, day)` | `DATEFROMPARTS(year, month, day)` | `TO_DATE(year\|\|month\|\|day, 'YYYYMMDD')` | `DATE(YYYY-MM-DD)` |
| **周相关计算**            | `EXTRACT(WEEK FROM date)` | `WEEK(date)`         | `EXTRACT(WEEK FROM date)` | `DATEPART(WEEK, date)` | `TO_CHAR(date, 'WW')` | `STRFTIME('%W', date)` |

### 聚集函数

#### `AVG()`

```sql
SELECT AVG(prod_price) AS avg_price FROM Products
WHERE vend_id = 'DLL01';
```

`AVG()`只能用来确定特定数值列的平均值，而且列名必须作为函数参 数给出。为了获得多个列的平均值，必须使用多个 AVG()函数。
`AVG()`函数忽略列值为 `NULL` 的行。

#### `COUNT()`

- 使用 `COUNT(*)`对表中行的数目进行计数，不管表列中包含的是空值还是非空值。
- 使用 `COUNT(column)`对特定列中具有值的行进行计数，忽略 `NULL` 值。

#### `MAX()`和`MIN()`

`MAX()`要求指定列名
虽然 `MAX()`一般用来找出最大的数值或日期值，但许多（并非所有） DBMS 允许将它用来返回任意列中的最大值，包括返回文本列中的最大值。在用于文本数据时，`MAX()`返回按该列排序后的最后一行。`MAX()`函数忽略列值为 NULL 的行。
`MIN()`函数也一样。在用于文本数据时，`MIN()`返回按该列排序后的第一行。

#### `SUM()`

`SUM()`函数忽略列值为 `NULL` 的行。

#### 组合

```sql
SELECT COUNT(*) AS num_items,
MIN(prod_price) AS price_min, MAX(prod_price) AS price_max, AVG(prod_price) AS price_avg FROM Products;
```

SQL 支持 5 个聚集函数，可以用多种方法使用 它们，返回所需的结果。这些函数很高效，它们返回结果一般比你在自 己的客户端应用程序中计算要快得多。

## 分组数据

### 创建分组

```sql
SELECT vend_id, 
    COUNT(*) AS num_prods 
FROM Products
GROUP BY vend_id;
```

- `GROUP BY` 子句可以包含任意数目的列，因而可以对分组进行嵌套，更细致地进行数据分组。
- 如果在 `GROUP BY` 子句中嵌套了分组，数据将在最后指定的分组上进 行汇总。换句话说，在建立分组时，指定的所有列都一起计算（所以不能从个别的列取回数据）。
- `GROUP BY` 子句中列出的每一列都必须是检索列或有效的表达式（但 不能是聚集函数）。如果在 `SELECT` 中使用表达式，则必须在 `GROUP BY` 子句中指定相同的表达式。不能使用别名。
- 大多数 SQL 实现不允许 `GROUP BY` 列带有长度可变的数据类型（如文本或备注型字段）。
- 除聚集计算语句外，`SELECT` 语句中的每一列都必须在 `GROUP BY` 子句中给出。
- 如果分组列中包含具有 `NULL` 值的行，则 `NULL` 将作为一个分组返回。如果列中有多行 NULL 值，它们将分为一组。
- `GROUP BY` 子句必须出现在 `WHERE` 子句之后，`ORDER BY` 子句之前

### 过滤分组

```sql
SELECT cust_id, 
    COUNT(*) AS orders 
FROM Orders
GROUP BY cust_id 
HAVING COUNT(*) >= 2;
```

`HAVING` 非常类似于 `WHERE`。事实上，目前为止所学过的 所有类型的 `WHERE` 子句都可以用 `HAVING` 来替代。唯一的差别是，`WHERE` 过滤行，而 `HAVING` 过滤分组。
`WHERE` 在数据分组前进行过滤，`HAVING` 在数据分组后进行过滤。这是一个重要的区别，`WHERE` 排除的行不包括在 分组中。这可能会改变计算值，从而影响 `HAVING` 子句中基于这些值过滤掉的分组。
一般在使用 `GROUP BY` 子句时，应该也给出 `ORDER BY` 子句。这是保证数据正确排序的唯一方法。千万不要仅依赖 `GROUP BY` 排序数据。

## 子查询

```sql
SELECT cust_name, cust_contact 
FROM Customers
WHERE cust_id IN (SELECT cust_id
                  FROM Orders
                  WHERE order_num IN (SELECT order_num
                                      FROM OrderItems
                                      WHERE prod_id = 'RGAN01'));
```

作为子查询的 `SELECT` 语句只能查询单个列。企图检索多个列将返回 错误。
这里给出的代码有效，并且获得了所需的结果。但是，使用子查询并 不总是执行这类数据检索的最有效方法。

```sql
SELECT cust_name,
        cust_state,
        (SELECT COUNT(*)
        FROM Orders
        WHERE Orders.cust_id = Customers.cust_id) AS orders 
FROM Customers
ORDER BY cust_name;
```

有时候，由于出现冲突列名而 导致的歧义性，会引起 DBMS 抛出错误信息。例如，`WHERE` 或 `ORDER BY` 子句指定的某个列名可能会出现在多个表中。好的做法是，如果在 `SELECT` 语句中操作多个表，就应使用完全限定列名来避免歧义

## 联结表

将数据分解为多个表能更有效地存储，更方便地处理，并且可伸缩性更好。但这些好处是有代价的。
如果数据存储在多个表中，怎样用一条 `SELECT` 语句就检索出数据呢？
答案是使用联结。简单说，联结是一种机制，用来在一条 `SELECT` 语句 中关联表，因此称为联结。使用特殊的语法，可以联结多个表返回一组 输出，联结在运行时关联表中正确的行。

### 使用WHERE子句

在一条 SELECT 语句中联结几个表时，相应的关系是在运行中构造的。在数据库表的定义中没有指示 DBMS 如何对表进行联结的内容。你必须自己做这件事情。在联结两个表时，实际要做的是将第一个表中的每一行与第二个表中的每一行配对。`WHERE` 子句作为过滤 条件，只包含那些匹配给定条件（这里是联结条件）的行。没有 `WHERE` 子句，第一个表中的每一行将与第二个表中的每一行配对，而不管它们 逻辑上是否能配在一起。
由没有联结条件的表关系返回的结果为笛卡儿积。检索出的行的数目 将是第一个表中的行数乘以第二个表中的行数。

### 内联结

目前为止使用的联结称为等值联结（equijoin），它基于两个表之间的相 等测试。这种联结也称为内联结（inner join）。

```sql
SELECT vend_name, prod_name, prod_price 
FROM Vendors
INNER JOIN Products 
ON Vendors.vend_id = Products.vend_id;
```

联结多个表

```sql
SELECT prod_name, vend_name, prod_price, quantity 
FROM OrderItems, Products, Vendors
WHERE Products.vend_id = Vendors.vend_id AND OrderItems.prod_id = Products.prod_id AND order_num = 20007;
```

## 创建高级联结

### 使用表别名

```sql
SELECT cust_name, 
      cust_contact 
FROM Customers AS C, 
      Orders AS O, 
      OrderItems AS OI 
WHERE C.cust_id = O.cust_id
      AND OI.order_num = O.order_num 
      AND prod_id = 'RGAN01';
```

需要注意，表别名只在查询执行中使用。与列别名不一样，表别名不返回到客户端。

### 自联结

假如要给与 Jim Jones 同一公司的所有顾客发送一封信件。这个查询要求 首先找出 Jim Jones 工作的公司，然后找出在该公司工作的顾客。下面是 解决此问题的一种方法：

```sql
SELECT cust_id, 
        cust_name, 
        cust_contact 
FROM Customers
WHERE cust_name = (SELECT cust_name
                    FROM Customers
                    WHERE cust_contact = 'Jim Jones');
```

```sql
SELECT c1.cust_id, 
        c1.cust_name, 
        c1.cust_contact 
FROM Customers AS c1, 
      Customers AS c2
WHERE c1.cust_name = c2.cust_name 
      AND c2.cust_contact = 'Jim Jones';
```

此查询中需要的两个表实际上是相同的表，因此 `Customers` 表在 FROM 子句中出现了两次。虽然这是完全合法的，但对 `Customers` 的引用具有 歧义性，因为 DBMS 不知道你引用的是哪个 `Customers` 表。
解决此问题，需要使用表别名。

自联结通常作为外部语句，用来替代从相同表中检索数据的使用子查询语句。虽然最终的结果是相同的，但许多 DBMS 处理联结远比处理子查询快得多。

### 自然联结

无论何时对表进行联结，应该至少有一列不止出现在一个表中（被联结的列）。标准的联结（前一课中介绍的内联结）返回所有数据，相同的列 甚至多次出现。自然联结排除多次出现，使每一列只返回一次。

```sql
SELECT C.*,
      O.order_num,
      O.order_date,
      OI.prod_id,
      OI.quantity, 
      OI.item_price 
FROM Customers AS C, 
     Orders AS O,
     OrderItems AS OI 
WHERE C.cust_id = O.cust_id 
      AND OI.order_num = O.order_num 
      AND prod_id = 'RGAN01';
```

### 外联结

许多联结将一个表中的行与另一个表中的行相关联，但有时候需要包含 没有关联行的那些行。
需要注意，用来创建外联结的语法在不同的 SQL 实现中可能稍有不同。

```sql
SELECT Customers.cust_id, Orders.order_num 
FROM Customers
LEFT OUTER JOIN Orders ON Customers.cust_id = Orders.cust_id;
```

在使用 `OUTER JOIN` 语法时，必须使用 `RIGHT` 或 `LEFT` 关键字指定包括其所有行的表 （`RIGHT` 指出的是 `OUTER JOIN` 右边的表，而 `LEFT` 指出的是 `OUTER JOIN` 左边的表）。上面的例子使用 `LEFT OUTER JOIN` 从 `FROM` 子句左边的表 （`Customers` 表）中选择所有行。

还存在另一种外联结，就是全外联结（full outer join），它检索两个表中 的所有行并关联那些可以关联的行。

```sql
SELECT Customers.cust_id, Orders.order_num 
FROM Customers
FULL OUTER JOIN Orders ON Customers.cust_id = Orders.cust_id;
```

MariaDB、MySQL 和 SQLite 不支持 `FULL OUTER JOIN` 语法
替代方案：使用 `UNION ALL` 组合 `LEFT JOIN` 和 `RIGHT JOIN`

### 带聚集函数的联结

### 总结

- 注意所使用的联结类型。一般我们使用内联结，但使用外联结也有效。 
- 关于确切的联结语法，应该查看具体的文档，看相应的 DBMS 支持何种语法（大多数 DBMS 使用这两课中描述的某种语法）。
- 保证使用正确的联结条件（不管采用哪种语法），否则会返回不正确的数据。
- 应该总是提供联结条件，否则会得出笛卡儿积。 
- 在一个联结中可以包含多个表，甚至可以对每个联结采用不同的联结 类型。虽然这样做是合法的，一般也很有用，但应该在一起测试它们前分别测试每个联结。这会使故障排除更为简单。


















## 一些需要注意的地方

### 精度

黄金法则：​涉及金钱计算必用 DECIMAL，地理坐标可用 DOUBLE，其他场景优先测试误差容忍度。

### 字符串

使用''
