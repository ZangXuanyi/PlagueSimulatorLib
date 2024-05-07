# Plague Simulator 代码参考资料
后端作者：乙烯

## 使用说明
首先必须说明的一点是：下列所有类均在命名空间`Ethene`内。
请事先进行`typedef`，或者全程使用双冒号。

### 总览

总共4个主要的后端类：
- 地区类 `CCountry`
- 疾病类 `CDisease`
- 政策类 `CPolicy`
- 世界类 `CWorld`

要使用上述代码,需要保证 `CCountry.hpp` 等4个文件都在的前提下，
引入 `PlagueSimulatorLib.h` 头文件。以下是一个极为简单的实例：
``` C++
#pragma once
#include "PlagueSimulatorLib.h"
#include <iostream>
#include <cstdio>

int main()
{
	Ethene::CWorld world = Ethene::CWorld::GetWorld();
	world.Initialize();
	std::cout << world.originalPopulation;
	return 0;
}
```
在上述代码中，我们实现了调取一个“世界”型实例，并且输出世界人口的总数。

以下将会分块阐释上述的类的使用方式。

#### `class CWorld`
这个类表示的是世界相关的变量和方法。

这个类，注意，是**单例**的。而且对应的实例在程序开始执行的那一瞬间就实例化了。
因此，我们**必须**通过下列语句调用这个世界实例：`CWorld world = CWorld::GetWorld();`。


该实例是静态的。我们有 `CWorld::Initialize()` 这个方法，使得世界实例被回归到最初的状态。
注意，这不是一个静态的函数。它通过一个简单的 `PlainText`文档输入需要的信息，并初始化整个世界。

可直接使用的变量和方法见下：

| 名称 | 说明 | 
| ---- | ---- |
| `static CWorld& GetWorld()` | 获取当前世界的实例 |
| `std::string name` | 世界的名称，~~例如：提瓦特大陆~~ |
| `static std::vector<CCountry> countries` | 世界上的所有地区|
| `static std::vector<CWorld> turns`|前些天所有的世界 *（人话：存档）* |
| `static std::map<CPolicy> policiesAll`|世界所有可能出现的政策|
| `double worldAttention = 0`| 当前的世界关注|
| `double worldTotalResearch = 0`|世界当前的解药研发总量|
| `double worldKindness = 0.3`|世界的“互助系数”，用于决定各国对世界的帮助欲望|
| `long originalPopulation`|世界的总人口|
| `long infectedPopulation`|世界的感染人口|
| `long healthyPopulation`|世界的健康人口|
| `long deadPopulation`|世界的死亡人口|
| `double infectedRatio`|世界的当前感染比例|
| `double deadRatio`|世界的当前死亡比例|
| `void Initialize()`| 初始化整个世界，会清空所有数据，然后从读取国家开始，重新整个执行一遍|
| `void Update(const CDisease& disease)` | 更新世界，换句话说，前进一天 |

#### `class CDisease`
这个类表示的是疾病相关的实例和方法。
为简便起见，该类是**单例**的，也就是说，世界上只有一个主要疾病。
而且对应的实例在程序开始执行的那一瞬间就实例化了。
我们**必须**通过下列语句调用该疾病实例：`CDisease disease = CDisease::GetDisease();`

可以直接使用的变量和方法如下：

| 名称 | 说明 |
| ---- | ---- |
|`std::string name`|疾病的名称|
|`double infectivity`|固有传染性|
|`double severity`|固有严重性|
|`double lethality`|固有致命性|
|`double wealthyResistance`|富裕抗性|
|`double povertyResistance`|贫困抗性|
|`double urbanResistance`|城市抗性|
|`double ruralResistance`|乡村抗性|
|`double hotResistance`|炎热抗性|
|`double coldResistance`|寒冷抗性|
|`double humidResistance`|潮湿抗性|
|`double aridResistance`|干旱抗性|
|`double corpseTransmission`|尸体传播|
|`double cureRequirement`|治愈需求|
|`double landTransmission`|跨境能力|
|`static CDisease& GetDisease()`|获取当前疾病的实例|
|`void Initialize()`|初始化疾病，从某个 `PlainText` 读入的|

#### `class CPolicy`
这个类表示的是地区采用的相关政策。

可以直接访问的变量和方法如下：

|名称|说明|
|----|----|
|`std::string name;`|政策的名称|
|`double changeToLocalInfectivity;`|对传染产生的效果|
|`double changeToLocalSeverity;`|对严重产生的效果|
|`double changeToLocalLethality;`|对致死产生的效果|
|`double changeToLocalCorpseTransmission;`|对尸体传播产生的效果|
|`double changeToLocalOrder;`|对地区秩序产生的效果|
|`double changeToMedicalInput;`|对地区开药量的影响|
|`bool changeToBorder;`|对地区边境的效果|
|`double cond_localInfectedRatio;`|开政策时的本地感染比例最小值|
|`double cond_localDeadRatio;`|开政策时的本地死亡比例最小值|
|`double cond_localAttention;`|开政策时的本地关注最小值|
|`double cond_worldInfectedRatio;`|开政策时的世界感染比例最小值|
|`double cond_worldDeadRatio;`|开政策时的世界死亡比例最小值|
|`double cond_worldAttention;`|开政策时的世界关注最小值|
|`void Execute(CCountry& country) const`|执行这个政策|
|`bool CanExecute(CWorld& world, CCountry& country) const`|这个政策是否可以执行|

#### `class CCountry`
这个类表示的是地区。

可以直接访问的变量和方法如下：

|名称|说明|
|----|----|
|`std::string name;`|地区的名称|
|`long originalPopulation;`|地区的总人口|
|`long healthyPopulation;`|地区的健康人口数量|
|`long infectedPopulation;`|地区的感染人口数量|
|`long deadPopulation;`|地区死者数量|
|`double infectedRatio;`|感染比例|
|`double deadRatio;`|死亡比例|
|`double realAreaAttention;`|地区真实关注|
|`double areaOrder`|地区秩序|
|`double researchInvestment`|地区解药研发投入|
|`double researchInvestmentTotal`|地区解药研发投入基础值|
|`double areaImportance;`|地区权重|
|`bool isWealthy;`|是不是富裕国家|
|`bool isPoverty;`|是不是贫困国家|
|`bool isUrban;`|是不是城市国家|
|`bool isRural;`|是不是乡村国家|
|`bool isHot;`|是不是炎热国家|
|`bool isCold;`|是不是寒冷国家|
|`bool isHumid;`|是不是潮湿地区|
|`bool isArid;`|是不是干燥地区|
|`bool isBorderOpen;`|边境是否开放|
|`double changeToLocalInfectivity = 0;`|政策导致的地区传染性变动|
|`double changeToLocalSeverity = 0;`|政策导致的地区严重性变动|
|`double changeToLocalLethality = 0;`|政策导致的地区死亡率变动|
|`double changeToLocalCorpseTransmission = 0;`|政策导致的地区尸传变动|
|`double changeToLocalOrder = 0;`|政策导致的地区秩序变动|
|`std::set<std::string> policyExecuted;`|在该地区触发过的政策名称集合|
|`void Update(CWorld& world, const CDisease& disease)`|更新国家数据，**只用于`CWorld::Update`**请勿重复调用|

### 初始化数据
本程序头的数据初始化不依赖于外部库。你需要在使用该程序头的可执行文件同目录下，新建一个`source`文件夹。

在该文件夹下，你需要创建三个 `UTF-8` 编码的纯文本文件 `countryInfo.txt` `diseaseInfo.txt` `policyInfo.txt` 。

在 `countryInfo.txt` 中，你应该将同一个地区的内容严格地按照下面代码中数组 `ci[12]` 给出的顺序，用半角逗号分割，写在同一行内；当写下一个地区的时候，你需要换行。除了名称以外，你在每一个字段都必须使用纯数字，如 `114` ，或者 `5.14` 。布尔型变量则用0或1即可。

``` C++
c.name = ci[0];
c.originalPopulation = std::stol(ci[1]);
c.researchInvestmentTotal = std::stod(ci[2]);
c.areaImportance = std::stod(ci[3]);
c.isArid = static_cast<bool>(std::stoi(ci[4]));
c.isCold = static_cast<bool>(std::stoi(ci[5]));
c.isHot = static_cast<bool>(std::stoi(ci[6]));
c.isHumid = static_cast<bool>(std::stoi(ci[7]));
c.isPoverty = static_cast<bool>(std::stoi(ci[8]));
c.isRural = static_cast<bool>(std::stoi(ci[9]));
c.isUrban = static_cast<bool>(std::stoi(ci[10]));
c.isWealthy = static_cast<bool>(std::stoi(ci[11]));
```

在 `diseaseInfo.txt` 中，你应该将疾病的属性严格地按照下面数组 `di[15]` 的顺序，用半角逗号分割，写在同一行内。除了名称以外，你在每一个字段都必须使用纯数字，如 `114` ，或者 `5.14` 。

```C++
name = di[0];
infectivity = std::stod(di[1]);
severity = std::stod(di[2]);
lethality = std::stod(di[3]);
wealthyResistance = std::stod(di[4]);
povertyResistance = std::stod(di[5]);
urbanResistance = std::stod(di[6]);
ruralResistance = std::stod(di[7]);
hotResistance = std::stod(di[8]);
coldResistance = std::stod(di[9]);
humidResistance = std::stod(di[10]);
aridResistance = std::stod(di[11]);
corpseTransmission = std::stod(di[12]);
cureRequirement = 1e6 * std::stod(di[13]);
landTransmission = std::stod(di[14]);
```

在 `policyInfo.txt` 中，你应该将同一个地区的内容严格地按照下面代码中数组 `pi[14]` 给出的顺序，用半角逗号分割，写在同一行内；当写下一个政策的时候，你需要换行。除了名称以外，你在每一个字段都必须使用纯数字，如 `114` ，或者 `5.14` 。

```C++
p.name = pi[0];
p.cond_localInfectedRatio = std::stod(pi[1]);
p.cond_localDeadRatio = std::stod(pi[2]);
p.cond_localAttention = std::stod(pi[3]);
p.cond_worldInfectedRatio = std::stod(pi[4]);
p.cond_worldDeadRatio = std::stod(pi[5]);
p.cond_worldAttention = std::stod(pi[6]);
p.changeToLocalInfectivity = std::stod(pi[7]);
p.changeToLocalSeverity = std::stod(pi[8]);
p.changeToLocalLethality = std::stod(pi[9]);
p.changeToLocalCorpseTransmission = std::stod(pi[10]);
p.changeToLocalOrder = std::stod(pi[11]);
p.changeToMedicalInput = std::stod(pi[12]);
p.changeToBorder = std::stod(pi[13]);
```

注意，不要写任何表头。任何多余的字符均有可能导致读入的失败。