# LosImages

## 项目目录

- 项目目录
```shell
\\wsl.localhost\Ubuntu-24.04\home\losangelous\LosAngelous\Pro\LosImages\
```

## 项目结构

- src/core 放置核心类 （一个类一个文件夹）（LosRouter/LosRouter.h LosRouter/LosRouter.cc）
- src/view 放置 ui文件以及其对应的cpp和.h文件（一个类一个文件夹）
- src/common 放置常量（整型 字符串 以及src/common/util/ 下放置工具类）
  - src/common/str/(类名+_+str) 如 (LosRouter_str.h) 放置string char char*等
  - src/common/num/(类名+_+str) 如 (LosRouter_num.h) 放置常量
  - src/common/enum/(类名+_+enum) 如 (LosRouter_enum.h) 放置enum 或者 struct
- src/test 放置测试文件

## 命名空间要求

src/core -> LosCore
src/view -> LosView
src/common -> LosCommon
src/test -> LosTest

## 书写要求

- 信号统一放置在 LosCore/LosRouter.h 这个文件下 通过单例模式 `emit LosRouter().instance()._ls_signal()` 来发射信号
  - 这个信号的命名 得 `_ls_` 开头
- 类的公有成员函数用 myFunc 这样的形式 就是第一个小写后面每个单词大写
- 类的成员变量 要 `L_` 开头 , 如果这个变量是自己定义的类，就用 `LOS_` 来开头
- 函数参数都用蛇形 myFunc(int int_val,string string_val);
- static的成员函数或者inline函数首字母也大写 MyFunc
- 常量都大写 如 DEFAULT_HEIGHT
- 枚举的类型也都大写 EMUM_ONE
- 结构体里面的变量和类里面的成员变量格式保持一致
- 注释统一我来写
- 所有关于QSS或者CSS部分写在src/view/style目录下 命名方式就是 对应服务的ui 比如 MainWindow.ui的QSS 该QSS文件就命名为 MainWindow_style.h
  - 里面的内容就是通过 inline string getStyle()的方式获取 命名空间是 `namespace LosView{namespace MainWindow_style{}}` 这样
- 所有的类 都要 Los打头

## ui风格

- 黑白大气端庄极客半黑暗猩红元素 每个控件之间要有呼吸感

## 任务
