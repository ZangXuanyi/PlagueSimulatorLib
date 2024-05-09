# PlagueSimulatorLib

后端作者：唯一乙烯（TheOnlyEthene）

## 说明
这是一些头文件，用于PKU24届程设QT大作业PAX-12小组的作品 `PlagueSimulator`，或者 `瘟疫传播和防治模拟器` 的数学建模和后端逻辑实现。

**严正声明：本 `PlagueSimulator` 和 `PlagueSimulatorLib` 中涉及到的一切内容均和现实世界无关，无任何衍生含义内容，不代表任何其他团体个人，无任何隐喻，暗示，反串，碰瓷，蹭热度等想法。该项目使用架空的世界地图、地区设定和疾病设定，如有雷同，纯属巧合；此头文件仅用于模拟，数学模型并不精确，且将会完全开源；此项目不可以也不将用于任何盈利行为，不可以也不将用于任何对任何国家、组织和/或个人的影射。如果有组织或个人违反上述条件，使用上述模型进行不适当的行为，PAX-12小组和唯一乙烯概不负责；如有组织或者个人使用该项目进行盈利，PAX-12小组和/或唯一乙烯保留追究其法律责任的权利。**

**Strict Statement: All contents related to `PlagueSimulator` and `PlagueSimulatorLib` are entirely unrelated to the real world, contain no derivative implications, no innuendoes about any other groups or individuals, and no metaphorical, suggestive, parody, or opportunistic intentions. The project employs a fictional world map, fictional regional settings, and fictional disease settings; any resemblance to actual entities is purely coincidental. This header file is solely for simulation purposes, the mathematical models are not precise and will be fully open-sourced. The project is not, nor will it be used for any profit-making activities, nor will it be used to imply or insinuate any country, organization, or individual. Should any organization or individual violate the above conditions and use the aforementioned models for inappropriate behavior, the PAX-12 group and TheOnlyEthene shall not be held responsible. If any organization or individual uses the project for profit-making purposes, the PAX-12 group and/or TheOnlyEthene reserve the right to pursue legal responsibility.**

~~（然而截至2024/05/07，我们实际上并未想好用什么地图比较合适，可能到时候真就原神启动了）~~

______________

具体的使用方式及数据导入等内容，需要看该项目中的 `API.md` 。此处不再介绍。

## 鸣谢
感谢下列人员和组织对 `PlagueSimulatorLib` 数学建模的帮助：
- CaptGyrfalcon
- 白猿·李
- 稀神 サグメ 
- 小黑
- 心似双丝网，中有千千结
- starcry.
- 圣堂科工
- 零黛玉
- 真昼
- C6H5_OH

## 更新日志

### V1.0.0
创建项目文件。

### V2.0.0
修复了愚蠢的 `C2027` 和 `LNK2001` 两大抽象问题，现在后端算是没啥编译和运行上的bug了，至多可能有语义bug。

### V2.0.1
修复了愚蠢的核爆和溢出bug，现在感染人口和死亡人口不会再突变数十万倍或者溢出成为负数了。