# Plague Simulator ����ο�����
������ߣ���ϩ

## ʹ��˵��
���ȱ���˵����һ���ǣ�������������������ռ�`Ethene`�ڡ�
�����Ƚ���`typedef`������ȫ��ʹ��˫ð�š�

### ����

�ܹ�4����Ҫ�ĺ���ࣺ
- ������ `CCountry`
- ������ `CDisease`
- ������ `CPolicy`
- ������ `CWorld`

Ҫʹ����������,��Ҫ��֤ `CCountry.hpp` ��4���ļ����ڵ�ǰ���£�
���� `PlagueSimulatorLib.h` ͷ�ļ���������һ����Ϊ�򵥵�ʵ����
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
�����������У�����ʵ���˵�ȡһ�������硱��ʵ����������������˿ڵ�������

���½���ֿ�������������ʹ�÷�ʽ��

#### `class CWorld`
������ʾ����������صı����ͷ�����

����࣬ע�⣬��**����**�ġ����Ҷ�Ӧ��ʵ���ڳ���ʼִ�е���һ˲���ʵ�����ˡ�
��ˣ�����**����**ͨ�������������������ʵ����`CWorld world = CWorld::GetWorld();`��


��ʵ���Ǿ�̬�ġ������� `CWorld::Initialize()` ���������ʹ������ʵ�����ع鵽�����״̬��
ע�⣬�ⲻ��һ����̬�ĺ�������ͨ��һ���򵥵� `PlainText`�ĵ�������Ҫ����Ϣ������ʼ���������硣

��ֱ��ʹ�õı����ͷ������£�

| ���� | ˵�� | 
| ---- | ---- |
| `static CWorld& GetWorld()` | ��ȡ��ǰ�����ʵ�� |
| `std::string name` | ��������ƣ�~~���磺�����ش�½~~ |
| `static std::vector<CCountry> countries` | �����ϵ����е���|
| `static std::vector<CWorld> turns`|ǰЩ�����е����� *���˻����浵��* |
| `static std::map<CPolicy> policiesAll`|�������п��ܳ��ֵ�����|
| `double worldAttention = 0`| ��ǰ�������ע|
| `double worldTotalResearch = 0`|���統ǰ�Ľ�ҩ�з�����|
| `double worldKindness = 0.3`|����ġ�����ϵ���������ھ�������������İ�������|
| `long originalPopulation`|��������˿�|
| `long infectedPopulation`|����ĸ�Ⱦ�˿�|
| `long healthyPopulation`|����Ľ����˿�|
| `long deadPopulation`|����������˿�|
| `double infectedRatio`|����ĵ�ǰ��Ⱦ����|
| `double deadRatio`|����ĵ�ǰ��������|
| `void Initialize()`| ��ʼ���������磬������������ݣ�Ȼ��Ӷ�ȡ���ҿ�ʼ����������ִ��һ��|
| `void Update(const CDisease& disease)` | �������磬���仰˵��ǰ��һ�� |

#### `class CDisease`
������ʾ���Ǽ�����ص�ʵ���ͷ�����
Ϊ��������������**����**�ģ�Ҳ����˵��������ֻ��һ����Ҫ������
���Ҷ�Ӧ��ʵ���ڳ���ʼִ�е���һ˲���ʵ�����ˡ�
����**����**ͨ�����������øü���ʵ����`CDisease disease = CDisease::GetDisease();`

����ֱ��ʹ�õı����ͷ������£�

| ���� | ˵�� |
| ---- | ---- |
|`std::string name`|����������|
|`double infectivity`|���д�Ⱦ��|
|`double severity`|����������|
|`double lethality`|����������|
|`double wealthyResistance`|��ԣ����|
|`double povertyResistance`|ƶ������|
|`double urbanResistance`|���п���|
|`double ruralResistance`|��忹��|
|`double hotResistance`|���ȿ���|
|`double coldResistance`|���俹��|
|`double humidResistance`|��ʪ����|
|`double aridResistance`|�ɺ�����|
|`double corpseTransmission`|ʬ�崫��|
|`double cureRequirement`|��������|
|`double landTransmission`|�羳����|
|`static CDisease& GetDisease()`|��ȡ��ǰ������ʵ��|
|`void Initialize()`|��ʼ����������ĳ�� `PlainText` �����|

#### `class CPolicy`
������ʾ���ǵ������õ�������ߡ�

����ֱ�ӷ��ʵı����ͷ������£�

|����|˵��|
|----|----|
|`std::string name;`|���ߵ�����|
|`double changeToLocalInfectivity;`|�Դ�Ⱦ������Ч��|
|`double changeToLocalSeverity;`|�����ز�����Ч��|
|`double changeToLocalLethality;`|������������Ч��|
|`double changeToLocalCorpseTransmission;`|��ʬ�崫��������Ч��|
|`double changeToLocalOrder;`|�Ե������������Ч��|
|`double changeToMedicalInput;`|�Ե�����ҩ����Ӱ��|
|`bool changeToBorder;`|�Ե����߾���Ч��|
|`double cond_localInfectedRatio;`|������ʱ�ı��ظ�Ⱦ������Сֵ|
|`double cond_localDeadRatio;`|������ʱ�ı�������������Сֵ|
|`double cond_localAttention;`|������ʱ�ı��ع�ע��Сֵ|
|`double cond_worldInfectedRatio;`|������ʱ�������Ⱦ������Сֵ|
|`double cond_worldDeadRatio;`|������ʱ����������������Сֵ|
|`double cond_worldAttention;`|������ʱ�������ע��Сֵ|
|`void Execute(CCountry& country) const`|ִ���������|
|`bool CanExecute(CWorld& world, CCountry& country) const`|��������Ƿ����ִ��|

#### `class CCountry`
������ʾ���ǵ�����

����ֱ�ӷ��ʵı����ͷ������£�

|����|˵��|
|----|----|
|`std::string name;`|����������|
|`long originalPopulation;`|���������˿�|
|`long healthyPopulation;`|�����Ľ����˿�����|
|`long infectedPopulation;`|�����ĸ�Ⱦ�˿�����|
|`long deadPopulation;`|������������|
|`double infectedRatio;`|��Ⱦ����|
|`double deadRatio;`|��������|
|`double realAreaAttention;`|������ʵ��ע|
|`double areaOrder`|��������|
|`double researchInvestment`|������ҩ�з�Ͷ��|
|`double researchInvestmentTotal`|������ҩ�з�Ͷ�����ֵ|
|`double areaImportance;`|����Ȩ��|
|`bool isWealthy;`|�ǲ��Ǹ�ԣ����|
|`bool isPoverty;`|�ǲ���ƶ������|
|`bool isUrban;`|�ǲ��ǳ��й���|
|`bool isRural;`|�ǲ���������|
|`bool isHot;`|�ǲ������ȹ���|
|`bool isCold;`|�ǲ��Ǻ������|
|`bool isHumid;`|�ǲ��ǳ�ʪ����|
|`bool isArid;`|�ǲ��Ǹ������|
|`bool isBorderOpen;`|�߾��Ƿ񿪷�|
|`double changeToLocalInfectivity = 0;`|���ߵ��µĵ�����Ⱦ�Ա䶯|
|`double changeToLocalSeverity = 0;`|���ߵ��µĵ��������Ա䶯|
|`double changeToLocalLethality = 0;`|���ߵ��µĵ��������ʱ䶯|
|`double changeToLocalCorpseTransmission = 0;`|���ߵ��µĵ���ʬ���䶯|
|`double changeToLocalOrder = 0;`|���ߵ��µĵ�������䶯|
|`std::set<std::string> policyExecuted;`|�ڸõ������������������Ƽ���|
|`void Update(CWorld& world, const CDisease& disease)`|���¹������ݣ�**ֻ����`CWorld::Update`**�����ظ�����|

### ��ʼ������
������ͷ�����ݳ�ʼ�����������ⲿ�⡣����Ҫ��ʹ�øó���ͷ�Ŀ�ִ���ļ�ͬĿ¼�£��½�һ��`source`�ļ��С�

�ڸ��ļ����£�����Ҫ�������� `UTF-8` ����Ĵ��ı��ļ� `countryInfo.txt` `diseaseInfo.txt` `policyInfo.txt` ��

�� `countryInfo.txt` �У���Ӧ�ý�ͬһ�������������ϸ�ذ���������������� `ci[12]` ������˳���ð�Ƕ��ŷָд��ͬһ���ڣ���д��һ��������ʱ������Ҫ���С������������⣬����ÿһ���ֶζ�����ʹ�ô����֣��� `114` ������ `5.14` �������ͱ�������0��1���ɡ�

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

�� `diseaseInfo.txt` �У���Ӧ�ý������������ϸ�ذ����������� `di[15]` ��˳���ð�Ƕ��ŷָд��ͬһ���ڡ������������⣬����ÿһ���ֶζ�����ʹ�ô����֣��� `114` ������ `5.14` ��

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

�� `policyInfo.txt` �У���Ӧ�ý�ͬһ�������������ϸ�ذ���������������� `pi[14]` ������˳���ð�Ƕ��ŷָд��ͬһ���ڣ���д��һ�����ߵ�ʱ������Ҫ���С������������⣬����ÿһ���ֶζ�����ʹ�ô����֣��� `114` ������ `5.14` ��

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

ע�⣬��Ҫд�κα�ͷ���κζ�����ַ����п��ܵ��¶����ʧ�ܡ�