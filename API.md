# Plague Simulator
后端作者：乙烯

## 使用说明
总共4个主要的后端类：
- 地区类 `CCountry`
- 疾病类 `CDisease`
- 政策类 `CPolicy`
- 世界类 `CWorld`

要使用上述代码,需要保证 `CCountry.hpp` 等4个文件都在的前提下，
引入 `PlagueSimulatorLib.h` 头文件。以下是一个事例：
``` C++
#pragma once
#include "PlagueSimulatorLib.h"
#include <iostream>
#include <cstdio>

int main()
{
	CWorld world = CWorld::GetWorld();
	std::cout << world.infectedRatio;
	return 0;
}
```
在上述实例中，我们实现了调取一个“世界”型实例，并且输出世界当前感染比例。
当然，如果没有经过额外的设定和演化，输出应该显然是0。
以下将会分块阐释上述的五个类的使用方式。

### `class CWorld`
这个类表示的是世界相关的变量和方法。

这个类，注意，是单例的。而且对应的实例在程序开始执行的那一瞬间就实例化了。
因此，我们必须通过下列语句调用这个世界实例：`CWorld world = CWorld::GetWorld();`。


该实例是静态的。我们有 `CWorld::Initialize()` 这个方法，使得世界实例被回归到最初的状态。
注意，这不是一个静态的函数。它通过一个简单的 `PlainText`文档输入需要的信息，并初始化整个世界。

可直接使用的变量和方法见下：

| 名称 | 说明 | 
| ---- | ---- |
| `static CWorld& GetWorld()` | 获取当前世界的实例 |
| `std::string name` | 世界的名称，~~例如：提瓦特大陆~~ |
| `static std::vector<CCountry> countries` | 世界上的所有地区|
| `static std::vector<CWorld> turns`|前些天所有的世界 *（人话：存档）* |
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

### `class CDisease`
这个类表示的是疾病相关的实例和方法。
为简便起见，该类是单例的，也就是说，世界上只有一个主要疾病。
我们必须通过下列语句调用该疾病实例：`CDisease disease = CDisease::GetDisease();`

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