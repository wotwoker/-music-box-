# 功能简介

## 手动演奏

    矩阵键盘按不同的键播放不同的音高。

### 手动演奏实现方式

    通过函数Buzzer_Freq(unsigned int Key)，使Buzzer反转，Key值影响Buzzer反转时长从而实现对频率的选择。
    函数内设定了反转90次，故不同频率的音，发音时间不同，目前没想到优化方案。

## 自动播放

    矩阵键盘按不同的键播放不同的音乐（目前只有设置Key1、Key2）
    播放后暂停，即可选择其他曲目。
    开始播放时不可暂停、切歌、模式切换等，要中断播放只能按复位键。

### 自动播放实现方式

    使用定时器中断系统，中断后使Buzzer反转，每个音对应不同的定时器初值。
    不同的曲目对应不同的 Music[]（目前只有Music1、Music2)。


## 成果图
![1](https://github.com/wotwoker/-music-box-/blob/main/firmware/%E6%9D%90%E6%96%99%E6%96%87%E6%A1%A3/%E9%A1%B9%E7%9B%AE%E5%9B%BE%E7%89%871.jpg?raw=true)
    
![2](https://github.com/wotwoker/-music-box-/blob/main/firmware/%E6%9D%90%E6%96%99%E6%96%87%E6%A1%A3/%E9%A1%B9%E7%9B%AE%E5%9B%BE%E7%89%872.jpg?raw=true)

![2](https://github.com/wotwoker/-music-box-/blob/main/firmware/%E6%9D%90%E6%96%99%E6%96%87%E6%A1%A3/%E9%A1%B9%E7%9B%AE%E5%9B%BE%E7%89%873.jpg?raw=true)

