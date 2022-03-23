# science-computer
科学计算器，学习逆波兰式的时候自己做的
##第一版

###功能：
1. 实现整数运算，包括plus ，minus ，multiple ，divide ，power
2. 对各种错误情况的报错
3. 另设分数计算器，实现严格的代数计算

###第二版预期：
1. 实现浮点运算：
  全部改成 long long double类型
  读入的时候加一个浮点计数器，如果counter==0，那么就补一个.0实现整数转化为浮点数便于后续处理，counter==1正常过，counter==2就报错
  取出的时候就很简单了，能过关的都是有一个浮点且以&结尾的东西，所以把这些都加到一个string中，然后使用atof函数直接转换
  把计算用的栈调整为double型的即可
2. 错误情况试图修复
  错误有两种
  一种是原来的意图就是不合理的，这种修正了也无法计算，所以还是采用直接报错的方法
  另一种就是，意图是合理的，也是符合平常书写规范的，被我们刚开始因简化需要而判为错误的
  我们要改的就是第二种。
    （1） 数和括号，括号和括号连在一起，这种在中间补*即可
    （2） 对0求模，这个见仁见智，追求包容性的话，可以直接用被除数当结果，符合逻辑
    （3） 负指数，这个用double直接pow函数即可
3. 模仿常见计算机逻辑
  （1） 不断计算，使用死循环
  （2） 每次计算后用ans储存之前的结果，直接显示出来，实现连续计算
  （3） 实时判断，不终止程序，但是会提示
  
### 第三版预期：//到这一步其实已经没什么用了，计算机而已，不值得
1. 实现图形界面
2. 做成不同语言的，试图跨平台。
