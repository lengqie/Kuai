<div align=center>
<img src="https://raw.githubusercontent.com/lengqie/Kuai/master/static/kuai.png"/>
</div>
<div align=center>
<img src="https://img.shields.io/badge/rustc-1.54.0-black"/>
</div>



## 1. 基本介绍

### 1.1 简介

一个rust实现的Windows命令行工具

主要内容在于参数与CMD命令的映射

原C语言版本  https://github.com/lengqie/Kuai/tree/master/static/c (Deprecated)

![](https://raw.githubusercontent.com/lengqie/Hou.GS/master/static/dome.gif)

### 1.2 功能

- [x]  参数映射
- [x]  ini文件 命令映射
- [x]  应用映射
- [ ]  命令反馈输出 (中文乱码)
- [ ]  多参数命令

## 2. 使用说明

### 2.1 运行

使用 ` releases `提供下载 https://github.com/lengqie/Kuai/releases

```
# 操作
1. 将下载的文件解压在D盘中
2. 确保文件目录正确 D:\Kuai\k.exe
3. 将D:\Kuai 添加到环境变量
4. 自定义添加常用的软件快捷方式到 D:\Kuai\lnk 目录
   自定义添加常用命令 D:\Kuai\kuai.ini 文件
```

修改运行文件地址请自行编译（c语言版本同 可以编译，功能大体相同）

### 2.2 编译

```bash
# 克隆项目
git clone https://github.com/lengqie/Kuai.git
```

````
# 操作
修改 src/files.rs 第10、11 行 等
````

```bash
# 编译
cargo build
```

```
# 操作
改名、移动目录、添加环境变量....
```

## 3. 协议

Licensed under the *MIT* license