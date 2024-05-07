# Plague Simulator
������ߣ���ϩ

## ʹ��˵��
�ܹ�4����Ҫ�ĺ���ࣺ
- ������ `CCountry`
- ������ `CDisease`
- ������ `CPolicy`
- ������ `CWorld`

Ҫʹ����������,��Ҫ��֤ `CCountry.hpp` ��4���ļ����ڵ�ǰ���£�
���� `PlagueSimulatorLib.h` ͷ�ļ���������һ��������
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
������ʵ���У�����ʵ���˵�ȡһ�������硱��ʵ��������������統ǰ��Ⱦ������
��Ȼ�����û�о���������趨���ݻ������Ӧ����Ȼ��0��
���½���ֿ����������������ʹ�÷�ʽ��

### `class CWorld`
������ʾ����������صı����ͷ�����

����࣬ע�⣬�ǵ����ġ����Ҷ�Ӧ��ʵ���ڳ���ʼִ�е���һ˲���ʵ�����ˡ�
��ˣ����Ǳ���ͨ�������������������ʵ����`CWorld world = CWorld::GetWorld();`��


��ʵ���Ǿ�̬�ġ������� `CWorld::Initialize()` ���������ʹ������ʵ�����ع鵽�����״̬��
ע�⣬�ⲻ��һ����̬�ĺ�������ͨ��һ���򵥵� `PlainText`�ĵ�������Ҫ����Ϣ������ʼ���������硣

��ֱ��ʹ�õı����ͷ������£�

| ���� | ˵�� | 
| ---- | ---- |
| `static CWorld& GetWorld()` | ��ȡ��ǰ�����ʵ�� |
| `std::string name` | ��������ƣ�~~���磺�����ش�½~~ |
| `static std::vector<CCountry> countries` | �����ϵ����е���|
| `static std::vector<CWorld> turns`|ǰЩ�����е����� *���˻����浵��* |
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

### `class CDisease`
������ʾ���Ǽ�����ص�ʵ���ͷ�����
Ϊ�������������ǵ����ģ�Ҳ����˵��������ֻ��һ����Ҫ������
���Ǳ���ͨ�����������øü���ʵ����`CDisease disease = CDisease::GetDisease();`

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